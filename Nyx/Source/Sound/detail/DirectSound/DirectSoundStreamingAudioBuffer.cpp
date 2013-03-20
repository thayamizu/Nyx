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
#include "Sound/AudioBuffer.h"
#include "Sound/WaveReader.h"
#include "DirectSoundStreamingAudioBuffer.h"

namespace Nyx {

	//-----------------------------------------------------------------------------------------
	DirectSoundStreamingAudioBuffer::DirectSoundStreamingAudioBuffer(DirectSound dsound, std::wstring fileName)
		: AudioBuffer(), pan(0), volume(0), isEOF(false), cursorPlay(0), cursorRead(0), waveSize(0), bufferSize(0), 
		notifySize(0), nextOffset(0), notifyThreadHandle(NULL)
	{
		
		DataChunk dataChunk;
		FmtChunk fmtChunk;
		WAVEFORMATEX wfx;
		unique_ptr<WaveReader> reader = unique_ptr<WaveReader>(new WaveReader());

		//Wave�f�[�^�̓ǂݎ��
		reader->ReadFromFile(fileName);
		reader->GetDataChunk(&dataChunk);
		reader->GetFmtChunk(&fmtChunk);

		//WAVE�f�[�^���R�s�[
		waveSize = dataChunk.chunkSize;
		waveData = shared_ptr<uchar>(new uchar[waveSize]);
		memcpy(&*waveData, dataChunk.waveData, dataChunk.chunkSize);

		//WAVE�t�H�[�}�b�g�̃Z�b�g�A�b�v
		memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
		wfx.wFormatTag      = fmtChunk.formatTag; 
		wfx.nChannels       = fmtChunk.channelNum; 
		wfx.nSamplesPerSec  = fmtChunk.samplingRate; 
		wfx.nBlockAlign     = fmtChunk.blockSize; 
		wfx.nAvgBytesPerSec = fmtChunk.bytesPerSec; 
		wfx.wBitsPerSample  = fmtChunk.bitsRate; 

		//�P�x�̏������݂ŃZ�J���_���o�b�t�@�Ɏ��߂�u���b�N�̑傫�����v�Z
		int samplingRate = wfx.nSamplesPerSec;   
		ulong blockAlign = (ulong)wfx.nBlockAlign;  
		ulong size = samplingRate * 2 * blockAlign / NotifyEventNums;	
		size -= size % blockAlign; 
		notifySize = size;

		// DirectSound�Z�J���_���[�o�b�t�@�[�쐬
		DSBUFFERDESC dsbd;  
		ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		dsbd.dwSize		= sizeof(DSBUFFERDESC);
		dsbd.dwFlags	= DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY 
			| DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_GLOBALFOCUS;
		dsbd.dwBufferBytes = notifySize * NotifyEventNums;
		dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
		dsbd.lpwfxFormat = &wfx;

		HRESULT hr = dsound->CreateSoundBuffer( &dsbd, &soundBuffer, NULL ); 
		Assert(hr == DS_OK);
		if (FAILED(hr)) {
			DebugOutput::DebugMessage("DirectSound�Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂���");
		}

		//�Z�J���_���o�b�t�@�ɔg�`�f�[�^�̏�������
		void* buf = NULL;
		ulong bufSize=0;
		soundBuffer->Lock( 0, dsbd.dwBufferBytes, &buf, &bufSize, NULL, NULL, 0); 
		{
			memcpy(buf, dataChunk.waveData, bufSize);
			bufferSize = bufSize;
			cursorRead += bufSize;
		}
		soundBuffer->Unlock( buf, bufferSize, NULL, 0 );

		//�ʒm�C�x�X���b�h�̐���
		notifyThreadHandle = CreateThread( NULL,0, NotifyThreadProc, (void*)this, 0, 0);

		//�ʒm�C�x���g�̐ݒ�
		LPDIRECTSOUNDNOTIFY notify;
		DSBPOSITIONNOTIFY  dspn[NotifyEventNums];
		hr = soundBuffer->QueryInterface(IID_IDirectSoundNotify, reinterpret_cast<void**>(&notify));
		Assert(hr == DS_OK);
		if ( FAILED(hr)) {
			DebugOutput::DebugMessage("IDirectSoundNotify�̎擾�Ɏ��s���܂���");
		}

		// �C�x���g�ƃV�O�i���ɂȂ�ʒu���擾
		for( int i = 0 ; i < NotifyEventNums ; i++ ) {
			notifyEvent[i] =CreateEvent(NULL, false, false, NULL);
			dspn[i].dwOffset = (notifySize * i) +notifySize-1; // �V�O�i���ɂȂ�ʒu���v�Z
			dspn[i].hEventNotify = notifyEvent[i];
		}

		// �C�x���g���Z�b�g
		hr = notify->SetNotificationPositions(NotifyEventNums, dspn);
		Assert(hr == DS_OK);
		if( FAILED(hr)) {
			SafeRelease(notify);
			DebugOutput::DebugMessage("IDirectSoundNotify�̐ݒ�Ɏ��s���܂���");
		}

		SafeRelease(notify);
	}
	DirectSoundStreamingAudioBuffer::DirectSoundStreamingAudioBuffer(DirectSound dsound, shared_ptr<char> wave)
		: AudioBuffer(), pan(0), volume(0), isEOF(false), cursorPlay(0), cursorRead(0), waveSize(0), 
		bufferSize(0), notifySize(0), nextOffset(0), notifyThreadHandle(NULL)
	{
		ulong blockSize;
		DataChunk dataChunk;
		FmtChunk fmtChunk;
		WAVEFORMATEX wfx;
		unique_ptr<WaveReader> reader = unique_ptr<WaveReader>(new WaveReader());

		//Wave�f�[�^�̓ǂݎ��
		reader->ReadFromMem(wave);
		reader->GetDataChunk(&dataChunk);
		reader->GetFmtChunk(&fmtChunk);

		//WAVE�f�[�^���R�s�[
		waveSize = dataChunk.chunkSize;
		waveData = shared_ptr<uchar>(new uchar[waveSize]);
		memcpy(&*waveData, dataChunk.waveData, dataChunk.chunkSize);

		//WAVE�t�H�[�}�b�g�̃Z�b�g�A�b�v
		memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
		wfx.wFormatTag      = fmtChunk.formatTag; 
		wfx.nChannels       = fmtChunk.channelNum; 
		wfx.nSamplesPerSec  = fmtChunk.samplingRate; 
		wfx.nBlockAlign     = fmtChunk.blockSize; 
		wfx.nAvgBytesPerSec = fmtChunk.bytesPerSec; 
		wfx.wBitsPerSample  = fmtChunk.bitsRate; 

		//�P�x�̏������݂ŃZ�J���_���o�b�t�@�Ɏ��߂�u���b�N�̑傫�����v�Z
		int samplingRate = wfx.nSamplesPerSec;   
		ulong blockAlign = (ulong)wfx.nBlockAlign;  
		ulong size = samplingRate * 2 * blockAlign / NotifyEventNums;	
		size -= size % blockAlign; 
		notifySize = size;

		// DirectSound�Z�J���_���[�o�b�t�@�[�쐬
		DSBUFFERDESC dsbd;  
		ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		dsbd.dwSize		= sizeof(DSBUFFERDESC);
		dsbd.dwFlags	= DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY 
			| DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_GLOBALFOCUS;
		dsbd.dwBufferBytes = notifySize * NotifyEventNums;
		dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
		dsbd.lpwfxFormat = &wfx;

		HRESULT hr = dsound->CreateSoundBuffer( &dsbd, &soundBuffer, NULL ); 
		Assert(hr == DS_OK);
		if (FAILED(hr)) {
			DebugOutput::DebugMessage("DirectSound�Z�J���_���o�b�t�@�̍쐬�Ɏ��s���܂���");
		}

		//�Z�J���_���o�b�t�@�ɔg�`�f�[�^�̏�������
		void* buf = NULL;
		ulong bufSize=0;
		soundBuffer->Lock( 0, dsbd.dwBufferBytes, &buf, &bufSize, NULL, NULL, 0); 
		{
			memcpy(buf, dataChunk.waveData, bufSize);
			bufferSize = bufSize;
			cursorRead += bufSize;
		}
		soundBuffer->Unlock( buf, bufferSize, NULL, 0 );

		//�ʒm�C�x�X���b�h�̐���
		notifyThreadHandle = CreateThread( NULL,0, NotifyThreadProc, (void*)this, 0, 0);

		//�ʒm�C�x���g�̐ݒ�
		LPDIRECTSOUNDNOTIFY notify;
		DSBPOSITIONNOTIFY  dspn[NotifyEventNums];
		hr = soundBuffer->QueryInterface(IID_IDirectSoundNotify, reinterpret_cast<void**>(&notify));
		Assert(hr == DS_OK);
		if ( FAILED(hr)) {
			DebugOutput::DebugMessage("IDirectSoundNotify�̎擾�Ɏ��s���܂���");
		}

		// �C�x���g�ƃV�O�i���ɂȂ�ʒu���擾
		for( int i = 0 ; i < NotifyEventNums ; i++ ) {
			notifyEvent[i] =CreateEvent(NULL, false, false, NULL);
			dspn[i].dwOffset = (notifySize * i) +notifySize-1; // �V�O�i���ɂȂ�ʒu���v�Z
			dspn[i].hEventNotify = notifyEvent[i];
		}

		// �C�x���g���Z�b�g
		hr = notify->SetNotificationPositions(NotifyEventNums, dspn);
		Assert(hr == DS_OK);
		if( FAILED(hr)) {
			SafeRelease(notify);
			DebugOutput::DebugMessage("IDirectSoundNotify�̐ݒ�Ɏ��s���܂���");
		}

		SafeRelease(notify);
	}

