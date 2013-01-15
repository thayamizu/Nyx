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

namespace Nyx {
	
	//-----------------------------------------------------------------------------
	// �R���X�g���N�^
	Win32Thread::Win32Thread(void * fp,  void* param, ulong stackSize, ulong flag) {
		thread = CreateThread(NULL, stackSize, 
			static_cast<LPTHREAD_START_ROUTINE>(fp), param, flag, &id);
	}


	//-----------------------------------------------------------------------------
	// �f�X�g���N�^
	Win32Thread::~Win32Thread() {
		CloseHandle(thread);
	}

	//-----------------------------------------------------------------------------
	// �X���b�h�̃��W���[��
	ulong Win32Thread::Resume() {
		return ResumeThread(thread);
	}

	//-----------------------------------------------------------------------------
	// �X���b�h�̃T�X�y���h
	ulong Win32Thread::Suspend() {
		return SuspendThread(thread);
	}

	//-----------------------------------------------------------------------------
	// ID�̎擾
	ulong Win32Thread::GetID() {
		return id; 
	}

	//-----------------------------------------------------------------------------
	// �D�揇�ʂ̎擾
	int Win32Thread::GetPriority() { 
		return GetThreadPriority(thread); 
	}

	//-----------------------------------------------------------------------------
	// �D�揇�ʂ̐ݒ�
	void Win32Thread::SetPriority(int priority) { 
		SetThreadPriority(thread, priority); 
	}

	//-----------------------------------------------------------------------------
	// �I���̑ҋ@
	bool Win32Thread::Join(ulong millisecond) {
		return WaitForSingleObject(thread, millisecond) == WAIT_OBJECT_0;
	}

	//-----------------------------------------------------------------------------
	// �I���R�[�h�̎擾
	ulong Win32Thread::GetExitCode() { 
		ulong res; 
		GetExitCodeThread(thread, &res); 

		return res; 
	}

	//-----------------------------------------------------------------------------
	// �n���h���̎擾
	HANDLE Win32Thread::GetHandle() {
		return thread;
	}

	//-----------------------------------------------------------------------------
	// �X���[�v
	void Win32Thread::Sleep(ulong time) {
		::Sleep(time);
	}   

}