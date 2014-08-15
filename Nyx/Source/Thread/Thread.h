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
#ifndef NYX_CORE_INCLUDED_THREAD_H_
#define NYX_CORE_INCLUDED_THREAD_H_
#include "Utility/Type.h"
#include "Utility/NonCopyable.h"

namespace nyx
{
	typedef HANDLE thread_handle;

	/// �X���b�h�N���X
	NYX_DEPRECATED class thread : private noncopyable
	{
	public:

		/**
		* �R���X�g���N�^
		* @remarks
		* �������� void *fp�́APTHREAD_START_ROUTINE�ƈ�v����悤�ɂ��Ă�������
		* @param �֐��|�C���^
		* @param �����ւ̃|�C���^
		* @param �X�^�b�N�T�C�Y
		* @param �N�����ɁA�X���b�h���N�����邩
		*/
		explicit  thread(void * fp,  void* param, uint64_t stackSize=0, uint64_t flag=0);

		/**
		* �f�X�g���N�^
		*/
		virtual ~thread();

		/** 
		* �X���b�h�̃��W���[��
		* @return �ȑO�̃T�X�y���h�J�E���g ���s�����0xffffffff
		*/
		uint64_t resume();


		/** 
		* �X���b�h�̃T�X�y���h
		* @return �ȑO�̃T�X�y���h�J�E���g ���s�����0xffffffff
		*/
		uint64_t suspend();

		/** 
		* ID�̎擾
		* @return �X���b�hID
		*/
		uint64_t get_thread_id();

		/**
		* �D�揇�ʂ̎擾
		* @return int �X���b�h�̑��ΓI�D�揇�ʁi�萔�j
		*/
		int get_priority(); 

		/**
		* �D�揇�ʂ̐ݒ�
		* @param int �X���b�h�̑��ΓI�D�揇��
		*/
		void set_priority(uint32_t priority) ;

		/**
		* �I���̑ҋ@
		* @param ulong �~���Z�R���h 
		*/
		bool join(uint64_t millisecond=INFINITE);

		/**
		* �I���R�[�h�̎擾
		* @return �I���R�[�h
		*/
		uint64_t get_exit_code();

		/**
		* �X���b�h�̃n���h����Ԃ��܂�
		* @return HANDLE �X���b�h�̃n���h��
		*/
		thread_handle get_handle();

		/**
		* �b�o�t���X���[�v
		* @param ulong �X���[�v����(�~���b�P��)
		*/
		static void sleep(uint64_t time);

	private:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};

}


#endif
//THREAD_H_