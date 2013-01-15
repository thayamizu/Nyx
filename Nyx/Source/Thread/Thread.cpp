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
	struct Thread::PImpl
	{
			PImpl(void * fp,  void* param, ulong stackSize, ulong flag)
				:thread(new Win32Thread(fp, param, stackSize, flag))
			{}
			std::unique_ptr<Win32Thread> thread;
	};

	//-----------------------------------------------------------------------------
	// �R���X�g���N�^
	Thread::Thread(void * fp,  void* param, ulong stackSize, ulong flag) 
		:pimpl_(new PImpl(fp, param, stackSize, flag))
	{
	}


	//-----------------------------------------------------------------------------
	// �f�X�g���N�^
	Thread::~Thread() {
	}

	//-----------------------------------------------------------------------------
	// �X���b�h�̃��W���[��
	ulong Thread::Resume() {
		return pimpl_->thread->Resume();
	}

	//-----------------------------------------------------------------------------
	// �X���b�h�̃T�X�y���h
	ulong Thread::Suspend() {
		return pimpl_->thread->Suspend();
	}

	//-----------------------------------------------------------------------------
	// ID�̎擾
	ulong Thread::GetID() {
		return pimpl_->thread->GetID();
	}

	//-----------------------------------------------------------------------------
	// �D�揇�ʂ̎擾
	int Thread::GetPriority() { 
		return pimpl_->thread->GetPriority();
	}

	//-----------------------------------------------------------------------------
	// �D�揇�ʂ̐ݒ�
	void Thread::SetPriority(int priority) { 
		return pimpl_->thread->SetPriority(priority);
	}

	//-----------------------------------------------------------------------------
	// �I���̑ҋ@
	bool Thread::Join(ulong millisecond) {
		return pimpl_->thread->Join(millisecond);
	}

	//-----------------------------------------------------------------------------
	// �I���R�[�h�̎擾
	ulong Thread::GetExitCode() { 
		return pimpl_->thread->GetExitCode();
	}

	//-----------------------------------------------------------------------------
	// �n���h���̎擾
	HANDLE Thread::GetHandle() {
		return pimpl_->thread->GetHandle();
	}

	//-----------------------------------------------------------------------------
	// �X���[�v
	void Thread::Sleep(ulong time) {
		using Nyx::Win32Thread;
		::Sleep(time);
		
	}   

}