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
#ifndef NYX_CORE_INCLUDED_AUDIO_CACHE_H_
#define NYX_CORE_INCLUDED_AUDIO_CACHE_H_
#include "Utility/NonCopyable.h"

namespace nyx
{
	class iaudio_buffer;
	struct audio_effect_desc;
	///オーディオキャッシュ
	class audio_cache : noncopyable {
	public:
		/**
		* デフォルトコンストラクタ
		*/
		explicit audio_cache();


		/**
		* コンストラクタ
		* @param size_t キャッシュサイズ
		*/
		explicit audio_cache(size_t cacheSize);


		/**
		* 添字演算子
		* @param const std::wstring& ファイル名
		* @return std::shared_ptr<IAudioBuffer> オーディオバッファ
		*/
		std::shared_ptr<iaudio_buffer> operator[](const std::wstring& fileName);


		/**
		* キャッシュにバッファを追加します
		* @param const std::wstring& ファイル名
		* @param std::shared_ptr<IAudioBuffer> オーディオバッファ
		*/
		void add(const std::wstring& fileName, std::shared_ptr<iaudio_buffer> audioBuffer);


		/**
		* キャシュからバッファを削除します
		* @param const std::wstring& ファイル名
		* @param std::shared_ptr<IAudioBuffer> オーディオバッファ
		*/
		void remove(const std::wstring& fileName);


		/**
		* キャシュをクリアします
		*/
		void clear();
		
		
		/**
		* 指定したオーディオバッファを再生します
		* @param const std::wstring& ファイル名
		*/
		void play(const std::wstring& fileName, bool isLoop=true);


		/**
		* 全てのオーディオバッファを再生します
		*/
		void play_all(bool isLoop=true);
		
		
		/**
		* 指定したオーディオバッファを停止します
		* @param const std::wstring& ファイル名
		*/
		void stop(const std::wstring& fileName);
		
		
		/**
		* 全てのオーディオバッファを停止します
		*/
		void stop_all();

		/**
		* 指定したオーディオバッファをレジュームします
		*/
		void resume(const std::wstring& fileName);
		
		
		/**
		* 全てのオーディオバッファをレジュームします
		*/
		void resume_all();
		
		
		/**
		* 指定したオーディオバッファを一時停止します
		*/
		void reset(const std::wstring& fileName);
		
		
		/**
		* 全てのオーディオバッファを一時停止します
		*/
		void reset_all();
		

		/**
		* 指定したオーディオバッファにエフェクトを設定します
		* @param const std::wstring& ファイル名
		* @param const const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void set_effect(const std::wstring& fileName, const audio_effect_desc& effectDesc);


		/**
		* 全てのオーディオバッファにエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void set_effect_all(const audio_effect_desc& effectDesc);


		/**
		* 指定したオーディオバッファのエフェクトを削除します
		* @param const std::wstring& ファイル名
		*/
		void reset_effect(const std::wstring& fileName);


		/**
		* 全てのオーディオバッファのエフェクトを削除します
		*/
		void reset_effect_all();

		
		/**
		* 指定したオーディオバッファを取得します
		* @param const std::wstring& ファイル名
		* @return const std::shared_ptr<IAudioBffer>& オーディオaバッファ
		*/
		const std::shared_ptr<iaudio_buffer> get_audio_buffer(const std::wstring& fileName);
	private :
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}


#endif