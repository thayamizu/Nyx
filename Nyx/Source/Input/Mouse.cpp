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
#include "Input/Mouse.h"
#include "Debug/Assert.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	Mouse::Mouse(HWND hwnd_) {
		hwnd = hwnd_;
		isAcquire=false;

		HRESULT hr;
		// DirectInput�̍쐬
		hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mouse, NULL);
		Assert(hr == DI_OK);

		// �f�o�C�X�E�I�u�W�F�N�g���쐬
		hr = mouse->CreateDevice(GUID_SysMouse, &mouseDevice, NULL); 
		Assert(hr == DI_OK);

		// �f�[�^�`����ݒ�
		hr = mouseDevice->SetDataFormat(&c_dfDIMouse2);
		Assert(hr == DI_OK);

		//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		hr = mouseDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		Assert(hr == DI_OK);

		// �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
		DIPROPDWORD diprop;
		diprop.diph.dwSize	= sizeof(diprop); 
		diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
		diprop.diph.dwObj	= 0;
		diprop.diph.dwHow	= DIPH_DEVICE;
		diprop.dwData		= DIPROPAXISMODE_REL;
		//	diprop.dwData		= DIPROPAXISMODE_ABS;	// ��Βl���[�h�͎�����g���Ȃ�
		hr = mouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
		Assert(hr == DI_OK);

		// �o�b�t�@�����O�E�f�[�^���擾���邽�߁A�o�b�t�@�E�T�C�Y��ݒ�
		diprop.dwData = BufferSize;
		hr = mouseDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
		Assert(hr == DI_OK);

	}

	//-------------------------------------------------------------------------------------------------------
	//
	Mouse::~Mouse() {
		Release();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Update() {
		//�l�̃N���A
		absolutePos = Point2i::Zero;

		//��΍��W�̎擾
		GetCursorPos(reinterpret_cast<POINT*>(&absolutePos.elements));
		ScreenToClient(hwnd, reinterpret_cast<POINT*>(&absolutePos.elements));


		//dinput�ɂ����W�E�{�^����Ԃ̎擾
		if (isAcquire == false) {
			//acquire���Ƃ��̂�
			if (!Acquire()) { 
				::ZeroMemory(&mouseState, sizeof(mouseState));
				return false;//acuire���s�B
			}

			return true;
		}


		HRESULT hr = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState);
		if (hr == DIERR_INPUTLOST) {
			if(!Acquire()) {
				return false;
			}
			hr = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState);
		}
		if (hr == DI_OK) {
			relativePos.x = static_cast<int>(mouseState.lX);
			relativePos.y = static_cast<int>(mouseState.lY);
			wheelState = mouseState.lZ;
		}
		else {
			//	�o�b�t�@���N���A���Ė߂�B�i��ʊO�Ƀt�H�[�J�X���ڂ����Ƃ��ɉ������ςȂ�
			//	�ɂȂ�̂�h�����߁j
			::ZeroMemory(&mouseState, sizeof(mouseState));
			return false;       
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::GetMouseButton(Nyx::uchar keycode) {
		if(keycode >= MouseButtonMax) {
			return false;
		}

		return (mouseState.rgbButtons[keycode] & 0x80) !=0;
	}
	//-------------------------------------------------------------------------------------------------------
	//
	Point2i Mouse::GetRelativePos() {
		return relativePos;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	Point2i Mouse::GetAbsolutePos() {
		return absolutePos;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	int Mouse::GetWheelState() {
		return wheelState;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Acquire() {
		HRESULT hr = mouseDevice->Acquire();
		if (hr == DI_OK) {
			isAcquire = true;
		}
		else {
			isAcquire = false;
		}

		return isAcquire;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Unacquire(){
		if (isAcquire == false ) {
			//acquire����ĂȂ�����
			return false;
		}

		HRESULT hr = mouseDevice->Unacquire();
		if (hr == DI_OK) {
			isAcquire = false;
		}
		else {
			isAcquire = true;
		}

		return !isAcquire;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void Mouse::Release() {
		if (mouseDevice) {
			Unacquire();
		}
		SafeRelease(mouseDevice);
		SafeRelease(mouse);
	}
}