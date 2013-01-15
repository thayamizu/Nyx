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
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Input/IKeyBase.h"
#include "Input/Keyboard.h"

namespace Nyx {
	Keyboard::Keyboard(HWND hwnd_) : IKeyBase(), isAcquire(false) {


		// DirectInput�̍쐬
		HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&keyboard, NULL); 
		Assert(hr == DI_OK); 

		// �f�o�C�X�E�I�u�W�F�N�g���쐬
		hr = keyboard->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL); 
		Assert(hr== DI_OK);

		// �f�[�^�`����ݒ�
		hr = keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
		Assert(hr == DI_OK);

		//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		hr = keyboardDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		Assert(hr == DI_OK);

		// �o�b�t�@�����O�E�f�[�^���擾���邽�߁A�o�b�t�@�E�T�C�Y��ݒ�
		DIPROPDWORD diprop;
		diprop.diph.dwSize	= sizeof(diprop); 
		diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
		diprop.diph.dwObj	= 0;
		diprop.diph.dwHow	= DIPH_DEVICE;
		diprop.dwData = 255;
		hr = keyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
		Assert(hr == DI_OK);

	}
	Keyboard::~Keyboard()  {
		Release();
	}
	bool Keyboard::Update() {
		HRESULT hr;
		Flip();

		//Acquire���Ƃ��̂�
		if  (isAcquire == false ) {
			if (Acquire() == false)  {
				::ZeroMemory((LPVOID)&(keyBuffer[flipCounter][0]), bufferSize);
				return false;  
			}
		}

		//�L�[�{�[�h�̏�Ԃ�ǂݍ���
		hr = keyboardDevice->GetDeviceState(bufferSize, (LPVOID)&(keyBuffer[flipCounter][0]));
		if(hr == DIERR_INPUTLOST) {
			// ���s������Acquire����
			if (!Acquire()) {
				//acquire�ł��ւ񂩂����B
				isAcquire = false;
				return true;
			}
			//	����ok
			hr = keyboardDevice->GetDeviceState(bufferSize, (LPVOID)&(keyBuffer[flipCounter][0]));
		} 

		if (hr != DI_OK) {
			//	�o�b�t�@���N���A���Ė߂�B�i��ʊO�Ƀt�H�[�J�X���ڂ����Ƃ��ɉ������ςȂ�
			//	�ɂȂ�̂�h�����߁j
			::ZeroMemory((LPVOID)&(keyBuffer[flipCounter][0]), bufferSize);
			return false;       
		}

		return true;
	}


	void  Keyboard::Release() {
		// DirectInput�̃f�o�C�X�����
		if (keyboardDevice) {
			keyboardDevice->Unacquire();
		}
		SafeRelease(keyboardDevice);
		SafeRelease(keyboard);
	}

	bool Keyboard::Acquire() {
		HRESULT hr = keyboardDevice->Acquire();
		if (hr==DI_OK) {
			isAcquire = true;
		} else {
			isAcquire = false;
		}
		return isAcquire;
	}

	bool Keyboard::Unacquire() {
		if (isAcquire == false) {
			//acquire����Ƃ��
			return false;
		}

		HRESULT hr = keyboardDevice->Unacquire();
		if (hr==DI_OK) {
			isAcquire = false;
		} else {
			isAcquire = true;
		}
		return !isAcquire;
	}
}