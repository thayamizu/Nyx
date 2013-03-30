#ifndef NYX_CORE_INCLUDED_IRADIO_BUTTON_H_
#define NYX_CORE_INCLUDED_IRADIO_BUTTON_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"
namespace Nyx 
{
	///���W�I�{�^���C���^�t�F�[�X
	class IRadioButton : public IControl
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
		virtual std::wstring GetLabel() const = 0;

		/**
		* ���x���̐ݒ�
		* @param const std::wstring& ���x��
		*/
		virtual void SetLabel(const std::wstring& label) = 0;

		/**
		* �{�^�����`�F�b�N��Ԃ��ǂ���
		* @return bool true�Ȃ�`�F�b�N����Ă���
		*/
		virtual bool IsChecked() const = 0;
	};
}
#endif