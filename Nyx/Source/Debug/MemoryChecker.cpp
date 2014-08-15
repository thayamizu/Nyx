/*  The MIT License
	*
	* Copyright (c)2010 -  t.hayamizu
	*
	*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F*�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
	*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
	*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
	*
	*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
	*
	*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
	*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
	*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
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
				debug_out::get_logger()->printfln("�������[���[�N");
				debug_out::get_logger()->print_thin_line();
				_CrtMemDumpAllObjectsSince(&diff);
				debug_out::get_logger()->print_thin_line();
				_CrtMemDumpStatistics(&diff);
				debug_out::get_logger()->print_thin_line();
				debug_out::get_logger()->printfln("�������[���[�N");
				debug_out::get_logger()->print_thick_line();

				return true;
			}


			return false;
		}
}