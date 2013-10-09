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
#include "Object/NonCopyable.h"

namespace Nyx
{
	/// �X���b�h�N���X
	DEPRECATED class Thread : private NonCopyable
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
		explicit  Thread(void * fp,  void* param, ulong stackSize=0, ulong flag=0);

		/**
		* �f�X�g���N�^
		*/
		virtual ~Thread();

		/** 
		* �X���b�h�̃��W���[��
		* @return �ȑO�̃T�X�y���h�J�E���g ���s�����0xffffffff
		*/
		ulong Resume();


		/** 
		* �X���b�h�̃T�X�y���h
		* @return �ȑO�̃T�X�y���h�J�E���g ���s�����0xffffffff
		*/
		ulong Suspend();

		/** 
		* ID�̎擾
		* @return �X���b�hID
		*/
		ulong GetID();

		/**
		* �D�揇�ʂ̎擾
		* @return int �X���b�h�̑��ΓI�D�揇�ʁi�萔�j
		*/
		int GetPriority(); 

		/**
		* �D�揇�ʂ̐ݒ�
		* @param int �X���b�h�̑��ΓI�D�揇��
		*/
		void SetPriority(int priority) ;

		/**
		* �I���̑ҋ@
		* @param ulong �~���Z�R���h 
		*/
		bool Join(ulong millisecond=INFINITE);

		/**
		* �I���R�[�h�̎擾
		* @return �I���R�[�h
		*/
		ulong GetExitCode();

		/**
		* �X���b�h�̃n���h����Ԃ��܂�
		* @return HANDLE �X���b�h�̃n���h��
		*/
		HANDLE GetHandle();

		/**
		* �b�o�t���X���[�v
		* @param ulong �X���[�v����(�~���b�P��)
		*/
		static void Sleep(ulong time);

	private:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};

}


#endif
//THREAD_H_