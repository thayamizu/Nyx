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
#include "Thread/Thread.h"
#include "Thread/detail/Win32/Win32Thread.h"

namespace nyx {
	
	//-----------------------------------------------------------------------------
	// �R���X�g���N�^
	win32_thread::win32_thread(void * fp,  void* param, uint64_t stackSize, uint64_t flag) {
		thread = CreateThread(NULL, stackSize, 
			static_cast<LPTHREAD_START_ROUTINE>(fp), param, flag, &id);
	}


	//-----------------------------------------------------------------------------
	// �f�X�g���N�^
	win32_thread::~win32_thread() {
		CloseHandle(thread);
	}

	//-----------------------------------------------------------------------------
	// �X���b�h�̃��W���[��
	uint64_t win32_thread::resume() {
		return ResumeThread(thread);
	}

	//-----------------------------------------------------------------------------
	// �X���b�h�̃T�X�y���h
	uint64_t win32_thread::suspend() {
		return SuspendThread(thread);
	}

	//-----------------------------------------------------------------------------
	// ID�̎擾
	uint64_t win32_thread::get_id() {
		return id; 
	}

	//-----------------------------------------------------------------------------
	// �D�揇�ʂ̎擾
	int win32_thread::get_priority() { 
		return GetThreadPriority(thread); 
	}

	//-----------------------------------------------------------------------------
	// �D�揇�ʂ̐ݒ�
	void win32_thread::set_priority(int priority) { 
		SetThreadPriority(thread, priority); 
	}

	//-----------------------------------------------------------------------------
	// �I���̑ҋ@
	bool win32_thread::join(uint64_t millisecond) {
		return WaitForSingleObject(thread, millisecond) == WAIT_OBJECT_0;
	}

	//-----------------------------------------------------------------------------
	// �I���R�[�h�̎擾
	uint64_t win32_thread::get_exit_code() { 
		uint64_t res; 
		GetExitCodeThread(thread, &res); 

		return res; 
	}

	//-----------------------------------------------------------------------------
	// �n���h���̎擾
	HANDLE win32_thread::get_handle() {
		return thread;
	}

	//-----------------------------------------------------------------------------
	// �X���[�v
	void win32_thread::sleep(uint64_t time) {
		::Sleep(time);
	}   

}