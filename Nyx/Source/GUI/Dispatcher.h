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
#include "IControl.h"
#include "Utility/NonCopyable.h"
namespace nyx {

	///�f�B�X�p�b�`��
	class dispatcher : private noncopyable {
		typedef std::unordered_map<WIDGET_EVENT_TYPE, gui_callback> hook_list;
		typedef std::unordered_map<WIDGET_EVENT_TYPE, gui_callback>::iterator hook_list_iterator;
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
		void add_callback(WIDGET_EVENT_TYPE eventType, gui_callback callback);

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���R���g���[�����폜����
		* @param uint id
		*/
		void remove_callback(WIDGET_EVENT_TYPE eventType);

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���R���g���[�����N���A����
		*/
		void clear_callback();

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���R���g���[�����擾����
		* @param uint id
		* @return Delegate2<std::shared_ptr<IControl>, EventArgs*>* 
		*/
		gui_callback get_callback(WIDGET_EVENT_TYPE eventType);
		
		//---------------------------------------------------------------------------------------
		//�C�x���g�̊��蓖��
		//---------------------------------------------------------------------------------------
		/**
		* �C�x���g�̊��蓖��
		* @param std::shared_ptr<IControl> sender
		* @param EventArgs* e
		*/
		void dispatch(WIDGET_EVENT_TYPE eventType, iwidget& widget, event_args& e);
	private:
		///�f�B�X�p�b�`���Ƀt�b�N����Ă���R���g���[���̃��X�g
		hook_list hooklist_;
	};
}

#endif
