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
#ifndef NYX_CORE_INCLUDED_AUDIO_MANAGER_H_
#define NYX_CORE_INCLUDED_AUDIO_MANAGER_H_
#include "Utility/NonCopyable.h"
#include "IAudioManager.h"

namespace nyx {
	//前方宣言
	class audio_cache;
	class iaudio_buffer;
	class iaudio_listener;
	struct audio_buffer_desc;
	struct audio_desc;
	
	///オーディオマネージャ
	class audio_manager : noncopyable, public iaudio_manager{
	public:
		/**
		 * コンストラクタ
		 */
		explicit audio_manager();


		/**
		 * コンストラクタ
		 * @param const const AudioDesc& オーディオバッファ
		 */
		explicit audio_manager(const audio_desc& desc);
		

		/**
		* オーディオマネージャの初期化
		* @return bool
		*/
		void initialize(const audio_desc& desc);
		

		/**
		* オーディオバッファを生成します
		* @param const std::wstring& ファイル名
		* @param SoundBufferType バッファタイプ
		* @return std::shared_ptr<IAudioBuffer> オーディオバッファ
		*/

		std::shared_ptr<iaudio_buffer> create_audio_buffer(const std::wstring& fileName, const audio_buffer_desc& bufferDesc);

		/**
		* オーディオリスナーを生成します
		* @return std::shared_ptr<IAudioListener> 
		*/
		std::shared_ptr<iaudio_listener> create_audio_listener();	


		/**
		* オーディオデータををロードしてきます
		* @param const std::wstring& ファイル名
		* @param SoundBufferType バッファタイプ
		* @return std::shared_ptr<AudioCache> オーディオキャッシュ
		*/
		std::shared_ptr<audio_cache> load_audio(const std::wstring& fileName,  const audio_buffer_desc& bufferDesc);
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif