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

namespace Nyx {
	class AudioBuffer3D;

	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundAudioBuffer::DirectSoundAudioBuffer() 
		: soundBuffer_(nullptr){

	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Load(const AudioBufferDesc& desc, const DirectSoundPtr ds) {
		WAVEFORMATEX wfx={};
		AudioUtility::BuildWaveFormatEx(&wfx, desc.waveFormat);

		DSBUFFERDESC bufferDesc = {};
		BuildDirectSoundBufferDesc(&bufferDesc, wfx);

		//�T�E���h�o�b�t�@�̐���
		LPDIRECTSOUNDBUFFER primaryBuffer;
		HRESULT hr = ds->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�̃v���C�}���o�b�t�@�̍쐬�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�̃v���C�}���o�b�t�@�̍쐬�Ɏ��s���܂����B", hr);
		}

		LPDIRECTSOUNDBUFFER8 soundBuffer;
		hr = primaryBuffer->QueryInterface(IID_IDirectSoundBuffer8 , (void**)&soundBuffer);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�̃Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�̃Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂����B", hr);
		}

		//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
		soundBuffer_ = DirectSoundBufferPtr(soundBuffer);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Play(bool isLoop) {
		Assert(soundBuffer_ != nullptr);
		HRESULT hr = soundBuffer_->Play(0, 0, isLoop);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@���Đ��o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@���Đ��o���܂���ł����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Stop() {
		Assert(soundBuffer_ != nullptr);
		HRESULT hr = soundBuffer_->Stop();
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@���~�o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@���~�o���܂���ł����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Resume() {
		Assert(soundBuffer_ != nullptr);
		//�Đ����Ȃ珈�����Ȃ�
		auto state = GetState();
		if (state.isPlaying) {
			return;
		} 

		//���W���[������
		HRESULT hr = soundBuffer_->Play(0, 0, state.isLooping);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�����W���[���o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�����W���[���o���܂���ł����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Reset() {
		Assert(soundBuffer_ != nullptr);
		//�Đ����Ȃ��~����
		auto state = GetState();
		if (state.isPlaying) {
			Stop();
		} 

		HRESULT hr = soundBuffer_->SetCurrentPosition(0);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̍Đ��ʒu�����Z�b�g�o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̍Đ��ʒu�����Z�b�g�o���܂���ł����B", hr);
		}
	}



	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetVolume(long volume) {
		Assert(soundBuffer_ != nullptr);
		long decibel = AudioUtility::VolumeToDecibel(volume);
		HRESULT hr = soundBuffer_->SetVolume(decibel);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃f�V�x���l�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃f�V�x���l�̐ݒ�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSoundAudioBuffer::GetVolume() const {
		Assert(soundBuffer_ != nullptr);
		long decibel;
		HRESULT hr = soundBuffer_->GetVolume(&decibel);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃f�V�x���l�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃f�V�x���l�̎擾�Ɏ��s���܂����B", hr);
		}

		return AudioUtility::DecibelToVolume(decibel);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetEffect(const AudioEffectDesc & effectDesc) {
		switch(effectDesc.effectType) {
		case AudioUtility::EffectType_Chorus:
			SetChorusEffect(effectDesc);
			break;
		case AudioUtility::EffectType_Distortion:
			SetDistortionEffect(effectDesc);
			break;
		case AudioUtility::EffectType_Echo:
			SetEchoEffect(effectDesc);
			break;
		case AudioUtility::EffectType_Flanger:
			SetFlangerEffect(effectDesc);
			break;
		case AudioUtility::EffectType_Gargle:
			SetFlangerEffect(effectDesc);
			break;
		case AudioUtility::EffectType_ParametricEqualizer:
			SetParametricEqualizerEffect(effectDesc);
			break;
		case AudioUtility::EffectType_Reverb:
			SetReverbEffect(effectDesc);
			break;
		default:
			DebugOutput::Trace("EffectType�̒l���Ⴂ�܂��B");
			throw std::invalid_argument("EffectType�̒l���Ⴂ�܂��B");
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::ResetEffect() {
		HRESULT hr = soundBuffer_->SetFX(0, NULL, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("�G�t�F�N�g�̃��Z�b�g�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("�G�t�F�N�g�̃��Z�b�g�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioState DirectSoundAudioBuffer::GetState() const {
		Assert(soundBuffer_ != nullptr);
		ulong status = GetStatus();

		AudioState state;
		state.isBufferLost = static_cast<bool>(status & DSBSTATUS_BUFFERLOST);
		state.isLooping    = static_cast<bool>(status & DSBSTATUS_LOOPING);
		state.isPlaying    = static_cast<bool>(status & DSBSTATUS_PLAYING);

		return state;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	const DirectSoundBufferPtr& DirectSoundAudioBuffer::GetHandle() const {
		return soundBuffer_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetChorusEffect(const AudioEffectDesc& effectDesc) {
		effectDesc;
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_CHORUS;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("�R�[���X�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("�R�[���X�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
		}

		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetDistortionEffect(const AudioEffectDesc& effectDesc) {
		effectDesc;
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_DISTORTION;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("�f�B�X�g�[�V�����G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("�f�B�X�g�[�V�����G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
		}
		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetEchoEffect(const AudioEffectDesc& effectDesc) {
		effectDesc;
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}


		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_ECHO;

		ulong result;
		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("�G�R�[�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("�G�R�[�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
		}
		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetFlangerEffect(const AudioEffectDesc& effectDesc) {
		effectDesc;
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_FLANGER;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("�t�����W���[�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("�t�����W���[�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
		}
		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetGargleEffect(const AudioEffectDesc& effectDesc) {
		effectDesc;
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_GARGLE;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("�K�[�O���G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("�K�[�O���G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
		}
		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetParametricEqualizerEffect(const AudioEffectDesc& effectDesc) {
		effectDesc;
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_PARAMEQ;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("�p�����g���b�N�C�R���C�U�[�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("�p�����g���b�N�C�R���C�U�[�X�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
		}
		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetReverbEffect(const AudioEffectDesc& effectDesc) {
		effectDesc;
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_WAVES_REVERB;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("���o�[�u�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("���o�[�u�X�G�t�F�N�g�̐ݒ�Ɏ��s���܂����B", hr);
		}
		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	ulong DirectSoundAudioBuffer::GetStatus() const {
		Assert(soundBuffer_ != nullptr);
		ulong status;
		HRESULT hr = soundBuffer_->GetStatus(&status);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃X�e�[�^�X�R�[�h���擾�o���܂���ł����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃X�e�[�^�X�R�[�h���擾�o���܂���ł����B", hr);
		}
		return status;
	}
}