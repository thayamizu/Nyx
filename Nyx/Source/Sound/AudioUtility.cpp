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
#include "AudioUtility.h"
#include "WaveFileHeader.h"

namespace nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	long volume_to_decibel(long volume) {
		volume  = math::clamp(volume, 1L, 100L);
		return static_cast<long>(33.2f * math::log10((float)volume/100) * 100);
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	long decibel_to_volume(long decibel) {
		decibel = math::clamp(decibel, -10000L, 10000L);
		if (decibel <= -10000L) {
			return 0L;
		}
		if (decibel >= 10000L ) {
			return 100L;
		}
		

		return static_cast<long>(math::power(10, (float)(decibel / 33.2/100)) * 100);
	}

	
	//-------------------------------------------------------------------------------------------------------
	//
	void build_wav_format_ex(WAVEFORMATEX* wfx, const wav_file_header& waveHeader){
		//Waveフォーマットのセットアップ
		ZeroMemory(wfx, sizeof(WAVEFORMATEX));
		wfx->wFormatTag      = waveHeader.formatChunk.formatTag;
		wfx->nChannels       = waveHeader.formatChunk.channelNum;
		wfx->wBitsPerSample  = waveHeader.formatChunk.bitsRate;
		wfx->nSamplesPerSec  = waveHeader.formatChunk.samplingRate;
		wfx->nBlockAlign     = waveHeader.formatChunk.blockSize;
		wfx->nAvgBytesPerSec = waveHeader.formatChunk.bytesPerSec;
		wfx->cbSize          = sizeof(WAVEFORMATEX);
	}
}