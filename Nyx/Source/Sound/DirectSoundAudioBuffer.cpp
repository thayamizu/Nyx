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

		//�T�E���h�o�b�t�@�̐���
		LPDIRECTSOUNDBUFFER primaryBuffer;
		HRESULT hr = ds->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�̃v���C�}���o�b�t�@�̍쐬�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�̃v���C�}���o�b�t�@�̍쐬�Ɏ��s���܂����B", hr);
		}

		LPDIRECTSOUNDBUFFER8 soundBuffer;
		hr = primaryBuffer->QueryInterface(IID_IDirectSoundBuffer8 , (void**)&soundBuffer);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�̃Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�̃Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂����B", hr);
		}

		//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
		soundBuffer_ = dsound_buffer_ptr(soundBuffer);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::play(bool isLoop) {
		NYX_ASSERT(soundBuffer_ != nullptr);
		isLoop_ = isLoop;
		HRESULT hr = soundBuffer_->Play(0, 0, isLoop_);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@���Đ��o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@���Đ��o���܂���ł����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::stop() {
		NYX_ASSERT(soundBuffer_ != nullptr);
		HRESULT hr = soundBuffer_->Stop();
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@���~�o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@���~�o���܂���ł����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::resume() {
		NYX_ASSERT(soundBuffer_ != nullptr);
		//�Đ����Ȃ珈�����Ȃ�
		auto state = get_audio_state();
		if (state.isPlaying) {
			return;
		} 
		if (state.isBufferLost) {
			HRESULT hr = soundBuffer_->Restore();
			if (FAILED(hr)) {
				debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@�����W���[���o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@�����W���[���o���܂���ł����B", hr);
			}
		}
		//���W���[������
		HRESULT hr = soundBuffer_->Play(0, 0, isLoop_);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@�����W���[���o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@�����W���[���o���܂���ł����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::reset() {
		NYX_ASSERT(soundBuffer_ != nullptr);

		HRESULT hr = soundBuffer_->SetCurrentPosition(0);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@�̍Đ��ʒu�����Z�b�g�o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@�̍Đ��ʒu�����Z�b�g�o���܂���ł����B", hr);
		}

	}



	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_audio_buffer::set_volume(long volume) {
		NYX_ASSERT(soundBuffer_ != nullptr);
		long decibel = AudioUtility::volume_to_decibel(volume);
		HRESULT hr = soundBuffer_->SetVolume(decibel);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@�̃f�V�x���l�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@�̃f�V�x���l�̐ݒ�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long dsound_audio_buffer::get_volume() const {
		NYX_ASSERT(soundBuffer_ != nullptr);
		long decibel;
		HRESULT hr = soundBuffer_->GetVolume(&decibel);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@�̃f�V�x���l�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@�̃f�V�x���l�̎擾�Ɏ��s���܂����B", hr);
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
			debug_out::trace("EffectType�̒l���Ⴂ�܂��B");
			throw std::invalid_argument("EffectType�̒l���Ⴂ�܂��B");
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
			debug_out::trace("�G�t�F�N�g�̃��Z�b�g�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("�G�t�F�N�g�̃��Z�b�g�Ɏ��s���܂����B", hr);
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
			debug_out::trace("�R�[���X�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("�R�[���X�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
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
			debug_out::trace("�f�B�X�g�[�V�����G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("�f�B�X�g�[�V�����G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
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
			debug_out::trace("�G�R�[�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("�G�R�[�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
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
			debug_out::trace("�t�����W���[�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("�t�����W���[�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
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
			debug_out::trace("�K�[�O���G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("�K�[�O���G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
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
			debug_out::trace("�p�����g���b�N�C�R���C�U�[�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("�p�����g���b�N�C�R���C�U�[�X�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
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
			debug_out::trace("���o�[�u�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("���o�[�u�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
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
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@�̃X�e�[�^�X�R�[�h���擾�o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@�̃X�e�[�^�X�R�[�h���擾�o���܂���ł����B", hr);
		}
		return status;
	}
}