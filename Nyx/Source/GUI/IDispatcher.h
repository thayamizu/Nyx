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
#ifndef NYX_CORE_INCLUDED_IDISPATCHER_H_
#define NYX_CORE_INCLUDED_IDISPATCHER_H_
#include "Object/Delegate.h"

namespace Nyx {
	//�O���錾
	struct EventArgs;
	class IControl;

	typedef std::function<void(std::shared_ptr<IControl>, EventArgs)> GUICallback;

	///�f�B�X�p�b�`���C���^�t�F�[�X
	class IDispatcher {
	public:
		//---------------------------------------------------------------------------------------
		//�\�z�E�j��
		//---------------------------------------------------------------------------------------
		/**
		* �f�X�g���N�^
		*/
		virtual ~IDispatcher() {}

		//---------------------------------------------------------------------------------------
		//�C�x���g�̒ǉ��ƍ폜
		//---------------------------------------------------------------------------------------
		/**
		* �f�B�X�p�b�`���Ƀf���Q�[�g�I�u�W�F�N�g��o�^����
		* @param Delegate2<std::shared_ptr<IControl>, EventArgs&>* delegate
		*/
		virtual void Add(std::shared_ptr<IControl> control, GUICallback callback) = 0 ;

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���f���Q�[�g�I�u�W�F�N�g���폜����
		* @param uint id
		*/
		virtual void Del(std::shared_ptr<IControl> control) = 0 ;

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���f���Q�[�g�I�u�W�F�N�g���N���A����
		*/
		virtual void Clear() = 0;
		
		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���f���Q�[�g�I�u�W�F�N�g���擾����
		* @param uint id
		* @return GUICallback �f���Q�[�g�I�u�W�F�N�g
		*/
		virtual GUICallback GetCallback(const std::shared_ptr<IControl> control) = 0;

		//---------------------------------------------------------------------------------------
		//�C�x���g�̊��蓖��
		//---------------------------------------------------------------------------------------
		/**
		* �C�x���g�̊��蓖��
		* @param std::shared_ptr<IControl> sender
		* @param EventArgs& e
		*/
		virtual void Dispatch(std::shared_ptr<IControl>  sender, EventArgs e) = 0;
	};
}

#endif