	//-----------------------------------------------------------------------------------------
	DirectSoundStreamingAudioBuffer::~DirectSoundStreamingAudioBuffer()
	{
		SafeRelease(soundBuffer);
	}

	void DirectSoundStreamingAudioBuffer::Play()
	{
		Assert(soundBuffer != nullptr);
		if (IsPause()) return;

		HRESULT hr = soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
		if (hr == DSERR_BUFFERLOST) {
			soundBuffer->Restore();//����������(���e�͕�������Ȃ�)
		}
		SetPlaying(true);


	}
	//-----------------------------------------------------------------------------------------
	//
	void DirectSoundStreamingAudioBuffer::Stop()
	{
		Assert(soundBuffer != nullptr);
		if (IsPause()) return;

		HRESULT hr = soundBuffer->Stop();
		SetPlaying(false);
	}

	//-----------------------------------------------------------------------------------------
	//
	void DirectSoundStreamingAudioBuffer::Resume()
	{
		Assert(soundBuffer != nullptr);
		Play();
	}

	//-----------------------------------------------------------------------------------------
	//
	void DirectSoundStreamingAudioBuffer::Reset()
	{
		Assert(soundBuffer != nullptr);
		bool isPlay = IsPlaying();
		//�Đ����Ȃ��x�~�߂Ă���
		if (isPlay) {
			Stop();
		}

		//�T�E���h�o�b�t�@��擪����ǂݒ���
		nextOffset = 0;
		cursorRead = 0;
		WriteToBuffer(nextOffset);

		//�Đ����������̂Ȃ牉�t�ĊJ
		if (isPlay) {
			Play();
		}
	}

