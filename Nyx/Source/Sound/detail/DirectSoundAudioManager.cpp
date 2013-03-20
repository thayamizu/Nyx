/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "IO/PackedFile.h"
#include "DirectSoundAudioBuffer.h"
#include "DirectSound3DAudioBuffer.h"
#include "DirectSoundAudioManager.h"
#include "DirectSoundStreamingAudioBuffer.h"

namespace Nyx {
	using Nyx::PackedFile;

	//--------------------------------------------------------------------------------------
	//
	DirectSoundAudioManager::DirectSoundAudioManager(HWND hwnd, int volume) 
		:hWnd(hwnd)
	{


		HRESULT hr = DirectSoundCreate8(NULL,&dsound,NULL);
		Assert(hr == DS_OK);
		if (FAILED(hr)) {
			DebugOutput::DebugMessage("DirectSoundの初期化に失敗しました");
		}
		dsound->AddRef();
		// 協調レベルの設定
		dsound->SetCooperativeLevel(hwnd,DSSCL_EXCLUSIVE);

		SetMasterVolume(volume);

	}
	
	//--------------------------------------------------------------------------------------
	//
	DirectSoundAudioManager::~DirectSoundAudioManager() {
		SafeRelease(dsound);
	}
	
	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::Play(size_t index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Play();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::PlayAll() {

		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Play();
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::Stop(size_t index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Stop();


	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::StopAll() {
		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Stop();
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::Resume(size_t index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Resume();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::ResumeAll() {
		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Resume();
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::Reset(size_t index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Reset();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::ResetAll() {
		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Reset();
			++it;
		}
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::SetPause(size_t index, bool p) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->SetPause(p);
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::SetPauseAll(bool p) {

		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->SetPause(p);
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	int DirectSoundAudioManager::GetMasterVolume() const {
		return masterVolume;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::SetMasterVolume(int v) {
		if (v > 100) { v = 100;}
		else if (v < 0) {v=0;}
		masterVolume = v;

		auto it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->SetVolume(v);
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioBuffer> DirectSoundAudioManager::GetAudioBuffer(size_t index) {
		if (index >= audioBufferList.size()) return NULL;

		return audioBufferList[index];
	}
	//---------------------------------------------------------------------------------------
	//
	bool DirectSoundAudioManager::Load(const std::wstring fileName, SoundBufferType bufferType) {

		//最後に.が見つかった場所か(ファイル名に.が含まれている場合の対策)
		int pos = fileName.find_last_of (L".");
		if (pos == std::wstring::npos) {
			return false;//空文字を返す
		}
		//拡張子のみを取得する
		std::wstring ext = fileName.substr(pos+1, fileName.size());

		//ロード
		if (ext== L"pack") {
			LoadFromPackedFile(fileName, bufferType);
		}
		else if (ext == L"wav" || ext == L"wave") {
			LoadFromWaveFile(fileName, bufferType);
		}
		else if (ext == L"ogg") {
			//未対応だが、将来的に導入するので、とりあえず確保しておく
			return false;
		}

		return true;
	}	

	//---------------------------------------------------------------------------------------
	//
	bool DirectSoundAudioManager::LoadFromPackedFile(const std::wstring fileName, SoundBufferType bufferType)
	{
		std::shared_ptr<AudioBuffer> audio = nullptr;
		unique_ptr<PackedFile> pack = unique_ptr<PackedFile>(new PackedFile(fileName.c_str()));
		int num = pack->GetFileNum();//パッキングされたファイルの数を取得
		for (int i=0; i< num; i++) {//一括で読んでまえ

			//parameterised fuctoryを導入するべきかな？
			switch(bufferType)
			{
			case Static:
				audio=std::make_shared<DirectSoundAudioBuffer>(dsound, pack->GetFileData(i));
				break;
			case Static3D:
				audio=std::make_shared<DirectSound3DAudioBuffer>(dsound, pack->GetFileData(i));
				break;
			case Streaming:
				audio=std::make_shared<DirectSoundStreamingAudioBuffer>(dsound, pack->GetFileData(i));
				break;
			case Streaming3D:
				//audio=new DirectSound3DAudioBuffer(dsound, hwnd, fileName);
				//break;
			default:
				return false;
			}
			if (audio != nullptr) {
				audio->SetVolume(GetMasterVolume());
				audioBufferList.push_back(audio);
			}
		}
		return true;
	}

	//---------------------------------------------------------------------------------------
	//
	bool DirectSoundAudioManager::LoadFromWaveFile(const std::wstring fileName, SoundBufferType bufferType){
		std::shared_ptr<AudioBuffer> audio = nullptr;
		switch(bufferType)
		{
		case Static:
			audio=std::make_shared<DirectSoundAudioBuffer>(dsound, fileName);
			break;
		case Static3D:
			audio=std::make_shared<DirectSound3DAudioBuffer>(dsound, fileName);
			break;
		case Streaming:
			audio=std::make_shared<DirectSoundStreamingAudioBuffer>(dsound, fileName);
			break;
		case Streaming3D:
			//audio=new DirectSound3DAudioBuffer(dsound, hwnd, fileName);
			break;
		default:
			DebugOutput::DebugMessage("生成失敗");
			return false;
		}

		if (audio != nullptr) {
			audioBufferList.push_back(audio);
		}
		return true;
	}
}