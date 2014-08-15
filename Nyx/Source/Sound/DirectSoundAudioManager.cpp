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
		//DirectSoundの初期化
		LPDIRECTSOUND8 directSound;
		HRESULT hr = ::DirectSoundCreate8(NULL, &directSound ,NULL);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundの初期化に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundの初期化に失敗しました。", hr);
		}

		auto hwnd = desc.handle;
		hr = directSound->SetCooperativeLevel(hwnd, DSSCL_EXCLUSIVE|DSSCL_PRIORITY ) ;
		if (FAILED(hr)){
			debug_out::trace("DirectSoundの協調レベルが設定出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundの協調レベルが設定出来ませんでした。", hr);
		}

		//スマートポインタの管理下に置く
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
		//sound readerは必ず初期化される
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
			throw std::invalid_argument("無効な引数が渡されました。");
		}
		return audio;
	}


	//---------------------------------------------------------------------------------------
	//
	std::shared_ptr<iaudio_buffer> dsound_audio_manager::create_audio_buffer_from_ogg(const std::wstring& fileName, const audio_buffer_desc& bufferDesc) {
		nyx::debug_out::trace("Oggファイルはサポートされていません");
		fileName, bufferDesc;
		return nullptr;
	}
}