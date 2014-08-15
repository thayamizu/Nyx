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
#include "AudioUtility.h"
#include "WaveReader.h"
#include "SoundReader.h"
#include "DirectSoundStatic3DAudioBuffer.h"

namespace nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	dsound_static_3d_audio_buffer::dsound_static_3d_audio_buffer(
		const audio_buffer_desc& bufferDesc, 
		const dsound_ptr dsound, const std::shared_ptr<sound_reader> reader)
		: dsound_3d_audio_buffer(), waveReader_(reader), bufferDesc_(bufferDesc){

			bufferDesc_.waveFormat = waveReader_->read_header();

			load(bufferDesc_, dsound);
			create_3d_buffer();
			write_wave_data();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AUDIO_BUFFER_TYPE dsound_static_3d_audio_buffer::get_buffer_type() const {
		return AUDIO_BUFFER_TYPE_STATIC_3D;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_static_3d_audio_buffer::write_wave_data(){
		//バッファに波形データの書き込み
		void* waveData  = nullptr;
		uint64_t waveSize  = 0;
		HRESULT hr = get_handle()->Lock(0, 0, &waveData, &waveSize, NULL, NULL, DSBLOCK_ENTIREBUFFER);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファのロックに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファのロックに失敗しました。", hr);
		}
		
		uint64_t readBytes;
		auto buffer= waveReader_->read(waveSize, &readBytes);
		CopyMemory(waveData, buffer.get(), readBytes);

		hr = get_handle()->Unlock(waveData, waveSize, NULL, NULL);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファのアンロックに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファのアンロックに失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_static_3d_audio_buffer::build_dsound_buffer_desc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx){
		NYX_ASSERT(waveReader_ != nullptr);
		const auto waveHeader = waveReader_->read_header();

		//フラグの設定
		DWORD flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_CTRLFREQUENCY;

		//フォーカスモードの設定
		if ( bufferDesc_.focusType == FOCUS_TYPE_GLOBAL) {
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