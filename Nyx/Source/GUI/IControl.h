#ifndef NYX_CORE_INCLUDED_ICONTROL_H_
#define NYX_CORE_INCLUDED_ICONTROL_H_
#include "Object/Delegate.h"
#include "Utility/Type.h"
#include "Primitive/Vector2.h"
#include "Primitive/Rect.h"
#include <Windows.h>
namespace Nyx 
{

	///GUI�R���g���[���̎��
	enum ControlType {
		ControlType_Window,
		ControlType_CheckBox,
		ControlType_Combobox,
		ControlType_ListBox,
		ControlType_PushButton,
		ControlType_RadioButton,
		ControlType_ControlTypeNum,
	};

	///�C�x���g����
	struct EventArgs {
		/**
		 *�f�t�H���g�R���X�g���N�^
		 */
		EventArgs():
			message(0), wparam(NULL), lparam(NULL){
		}

		
		/**
		 *�R���X�g���N�^
		 * @param uint
		 * @param WPARAM
		 * @param LPARAM
		 */
		EventArgs(uint msg, WPARAM wParam, LPARAM lParam) 
			:message(msg), wparam(wParam), lparam(lParam) {
		}

		//���b�Z�[�W
		uint message;

		//WPARAM
		WPARAM wparam;

		//LPARAM
		LPARAM lparam;
	};


	///�R���g���[���C���^�t�F�[�X
	class IControl {
	public:
		virtual ~IControl() {}
		//--------------------------------------------------------------------------------------
		//�n���h���̎擾
		//---------------------------------------------------------------------------------------
		/**
		* �E�C���h�E�n���h���̎擾
		* @return HWND
		*/
		virtual HWND GetHandle() = 0;

		//---------------------------------------------------------------------------------------
		//�`��E�X�V
		//---------------------------------------------------------------------------------------
		/**
		* �E�C���h�E��\������
		*/
		virtual void Show() = 0;


		/**
		* �E�C���h�E���B��
		*/
		virtual void Hide() = 0;
		
		
		/**
		* �E�C���h�E���X�V����
		*/
		virtual void Update() = 0;

		/**
		* �E�C���h�E���\������Ă��邩
		* @return true�Ȃ�E�C���h�E�͕\������Ă���
		*/
		virtual bool IsShow() = 0;

		//---------------------------------------------------------------------------------------
		//�R���g���[���̗L�����Ɩ�����
		//---------------------------------------------------------------------------------------
		/**
		* �R���g���[����L��������
		*/
		virtual void Activate() = 0;

		/**
		* �R���g���[���𖳌�������
		*/
		virtual void Unactivate() = 0;

		/**
		* �R���g���[�����L�����ǂ���
		* @return bool true�Ȃ�R���g���[���͗L��
		*/
		virtual bool IsActivate() const = 0;

		//---------------------------------------------------------------------------------------
		//�l�̎擾�E�ݒ�
		//---------------------------------------------------------------------------------------
		/**
		* �R���g���[���̃^�C�v���擾����
		* @return ControlType::enum_t�̒l
		*/
		virtual ControlType GetType() const = 0;
		

		/**
		* ���[�U�[�f�[�^���擾����
		* @return void*
		*/
		virtual std::shared_ptr<void> GetUserData() const = 0;


		/**
		* ���[�U�[�f�[�^��ݒ肷��
		* @param void* ���[�U�[�f�[�^
		*/
		virtual void SetUserData(std::shared_ptr<void> data)  = 0;
		

		/**
		* �R���g���[����ID���擾����
		* @return uint �R���g���[����ID
		*/
		virtual uint GetID() const = 0;

		
		/**
		* �R���g���[����ID��ݒ肷��
		* @return �R���g���[����ID
		*/
		virtual void SetID(size_t id)   = 0;


		/**
		* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y���擾����
		* @param Rect2i* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y
		*/
		virtual void GetSize(Rect2i& rect) const = 0;


		/**
		* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y��ݒ肷��
		* @param Rect2i& �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y
		*/
		virtual void SetSize(const Rect2i& rect) = 0;


		/**
		* �E�C���h�E�̈ʒu���擾����
		* @param Point2i& p
		*/
		virtual void GetPosition(Point2i& p) const = 0;


		/**
		* �E�C���h�E�̈ʒu��ݒ肷��
		*/
		virtual void SetPosition(const Point2i& p) = 0;
	};
};
#endif