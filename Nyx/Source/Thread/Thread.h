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
#ifndef NYX_CORE_INCLUDED_THREAD_H_
#define NYX_CORE_INCLUDED_THREAD_H_
#include "Utility/Type.h"
#include "Utility/NonCopyable.h"

namespace nyx
{
	typedef HANDLE thread_handle;

	/// スレッドクラス
	NYX_DEPRECATED class thread : private noncopyable
	{
	public:

		/**
		* コンストラクタ
		* @remarks
		* 第一引数の void *fpは、PTHREAD_START_ROUTINEと一致するようにしてください
		* @param 関数ポインタ
		* @param 引数へのポインタ
		* @param スタックサイズ
		* @param 起動時に、スレッドを起動するか
		*/
		explicit  thread(void * fp,  void* param, uint64_t stackSize=0, uint64_t flag=0);

		/**
		* デストラクタ
		*/
		virtual ~thread();

		/** 
		* スレッドのレジューム
		* @return 以前のサスペンドカウント 失敗すると0xffffffff
		*/
		uint64_t resume();


		/** 
		* スレッドのサスペンド
		* @return 以前のサスペンドカウント 失敗すると0xffffffff
		*/
		uint64_t suspend();

		/** 
		* IDの取得
		* @return スレッドID
		*/
		uint64_t get_thread_id();

		/**
		* 優先順位の取得
		* @return int スレッドの相対的優先順位（定数）
		*/
		int get_priority(); 

		/**
		* 優先順位の設定
		* @param int スレッドの相対的優先順位
		*/
		void set_priority(uint32_t priority) ;

		/**
		* 終了の待機
		* @param ulong ミリセコンド 
		*/
		bool join(uint64_t millisecond=INFINITE);

		/**
		* 終了コードの取得
		* @return 終了コード
		*/
		uint64_t get_exit_code();

		/**
		* スレッドのハンドルを返します
		* @return HANDLE スレッドのハンドル
		*/
		thread_handle get_handle();

		/**
		* ＣＰＵをスリープ
		* @param ulong スリープ時間(ミリ秒単位)
		*/
		static void sleep(uint64_t time);

	private:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};

}


#endif
//THREAD_H_