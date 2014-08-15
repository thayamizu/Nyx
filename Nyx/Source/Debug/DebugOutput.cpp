/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
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
#include <iostream>

using nyx::logger;
namespace nyx {
	static void trace_log(char* string) {
		debug_out::get_logger()->printfln(string);
	}

	static void trace_console(char* string) {
		::OutputDebugStringA(string);
		::OutputDebugStringA("\n");
	}

	static void trace_stderr(char* string) {
		std::cout << string << std::endl;
	}

	//----------------------------------------------------------------------------------------------
	//
	DEBUG_OUTPUT_MODE debug_out::outputMode_ = DEBUG_OUTPUT_MODE::DEBUG_OUTPUT_MODE_STDOUT;
	logger* debug_out::logger_ = NULL;

	//----------------------------------------------------------------------------------------------
	//
	logger* debug_out::get_logger() {
		if (logger_ == NULL) {
			logger_ = new logger(L"NyxDebugOut.txt");
		}
		return logger_;
	}

	//----------------------------------------------------------------------------------------------
	//
	void debug_out::trace(char* format, ...) {
		va_list list;
		va_start(list, format);
		static const int length = 1024;
		static char buffer[length];
		vsprintf_s(buffer, length, format, list);
		va_end(list);

		switch(outputMode_) {
		case DEBUG_OUTPUT_MODE::DEBUG_OUTPUT_MODE_STDOUT:
			trace_stderr(buffer);
			break;
		case DEBUG_OUTPUT_MODE::DEBUG_OUTPUT_MODE_CONSOLE:
			trace_console(buffer);
			break;
		case DEBUG_OUTPUT_MODE::DEBUG_OUTPUT_MODE_FILE:
			trace_log(buffer);
			break;
		}
	}

	//----------------------------------------------------------------------------------------------
	//
	void debug_out::set_output_mode(DEBUG_OUTPUT_MODE mode) {
		outputMode_ =  mode;
	}

	//----------------------------------------------------------------------------------------------
	//
	void debug_out::debug_messagebox(char* format, ...) {
		va_list list;
		va_start(list, format);
		static const int length = 1024;
		static char tmp[length];
		vsprintf_s(tmp, length, format, list);
		::MessageBoxA(NULL, tmp, "���f�o�b�O��", MB_OK);
		va_end(list);

	}

	//----------------------------------------------------------------------------------------------
	//
	void debug_out::delete_instance() {
		SafeDelete(logger_);
	}
}