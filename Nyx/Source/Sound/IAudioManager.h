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
#ifndef NYX_CORE_INCLUDED_IAUDIO_MANAGER_H_
#define NYX_CORE_INCLUDED_IAUDIO_MANAGER_H_
#include "AudioUtility.h"

namespace nyx {
	//前方宣言
	class iaudio_listener;
	class audio_cache;

	///オーディオマネージャインタフェース
	class iaudio_manager {
	public:
		/**
		* デストラクタ
		*/
		virtual ~iaudio_manager() {}


		/**
		* オーディオマネージャの初期化します
		* const AudioDesc& オーディオ初期化記述子
		*/
		virtual void initialize(const audio_desc& desc) = 0;


		/**
		* オーディオバッファを生成します
		* @param const std::wstring& ファイル名
		* @param AudioBufferDesc バッファタイプ
		* @return std::shared_ptr<AudioBuffer> オーディオバッファ
		*/
		virtual std::shared_ptr<iaudio_buffer> create_audio_buffer(const std::wstring& fileName, const audio_buffer_desc& bufferDesc) = 0;


		/**
		* オーディオリスナーを生成します
		* @return std::shared_ptr<IAudioListener> 
		*/
		virtual std::shared_ptr<iaudio_listener> create_audio_listener() = 0;	


		/**
		* オーディオデータををロードします
		* @param const std::wstring& ファイル名
		* @param SoundBufferType バッファタイプ
		* @param std::int& index 読み込んできたオーディオの管理番号
		*/
		virtual std::shared_ptr<audio_cache> load_audio(const std::wstring& fileName, const audio_buffer_desc& desc) = 0;
	};
}
#endif