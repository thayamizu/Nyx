#ifndef NYX_CORE_INCLUDED_ILISTBOX_H_
#define NYX_CORE_INCLUDED_ILISTBOX_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"

namespace Nyx 
{

	///���X�g�{�b�N�X�C���^�t�F�[�X
	class IListBox : public IControl
	{
	public:
		//----------------------------------------------------------------
		//�\�z�E�j��
		//----------------------------------------------------------------
		/**
		* �f�X�g���N�^
		*/
		virtual ~IListBox() {} 

		//----------------------------------------------------------------
		//���X�g�{�b�N�X�ŗL�̑���
		//----------------------------------------------------------------
		/**
		* ���X�g�{�b�N�X�ɃA�C�e����ǉ�����
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
		*/
		virtual uint GetSelectedIndex() = 0 ;

		/**
		* ���ݑI������Ă���A�C�e�������擾����
		* @return std::wstring
		*/
		virtual std::wstring GetSelectedItem() = 0;
	};
}

#endif