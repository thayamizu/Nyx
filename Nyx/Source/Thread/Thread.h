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
#include "Object/NonCopyable.h"

namespace Nyx
{
	/// スレッドクラス
	DEPRECATED class Thread : private NonCopyable
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
		explicit  Thread(void * fp,  void* param, ulong stackSize=0, ulong flag=0);

		/**
		* デストラクタ
		*/
		virtual ~Thread();

		/** 
		* スレッドのレジューム
		* @return 以前のサスペンドカウント 失敗すると0xffffffff
		*/
		ulong Resume();


		/** 
		* スレッドのサスペンド
		* @return 以前のサスペンドカウント 失敗すると0xffffffff
		*/
		ulong Suspend();

		/** 
		* IDの取得
		* @return スレッドID
		*/
		ulong GetID();

		/**
		* 優先順位の取得
		* @return int スレッドの相対的優先順位（定数）
		*/
		int GetPriority(); 

		/**
		* 優先順位の設定
		* @param int スレッドの相対的優先順位
		*/
		void SetPriority(int priority) ;

		/**
		* 終了の待機
		* @param ulong ミリセコンド 
		*/
		bool Join(ulong millisecond=INFINITE);

		/**
		* 終了コードの取得
		* @return 終了コード
		*/
		ulong GetExitCode();

		/**
		* スレッドのハンドルを返します
		* @return HANDLE スレッドのハンドル
		*/
		HANDLE GetHandle();

		/**
		* ＣＰＵをスリープ
		* @param ulong スリープ時間(ミリ秒単位)
		*/
		static void Sleep(ulong time);

	private:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};

}


#endif
//THREAD_H_