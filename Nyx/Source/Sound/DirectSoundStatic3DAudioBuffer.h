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
#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STATIC_3DAUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STATIC_3DAUDIO_BUFFER_H_
#include "DirectSoundDefinition.h"
#include "DirectSound3DAudioBuffer.h"

namespace nyx {
	struct AudioBuffeDesc;
	class sound_reader;

	///静的3Dバッファ
	class dsound_static_3d_audio_buffer : public dsound_3d_audio_buffer {
	public:
		/**
		* コンストラクタ
		* @param const AudioBufferDesc& bufferDesc
		* @param const DirectSoundPtr 
		* @param const std::wstring& fileName
		*/
		dsound_static_3d_audio_buffer(const audio_buffer_desc& bufferDesc, const dsound_ptr dsound, const std::shared_ptr<sound_reader> reader);


		/**
		* オーディオバッファの状態の取得します
		* @return BufferType
		*/
		AUDIO_BUFFER_TYPE get_buffer_type() const;
	private:
		/**
		* DirectSoundのセカンダリバッファにwaveデータを書き込みます
		* @param size_t バッファサイズ
		*/
		void write_wave_data();


		/**
		* 静的なDirectSoundセカンダリバッファ記述子を作成します
		* @param DSBUFFERDESC*
		* @param WAVEFORMATEX& wfx
		*/
		void build_dsound_buffer_desc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx);
	private:
		audio_buffer_desc bufferDesc_;
		std::shared_ptr<sound_reader> waveReader_;
	};
}
#endif