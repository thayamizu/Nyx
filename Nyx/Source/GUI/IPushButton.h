#ifndef NYX_CORE_INCLUDED_IPUSH_BUTTON_H_
#define NYX_CORE_INCLUDED_IPUSH_BUTTON_H_

#include "GUI/IControl.h"
#include "Utility/Type.h"
namespace Nyx {
	
	///�v�b�V���{�^���C���^�t�F�[�X
	class IPushButton : public IControl
	{
	public:
		//----------------------------------------------------------------
		//�\�z�E�j��
		//----------------------------------------------------------------
		/**
		* �f�X�g���N�^
		*/
		virtual ~IPushButton() {}

		//----------------------------------------------------------------
		// �v�b�V���{�^���ŗL�̑���
		//-----------------------------------------------------------------
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
	};
}
#endif