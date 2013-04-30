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
		: soundBuffer_(nullptr) {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundAudioBuffer::DirectSoundAudioBuffer(const DirectSoundPtr dsound, const std::wstring& fileName){
		Load(dsound, fileName);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Load(const DirectSoundPtr ds, const std::wstring& fileName) {
		std::unique_ptr<WaveReader> waveReader(new WaveReader(fileName));
		const auto waveHeader = waveReader->GetFileHeader();

		//Wave�t�H�[�}�b�g�̃Z�b�g�A�b�v
		WAVEFORMATEX wfx;
		ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
		wfx.wFormatTag      = waveHeader.formatChunk.formatTag;
		wfx.nChannels       = waveHeader.formatChunk.channelNum;
		wfx.wBitsPerSample  = waveHeader.formatChunk.bitsRate;
		wfx.nSamplesPerSec  = waveHeader.formatChunk.samplingRate;
		wfx.nBlockAlign     = waveHeader.formatChunk.blockSize;
		wfx.nAvgBytesPerSec = waveHeader.formatChunk.bytesPerSec;
		wfx.cbSize          = sizeof(WAVEFORMATEX);
		
		//DSBufferDesc�̃Z�b�g�A�b�v
		DSBUFFERDESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DSBUFFERDESC));
		bufferDesc.dwBufferBytes   = waveHeader.dataChunk.chunkSize;
		bufferDesc.dwFlags         = DSBCAPS_CTRLVOLUME;
		bufferDesc.dwSize          = sizeof(DSBUFFERDESC);
		bufferDesc.lpwfxFormat     = &wfx;
		bufferDesc.guid3DAlgorithm = DS3DALG_DEFAULT;

		//�T�E���h�o�b�t�@�̐���
		LPDIRECTSOUNDBUFFER soundBuffer;
		HRESULT hr = ds->CreateSoundBuffer(&bufferDesc, &soundBuffer, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̍쐬�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̍쐬�Ɏ��s���܂����B", hr);
		}

		//�o�b�t�@�ɔg�`�f�[�^�̏�������
		void* waveData = nullptr;
		ulong waveSize = 0;
		hr = soundBuffer->Lock(0, waveHeader.dataChunk.chunkSize, &waveData, &waveSize, NULL, NULL, 0);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B", hr);
		}
		
		auto waveDataSource = waveReader->GetWaveData();
		memcpy(waveData, waveDataSource.get(), waveHeader.dataChunk.chunkSize);

		hr = soundBuffer->Unlock(waveData, waveSize, NULL, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B", hr);
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
		ulong status = GetStatus();
		if (!(status & DSBSTATUS_PLAYING)) {
			return;
		} 
			
		//���W���[������
		HRESULT hr = soundBuffer_->Play(0, 0, true);
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