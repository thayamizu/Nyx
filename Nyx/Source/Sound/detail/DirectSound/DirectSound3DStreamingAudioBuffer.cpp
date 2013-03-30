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
#include "Sound/WaveReader.h"
#include "DirectSound3DStreamingAudioBuffer.h"
namespace Nyx {
	using Nyx::File;
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSound3DStreamingAudioBuffer::DirectSound3DStreamingAudioBuffer(const DirectSound dsound, const std::wstring fileName) 
		:IAudioBuffer() {

			DataChunk dataChunk;
			FmtChunk fmtChunk;
			WAVEFORMATEX wfx;
			std::unique_ptr<WaveReader> reader(new WaveReader());

			//Wave�f�[�^�̓ǂݎ��
			reader->ReadFromFile(fileName);
			reader->GetDataChunk(&dataChunk);
			reader->GetFmtChunk(&fmtChunk);

			//WAVE�t�H�[�}�b�g�̃Z�b�g�A�b�v
			memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
			wfx.wFormatTag = fmtChunk.formatTag; 
			wfx.nChannels = fmtChunk.channelNum; 
			wfx.nSamplesPerSec = fmtChunk.samplingRate; 
			wfx.nBlockAlign = fmtChunk.blockSize; 
			wfx.nAvgBytesPerSec = fmtChunk.bytesPerSec; 
			wfx.wBitsPerSample = fmtChunk.bitsRate; 

			//�W�����j�APCM�̊m�F�B���kPCM��}���`�`�����l�����͑z��O�B�Ȃ��A3D�T�E���h�̉����̓��m�����ł���K�v������
			if( wfx.wFormatTag == WAVE_FORMAT_PCM ) {
				if(wfx.nChannels > 1) {
					DebugOutput::DebugMessage("3D�Đ��͉��������m�����ł���K�v������܂�");
					return;
				}  
			}
			else {
				DebugOutput::DebugMessage("PCM�t�H�[�}�b�g�ł͂���܂���");
				return;
			}

			// DirectSound�Z�J���_���[�o�b�t�@�[�쐬
			DSBUFFERDESC dsbd;  
			ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
			dsbd.dwSize		= sizeof(DSBUFFERDESC);
			dsbd.dwFlags	=   DSBCAPS_CTRL3D |  DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLFX;
			dsbd.dwBufferBytes = dataChunk.chunkSize;
			dsbd.guid3DAlgorithm = DS3DALG_HRTF_FULL;
			dsbd.lpwfxFormat = &wfx;

			HRESULT hr = dsound->CreateSoundBuffer( &dsbd, &soundBuffer, NULL ); 
			if (FAILED(hr)) {
				DebugOutput::DebugMessage("DirectSound�Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂���");
			}

			//DirectSound3DBuffer�̎擾
			hr = soundBuffer->QueryInterface(IID_IDirectSound3DBuffer8, reinterpret_cast<void**>(&sound3DBuffer));
			if(FAILED(hr)){
				DebugOutput::DebugMessage("IDirectSound3DBuffer8�̎擾�Ɏ��s���܂���");
			}

			//�Z�J���_���o�b�t�@�ɔg�`�f�[�^�̏�������
			void* buffer = NULL;
			ulong bufferSize=0;
			soundBuffer->Lock( 0, dataChunk.chunkSize, &buffer, &bufferSize, NULL, NULL, 0); 
			{
				memcpy(buffer, dataChunk.waveData, dataChunk.chunkSize);
			}
			soundBuffer->Unlock( buffer, bufferSize, NULL, 0 );


			//�����ʒu�̐ݒ�
			SetPos(0.f, 0.f, 0.f);

			//�ŏ������ƍő勗���̐ݒ�
			SetMinDistance(15.0f);
			SetMaxDistance(20.0f);

			//�p���E�{�����[���̐ݒ�
			soundBuffer->GetPan(&pan);
			soundBuffer->GetVolume(&volume);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	DirectSound3DStreamingAudioBuffer::DirectSound3DStreamingAudioBuffer(const DirectSound dsound, std::shared_ptr<char> waveData) {
		DataChunk dataChunk;
		FmtChunk fmtChunk;
		WAVEFORMATEX wfx;
		unique_ptr<WaveReader> reader = unique_ptr<WaveReader>(new WaveReader());

		//Wave�f�[�^�̓ǂݎ��
		reader->ReadFromMem(waveData);
		reader->GetDataChunk(&dataChunk);
		reader->GetFmtChunk(&fmtChunk);

		//WAVE�t�H�[�}�b�g�̃Z�b�g�A�b�v
		memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
		wfx.wFormatTag = fmtChunk.formatTag; 
		wfx.nChannels = fmtChunk.channelNum; 
		wfx.nSamplesPerSec = fmtChunk.samplingRate; 
		wfx.nBlockAlign = fmtChunk.blockSize; 
		wfx.nAvgBytesPerSec = fmtChunk.bytesPerSec; 
		wfx.wBitsPerSample = fmtChunk.bitsRate; 

		//�W�����j�APCM�̊m�F�B���kPCM��}���`�`�����l�����͑z��O�B�Ȃ��A3D�T�E���h�̉����̓��m�����ł���K�v������
		if( wfx.wFormatTag == WAVE_FORMAT_PCM ) {
			if(wfx.nChannels > 1) {
				DebugOutput::DebugMessage("3D�Đ��͉��������m�����ł���K�v������܂�");
				return;
			}  
		}
		else {
			DebugOutput::DebugMessage("PCM�t�H�[�}�b�g�ł͂���܂���");
			return;
		}

		// DirectSound�Z�J���_���[�o�b�t�@�[�쐬
		DSBUFFERDESC dsbd;  
		ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		dsbd.dwSize		= sizeof(DSBUFFERDESC);
		dsbd.dwFlags	=   DSBCAPS_CTRL3D|DSBCAPS_CTRLVOLUME;
		dsbd.dwBufferBytes = dataChunk.chunkSize;
		dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
		dsbd.lpwfxFormat = &wfx;

		HRESULT hr = dsound->CreateSoundBuffer( &dsbd, &soundBuffer, NULL ); 
		if (FAILED(hr)) {
			DebugOutput::DebugMessage("DirectSound�Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂���");
		}

		//�Z�J���_���o�b�t�@�ɔg�`�f�[�^�̏�������
		void* buffer = NULL;
		ulong bufferSize=0;
		soundBuffer->Lock( 0, dataChunk.chunkSize, &buffer, &bufferSize, NULL, NULL, 0); 
		{
			memcpy(buffer, dataChunk.waveData, dataChunk.chunkSize);
		}
		soundBuffer->Unlock( buffer, bufferSize, NULL, 0 );



		//DirectSound3DBuffer�̎擾
		hr = soundBuffer->QueryInterface(IID_IDirectSound3DBuffer8, reinterpret_cast<void**>(&sound3DBuffer));
		if(FAILED(hr)){
			DebugOutput::DebugMessage("IDirectSoundBuffer8�̎擾�Ɏ��s���܂���");
		}

		//�����ʒu�̐ݒ�
		SetPos(0.f, 0.f, 0.f);

		//�ŏ������ƍő勗���̐ݒ�
		SetMinDistance(15.0f);
		SetMaxDistance(20.0f);

		//�p���E�{�����[���̐ݒ�
		soundBuffer->GetPan(&pan);
		soundBuffer->GetVolume(&volume);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	DirectSound3DStreamingAudioBuffer::~DirectSound3DStreamingAudioBuffer() {
		SafeRelease(soundBuffer);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DStreamingAudioBuffer::Play() {
		if (soundBuffer == NULL) return;
		if (IsPause()) return;

		HRESULT hr = soundBuffer->Play(0, 0, IsLooping() ? DSBPLAY_LOOPING : NULL);
		if (hr == DSERR_BUFFERLOST) {
			soundBuffer->Restore();
		}

		/*
		* IDirectSoundBuffer8��GetStatus�́A�h���C�o���邢�̓f�o�C�X�ɂ���Ă͂����������Ƃ�����̂ŁA
		* �g��Ȃ����Ƃɂ���B����ɁAIAudioBuffer::playing���Đ��E��~���Ƃɐݒ肷�邱�ƂőΏ�
		* �ǂȂ���˂�
		*long status;
		*soundBuffer->GetStatus(&status);
		*/
		SetPlaying(true);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DStreamingAudioBuffer::Stop() {
		if (soundBuffer == NULL) return;
		if (IsPause()) return;

		soundBuffer->Stop();
		SetPlaying(false);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DStreamingAudioBuffer::Resume() {
		if (soundBuffer == NULL) return;
		if (IsPause()) return;

		HRESULT hr = soundBuffer->Play( 0, 0, IsLooping() ? DSBPLAY_LOOPING : NULL);
		if (hr == DSERR_BUFFERLOST) {
			soundBuffer->Restore();	
		}
		SetPlaying(true);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DStreamingAudioBuffer::Reset() {
		if (soundBuffer == NULL ) return;
		if (IsPause()) return;
		if (IsPlaying()) {
			soundBuffer->Stop();
		}
		soundBuffer->SetCurrentPosition(0);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DStreamingAudioBuffer::SetPan(long pan_) {
		pan = pan_;
		soundBuffer->SetPan(pan_);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSound3DStreamingAudioBuffer::GetPan() const {
		return pan;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DStreamingAudioBuffer::SetVolume(long v) {
		if (v > 100) { v = 100;}
		else if (v < 0) {v=0;}

		volume = v;
		soundBuffer->SetVolume(v*100 + DSBVOLUME_MIN);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSound3DStreamingAudioBuffer::GetVolume() const {
		return volume;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DStreamingAudioBuffer::SetPos(float x, float y, float z) {
		sound3DBuffer->SetPosition(x, y, z, DS3D_IMMEDIATE);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DStreamingAudioBuffer::SetMinDistance(float min) {
		sound3DBuffer->SetMinDistance(min, DS3D_IMMEDIATE);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DStreamingAudioBuffer::SetMaxDistance(float max) {
		sound3DBuffer->SetMaxDistance(max, DS3D_IMMEDIATE);
	}
}