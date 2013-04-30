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
#include "IO/File.h"
#include "Sound/AudioUtility.h"
#include "Sound/AudioCache.h"
#include "DirectSoundAudioBuffer.h"
#include "DirectSoundAudioManager.h"

namespace Nyx {
	//--------------------------------------------------------------------------------------
	//
	DirectSoundAudioManager::DirectSoundAudioManager() {
	
	}


	//--------------------------------------------------------------------------------------
	//
	DirectSoundAudioManager::DirectSoundAudioManager(const AudioDesc& desc) {
			Initialize(desc);
	}


	//--------------------------------------------------------------------------------------
	//
	void DirectSoundAudioManager::Initialize(const AudioDesc& desc) {
		//DirectSoundの初期化
		LPDIRECTSOUND directSound;
		HRESULT hr = ::DirectSoundCreate(NULL, &directSound ,NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundの初期化に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundの初期化に失敗しました。", hr);
		}

		auto hwnd = desc.handle;
		hr = directSound->SetCooperativeLevel(hwnd, DSSCL_EXCLUSIVE|DSSCL_PRIORITY ) ;
		if (FAILED(hr)){
			DebugOutput::Trace("DirectSoundの協調レベルが設定出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundの協調レベルが設定出来ませんでした。", hr);
		}

		//スマートポインタの管理下に置く
		directSound_ = DirectSoundPtr(directSound, true);
	}


	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<AudioCache> DirectSoundAudioManager::Load(const std::wstring& fileName, AudioUtility::AudioBufferType bufferType) {
		std::wstring line(L"");
		std::wifstream file(fileName);
		std::shared_ptr<AudioCache> audioCache(std::make_shared<AudioCache>());

		while (std::getline(file, line)) {
			std::shared_ptr<IAudioBuffer> buffer = LoadFromWaveFile(line, bufferType);
			//audioCache->Add(line, buffer);
		}

		return audioCache;
	}	

	

	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioBuffer> DirectSoundAudioManager::LoadFromWaveFile(const std::wstring fileName, AudioUtility::AudioBufferType bufferType){
		std::shared_ptr<IAudioBuffer> audio;

		switch(bufferType) {
		case AudioUtility::StaticAudioBuffer:
			audio = std::make_shared<DirectSoundAudioBuffer>(directSound_, fileName);
			break;
		case AudioUtility::Static3DAudioBufer:
			audio = std::make_shared<DirectSoundAudioBuffer>(directSound_, fileName);
			break;
		case AudioUtility::StreamingAudioBuffer:
			audio = std::make_shared<DirectSoundAudioBuffer>(directSound_, fileName);
			break;
		case AudioUtility::Streaming3DAudioBuffer:
			audio = std::make_shared<DirectSoundAudioBuffer>(directSound_, fileName);
			break;
		}

		return audio;
	}


	//---------------------------------------------------------------------------------------
	//
	const DirectSoundPtr DirectSoundAudioManager::GetHandle() {
		return directSound_;
	}
}