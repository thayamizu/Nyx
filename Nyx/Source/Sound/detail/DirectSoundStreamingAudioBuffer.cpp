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

		//Waveデータの読み取り
		reader->ReadFromFile(fileName);
		reader->GetDataChunk(&dataChunk);
		reader->GetFmtChunk(&fmtChunk);

		//WAVEデータをコピー
		waveSize = dataChunk.chunkSize;
		waveData = shared_ptr<uchar>(new uchar[waveSize]);
		memcpy(&*waveData, dataChunk.waveData, dataChunk.chunkSize);

		//WAVEフォーマットのセットアップ
		memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
		wfx.wFormatTag      = fmtChunk.formatTag; 
		wfx.nChannels       = fmtChunk.channelNum; 
		wfx.nSamplesPerSec  = fmtChunk.samplingRate; 
		wfx.nBlockAlign     = fmtChunk.blockSize; 
		wfx.nAvgBytesPerSec = fmtChunk.bytesPerSec; 
		wfx.wBitsPerSample  = fmtChunk.bitsRate; 

		//１度の書き込みでセカンダリバッファに収めるブロックの大きさを計算
		int samplingRate = wfx.nSamplesPerSec;   
		ulong blockAlign = (ulong)wfx.nBlockAlign;  
		ulong size = samplingRate * 2 * blockAlign / NotifyEventNums;	
		size -= size % blockAlign; 
		notifySize = size;

		// DirectSoundセカンダリーバッファー作成
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
			DebugOutput::DebugMessage("DirectSoundセカンダリバッファの作成に失敗しました");
		}

		//セカンダリバッファに波形データの書き込み
		void* buf = NULL;
		ulong bufSize=0;
		soundBuffer->Lock( 0, dsbd.dwBufferBytes, &buf, &bufSize, NULL, NULL, 0); 
		{
			memcpy(buf, dataChunk.waveData, bufSize);
			bufferSize = bufSize;
			cursorRead += bufSize;
		}
		soundBuffer->Unlock( buf, bufferSize, NULL, 0 );

		//通知イベスレッドの生成
		notifyThreadHandle = CreateThread( NULL,0, NotifyThreadProc, (void*)this, 0, 0);

		//通知イベントの設定
		LPDIRECTSOUNDNOTIFY notify;
		DSBPOSITIONNOTIFY  dspn[NotifyEventNums];
		hr = soundBuffer->QueryInterface(IID_IDirectSoundNotify, reinterpret_cast<void**>(&notify));
		Assert(hr == DS_OK);
		if ( FAILED(hr)) {
			DebugOutput::DebugMessage("IDirectSoundNotifyの取得に失敗しました");
		}

		// イベントとシグナルになる位置を取得
		for( int i = 0 ; i < NotifyEventNums ; i++ ) {
			notifyEvent[i] =CreateEvent(NULL, false, false, NULL);
			dspn[i].dwOffset = (notifySize * i) +notifySize-1; // シグナルになる位置を計算
			dspn[i].hEventNotify = notifyEvent[i];
		}

		// イベントをセット
		hr = notify->SetNotificationPositions(NotifyEventNums, dspn);
		Assert(hr == DS_OK);
		if( FAILED(hr)) {
			SafeRelease(notify);
			DebugOutput::DebugMessage("IDirectSoundNotifyの設定に失敗しました");
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

		//Waveデータの読み取り
		reader->ReadFromMem(wave);
		reader->GetDataChunk(&dataChunk);
		reader->GetFmtChunk(&fmtChunk);

		//WAVEデータをコピー
		waveSize = dataChunk.chunkSize;
		waveData = shared_ptr<uchar>(new uchar[waveSize]);
		memcpy(&*waveData, dataChunk.waveData, dataChunk.chunkSize);

		//WAVEフォーマットのセットアップ
		memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
		wfx.wFormatTag      = fmtChunk.formatTag; 
		wfx.nChannels       = fmtChunk.channelNum; 
		wfx.nSamplesPerSec  = fmtChunk.samplingRate; 
		wfx.nBlockAlign     = fmtChunk.blockSize; 
		wfx.nAvgBytesPerSec = fmtChunk.bytesPerSec; 
		wfx.wBitsPerSample  = fmtChunk.bitsRate; 

		//１度の書き込みでセカンダリバッファに収めるブロックの大きさを計算
		int samplingRate = wfx.nSamplesPerSec;   
		ulong blockAlign = (ulong)wfx.nBlockAlign;  
		ulong size = samplingRate * 2 * blockAlign / NotifyEventNums;	
		size -= size % blockAlign; 
		notifySize = size;

		// DirectSoundセカンダリーバッファー作成
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
			DebugOutput::DebugMessage("DirectSoundセカンダリバッファの作成に失敗しました");
		}

		//セカンダリバッファに波形データの書き込み
		void* buf = NULL;
		ulong bufSize=0;
		soundBuffer->Lock( 0, dsbd.dwBufferBytes, &buf, &bufSize, NULL, NULL, 0); 
		{
			memcpy(buf, dataChunk.waveData, bufSize);
			bufferSize = bufSize;
			cursorRead += bufSize;
		}
		soundBuffer->Unlock( buf, bufferSize, NULL, 0 );

		//通知イベスレッドの生成
		notifyThreadHandle = CreateThread( NULL,0, NotifyThreadProc, (void*)this, 0, 0);

		//通知イベントの設定
		LPDIRECTSOUNDNOTIFY notify;
		DSBPOSITIONNOTIFY  dspn[NotifyEventNums];
		hr = soundBuffer->QueryInterface(IID_IDirectSoundNotify, reinterpret_cast<void**>(&notify));
		Assert(hr == DS_OK);
		if ( FAILED(hr)) {
			DebugOutput::DebugMessage("IDirectSoundNotifyの取得に失敗しました");
		}

		// イベントとシグナルになる位置を取得
		for( int i = 0 ; i < NotifyEventNums ; i++ ) {
			notifyEvent[i] =CreateEvent(NULL, false, false, NULL);
			dspn[i].dwOffset = (notifySize * i) +notifySize-1; // シグナルになる位置を計算
			dspn[i].hEventNotify = notifyEvent[i];
		}

		// イベントをセット
		hr = notify->SetNotificationPositions(NotifyEventNums, dspn);
		Assert(hr == DS_OK);
		if( FAILED(hr)) {
			SafeRelease(notify);
			DebugOutput::DebugMessage("IDirectSoundNotifyの設定に失敗しました");
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
			soundBuffer->Restore();//メモリ復元(内容は復元されない)
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
		//再生中なら一度止めておく
		if (isPlay) {
			Stop();
		}

		//サウンドバッファを先頭から読み直す
		nextOffset = 0;
		cursorRead = 0;
		WriteToBuffer(nextOffset);

		//再生中だったのなら演奏再開
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
				//シグナル状態にある。（つまり、再生カーソルが通知位置を通過した）
			case WAIT_OBJECT_0: 
			case WAIT_OBJECT_0+1:
			case WAIT_OBJECT_0+2:
			case WAIT_OBJECT_0+3://再生シグナル
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
		void* buf = NULL;//書き込みバッファ
		ulong bufSize=0;//バッファサイズ

		//読み込みカーソルが全WAVの最後に到達した（これ以上読み込むとクラッシュ）
		if(cursorRead + notifySize >= waveSize) {	
			if (IsLooping()) {
				//通知イベントをリセット
				for (int i=0; i< NotifyEventNums;i++) {
					ResetEvent(notifyEvent[i]);
				} 
				//読み込み位置をリセット
				cursorRead = 0;
				cursorPlay = 0;
				nextOffset = 0;
			}
			else {
				isEOF = true;

				//読み込まずに、単に無音データをコピーしておく
				soundBuffer->Lock(offset, notifySize,&buf, &bufSize,NULL,NULL,0);
				{
					memset(buf,0,bufSize);//無音（0)にするだけ
				}
				soundBuffer->Unlock(buf, bufSize, NULL,NULL);
				nextOffset += bufSize;
				nextOffset %= bufferSize;	

				return E_FAIL;
			}
		}
		///データの読み込み
		hr = soundBuffer->Lock(offset, notifySize, &buf,&bufSize, NULL, NULL, 0);
		Assert(hr == DS_OK);
		if(FAILED(hr)) {
			DebugOutput::DebugMessage("ロック失敗");
			return hr;
		}

		//バッファへコピー
		memcpy(buf, (void*)(&*waveData+cursorRead), bufSize);
		nextOffset += bufSize;
		nextOffset %= bufferSize;

		//読み込みカーソルを進める
		cursorRead += bufSize;	

		hr = soundBuffer->Unlock(buf,bufSize,NULL,NULL);
		Assert(hr == DS_OK);
		if(FAILED(hr)) {
			DebugOutput::DebugMessage("アンロック失敗");
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
