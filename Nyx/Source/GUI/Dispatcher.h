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
#ifndef NYX_CORE_INCLUDED_DISPATCHER_H_
#define NYX_CORE_INCLUDED_DISPATCHER_H_
#include <Windows.h>
#include <unordered_map>
#include "GUI/IDispatcher.h"
#include "Utility/NonCopyable.h"
namespace nyx {

	///�f�B�X�p�b�`��
	class dispatcher : public idispatcher, private noncopyable {
		typedef std::unordered_map<uint32_t, gui_callback> HookList;
		typedef std::unordered_map<uint32_t, gui_callback>::iterator HookListIterator;
	public:
		//---------------------------------------------------------------------------------------
		//�\�z�E�j��
		//---------------------------------------------------------------------------------------
		/**
		* �R���X�g���N�^
		*/
		explicit dispatcher();

		/**
		* �f�X�g���N�^
		*/
		virtual ~dispatcher();
		
		//---------------------------------------------------------------------------------------
		//�C�x���g�̒ǉ��ƍ폜
		//---------------------------------------------------------------------------------------
		/**
		* �f�B�X�p�b�`���ɃR���g���[����o�^����
		* @param GUICallback
		*/
		void add(std::shared_ptr<iwidget> control, gui_callback callback);

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���R���g���[�����폜����
		* @param uint id
		*/
		void remove(std::shared_ptr<iwidget> control);

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���R���g���[�����N���A����
		*/
		void clear();

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���R���g���[�����擾����
		* @param uint id
		* @return Delegate2<std::shared_ptr<IControl>, EventArgs*>* 
		*/
		gui_callback get_callback(const std::shared_ptr<iwidget> control);
		
		//---------------------------------------------------------------------------------------
		//�C�x���g�̊��蓖��
		//---------------------------------------------------------------------------------------
		/**
		* �C�x���g�̊��蓖��
		* @param std::shared_ptr<IControl> sender
		* @param EventArgs* e
		*/
		void dispatch(std::shared_ptr<iwidget> control, event_args e);
	private:
		///�f�B�X�p�b�`���Ƀt�b�N����Ă���R���g���[���̃��X�g
		HookList hooklist;
	};
}

#endif
