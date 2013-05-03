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
	DirectSoundAudioBuffer::DirectSoundAudioBuffer() 
		: soundBuffer_(nullptr), bufferDesc_(), waveReader_(nullptr) {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundAudioBuffer::DirectSoundAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr dsound, const std::wstring& fileName)
		: soundBuffer_(nullptr), bufferDesc_(bufferDesc), waveReader_(new WaveReader(fileName)){
			
			Load(bufferDesc, dsound, fileName);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Load(const AudioBufferDesc& desc, const DirectSoundPtr ds, const std::wstring& fileName) {
		WAVEFORMATEX wfx;
		BuildWaveFormatEx(wfx);

		DSBUFFERDESC bufferDesc;
		BuildDirectSoundBufferDesc(bufferDesc, wfx);

		//�t�H�[�J�X���[�h
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

		//�o�b�t�@�ɏ�������
		WriteWaveData();
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
		ulong status = GetStatus();
		if ((status & DSBSTATUS_PLAYING)) {
			return;
		} 

		//���W���[������
		HRESULT hr = soundBuffer_->Play(0, 0, status & DSBPLAY_LOOPING);
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
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
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
	void DirectSoundAudioBuffer::SetPan(long pan) {
		Assert(soundBuffer_ != nullptr);
		HRESULT hr = soundBuffer_->SetPan(pan);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̐ݒ�Ɏ��s���܂����B", hr);
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
	long DirectSoundAudioBuffer::GetPan() const {
		Assert(soundBuffer_ != nullptr);
		long pan;
		HRESULT hr = soundBuffer_->GetPan(&pan);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̎擾�Ɏ��s���܂����B", hr);
		}

		return pan;
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
	void DirectSoundAudioBuffer::ResetEffect() {
		HRESULT hr = soundBuffer_->SetFX(0, NULL, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("�G�t�F�N�g�̃��Z�b�g�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("�G�t�F�N�g�̃��Z�b�g�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetEffect(const AudioEffectDesc& effectDesc) {
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
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::BuildWaveFormatEx(WAVEFORMATEX& wfx) {
		//�w�b�_���
		const auto waveHeader = waveReader_->GetFileHeader();

		//Wave�t�H�[�}�b�g�̃Z�b�g�A�b�v
		ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
		wfx.wFormatTag      = waveHeader.formatChunk.formatTag;
		wfx.nChannels       = waveHeader.formatChunk.channelNum;
		wfx.wBitsPerSample  = waveHeader.formatChunk.bitsRate;
		wfx.nSamplesPerSec  = waveHeader.formatChunk.samplingRate;
		wfx.nBlockAlign     = waveHeader.formatChunk.blockSize;
		wfx.nAvgBytesPerSec = waveHeader.formatChunk.bytesPerSec;
		wfx.cbSize          = sizeof(WAVEFORMATEX);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::BuildDirectSoundBufferDesc(DSBUFFERDESC& dsBufferDesc, WAVEFORMATEX& wfx) {
		//�w�b�_���
		const auto waveHeader = waveReader_->GetFileHeader();

		//�t���O�̐ݒ�
		DWORD flag;
		switch(bufferDesc_.bufferType)
		{
		case AudioUtility::BufferType_StaticAudioBuffer:
			flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
			break;
		case AudioUtility::BufferType_Static3DAudioBufer:
			flag = DSBCAPS_CTRLFX | DSBCAPS_CTRL3D  | DSBCAPS_CTRLVOLUME;
			break;
		case AudioUtility::BufferType_StreamingAudioBuffer:
			flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPOSITIONNOTIFY;
			break;
		case AudioUtility::BufferType_Streaming3DAudioBuffer:
			flag = DSBCAPS_CTRLFX | DSBCAPS_CTRL3D  | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPOSITIONNOTIFY;
			break;
		}

		//�t�H�[�J�X���[�h�̐ݒ�
		if ( bufferDesc_.focusType == AudioUtility::FocusType_GlobalFocus) {
			flag |= DSBCAPS_GLOBALFOCUS;
		}
		else {
			flag |= DSBCAPS_STICKYFOCUS;

		}

		//DSBufferDesc�̃Z�b�g�A�b�v
		ZeroMemory(&dsBufferDesc, sizeof(DSBUFFERDESC));
		dsBufferDesc.lpwfxFormat     = &wfx;
		dsBufferDesc.dwBufferBytes   = bufferDesc_.bufferSize;
		dsBufferDesc.dwFlags         = flag;
		dsBufferDesc.dwSize          = sizeof(DSBUFFERDESC);
		dsBufferDesc.guid3DAlgorithm = bufferDesc_.algorithm;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::WriteWaveData() {
		Assert(waveReader_ != nullptr);
		const auto waveHeader = waveReader_->GetFileHeader();

		//�o�b�t�@�ɔg�`�f�[�^�̏�������
		void* waveData  = nullptr;
		ulong waveSize  = 0;
		ulong chunkSize = waveHeader.dataChunk.chunkSize; 
		HRESULT hr = soundBuffer_->Lock(0, chunkSize, &waveData, &waveSize, NULL, NULL, 0);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B", hr);
		}

		auto waveDataSource = waveReader_->GetWaveData();
		memcpy(waveData, waveDataSource.get(), chunkSize);

		hr = soundBuffer_->Unlock(waveData, waveSize, NULL, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetChorusEffect(const AudioEffectDesc& effectDesc) {
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
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_ECHO;

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