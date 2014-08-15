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
#include "SoundReader.h"
#include "WaveReader.h"
#include "OggReader.h"

namespace nyx {
	//--------------------------------------------------------------------------------------
	//
	dsound_audio_manager::dsound_audio_manager() {

	}


	//--------------------------------------------------------------------------------------
	//
	dsound_audio_manager::dsound_audio_manager(const audio_desc& desc) {
		initialize(desc);
	}


	//--------------------------------------------------------------------------------------
	//
	void dsound_audio_manager::initialize(const audio_desc& desc) {
		//DirectSound�̏�����
		LPDIRECTSOUND8 directSound;
		HRESULT hr = ::DirectSoundCreate8(NULL, &directSound ,NULL);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�̏������Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�̏������Ɏ��s���܂����B", hr);
		}

		auto hwnd = desc.handle;
		hr = directSound->SetCooperativeLevel(hwnd, DSSCL_EXCLUSIVE|DSSCL_PRIORITY ) ;
		if (FAILED(hr)){
			debug_out::trace("DirectSound�̋������x�����ݒ�o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�̋������x�����ݒ�o���܂���ł����B", hr);
		}

		//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
		directSound_ = dsound_ptr(directSound, true);
	}


	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<iaudio_buffer> dsound_audio_manager::create_audio_buffer(const std::wstring& fileName, const audio_buffer_desc& bufferDesc) {
		std::shared_ptr<iaudio_buffer> audio;
		size_t pos = fileName.find_last_of(L".");
		std::wstring ext = fileName.substr( pos+1, fileName.npos);
		
		if (ext == L"wav") {
			audio = create_audio_buffer_from_wave(fileName, bufferDesc);
		}
		else if (ext == L"ogg") {
			audio = create_audio_buffer_from_ogg(fileName, bufferDesc);
		}
		else {
			audio = nullptr;
		}

		return audio;
	}


	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<iaudio_listener> dsound_audio_manager::create_audio_listener() {
		return std::make_shared<dsound_audio_listener>(directSound_);
	}


	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<audio_cache> dsound_audio_manager::load_audio(const std::wstring& fileName, const audio_buffer_desc& bufferDesc) {
		std::wstring line(L"");
		std::wifstream file(fileName);
		std::shared_ptr<audio_cache> audioCache(std::make_shared<audio_cache>());

		while (std::getline(file, line)) {
			std::shared_ptr<iaudio_buffer> buffer = create_audio_buffer(line, bufferDesc);
			audioCache->add(line, buffer);
		}

		return audioCache;
	}	


	//---------------------------------------------------------------------------------------
	//
	const dsound_ptr dsound_audio_manager::get_handle() {
		return directSound_;
	}


	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<iaudio_buffer> dsound_audio_manager::create_audio_buffer_from_wave(const std::wstring& fileName, const audio_buffer_desc& bufferDesc) {
		std::shared_ptr<iaudio_buffer> audio;
		std::shared_ptr<sound_reader> reader = std::make_shared<wave_reader>(fileName);
		//sound reader�͕K�������������
		NYX_ASSERT (reader != nullptr) 

		switch(bufferDesc.bufferType) {
		case AudioUtility::AUDIO_BUFFER_TYPE_STATIC :
			audio = std::make_shared<dsound_static_audio_buffer>(bufferDesc, directSound_, reader);
			break;
		case AudioUtility::AUDIO_BUFFER_TYPE_STATIC_3D:
			audio = std::make_shared<dsound_static_3d_audio_buffer>(bufferDesc, directSound_, reader);
			break;
		case AudioUtility::AUDIO_BUFFER_TYPE_STREAMING:
			audio = std::make_shared<dsound_streaming_audio_buffer>(bufferDesc, directSound_, reader);
			break;
		case AudioUtility::AUDIO_BUFFER_TYPE_STREAMING_3D:
			audio = std::make_shared<dsound_streaming_3d_audio_buffer>(bufferDesc, directSound_, reader);
			break;
		default:
			throw std::invalid_argument("�����Ȉ������n����܂����B");
		}
		return audio;
	}


	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<iaudio_buffer> dsound_audio_manager::create_audio_buffer_from_ogg(const std::wstring& fileName, const audio_buffer_desc& bufferDesc) {
		nyx::debug_out::trace("Ogg�t�@�C���̓T�|�[�g����Ă��܂���");
		fileName, bufferDesc;
		return nullptr;
	}
}