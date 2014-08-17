#ifndef NYX_CORE_INCLUDED_ICONTROL_H_
#define NYX_CORE_INCLUDED_ICONTROL_H_
#include "Utility/Type.h"
#include "Primitive/Vector2.h"
#include "Primitive/Rect.h"
#include <Windows.h>

namespace nyx 
{
	class iwidget;
	///GUI�R���g���[���̎��
	enum WIDGET_TYPE {
		WIDGET_TYPE_WINDOW,
		WIDGET_TYPE_CHECK_BOX,
		WIDGET_TYPE_COMBO_BOX,
		WIDGET_TYPE_LIST_BOX,
		WIDGET_TYPE_BUTTON,
		WIDGET_TYPE_RADIO_BUTTON,
		WIDGET_TYPE_NUM,
	};

	enum WIDGET_EVENT_TYPE {
		WIDGET_EVENT_TYPE_CLICK,
		WIDGET_EVENT_TYPE_CHECKED_CHANGED,
		WIDGET_EVENT_TYPE_INDEX_CHANGED,
		WIDGET_EVENT_TYPE_MOUSE_DOWN,
		WIDGET_EVENT_TYPE_MOUSE_UP,
		WIDGET_EVENT_TYPE_PAINT,
		WIDGET_EVENT_TYPE_NUM
	};

	///�C�x���g����
	struct event_args {
		/**
		 *�f�t�H���g�R���X�g���N�^
		 */
		event_args():
			message(0), wparam(NULL), lparam(NULL){
		}

		
		/**
		 *�R���X�g���N�^
		 * @param uint
		 * @param WPARAM
		 * @param LPARAM
		 */
		event_args(uint32_t msg, WPARAM wParam, LPARAM lParam) 
			:message(msg), wparam(wParam), lparam(lParam) {
		}

		//���b�Z�[�W
		uint32_t message;

		//WPARAM
		WPARAM wparam;

		//LPARAM
		LPARAM lparam;

	};
	typedef HWND  window_handle;
	typedef HMENU menu_handle;
	typedef std::function < void(iwidget&, event_args& e)> gui_callback;
	
	///�R���g���[���C���^�t�F�[�X
	class iwidget {
	public:
		virtual ~iwidget() {}
		//--------------------------------------------------------------------------------------
		//�n���h���̎擾
		//---------------------------------------------------------------------------------------
		/**
		* �E�C���h�E�n���h���̎擾
		* @return HWND
		*/
		virtual window_handle get_handle() = 0;

		//---------------------------------------------------------------------------------------
		//�`��E�X�V
		//---------------------------------------------------------------------------------------
		/**
		* �E�C���h�E��\������
		*/
		virtual void show() = 0;


		/**
		* �E�C���h�E���B��
		*/
		virtual void hide() = 0;
		
		
		/**
		* �E�C���h�E���X�V����
		*/
		virtual void update() = 0;

		/**
		* �E�C���h�E���\������Ă��邩
		* @return true�Ȃ�E�C���h�E�͕\������Ă���
		*/
		virtual bool is_show() = 0;

		//---------------------------------------------------------------------------------------
		//�R���g���[���̗L�����Ɩ�����
		//---------------------------------------------------------------------------------------
		/**
		* �R���g���[����L��������
		*/
		virtual void activate() = 0;

		/**
		* �R���g���[���𖳌�������
		*/
		virtual void unactivate() = 0;

		/**
		* �R���g���[�����L�����ǂ���
		* @return bool true�Ȃ�R���g���[���͗L��
		*/
		virtual bool is_activate() const = 0;

		//---------------------------------------------------------------------------------------
		//�l�̎擾�E�ݒ�
		//---------------------------------------------------------------------------------------
		/**
		* �R���g���[���̃^�C�v���擾����
		* @return ControlType::enum_t�̒l
		*/
		virtual WIDGET_TYPE get_type() const = 0;
		

		/**
		* ���[�U�[�f�[�^���擾����
		* @return void*
		*/
		virtual std::shared_ptr<void> get_user_data() const = 0;


		/**
		* ���[�U�[�f�[�^��ݒ肷��
		* @param void* ���[�U�[�f�[�^
		*/
		virtual void set_user_data(const std::shared_ptr<void>& data) = 0;
		

		/**
		* �R���g���[����ID���擾����
		* @return uint �R���g���[����ID
		*/
		virtual uint32_t get_id() const = 0;

		
		/**
		* �R���g���[����ID��ݒ肷��
		* @return �R���g���[����ID
		*/
		virtual void set_id(uint32_t id) = 0;


		/**
		* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y���擾����
		* @param Rect2i* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y
		*/
		virtual void get_size(rect2i& rect) const = 0;


		/**
		* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y��ݒ肷��
		* @param Rect2i& �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y
		*/
		virtual void set_size(const rect2i& rect) = 0;


		/**
		* �E�C���h�E�̈ʒu���擾����
		* @param Point2i& p
		*/
		virtual void get_position(point2i& p) const = 0;


		/**
		* �E�C���h�E�̈ʒu��ݒ肷��
		*/
		virtual void set_position(const point2i& p) = 0;

		virtual void dispatch(WIDGET_EVENT_TYPE eventType, event_args& e) = 0;
	};
};
#endif