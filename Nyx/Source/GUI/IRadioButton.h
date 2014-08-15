#ifndef NYX_CORE_INCLUDED_IRADIO_BUTTON_H_
#define NYX_CORE_INCLUDED_IRADIO_BUTTON_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"
namespace nyx 
{
	///���W�I�{�^���C���^�t�F�[�X
	class IRadioButton : public iwidget
	{
	public:
		//----------------------------------------------------------------
		//�\�z�E�j��
		//----------------------------------------------------------------
		virtual ~IRadioButton() {}

		//----------------------------------------------------------------
		// ���W�I�{�^���ŗL�̑���
		//----------------------------------------------------------------
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

		/**
		* �{�^�����`�F�b�N��Ԃ��ǂ���
		* @return bool true�Ȃ�`�F�b�N����Ă���
		*/
		virtual bool is_checked() const = 0;
	};
}
#endif