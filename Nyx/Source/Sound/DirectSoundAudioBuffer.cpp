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
#include "Sound/AudioUtility.h"
#include "Sound/WaveReader.h"
#include "DirectSoundAudioBuffer.h"

namespace nyx {
	class AudioBuffer3D;

	//-------------------------------------------------------------------------------------------------------
	//
	dsound_audio_buffer::dsound_audio_buffer() 
		: isLoop_(false), soundBuffer_(nullptr){

	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::load(const audio_buffer_desc& desc, const dsound_ptr ds) {
		WAVEFORMATEX wfx={};
		AudioUtility::build_wav_format_ex(&wfx, desc.waveFormat);

		DSBUFFERDESC bufferDesc = {};
		build_dsound_buffer_desc(&bufferDesc, wfx);

		//サウンドバッファの生成
		LPDIRECTSOUNDBUFFER primaryBuffer;
		HRESULT hr = ds->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオのプライマリバッファの作成に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオのプライマリバッファの作成に失敗しました。", hr);
		}

		LPDIRECTSOUNDBUFFER8 soundBuffer;
		hr = primaryBuffer->QueryInterface(IID_IDirectSoundBuffer8 , (void**)&soundBuffer);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオのセカンダリバッファの作成に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオのセカンダリバッファの作成に失敗しました。", hr);
		}

