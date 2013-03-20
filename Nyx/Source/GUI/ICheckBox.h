#ifndef NYX_CORE_INCLUDED_ICHECKBOX_H_
#define NYX_CORE_INCLUDED_ICHECKBOX_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"

namespace Nyx
{
	///�`�F�b�N�{�b�N�X�C���^�t�F�[�X
	class ICheckBox : public IControl {
	public:
		//----------------------------------------------------------------
		//�\�z�E�j��
		//----------------------------------------------------------------
		/**
		* �f�X�g���N�^
		*/
		virtual ~ICheckBox() {}

		//----------------------------------------------------------------
		// �`�F�b�N�{�b�N�X�ŗL�̑���
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