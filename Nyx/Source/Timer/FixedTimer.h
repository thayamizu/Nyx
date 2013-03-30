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
#ifndef NYX_CORE_INCLUDED_FIXED_TIMER_H_ 
#define NYX_CORE_INCLUDED_FIXED_TIMER_H_ 
#include "Object/NonCopyable.h"
#include "Timer/ITimer.h"
namespace Nyx {

	///�Œ�^�C�}�[
	class FixedTimer : public ITimer, private NonCopyable{
	public:
		/**
		* �R���X�g���N�^
		*/
		FixedTimer();

		/**
		* �f�X�g���N�^
		*/
		~FixedTimer ();

		/**
		* �^�C�}���Z�b�g
		*/
		void Reset();
		/**
		* �����̎擾
		* @return ulong ����
		*/
		ulong Get();
		/**
		* �����̐ݒ�
		* @param ulong ����
		*/
		void Set(ulong t);

		/**
		* �^�C�}�[���|�[�Y
		* @param bool true�ł���΃^�C�}���|�[�Y
		*/
		void Pause(bool pause);
		/**
		* �^�C�}���|�[�Y���ł��邩�ǂ���
		* @return bool �^�C�}���|�[�Y���ł����true
		*/
		bool IsPause();

		/**
		* �^�C�}�[�����X�^�[�g
		*/
		void Restart();

		/**
		* �^�C�}���t���b�V������
		*/
		void Flush();
	private:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
		
	};

}

#endif