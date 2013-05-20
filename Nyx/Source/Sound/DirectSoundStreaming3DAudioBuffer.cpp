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
#include "DirectSoundStreaming3DAudioBuffer.h"
namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStreaming3DAudioBuffer::DirectSoundStreaming3DAudioBuffer(
		const AudioBufferDesc& bufferDesc, 
		const DirectSoundPtr dsound, const std::wstring& fileName)
		: DirectSound3DAudioBuffer(), waveReader_(new WaveReader(fileName)), bufferDesc_(bufferDesc), offset_(0){

			//バッファを作成

			bufferDesc_.waveFormat = waveReader_->ReadHeader();

			//バッファに再生データを書き込む
			const ulong samplingRate = bufferDesc_.waveFormat.formatChunk.samplingRate;   
			const ulong blockAlign   = bufferDesc_.waveFormat.formatChunk.blockSize;  
			const ulong size         = samplingRate * 2 * blockAlign / NotifyEventNum;   
			notifySize_  = size;

			Load(bufferDesc_, dsound, fileName);
			Create3DBuffer();
			WriteWaveData(notifySize_);

			//通知スレッドの生成
			notifyThreadHandle_ = CreateThread( NULL,0, Notify3DBufferProc, (void*)this, 0, 0);

			//通知イベントの設定
			LPDIRECTSOUNDNOTIFY notify;
			DSBPOSITIONNOTIFY  positionNotify[NotifyEventNum] = {};
			HRESULT hr = GetHandle()->QueryInterface(IID_IDirectSoundNotify, reinterpret_cast<void**>(&notify));
			if ( FAILED(hr)) {
				DebugOutput::Trace("IDirectSoundNotifyの取得に失敗しました。", hr);
				throw COMException("IDirectSoundNotifyの取得に失敗しました。", hr);
			}

			// イベントとシグナルになる位置を取得
			for( int i = 0 ; i < NotifyEventNum ; i++ ) {
				notifyEventList_[i] = CreateEvent(NULL, false, false, NULL);
				positionNotify[i].dwOffset     = (notifySize_ * i) + notifySize_-1; 
				positionNotify[i].hEventNotify = notifyEventList_[i];
			}

			// イベントをセット
			hr = notify->SetNotificationPositions(NotifyEventNum, positionNotify);
			if( FAILED(hr)) {
				DebugOutput::Trace("IDirectSoundNotify通知イベントの設定が失敗しました。", hr);
				throw COMException("IDirectSoundNotify通知イベントの設定が失敗しました。", hr);
			}

			SafeRelease(notify);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStreaming3DAudioBuffer::~DirectSoundStreaming3DAudioBuffer() {
		for (auto var : notifyEventList_) {
			CloseHandle(var);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioUtility::BufferType DirectSoundStreaming3DAudioBuffer::GetBufferType() const {
		return AudioUtility::BufferType_Streaming3DAudioBuffer;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStreaming3DAudioBuffer::WriteWaveData(size_t bufferSize){
		const auto handle = GetHandle();
		const auto size   = bufferDesc_.waveFormat.dataChunk.chunkSize;
		
		if (size <= offset_ + notifySize_) {
			offset_ = 0;
			waveReader_->SetCursor(0);
		}

		//バッファをロック
		void* readData1 = nullptr;
		void* readData2 = nullptr;
		ulong readSize1  = 0;
		ulong readSize2  = 0;
		HRESULT hr = handle->Lock(0, notifySize_, &readData1, &readSize1, &readData2, &readSize2, DSBLOCK_FROMWRITECURSOR);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのロックに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのロックに失敗しました。", hr);
		}

		//バッファに書き込み
		ulong readBytes;
		const auto buffer = waveReader_->Read(readSize1, &readBytes);
		CopyMemory(readData1, buffer.get(), readBytes);
		offset_ += readSize1;
		if (readData2 != nullptr) {
			const auto buffer = waveReader_->Read(readSize2, &readBytes);
			CopyMemory(readData2, buffer.get(), readBytes);
			offset_ += readSize2;
		}
		
		//バッファをアンロック
		hr = handle->Unlock(readData1, readSize1, readData2, readSize2);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのアンロックに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのアンロックに失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStreaming3DAudioBuffer::BuildDirectSoundBufferDesc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx){
		//フラグの設定
		DWORD flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D |  DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2;

		//フォーカスモードの設定
		if ( bufferDesc_.focusType == AudioUtility::FocusType_GlobalFocus) {
			flag |= DSBCAPS_GLOBALFOCUS;
		}
		else {
			flag |= DSBCAPS_STICKYFOCUS;

		}

		//DSBufferDescのセットアップ
		ZeroMemory(dsBufferDesc, sizeof(DSBUFFERDESC));
		dsBufferDesc->lpwfxFormat     = &wfx;
		dsBufferDesc->dwBufferBytes   = notifySize_ * NotifyEventNum;
		dsBufferDesc->dwFlags         = flag;
		dsBufferDesc->dwSize          = sizeof(DSBUFFERDESC);
		dsBufferDesc->guid3DAlgorithm = bufferDesc_.algorithm;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	ulong _stdcall Notify3DBufferProc(void* parameter) {
		Assert(parameter != nullptr)
		auto audio = reinterpret_cast<DirectSoundStreaming3DAudioBuffer*>(parameter);
		audio->NotifyThread();
		return 0L;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStreaming3DAudioBuffer::NotifyThread() {
		bool isDone = false;
		while( !isDone ) { 
			ulong signal = MsgWaitForMultipleObjects(NotifyEventNum, notifyEventList_, 
				FALSE, INFINITE, QS_ALLEVENTS );

			switch( signal ) {
			case WAIT_OBJECT_0: 
				std::cout <<"バッファ書き込み1" << std::endl;
				WriteWaveData(0);
				break;
			case WAIT_OBJECT_0+1:
				std::cout <<"バッファ書き込み2" << std::endl;
				WriteWaveData(0);
				break;
			case WAIT_OBJECT_0+2:
				std::cout <<"バッファ書き込み3" << std::endl;
				WriteWaveData(0);
			break;
			case WAIT_OBJECT_0+3:
				std::cout <<"バッファ書き込み4" << std::endl;
				WriteWaveData(0);
				break;
			case WAIT_OBJECT_0+NotifyEventNum:
				std::cout <<"バッファ書き込み5" << std::endl;

				MSG msg;
				while( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
					if( msg.message == WM_QUIT ){
				std::cout <<"バッファ書き込み6" << std::endl;
						isDone=true;
					}
				}
				break;
			}
		}
	}
}