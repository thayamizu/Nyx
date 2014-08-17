#ifndef NYX_CORE_INCLUDED_IPUSH_BUTTON_H_
#define NYX_CORE_INCLUDED_IPUSH_BUTTON_H_

#include "GUI/IControl.h"
#include "Utility/Type.h"
namespace nyx {
	
	///�v�b�V���{�^���C���^�t�F�[�X
	class ipush_button : public iwidget
	{
	public:
		//----------------------------------------------------------------
		//�\�z�E�j��
		//----------------------------------------------------------------
		/**
		* �f�X�g���N�^
		*/
		virtual ~ipush_button() {}

		//----------------------------------------------------------------
		// �v�b�V���{�^���ŗL�̑���
		//-----------------------------------------------------------------
		/**
		* ���x���̎擾
		* @return std::wstring& ���x��
		*/
		virtual std::wstring get_label() const = 0;

		/**
		* ���x���̐ݒ�
		* @param const std::wstring& ���x��
		*/
		virtual void set_label(const std::wstring& label) = 0;


		virtual void on_click(const gui_callback& callback) = 0;
	};
}
#endif