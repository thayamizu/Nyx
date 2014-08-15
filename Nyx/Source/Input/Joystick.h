/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
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
#ifndef NYX_CORE_INCLUDED_JOYSTICK_H_
#define NYX_CORE_INCLUDED_JOYSTICK_H_
#include "IJoystick.h"
#include "KeyCode.h"

namespace nyx {
	struct input_device_desc;

	///DirectInput���g�����W���C�X�e�B�b�N����
	class joystick {
	public:
		//--------------------------------------------------------
		//�\�z�E�j��
		//--------------------------------------------------------
		/**
		*
		*/
		joystick() ;

		/**
		*
		*/
		joystick(const input_device_desc& desc) ;
		
		/**
		*
		*/
		~joystick();
		
		/**
		*
		*/
		bool initialize(const input_device_desc& desc);

		/**
		*
		*/
		bool is_initialized(); 

		/**
		*
		*/
		bool update();

		/**
		*
		*/
		void release();

		/**
		*
		*/
		bool acquire();

		/**
		*
		*/
		bool unacquire();

		/**
		*
		*/
		uint8_t* get_key_buffer();

		/**
		*
		*/
		axis3f get_axis();

		/**
		*
		*/
		bool is_pressed(JOYSTICK_BUTTON button);


		/**
		*
		*/
		bool is_pushed(JOYSTICK_BUTTON button);


		/**
		*
		*/
		void set_button_num(size_t buttonNum);

		/**
		*
		*/
		size_t get_button_num();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif