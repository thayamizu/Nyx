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
#include "IO/File.h"
#include "AudioCache.h"
#include "AudioUtility.h"
#include "DirectSoundAudioManager.h"
#include "DirectSoundAudioListenerh.h"
#include "DirectSoundStaticAudioBuffer.h"
#include "DirectSoundStatic3DAudioBuffer.h"
#include "DirectSoundStreamingAudioBuffer.h"
#include "DirectSoundStreaming3DAudioBuffer.h"
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
		//DirectSound�̏�����
		LPDIRECTSOUND8 directSound;
		HRESULT hr = ::DirectSoundCreate8(NULL, &directSound ,NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�̏������Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�̏������Ɏ��s���܂����B", hr);
		}

		auto hwnd = desc.handle;
		hr = directSound->SetCooperativeLevel(hwnd, DSSCL_EXCLUSIVE|DSSCL_PRIORITY ) ;
		if (FAILED(hr)){
			DebugOutput::Trace("DirectSound�̋������x�����ݒ�o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�̋������x�����ݒ�o���܂���ł����B", hr);
		}

		//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
		directSound_ = DirectSoundPtr(directSound, true);
	}


	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioBuffer> DirectSoundAudioManager::CreateAudioBuffer(const std::wstring& fileName, const AudioBufferDesc& bufferDesc) {
			std::shared_ptr<IAudioBuffer> audio;
		switch(bufferDesc.bufferType) {
		case AudioUtility::BufferType_StaticAudioBuffer :
			audio = std::make_shared<DirectSoundStaticAudioBuffer>(bufferDesc, directSound_, fileName);
			break;
		case AudioUtility::BufferType_Static3DAudioBuffer:
			audio = std::make_shared<DirectSoundStatic3DAudioBuffer>(bufferDesc, directSound_, fileName);
			break;
		case AudioUtility::BufferType_StreamingAudioBuffer:
			audio = std::make_shared<DirectSoundStreamingAudioBuffer>(bufferDesc, directSound_, fileName);
			break;
		case AudioUtility::BufferType_Streaming3DAudioBuffer:
			audio = std::make_shared<DirectSoundStreaming3DAudioBuffer>(bufferDesc, directSound_, fileName);
			break;
		default:
			throw std::invalid_argument("�����Ȉ������n����܂����B");
		}
		return audio;
	}


	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioListener> DirectSoundAudioManager::CreateAudioListener() {
		return std::make_shared<DirectSoundAudioListener>(directSound_);
	}


	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<AudioCache> DirectSoundAudioManager::Load(const std::wstring& fileName, const AudioBufferDesc& bufferDesc) {
		std::wstring line(L"");
		std::wifstream file(fileName);
		std::shared_ptr<AudioCache> audioCache(std::make_shared<AudioCache>());

		while (std::getline(file, line)) {
			std::shared_ptr<IAudioBuffer> buffer = CreateAudioBuffer(line, bufferDesc);
			audioCache->Add(line, buffer);
		}

		return audioCache;
	}	


	//---------------------------------------------------------------------------------------
	//
	const DirectSoundPtr DirectSoundAudioManager::GetHandle() {
		return directSound_;
	}
}