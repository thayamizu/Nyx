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
#ifndef NYX_CORE_INCLUDED_FPS_TIMER_H_ 
#define NYX_CORE_INCLUDED_FPS_TIMER_H_
#include "Timer/ITimer.h"
#include "Utility/NonCopyable.h"
namespace nyx {

	///FPSタイマー
	class fps_timer : public itimer, private noncopyable {
	public:
		//------------------------------------------------------------------------
		//　公開メンバ変数
		//------------------------------------------------------------------------
		static const uint32_t FPS30;	///< 30FPS
		static const uint32_t FPS60;	///< 60FPS
	public:
		//------------------------------------------------------------------------
		//　構築・破壊
		//------------------------------------------------------------------------
		/**
		*　コンストラクタ
		*/
		fps_timer(uint64_t fps=FPS60);

		/**
		* デストラクタ 
		*/
		~fps_timer();

		//------------------------------------------------------------------------
		//　時間の取得・設定
		//------------------------------------------------------------------------
		/**
		* タイマの時刻をリセットする．
		*以降、Getを呼ぶとリセットされた時刻からの経過時間が買える
		*/
		void reset();

		/**
		* 時刻の取得
		* @return ulong
		*/
		uint64_t get();

		/**
		*タイマの時刻設定
		*@param ulong 時刻
		*/
		void set(uint64_t now);

		/*
		* タイマーをポーズする
		*@param bool ポーズするのであればtrueを指定
		*/
		void pause(bool pause);

		/**
		* ポーズ中かどうか
		* @return bool trueならポーズ
		*/
		bool is_pause();

		/**
		* ポーズ中ならタイマをリスタートさせる．そうでなければなにもしない
		*/
		void restart();

		//------------------------------------------------------------------------
		//　FPSの調整
		//------------------------------------------------------------------------
		/**
		* FPSの取得
		* @return uint FPS
		*/
		uint32_t get_fps();

		/**
		* 現在のFPSを取得
		* @param uint FPS
		*/
		uint32_t get_current_fps();

		/**
		* FPSを設定する
		*/
		void set_fps(uint32_t fps);

		/**
		* 指定したFPSになるようフレームを調整
		*/
		void wait_frame();

	private:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};
}
#endif