		//スマートポインタの管理下に置く
		soundBuffer_ = dsound_buffer_ptr(soundBuffer);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::play(bool isLoop) {
		NYX_ASSERT(soundBuffer_ != nullptr);
		isLoop_ = isLoop;
		HRESULT hr = soundBuffer_->Play(0, 0, isLoop_);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファを再生出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファを再生出来ませんでした。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::stop() {
		NYX_ASSERT(soundBuffer_ != nullptr);
		HRESULT hr = soundBuffer_->Stop();
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファを停止出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファを停止出来ませんでした。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::resume() {
		NYX_ASSERT(soundBuffer_ != nullptr);
		//再生中なら処理しない
		auto state = get_audio_state();
		if (state.isPlaying) {
			return;
		} 
		if (state.isBufferLost) {
			HRESULT hr = soundBuffer_->Restore();
			if (FAILED(hr)) {
				debug_out::trace("DirectSoundオーディオバッファをレジューム出来ませんでした。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("DirectSoundオーディオバッファをレジューム出来ませんでした。", hr);
			}
		}
		//レジュームする
		HRESULT hr = soundBuffer_->Play(0, 0, isLoop_);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファをレジューム出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファをレジューム出来ませんでした。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::reset() {
		NYX_ASSERT(soundBuffer_ != nullptr);

		HRESULT hr = soundBuffer_->SetCurrentPosition(0);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファの再生位置をリセット出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファの再生位置をリセット出来ませんでした。", hr);
		}

	}



	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::set_volume(long volume) {
		NYX_ASSERT(soundBuffer_ != nullptr);
		long decibel = AudioUtility::volume_to_decibel(volume);
		HRESULT hr = soundBuffer_->SetVolume(decibel);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファのデシベル値の設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファのデシベル値の設定に失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long dsound_audio_buffer::get_volume() const {
		NYX_ASSERT(soundBuffer_ != nullptr);
		long decibel;
		HRESULT hr = soundBuffer_->GetVolume(&decibel);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファのデシベル値の取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファのデシベル値の取得に失敗しました。", hr);
		}

		return AudioUtility::decibel_to_volume(decibel);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::set_effect(const audio_effect_desc & effectDesc) {
		switch(effectDesc.effectType) {
		case AudioUtility::AUIO_EFFECT_TYPE_CHORUS:
			set_chorus_effect(effectDesc);
			break;
		case AudioUtility::AUDIO_EFFECT_TYPE_DISTORTION:
			set_distortion_effect(effectDesc);
			break;
		case AudioUtility::AUDIO_EFFECT_TYPE_ECHO:
			set_echo_effect(effectDesc);
			break;
		case AudioUtility::AUDIO_EFFECT_TYPE_FLANGER:
			set_flanger_effect(effectDesc);
			break;
		case AudioUtility::AUDIO_EFFECT_TYPE_GARGLE:
			set_flanger_effect(effectDesc);
			break;
		case AudioUtility::AUDIO_EFFECT_TYPE_PARAMETRIC_EQUALIZER:
			set_parametric_equalizer_effect(effectDesc);
			break;
		case AudioUtility::AUDIO_EFFECT_TYPE_REVERB:
			set_reverb_effect(effectDesc);
			break;
		default:
			debug_out::trace("EffectTypeの値が違います。");
			throw std::invalid_argument("EffectTypeの値が違います。");
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::reset_effect() {
		uint64_t status = get_status();
		if (status & DSBSTATUS_PLAYING) {
			stop();
		}

		HRESULT hr = soundBuffer_->SetFX(0, NULL, NULL);
		if (FAILED(hr)) {
			debug_out::trace("エフェクトのリセットに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("エフェクトのリセットに失敗しました。", hr);
		}

		resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	audio_state dsound_audio_buffer::get_audio_state() const {
		NYX_ASSERT(soundBuffer_ != nullptr);
		uint64_t status = get_status();

		audio_state state;
		state.isBufferLost = (status & DSBSTATUS_BUFFERLOST) != 0;
		state.isLooping    = (status & DSBSTATUS_LOOPING)    != 0;
		state.isPlaying    = (status & DSBSTATUS_PLAYING)    != 0;

		return state;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	const dsound_buffer_ptr& dsound_audio_buffer::get_handle() const {
		return soundBuffer_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::set_chorus_effect(const audio_effect_desc& effectDesc) {
		effectDesc;
		uint64_t status = get_status();
		if (status & DSBSTATUS_PLAYING) {
			stop();
		}

		uint64_t result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_CHORUS;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			debug_out::trace("コーラスエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("コーラスエフェクトの設定に失敗しました。", hr);
		}

		resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::set_distortion_effect(const audio_effect_desc& effectDesc) {
		effectDesc;
		uint64_t status = get_status();
		if (status & DSBSTATUS_PLAYING) {
			stop();
		}

		uint64_t result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_DISTORTION;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			debug_out::trace("ディストーションエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("ディストーションエフェクトの設定に失敗しました。", hr);
		}
		resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::set_echo_effect(const audio_effect_desc& effectDesc) {
		effectDesc;
		uint64_t status = get_status();
		if (status & DSBSTATUS_PLAYING) {
			stop();
		}


		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_ECHO;

		uint64_t result;
		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			debug_out::trace("エコーエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("エコーエフェクトの設定に失敗しました。", hr);
		}
		resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::set_flanger_effect(const audio_effect_desc& effectDesc) {
		effectDesc;
		uint64_t status = get_status();
		if (status & DSBSTATUS_PLAYING) {
			stop();
		}

		uint64_t result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_FLANGER;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			debug_out::trace("フランジャーエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("フランジャーエフェクトの設定に失敗しました。", hr);
		}
		resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::set_gargle_effect(const audio_effect_desc& effectDesc) {
		effectDesc;
		uint64_t status = get_status();
		if (status & DSBSTATUS_PLAYING) {
			stop();
		}

		uint64_t result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_GARGLE;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			debug_out::trace("ガーグルエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("ガーグルエフェクトの設定に失敗しました。", hr);
		}
		resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::set_parametric_equalizer_effect(const audio_effect_desc& effectDesc) {
		effectDesc;
		uint64_t status = get_status();
		if (status & DSBSTATUS_PLAYING) {
			stop();
		}

		uint64_t result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_PARAMEQ;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			debug_out::trace("パラメトリックイコライザーエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("パラメトリックイコライザースエフェクトの設定に失敗しました。", hr);
		}
		resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::set_reverb_effect(const audio_effect_desc& effectDesc) {
		effectDesc;
		uint64_t status = get_status();
		if (status & DSBSTATUS_PLAYING) {
			stop();
		}

		uint64_t result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_WAVES_REVERB;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			debug_out::trace("リバーブエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("リバーブエフェクトの設定に失敗しました。", hr);
		}
		resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	uint64_t dsound_audio_buffer::get_status() const {
		NYX_ASSERT(soundBuffer_ != nullptr);
		uint64_t status;
		HRESULT hr = soundBuffer_->GetStatus(&status);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファのステータスコードを取得出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファのステータスコードを取得出来ませんでした。", hr);
		}
		return status;
	}
}