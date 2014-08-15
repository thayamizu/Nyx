#ifndef NYX_CORE_INCLUDED_ILISTBOX_H_
#define NYX_CORE_INCLUDED_ILISTBOX_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"

namespace nyx 
{

	///���X�g�{�b�N�X�C���^�t�F�[�X
	class ilist_box : public iwidget
	{
	public:
		//----------------------------------------------------------------
		//�\�z�E�j��
		//----------------------------------------------------------------
		/**
		* �f�X�g���N�^
		*/
		virtual ~ilist_box() {} 

		//----------------------------------------------------------------
		//���X�g�{�b�N�X�ŗL�̑���
		//----------------------------------------------------------------
		/**
		* ���X�g�{�b�N�X�ɃA�C�e����ǉ�����
		*/
		virtual void add(const std::wstring& item) = 0;

		/**
		* ���X�g�{�b�N�X�̃A�C�e�����폜����
		*/
		virtual void remove() = 0;

		/**
		* ���X�g�{�b�N�X�̃A�C�e�����N���A����
		*/
		virtual void clear() = 0;

		/**
		* ���ݑI������Ă���A�C�e���̃C���f�b�N�X���擾����
		*/
		virtual uint32_t get_select_index() = 0 ;

		/**
		* ���ݑI������Ă���A�C�e�������擾����
		* @return std::wstring
		*/
		virtual std::wstring get_select_item() = 0;
	};
}

#endif