	//-----------------------------------------------------------------------------------------
	//
	long DirectSoundStreamingAudioBuffer::GetPan()
		const 
	{
		return pan;
	}

	//-----------------------------------------------------------------------------------------
	//
	void DirectSoundStreamingAudioBuffer::SetPan(int pan_)
	{	
		pan = pan_;
		soundBuffer->SetPan(pan_);	
	}

	//-----------------------------------------------------------------------------------------
	//
	long DirectSoundStreamingAudioBuffer::GetVolume()
		const 
	{
		return volume;
	}

	//-----------------------------------------------------------------------------------------
	//
	void DirectSoundStreamingAudioBuffer::SetVolume(int v)
	{
		if (v > 100) { v = 100;}
		else if (v < 0) {v=0;}

		volume = v;
		soundBuffer->SetVolume(v*100 + DSBVOLUME_MIN);
	}

	//----------------------------------------------------------------------------------------
	//
	void DirectSoundStreamingAudioBuffer::NotifyThread()
	{
		MSG msg;
		bool isDone = false;
		while( !isDone ) 
		{ 
			ulong dwResult = MsgWaitForMultipleObjects(NotifyEventNums, notifyEvent, 
				false, INFINITE, QS_ALLEVENTS );
			switch( dwResult )
			{
				//�V�O�i����Ԃɂ���B�i�܂�A�Đ��J�[�\�����ʒm�ʒu��ʉ߂����j
			case WAIT_OBJECT_0: 
			case WAIT_OBJECT_0+1:
			case WAIT_OBJECT_0+2:
			case WAIT_OBJECT_0+3://�Đ��V�O�i��
				WriteToBuffer(nextOffset);
				break;
			case WAIT_OBJECT_0+NotifyEventNums:	 
				while( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
					if( msg.message == WM_QUIT ){
						isDone=true;
					}
				}
				break;
			}
		}
	}
	HRESULT DirectSoundStreamingAudioBuffer::WriteToBuffer(ulong offset)
	{
		HRESULT hr=E_FAIL;
		void* buf = NULL;//�������݃o�b�t�@
		ulong bufSize=0;//�o�b�t�@�T�C�Y

		//�ǂݍ��݃J�[�\�����SWAV�̍Ō�ɓ��B�����i����ȏ�ǂݍ��ނƃN���b�V���j
		if(cursorRead + notifySize >= waveSize) {	
			if (IsLooping()) {
				//�ʒm�C�x���g�����Z�b�g
				for (int i=0; i< NotifyEventNums;i++) {
					ResetEvent(notifyEvent[i]);
				} 
				//�ǂݍ��݈ʒu�����Z�b�g
				cursorRead = 0;
				cursorPlay = 0;
				nextOffset = 0;
			}
			else {
				isEOF = true;

				//�ǂݍ��܂��ɁA�P�ɖ����f�[�^���R�s�[���Ă���
				soundBuffer->Lock(offset, notifySize,&buf, &bufSize,NULL,NULL,0);
				{
					memset(buf,0,bufSize);//�����i0)�ɂ��邾��
				}
				soundBuffer->Unlock(buf, bufSize, NULL,NULL);
				nextOffset += bufSize;
				nextOffset %= bufferSize;	

				return E_FAIL;
			}
		}
		///�f�[�^�̓ǂݍ���
		hr = soundBuffer->Lock(offset, notifySize, &buf,&bufSize, NULL, NULL, 0);
		Assert(hr == DS_OK);
		if(FAILED(hr)) {
			DebugOutput::DebugMessage("���b�N���s");
			return hr;
		}

		//�o�b�t�@�փR�s�[
		memcpy(buf, (void*)(&*waveData+cursorRead), bufSize);
		nextOffset += bufSize;
		nextOffset %= bufferSize;

		//�ǂݍ��݃J�[�\����i�߂�
		cursorRead += bufSize;	

		hr = soundBuffer->Unlock(buf,bufSize,NULL,NULL);
		Assert(hr == DS_OK);
		if(FAILED(hr)) {
			DebugOutput::DebugMessage("�A�����b�N���s");
			return hr;
		}	

		return DS_OK;
	}
	//----------------------------------------------------------------------------------------
	//
	ulong __stdcall NotifyThreadProc(void* param) {
		DirectSoundStreamingAudioBuffer* streamingBuffer = reinterpret_cast<DirectSoundStreamingAudioBuffer*>(param);
		streamingBuffer->NotifyThread();
		return 0;
	}
}
