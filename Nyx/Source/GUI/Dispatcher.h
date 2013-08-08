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

#include <unordered_map>
#include "GUI/IDispatcher.h"
#include "Object/NonCopyable.h"
#include "Object/Delegate.h"
namespace Nyx {

	///�f�B�X�p�b�`��
	class Dispatcher : public IDispatcher, private NonCopyable {
		typedef std::unordered_map<uint, GUICallback> HookList;
		typedef std::unordered_map<uint, GUICallback>::iterator HookListIterator;
	public:
		//---------------------------------------------------------------------------------------
		//�\�z�E�j��
		//---------------------------------------------------------------------------------------
		/**
		* �R���X�g���N�^
		*/
		explicit Dispatcher();

		/**
		* �f�X�g���N�^
		*/
		virtual ~Dispatcher();
		
		//---------------------------------------------------------------------------------------
		//�C�x���g�̒ǉ��ƍ폜
		//---------------------------------------------------------------------------------------
		/**
		* �f�B�X�p�b�`���ɃR���g���[����o�^����
		* @param GUICallback
		*/
		void Add(std::shared_ptr<IControl> control, GUICallback callback);

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���R���g���[�����폜����
		* @param uint id
		*/
		void Del(std::shared_ptr<IControl> control);

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���R���g���[�����N���A����
		*/
		void Clear();

		/**
		* �f�B�X�p�b�`���ɓo�^����Ă���R���g���[�����擾����
		* @param uint id
		* @return Delegate2<std::shared_ptr<IControl>, EventArgs*>* 
		*/
		GUICallback GetCallback(const std::shared_ptr<IControl> control);
		
		//---------------------------------------------------------------------------------------
		//�C�x���g�̊��蓖��
		//---------------------------------------------------------------------------------------
		/**
		* �C�x���g�̊��蓖��
		* @param std::shared_ptr<IControl> sender
		* @param EventArgs* e
		*/
		void Dispatch(std::shared_ptr<IControl> control, EventArgs& e);
	private:
		///�f�B�X�p�b�`���Ƀt�b�N����Ă���R���g���[���̃��X�g
		HookList hooklist;
	};
}

#endif
