/*  The MIT License
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
#include "PCH/PCH.h"
#include "Debug/DebugOutput.h"
#include "Debug/MemoryChecker.h"

namespace nyx {
	//----------------------------------------------------------------------------------------------
	//
	bool memory_checker::initialized = false;

	//----------------------------------------------------------------------------------------------
	//
	bool memory_checker::initialize() {
		if (initialized) {
			return initialized;
		}

		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

		initialized = true;
		return initialized;
	}

	//----------------------------------------------------------------------------------------------
	//
	memory_state memory_checker::get_memory_state() {
		memory_state state = {};
		_CrtMemCheckpoint(&state);
		return state;
	}

	//----------------------------------------------------------------------------------------------
	//
	void memory_checker::dump_detail() {
		_CrtMemDumpAllObjectsSince(NULL);
	}

	//----------------------------------------------------------------------------------------------
	//
	void memory_checker::dump_detail(const memory_state& old) {
		_CrtMemDumpAllObjectsSince(&old);
	}

	//----------------------------------------------------------------------------------------------
	//
	void memory_checker::dump_statics() {
		memory_state state;
		_CrtMemCheckpoint(&state);
		_CrtMemDumpStatistics(&state);
	}

	//----------------------------------------------------------------------------------------------
	//
	void memory_checker::dump_statics(const memory_state& old) {
		memory_state now, diff;
		_CrtMemCheckpoint(&now);
		_CrtMemDifference(&diff, &old, &now);
		_CrtMemDumpStatistics(&diff);
	}

	//----------------------------------------------------------------------------------------------
	//
	bool memory_checker::leak_check(const memory_state & old) {
		memory_state now, diff;
		_CrtMemCheckpoint(&now);
		if (_CrtMemDifference(&diff, &old, &now)) {
			_CrtDumpMemoryLeaks();
			debug_out::get_logger()->print_thick_line();
			debug_out::get_logger()->printfln("メモリーリーク");
			debug_out::get_logger()->print_thin_line();
			_CrtMemDumpAllObjectsSince(&diff);
			debug_out::get_logger()->print_thin_line();
			_CrtMemDumpStatistics(&diff);
			debug_out::get_logger()->print_thin_line();
			debug_out::get_logger()->printfln("メモリーリーク");
			debug_out::get_logger()->print_thick_line();

			return true;
		}


		return false;
	}
}