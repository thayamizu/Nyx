#ifndef NYX_CORE_INCLUDED_ICOMBOBOX_H_
#define NYX_CORE_INCLUDED_ICOMBOBOX_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"

namespace Nyx {

	///�R���{�{�b�N�X�C���^�t�F�[�X
	class IComboBox : public IControl 
	{
	public:
		//----------------------------------------------------------------
		//�\�z�E�j��
		//----------------------------------------------------------------
		/**
		* �f�X�g���N�^
		*/
		virtual ~IComboBox() {} 

		//----------------------------------------------------------------
		//�l�̒ǉ�/�폜
		//----------------------------------------------------------------
		/**
		* ���X�g�{�b�N�X�ɃA�C�e����ǉ�����
		* param const std::wstring& �A�C�e��
		*/
		virtual void AddItem(const std::wstring& item) = 0;

		/**
		* ���X�g�{�b�N�X�̃A�C�e�����폜����
		*/
		virtual void DeleteItem() = 0;

		/**
		* ���X�g�{�b�N�X�̃A�C�e�����N���A����
		*/
		virtual void ClearItem() = 0;

		/**
		* ���ݑI������Ă���A�C�e���̃C���f�b�N�X���擾����
		* @return uint �C���f�b�N�X
		*/
		virtual uint GetSelectedIndex() = 0 ;

		/**
		* ���ݑI������Ă���A�C�e�������擾����
		* @return std::wstring �A�C�e����
		*/
		virtual std::wstring GetSelectedItem() = 0;
	};
}
#endif