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
#include "AudioUtility.h"
#include "DirectSoundAudioBuffer.h"
#include "DirectSoundStaticAudioBuffer.h"
#include "WaveReader.h"
namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStaticAudioBuffer::DirectSoundStaticAudioBuffer(
		const AudioBufferDesc& bufferDesc, 
		const DirectSoundPtr dsound, const std::wstring& fileName)
		: DirectSoundStereoAudioBuffer(), waveReader_(new WaveReader(fileName)), bufferDesc_(bufferDesc){

			bufferDesc_.waveFormat = waveReader_->ReadHeader();

			Load(bufferDesc_, dsound);

			WriteWaveData();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioUtility::BufferType DirectSoundStaticAudioBuffer::GetBufferType() const {
		return AudioUtility::BufferType_StaticAudioBuffer;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::WriteWaveData(){
		//バッファに波形データの書き込み
		void* waveData  = nullptr;
		ulong waveSize  = 0;
		HRESULT hr = GetHandle()->Lock(0, 0, &waveData, &waveSize, NULL, NULL, DSBLOCK_ENTIREBUFFER);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのロックに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのロックに失敗しました。", hr);
		}
		
		ulong readBytes;
		auto buffer= waveReader_->Read(waveSize, &readBytes);
		CopyMemory(waveData, buffer.get(), readBytes);

		hr = GetHandle()->Unlock(waveData, waveSize, NULL, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのアンロックに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのアンロックに失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::BuildDirectSoundBufferDesc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx){
		Assert(waveReader_ != nullptr);
		const auto waveHeader = waveReader_->ReadHeader();

		//フラグの設定
		DWORD flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;

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
		dsBufferDesc->dwBufferBytes   = waveHeader.dataChunk.chunkSize;
		dsBufferDesc->dwFlags         = flag;
		dsBufferDesc->dwSize          = sizeof(DSBUFFERDESC);
		dsBufferDesc->guid3DAlgorithm = bufferDesc_.algorithm;
	}
}