/********************************************************************************
*
*  The MIT License
*
* Copyright (c) 2010-2011 t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_RADIO_Button_H_
#define NYX_CORE_INCLUDED_RADIO_Button_H_

#include "GUI/IRadioButton.h"

namespace nyx {
	class window;
	class dispatcher;

	///���W�I�{�^��
	class radio_button : public iradio_button {
	public:
		//---------------------------------------------------------------------------------------
		//�����E�j��
		//---------------------------------------------------------------------------------------
		/**
		*
		*/
		radio_button(std::shared_ptr<window>& parent,std::wstring label, int x, int y, int width,int height, bool isOwnerDraw=false);
		/**
		*
		*/

		~radio_button();
		/**
		*
		*/
		bool create(window_handle hwnd, std::wstring label, int x, int y, int width, int height, bool isOwnerDraw);

		//--------------------------------------------------------------------------------------
		//�n���h���̎擾
		//---------------------------------------------------------------------------------------
		/**
		* �E�C���h�E�n���h���̎擾
		* @return HWND
		*/
		window_handle get_handle();
		
		
		//---------------------------------------------------------------------------------------
		//�`��E�X�V
		//---------------------------------------------------------------------------------------
		/**
		* �E�C���h�E��\������
		*/
		void show();


		/**
		* �E�C���h�E���B��
		*/
		void hide();
		
		
		/**
		* �E�C���h�E���X�V����
		*/
		void update();
		
		
		/**
		* �E�C���h�E���\������Ă��邩
		* @return true�Ȃ�E�C���h�E�͕\������Ă���
		*/
		bool is_show();

		//---------------------------------------------------------------------------------------
		//�R���g���[���̗L�����Ɩ�����
		//---------------------------------------------------------------------------------------
		/**
		* �R���g���[����L��������
		*/
		void activate();

		/**
		* �R���g���[���𖳌�������
		*/
		void unactivate();

		/**
		* �R���g���[�����L�����ǂ���
		* @return bool true�Ȃ�R���g���[���͗L��
		*/
		bool is_activate() const;

		//---------------------------------------------------------------------------------------
		//�l�̎擾�E�ݒ�
		//---------------------------------------------------------------------------------------
		/**
		* �R���g���[���̃^�C�v���擾����
		* @return ControlType::enum_t�̒l
		*/
		WIDGET_TYPE get_type() const;

		/**
		* ���[�U�[�f�[�^���擾����
		* @return void*
		*/
		std::shared_ptr<void> get_user_data() const;

		/**
		* ���[�U�[�f�[�^��ݒ肷��
		* @param void* ���[�U�[�f�[�^
		*/
		void set_user_data(const std::shared_ptr<void>& data) ;

		/**
		* �R���g���[����ID���擾����
		* @return uint �R���g���[����ID
		*/
		uint32_t get_id() const;

		/**
		* �R���g���[����ID��ݒ肷��
		* @return �R���g���[����ID
		*/
		void set_id(uint32_t id)  ;

		/**
		* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y���擾����
		* @param Rect2i& �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y
		*/
		void get_size(rect2i& rect) const;

		/**
		* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y��ݒ肷��
		* @param Rect2i& �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y
		*/
		void set_size(const rect2i& rect);

		/**
		* �E�C���h�E�̈ʒu���擾����
		* @param Point2i& p
		*/
		void get_position(point2i& p) const;

		/**
		* �E�C���h�E�̈ʒu��ݒ肷��
		*/
		void set_position(const point2i& p);

		//----------------------------------------------------------------
		// ���W�I�{�^���ŗL�̑���
		//----------------------------------------------------------------
		/**
		* ���x���̎擾
		* @return std::wstring& ���x��
		*/
		std::wstring get_label() const ;

		/**
		* ���x���̐ݒ�
		* @param const std::wstring& ���x��
		*/
		void set_label(const std::wstring& label) ;

		/**
		* �{�^�����`�F�b�N��Ԃ��ǂ���
		* @return bool true�Ȃ�`�F�b�N����Ă���
		*/
		bool is_checked() const ;

		void on_checked_changed(const gui_callback& callback);

		void on_click(const gui_callback& callback);

		void on_paint(const gui_callback& callback);

		void dispatch(WIDGET_EVENT_TYPE eventType, event_args& e);
	private:

	private:
		///�{�^���̕\�����x��
		std::wstring label_;
		/// �n���h���C���X�^���X
		HWND hwnd_;
		///�{�^��ID
		int id_;
		///�A�g��
		ATOM atom_;
		///�\������Ă��邩�ǂ���
		bool isShow_;
		///���[�U�[�f�[�^
		std::shared_ptr<void> userData_;

		std::shared_ptr<dispatcher> guiEventList_;
	};
}
#endif