#ifndef NYX_CORE_INCLUDED_ICHECKBOX_H_
#define NYX_CORE_INCLUDED_ICHECKBOX_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"

namespace nyx
{
	///�`�F�b�N�{�b�N�X�C���^�t�F�[�X
	class icheckbox : public iwidget{
	public:
		//----------------------------------------------------------------
		//�\�z�E�j��
		//----------------------------------------------------------------
		/**
		* �f�X�g���N�^
		*/
		virtual ~icheckbox() {}

		//----------------------------------------------------------------
		// �`�F�b�N�{�b�N�X�ŗL�̑���
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