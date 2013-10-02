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
#include <memory>

namespace Nyx {

	/////�W���C�X�e�B�b�N�k���f�o�C�X
	//class JoystickNullDevice: public IJoystick {
	//public:
	//	JoystickNullDevice();
	//	~JoystickNullDevice();
	//	/**
	//	*/
	//	bool Update();
	//	bool SetButtonMax(uchar num);
	//	uchar GetButtonMax();
	//	uchar GetJoyCount();
	//};

	//JoystickNullDevice::JoystickNullDevice(){}
	//JoystickNullDevice::~JoystickNullDevice(){}
	//
	//bool JoystickNullDevice::Update() {
	//	return false;
	//}
	//
	//bool JoystickNullDevice::SetButtonMax(uchar num) {
	//	return false;
	//}
	//
	//uchar JoystickNullDevice::GetButtonMax() {
	//	return 0;
	//}



	///DirectInput���g�����W���C�X�e�B�b�N����
	class Joystick : public IJoystick {
	public:
		//--------------------------------------------------------
		//�\�z�E�j��
		//--------------------------------------------------------
		Joystick(HWND hwnd_, int range) ;
		~Joystick() ;
		/**
		*
		*/
		bool Initialize();

		/**
		*
		*/
		bool IsInitialized(); 

		/**
		*
		*/
		bool Update();

		/**
		*
		*/
		void Release();

		/**
		*
		*/
		bool Acquire();

		/**
		*
		*/
		bool Unacquire();

		/**
		*
		*/
		bool IsInitialized();

		/**
		*
		*/
		bool SetButtonMax(uchar buttonNum);

		/**
		*
		*/
		uchar GetButtonMax();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif