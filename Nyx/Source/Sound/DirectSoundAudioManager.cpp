/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "IO/PackedFile.h"
#include "Sound/DirectSoundAudioBuffer.h"
#include "Sound/DirectSound3DAudioBuffer.h"
#include "Sound/DirectSoundAudioManager.h"

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
			DebugOutput::DebugMessage("DirectSound�̏������Ɏ��s���܂���");
		}
		dsound->AddRef();
		// �������x���̐ݒ�
		dsound->SetCooperativeLevel(hwnd,DSSCL_EXCLUSIVE);

		SetMasterVolume(volume);

	}
	//--------------------------------------------------------------------------------------
	//
	DirectSoundAudioManager::~DirectSoundAudioManager() {
		SafeRelease(dsound);
	}

	//---------------------------------------------------------------------------------------
	//
	bool DirectSoundAudioManager::Load(const tstring fileName, SoundBufferType bufferType) {

		//�Ō��.�����������ꏊ��(�t�@�C������.���܂܂�Ă���ꍇ�̑΍�)
		int pos = fileName.find_last_of (L".");
		if (pos == tstring::npos) {
			return false;//�󕶎���Ԃ�
		}
		//�g���q�݂̂��擾����
		tstring ext = fileName.substr(pos+1, fileName.size());

		//���[�h
		if (ext== L"pack") {
			LoadFromPackedFile(fileName, bufferType);
		}
		else if (ext == L"wav" || ext == L"wave") {
			LoadFromWaveFile(fileName, bufferType);
		}
		else if (ext == L"ogg") {
			//���Ή������A�����I�ɓ�������̂ŁA�Ƃ肠�����m�ۂ��Ă���
			return false;
		}

		return true;
	}	

	//---------------------------------------------------------------------------------------
	//
	bool DirectSoundAudioManager::LoadFromPackedFile(const tstring fileName, SoundBufferType bufferType)
	{
		AudioBuffer* audio = nullptr;
		unique_ptr<PackedFile> pack = unique_ptr<PackedFile>(new PackedFile(fileName.c_str()));
		int num = pack->GetFileNum();//�p�b�L���O���ꂽ�t�@�C���̐����擾
		for (int i=0; i< num; i++) {//�ꊇ�œǂ�ł܂�

			//parameterised fuctory�𓱓�����ׂ����ȁH
			switch(bufferType)
			{
			case Static:
				audio=new DirectSoundAudioBuffer(dsound, pack->GetFileData(i));
				break;
			case Static3D:
				audio=new DirectSound3DAudioBuffer(dsound, pack->GetFileData(i));
				break;
			case Streaming:
				audio=new DirectSoundStreamingAudioBuffer(dsound, pack->GetFileData(i));
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
	bool DirectSoundAudioManager::LoadFromWaveFile(const tstring fileName, SoundBufferType bufferType){
		AudioBuffer* audio = nullptr;
		switch(bufferType)
		{
		case Static:
			audio=new DirectSoundAudioBuffer(dsound, fileName);
			break;
		case Static3D:
			audio=new DirectSound3DAudioBuffer(dsound, fileName);
			break;
		case Streaming:
			audio=new DirectSoundStreamingAudioBuffer(dsound, fileName);
			break;
		case Streaming3D:
			//audio=new DirectSound3DAudioBuffer(dsound, hwnd, fileName);
			break;
		default:
			DebugOutput::DebugMessage("�������s");
			if (audio != nullptr) {
				SafeDelete(audio);
			}
			return false;
		}

		if (audio != nullptr) {
			audioBufferList.push_back(audio);
		}
		return true;
	}
}