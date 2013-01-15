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
#include "Sound/DirectSoundAudioBuffer.h"

namespace Nyx {
	using Nyx::File;
	using std::shared_ptr;
	using std::unique_ptr;
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundAudioBuffer::DirectSoundAudioBuffer(const DirectSound dsound, tstring fileName)
		:AudioBuffer()
	{
		DataChunk dataChunk;
		FmtChunk fmtChunk;
		WAVEFORMATEX wfx;
		unique_ptr<WaveReader> reader = unique_ptr<WaveReader>(new WaveReader());

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

		// DirectSound�Z�J���_���[�o�b�t�@�[�쐬
		DSBUFFERDESC dsbd;  
		ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		dsbd.dwSize		= sizeof(DSBUFFERDESC);
		dsbd.dwFlags	= DSBCAPS_CTRLFX|DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLPAN|DSBCAPS_GLOBALFOCUS;
		dsbd.dwBufferBytes = dataChunk.chunkSize;
		dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
		dsbd.lpwfxFormat = &wfx;

		HRESULT hr = dsound->CreateSoundBuffer( &dsbd, &soundBuffer, NULL ); 
		Assert(hr == S_OK);
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

	}
	DirectSoundAudioBuffer::DirectSoundAudioBuffer(const DirectSound dsound, shared_ptr<char> waveData) {
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

		// DirectSound�Z�J���_���[�o�b�t�@�[�쐬
		DSBUFFERDESC dsbd;  
		ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		dsbd.dwSize		= sizeof(DSBUFFERDESC);
		dsbd.dwFlags	= DSBCAPS_CTRLFX|DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLPAN|DSBCAPS_GLOBALFOCUS;
		dsbd.dwBufferBytes = dataChunk.chunkSize;
		dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
		dsbd.lpwfxFormat = &wfx;

		HRESULT hr = dsound->CreateSoundBuffer( &dsbd, &soundBuffer, NULL ); 
		Assert(hr == S_OK);
		if (FAILED(hr)) {
			DebugOutput::DebugMessage("DirectSound�Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂���");
		}

		void* buffer = NULL;
		ulong bufferSize=0;
		//�Z�J���_���o�b�t�@�ɔg�`�f�[�^�̏�������
		soundBuffer->Lock( 0, dataChunk.chunkSize, &buffer, &bufferSize, NULL, NULL, 0); 
		{
			memcpy(buffer, dataChunk.waveData, dataChunk.chunkSize);
		}
		soundBuffer->Unlock( buffer, bufferSize, NULL, 0 );


	}
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundAudioBuffer::~DirectSoundAudioBuffer() {
		SafeRelease(soundBuffer);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Play() {
		if (soundBuffer == NULL) return;
		if (IsPause()) return;

		HRESULT hr = soundBuffer->Play(0, 0, IsLooping() ? DSBPLAY_LOOPING : NULL);
		if (hr == DSERR_BUFFERLOST) {
			soundBuffer->Restore();//����������(���e�͕�������Ȃ�)
		}
		SetPlaying(true);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Stop() {
		if (soundBuffer == NULL) return;
		if (IsPause()) return;


		HRESULT hr = soundBuffer->Stop();
		SetPlaying(false);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Resume() {
		if (soundBuffer == NULL) return;
		if (IsPause()) return;

		HRESULT hr = soundBuffer->Play( 0, 0, IsLooping() ? DSBPLAY_LOOPING : NULL);
		if ( hr == DSERR_BUFFERLOST) {
			soundBuffer->Restore();
		}

		SetPlaying(true);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Reset() {
		if (soundBuffer == NULL ) return;
		if (IsPause()) return;

		if (IsPlaying()) {
			soundBuffer->Stop();
		}
		soundBuffer->SetCurrentPosition(0);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetPan(int pan_) {
		pan = pan_;
		soundBuffer->SetPan(pan_);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetVolume(int v) {
		if (v > 100) { v = 100;}
		else if (v < 0) {v=0;}

		volume = v;
		soundBuffer->SetVolume(v*100 + DSBVOLUME_MIN);
	}


}