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
#include "Sound/WaveReader.h"
#include "DirectSound3DAudioBuffer.h"
namespace Nyx {
	using Nyx::File;
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSound3DAudioBuffer::DirectSound3DAudioBuffer(const DirectSound dsound, const std::wstring fileName) 
		:IAudioBuffer() {

		//DataChunk dataChunk;
		//FmtChunk fmtChunk;
		//WAVEFORMATEX wfx;
		//unique_ptr<WaveReader> reader = unique_ptr<WaveReader>(new WaveReader());

		////Waveデータの読み取り
		//reader->ReadFromFile(fileName);
		//reader->GetDataChunk(&dataChunk);
		//reader->GetFmtChunk(&fmtChunk);

		////WAVEフォーマットのセットアップ
		//memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
		//wfx.wFormatTag = fmtChunk.formatTag; 
		//wfx.nChannels = fmtChunk.channelNum; 
		//wfx.nSamplesPerSec = fmtChunk.samplingRate; 
		//wfx.nBlockAlign = fmtChunk.blockSize; 
		//wfx.nAvgBytesPerSec = fmtChunk.bytesPerSec; 
		//wfx.wBitsPerSample = fmtChunk.bitsRate; 

		//// DirectSoundセカンダリーバッファー作成
		//DSBUFFERDESC dsbd;  
		//ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		//dsbd.dwSize		= sizeof(DSBUFFERDESC);
		//dsbd.dwFlags	= DSBCAPS_CTRLFX|DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLPAN|DSBCAPS_GLOBALFOCUS;
		//dsbd.dwBufferBytes = dataChunk.chunkSize;
		//dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
		//dsbd.lpwfxFormat = &wfx;

		//DirectSoundBuffer tmpBuffer;
		//HRESULT hr = dsound->CreateSoundBuffer( &dsbd, &tmpBuffer, NULL ); 
		//if (FAILED(hr)) {
		//	DebugOutput::DebugMessage("DirectSoundセカンダリバッファの作成に失敗しました");
		//}

		//hr =tmpBuffer->QueryInterface(IID_IDirectSoundBuffer, reinterpret_cast<void**>(&soundBuffer));
		//if (FAILED(hr)) {
		//	DebugOutput::DebugMessage("DirectSoundセカンダリバッファの取得に失敗しました");
		//}
		//void* buffer = NULL;
		//ulong bufferSize=0;
		////セカンダリバッファに波形データの書き込み
		//soundBuffer->Lock( 0, dataChunk.chunkSize, &buffer, &bufferSize, NULL, NULL, 0); 
		//{
		//	memcpy(buffer, dataChunk.waveData, dataChunk.chunkSize);
		//}
		//soundBuffer->Unlock( buffer, bufferSize, NULL, 0 );


		////DirectSound3DBufferの取得
		//hr = tmpBuffer->QueryInterface(IID_IDirectSound3DBuffer8,reinterpret_cast<void**>(&sound3DBuffer));
		//if(FAILED(hr)){
		//	DebugOutput::DebugMessage("IDirectSoundBuffer8の取得に失敗しました");
		//}

		////音源位置の設定
		//SetPos(0.f, 0.f, 0.f);

		////最小距離と最大距離の設定
		//SetMinDistance(15.0f);
		//SetMaxDistance(20.0f);
		//
		//パン・ボリュームの設定
		//soundBuffer->GetPan(&pan);
		//soundBuffer->GetVolume(&volume);
		HRESULT hr;
		//WAVEフォーマット読み込み情報
		HMMIO hMmio		= NULL;
		ulong waveSize  = 0;
		WAVEFORMATEX* waveFmt;
		//チャンク情報
		MMCKINFO ckInfo;	//チャンク情報
		MMCKINFO riffckInfo;//RIFFチャンク保存用
		//PCMフォーマット
		PCMWAVEFORMAT pcmWaveFmt;

		//WAVファイル内のヘッダー情報（音データ以外）の確認と読み込み
		hMmio = mmioOpen( const_cast<wchar_t*>(fileName.c_str()), NULL, MMIO_ALLOCBUF | MMIO_READ );
		//ファイルポインタをRIFFチャンクの先頭にセットする
		mmioDescend( hMmio, &riffckInfo, NULL, 0 );
		// ファイルポインタを'f' 'm' 't' ' ' チャンクにセットする
		ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );
		//フォーマットを読み込む
		mmioRead( hMmio, (HPSTR) &pcmWaveFmt,sizeof(pcmWaveFmt));  
		waveFmt = (WAVEFORMATEX*)new char[sizeof(WAVEFORMATEX) ];   
		memcpy( waveFmt, &pcmWaveFmt, sizeof(pcmWaveFmt) );   
		waveFmt->cbSize = 0;	
		mmioAscend( hMmio, &ckInfo, 0 );

