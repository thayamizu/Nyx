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
	struct thread::PImpl
	{
			PImpl(void * fp,  void* param, uint64_t stackSize, uint64_t flag)
				:thread(new win32_thread(fp, param, stackSize, flag))
			{}
			std::unique_ptr<win32_thread> thread;
	};

	//-----------------------------------------------------------------------------
	// �R���X�g���N�^
	thread::thread(void * fp,  void* param, uint64_t stackSize, uint64_t flag) 
		:pimpl_(new PImpl(fp, param, stackSize, flag))
	{
	}


	//-----------------------------------------------------------------------------
	// �f�X�g���N�^
	thread::~thread() {
	}

	//-----------------------------------------------------------------------------
	// �X���b�h�̃��W���[��
	uint64_t thread::resume() {
		return pimpl_->thread->resume();
	}

	//-----------------------------------------------------------------------------
	// �X���b�h�̃T�X�y���h
	uint64_t thread::suspend() {
		return pimpl_->thread->suspend();
	}

	//-----------------------------------------------------------------------------
	// ID�̎擾
	uint64_t thread::get_thread_id() {
		return pimpl_->thread->get_id();
	}

	//-----------------------------------------------------------------------------
	// �D�揇�ʂ̎擾
	int thread::get_priority() { 
		return pimpl_->thread->get_priority();
	}

	//-----------------------------------------------------------------------------
	// �D�揇�ʂ̐ݒ�
	void thread::set_priority(uint32_t priority) { 
		return pimpl_->thread->set_priority(priority);
	}

	//-----------------------------------------------------------------------------
	// �I���̑ҋ@
	bool thread::join(uint64_t millisecond) {
		return pimpl_->thread->join(millisecond);
	}

	//-----------------------------------------------------------------------------
	// �I���R�[�h�̎擾
	uint64_t thread::get_exit_code() { 
		return pimpl_->thread->get_exit_code();
	}

	//-----------------------------------------------------------------------------
	// �n���h���̎擾
	thread_handle thread::get_handle() {
		return pimpl_->thread->get_handle();
	}

	//-----------------------------------------------------------------------------
	// �X���[�v
	void thread::sleep(uint64_t time) {
		using nyx::win32_thread;
		::Sleep(time);	
	}   

}