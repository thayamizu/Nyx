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

		//Waveデータの読み取り
		reader->ReadFromFile(fileName);
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

		// DirectSoundセカンダリーバッファー作成
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

	}
	DirectSoundAudioBuffer::DirectSoundAudioBuffer(const DirectSound dsound, shared_ptr<char> waveData) {
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

		// DirectSoundセカンダリーバッファー作成
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
			DebugOutput::DebugMessage("DirectSoundセカンダリバッファの作成に失敗しました");
		}

		void* buffer = NULL;
		ulong bufferSize=0;
		//セカンダリバッファに波形データの書き込み
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
			soundBuffer->Restore();//メモリ復元(内容は復元されない)
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