		// WAVファイル内の音データの読み込み	
		ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');   
		mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );//データチャンクにセット
		waveSize = ckInfo.cksize;

		// DirectSoundセカンダリーバッファー作成
		DSBUFFERDESC dsbd;  
		ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_CTRL3D |  DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLFX;
		dsbd.dwBufferBytes = waveSize;
		dsbd.guid3DAlgorithm = DS3DALG_HRTF_FULL;
		dsbd.lpwfxFormat = waveFmt;
		DirectSoundBuffer tmpBuffer;
		hr = dsound->CreateSoundBuffer( &dsbd, &tmpBuffer, NULL ); 
		if (FAILED(hr)) {
			DebugOutput::DebugMessage("DirectSoundセカンダリバッファの作成に失敗しました");
		}

		hr =tmpBuffer->QueryInterface(IID_IDirectSoundBuffer, reinterpret_cast<void**>(&soundBuffer));
		if (FAILED(hr)) {
			DebugOutput::DebugMessage("DirectSoundセカンダリバッファの取得に失敗しました");
		}

		//セカンダリバッファに波形データの書き込み
		void* buffer = NULL;
		uchar* wavData = NULL;
		ulong bufferSize = 0; 
		soundBuffer->Lock( 0, waveSize,&buffer, &bufferSize, NULL, NULL, 0); 
		{
			File file(fileName.c_str(), Nyx::ReadMode);		
			file.SeekBegin(riffckInfo.dwDataOffset + sizeof(FOURCC));

			wavData=new BYTE[ bufferSize ];
			file.Read(wavData, bufferSize);

			memcpy(buffer, wavData, bufferSize);		
		}
		soundBuffer->Unlock( buffer, bufferSize, NULL, 0 );

		//DirectSound3DBufferの取得
		hr = tmpBuffer->QueryInterface(IID_IDirectSound3DBuffer8,reinterpret_cast<void**>(&sound3DBuffer));
		if(FAILED(hr)){
			DebugOutput::DebugMessage("IDirectSoundBuffer8の取得に失敗しました");
		}

		//最小距離と最大距離の設定
		sound3DBuffer->SetMinDistance(15,DS3D_IMMEDIATE);
		sound3DBuffer->SetMaxDistance(20,DS3D_IMMEDIATE);

		//音源の速度を設定しておく。時速40キロメートル
		sound3DBuffer->SetVelocity(0,0,40,DS3D_IMMEDIATE);  

		//リスナーインターフェイスを取得する  
		LPDIRECTSOUNDBUFFER	pPrimary;  
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));  
		dsbd.dwSize = sizeof(DSBUFFERDESC);  
		dsbd.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;  
		if (SUCCEEDED(dsound->CreateSoundBuffer(&dsbd, &pPrimary, NULL)))   { 
			pPrimary->QueryInterface(IID_IDirectSound3DListener8,(LPVOID *)&listener);    
			pPrimary->Release();  
		}

		//リスナーインターフェイスによりドップラー効果のかかり具合を設定しておく
		listener->SetDopplerFactor(100,DS3D_IMMEDIATE);

		//メンバの初期化
		soundBuffer->GetPan(&pan);
		soundBuffer->GetVolume(&volume);


		//後始末
		SafeDelete(wavData);
		SafeDelete(waveFmt);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	DirectSound3DAudioBuffer::DirectSound3DAudioBuffer(const DirectSound dsound, shared_ptr<char> waveData) {
		DataChunk dataChunk;
		FmtChunk fmtChunk;
		WAVEFORMATEX wfx;
		unique_ptr<WaveReader> reader = unique_ptr<WaveReader>(new WaveReader());

		//Waveデータの読み取り
		reader->ReadFromMem(waveData);
		reader->GetDataChunk(&dataChunk);
		reader->GetFmtChunk(&fmtChunk);

		//WAVEフォーマットのセットアップ
		memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
		wfx.wFormatTag = fmtChunk.formatTag; 
		wfx.nChannels = fmtChunk.channelNum; 
		wfx.nSamplesPerSec = fmtChunk.samplingRate; 
		wfx.nBlockAlign = fmtChunk.blockSize; 
		wfx.nAvgBytesPerSec = fmtChunk.bytesPerSec; 
		wfx.wBitsPerSample = fmtChunk.bitsRate; 

		//標準リニアPCMの確認。圧縮PCMやマルチチャンネル等は想定外。なお、3Dサウンドの音源はモノラルである必要がある
		if( wfx.wFormatTag == WAVE_FORMAT_PCM ) {
			if(wfx.nChannels > 1) {
				DebugOutput::DebugMessage("3D再生は音源がモノラルである必要があります");
				return;
			}  
		}
		else {
			DebugOutput::DebugMessage("PCMフォーマットではありません");
			return;
		}

		// DirectSoundセカンダリーバッファー作成
		DSBUFFERDESC dsbd;  
		ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		dsbd.dwSize		= sizeof(DSBUFFERDESC);
		dsbd.dwFlags	=   DSBCAPS_CTRL3D|DSBCAPS_CTRLVOLUME;
		dsbd.dwBufferBytes = dataChunk.chunkSize;
		dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
		dsbd.lpwfxFormat = &wfx;

		HRESULT hr = dsound->CreateSoundBuffer( &dsbd, &soundBuffer, NULL ); 
		if (FAILED(hr)) {
			DebugOutput::DebugMessage("DirectSoundセカンダリバッファの作成に失敗しました");
		}

		//セカンダリバッファに波形データの書き込み
		void* buffer = NULL;
		ulong bufferSize=0;
		soundBuffer->Lock( 0, dataChunk.chunkSize, &buffer, &bufferSize, NULL, NULL, 0); 
		{
			memcpy(buffer, dataChunk.waveData, dataChunk.chunkSize);
		}
		soundBuffer->Unlock( buffer, bufferSize, NULL, 0 );



		//DirectSound3DBufferの取得
		hr = soundBuffer->QueryInterface(IID_IDirectSound3DBuffer8, reinterpret_cast<void**>(&sound3DBuffer));
		if(FAILED(hr)){
			DebugOutput::DebugMessage("IDirectSoundBuffer8の取得に失敗しました");
		}

		//音源位置の設定
		SetPos(0.f, 0.f, 0.f);

		//最小距離と最大距離の設定
		SetMinDistance(15.0f);
		SetMaxDistance(20.0f);

		//パン・ボリュームの設定
		soundBuffer->GetPan(&pan);
		soundBuffer->GetVolume(&volume);
	}
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSound3DAudioBuffer::~DirectSound3DAudioBuffer() {
		SafeRelease(soundBuffer);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::Play() {
		if (soundBuffer == NULL) return;
		if (IsPause()) return;

		HRESULT hr = soundBuffer->Play(0, 0, IsLooping() ? DSBPLAY_LOOPING : NULL);
		if (hr == DSERR_BUFFERLOST) {
			soundBuffer->Restore();
		}

		/*
		* IDirectSoundBuffer8のGetStatusは、ドライバあるいはデバイスによってはうそをつくことがあるので、
		* 使わないことにする。代わりに、IAudioBuffer::playingを再生・停止ごとに設定することで対処
		* どないやねん
		*long status;
		*soundBuffer->GetStatus(&status);
		*/
		SetPlaying(true);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::Stop() {
		if (soundBuffer == NULL) return;
		if (IsPause()) return;

		soundBuffer->Stop();
		SetPlaying(false);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::Resume() {
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
	void DirectSound3DAudioBuffer::Reset() {
		if (soundBuffer == NULL ) return;
		if (IsPause()) return;
		if (IsPlaying()) {
			soundBuffer->Stop();
		}
		soundBuffer->SetCurrentPosition(0);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetPan(int pan_) {
		pan = pan_;
		soundBuffer->SetPan(pan_);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetVolume(int v) {
		if (v > 100) { v = 100;}
		else if (v < 0) {v=0;}

		volume = v;
		soundBuffer->SetVolume(v*100 + DSBVOLUME_MIN);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetPos(float x, float y, float z) {
		sound3DBuffer->SetPosition(x, y, z, DS3D_IMMEDIATE);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetMinDistance(float min) {
		sound3DBuffer->SetMinDistance(min, DS3D_IMMEDIATE);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetMaxDistance(float max) {
		sound3DBuffer->SetMaxDistance(max, DS3D_IMMEDIATE);
	}
}