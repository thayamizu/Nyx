/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェ*ア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/

#ifndef NYX_CORE_INCLUDED_MEMORY_CHECKER_H_
#define NYX_CORE_INCLUDED_MEMORY_CHECKER_H_

#ifdef _DEBUG
// crtdbg.h をインクルードしたあとに _CRTDBG_MAP_ALLOC を定義してやる
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new  ::new(_CLIENT_BLOCK, __FILE__, __LINE__)

namespace nyx {
	///メモリの状態
	typedef ::_CrtMemState memory_state;

	///メモリチェッカー
	class memory_checker {
	public:
		/**
		* メモリチェッカーの初期化
		* @return 成功ならtrue
		*/
		static bool initialize();

		/**
		* メモリ状態を取得する
		* @return MemoryState
		*/
		static memory_state get_memory_state();

		/**
		*　メモリの詳細ダンプを実行する
		*/
		static void dump_detail();

		/*
		*　メモリの差分詳細ダンプを実行する
		* @param MemoryState& メモリ状態
		*/
		static void dump_detail(const memory_state& old);


		/*
		*　メモリの統計ダンプを実行する
		*/
		static void dump_statics();

		/*
		*　メモリの差分統計ダンプを実行する
		* @param const MemoryState メモリ状態
		*/
		static void dump_statics(const memory_state& old);


		/*
		*　メモリリークをチェックする
		* @param const MemoryState& メモリ状態
		*/
		static bool leak_check(const memory_state& state );

	private:
		memory_checker(){}//生成禁止
		static bool initialized;///< 初期済みかどうか
	};
}
#else 
//リリース時は、メモリチェッカーを切る
namespace nyx {
	typedef ::_CrtMemState memory_state;

	class memory_checker {
	public:

		static bool initialize();

		static memory_state get_memory_state();

		static void dump_detail();
		static void dump_detail(const memory_state& old);

		static void dump_statics();
		static void dump_statics(const memory_state& old);

		static bool leak_check(const memory_state& state );

	private:
		memory_checker(){}//生成禁止
		static bool initialized;
	};

}
#endif

#endif
