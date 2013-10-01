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
#include "Debug/DebugOutput.h"
#include "Utility/Common.h"
#include "Utility/Exception.h"
#include "DirectInputJoystick.h"


namespace Nyx {
	int DirectInputJoystick::joystickNum = 0;
	//-----------------------------------------------------------------------------------------
	//
	DirectInputJoystick::DirectInputJoystick(HWND hwnd_, int range) 
		: IJoystick(), allowRange(range), joystick(NULL), joystickDevice(NULL), isAcquire(false), isInitialized(false) {
			//JOYINFO joyInfo;
			//�����o������
			::ZeroMemory(&joyCaps, sizeof(joyCaps));

			SetButtonMax(32);
			//	if (joyGetPos(joystickNum++, &joyInfo) != JOYERR_NOERROR) {return;}



			//DirectInput�I�u�W�F�N�g�̍쐬
			HRESULT hr;
			hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&joystick, NULL );

			Assert(hr == DI_OK);
			if(FAILED(hr)) 
			{
				DebugOutput::DebugMessage("DirectInput�̏������Ɏ��s���܂���");
			}

			//�f�o�C�X�̗�
			hr = joystick->EnumDevices(
				DI8DEVCLASS_GAMECTRL, DirectInputJoystick::EnumJoysticksCallback,(void *)this, DIEDFL_ATTACHEDONLY );
			Assert(hr == DI_OK);
			if( FAILED(hr))
			{
				DebugOutput::DebugMessage("�W���C�X�e�B�b�N���ڑ�����Ă��܂���");
			}

			//�W���C�X�e�B�b�N�f�o�C�X���쐬�ł���
			if (joystickDevice != NULL ) {
				hr = joystickDevice->SetDataFormat(&c_dfDIJoystick2);
				Assert(hr == DI_OK);
				if( FAILED(hr))
				{
					DebugOutput::DebugMessage("�W���C�X�e�B�b�N�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł���");
				}

				//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
				hr = joystickDevice->SetCooperativeLevel(hwnd_, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
				Assert(hr == DI_OK);
				if( FAILED(hr))
				{
					DebugOutput::DebugMessage("�W���C�X�e�B�b�N�̃��[�h�ݒ�Ɏ��s���܂���");

				}
				// �R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
				hr = joystickDevice->EnumObjects(Joystick::EnumAxesCallback,(void*)this, DIDFT_AXIS);
				Assert(hr == DI_OK);
				if( FAILED(hr))
				{
					DebugOutput::DebugMessage("�W���C�X�e�B�b�N�̎����[�h�ݒ�Ɏ��s���܂���");
				}


				//����������
				isInitialized =true;
			}
			else {
				joystickDevice=NULL;
				//SafeRelease
			}

	}

	//-----------------------------------------------------------------------------------------
	//
	DirectInputJoystick::~DirectInputJoystick()  {
		Release();
	}
	bool DirectInputJoystick::Update() {
		HRESULT hr;
		//�o�b�t�@�t���b�v��
		Flip();


		//Acquire���Ƃ��̂�
		if  (isAcquire == false ) {
			if (Acquire() == false)  {
				::ZeroMemory((LPVOID)&(keyBuffer[flipCounter][0]), bufferSize);
				return false;  
			}
		}

		//�W���C�X�e�B�b�N���|�[�����Ȃ͂�
		hr = joystickDevice->Poll();
		if (FAILED(hr)) {
			if (!Acquire()) {
				return false;
			}
		}

		//�W���C�X�e�B�b�N�̏�ԂƂ��
		DIJOYSTATE2 dijs;
		ZeroMemory(&dijs, sizeof(DIJOYSTATE2));
		hr = joystickDevice->GetDeviceState(sizeof(DIJOYSTATE2),&dijs );
		if(hr == DIERR_INPUTLOST) {
			// ���s������Acquire����
			if (!Acquire()) {
				//acquire�ł��ւ񂩂����B
				//isAcquire = false;
				return true;
			}
			//	����ok
			hr = joystickDevice->GetDeviceState(sizeof(DIJOYSTATE2),&dijs);
		} 

		if (SUCCEEDED(hr)) {
			//�L�[�o�b�t�@���X�V����O�ɁA��x�N���A���Ă���
			::ZeroMemory((LPVOID)&(keyBuffer[flipCounter][0]), bufferSize);
			//�L�[�o�b�t�@�X�V���Ă���[
			//0~3�̓W���C�X�e�B�b�N�̎��̏�ԂȂ���0�Ԗڂ���㉺���E�̏��Ԃɂ͂����Ƃ��
			if (dijs.lY >= allowRange) {
				keyBuffer[flipCounter][0] = 0x80;
			}
			if (dijs.lY <= -allowRange) {
				keyBuffer[flipCounter][1] = 0x80;
			}
			if (dijs.lX >= allowRange) {
				keyBuffer[flipCounter][2] = 0x80;
			}
			if (dijs.lX <= -allowRange) {
				keyBuffer[flipCounter][3] = 0x80;
			}

			//4�Ԗڈȍ~�̓W���C�X�e�B�b�N�{�^���̏�Ԃ�
			//�f�t�H���g�͂R�Q��D�K�v�ɉ�����SetButton�Ń{�^������K���ɒ���������
			for (int i=0; i<buttonNum; i++) {
				keyBuffer[flipCounter][4+i] = dijs.rgbButtons[i]&0x80;
			}

		}
		if (hr != DI_OK) {
			//	�o�b�t�@���N���A���Ė߂�B�i��ʊO�Ƀt�H�[�J�X���ڂ����Ƃ��ɉ������ςȂ�
			//	�ɂȂ�̂�h�����߁j
			::ZeroMemory((LPVOID)&(keyBuffer[flipCounter][0]), bufferSize);
			return false;       
		}

		return true;
	}

	//-----------------------------------------------------------------------------------------
	//
	void  DirectInputJoystick::Release() {
		// DirectInput�̃f�o�C�X�����
		if (joystickDevice) {
			joystickDevice->Unacquire();
		}
		SafeRelease(joystickDevice);
		SafeRelease(joystick);
	}

	//-----------------------------------------------------------------------------------------
	//
	bool DirectInputJoystick::Acquire() {
		HRESULT hr = joystickDevice->Acquire();
		if (hr==DI_OK) {
			isAcquire = true;
		} else {
			isAcquire = false;
		}
		return isAcquire;
	}

	//-----------------------------------------------------------------------------------------
	//
	bool DirectInputJoystick::Unacquire() {
		if (isAcquire == false) {
			//acquire����Ƃ��
			return false;
		}

		HRESULT hr = joystickDevice->Unacquire();
		if (hr==DI_OK) {
			isAcquire = false;
		} else {
			isAcquire = true;
		}
		return !isAcquire;

	}
	bool DirectInputJoystick::IsInitialized() {
		return isInitialized;
	}

	//-----------------------------------------------------------------------------------------
	//
	bool DirectInputJoystick::SetButtonMax(uchar num) {
		buttonNum = num;
		return true;
	}

	//-----------------------------------------------------------------------------------------
	//
	uchar DirectInputJoystick::GetButtonMax() {
		return buttonNum;
	}

	//-----------------------------------------------------------------------------------------
	//
	int CALLBACK DirectInputJoystick::EnumJoysticksCallback(const DIDEVICEINSTANCE* lpddi, VOID* lpContext) {
		// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾����B
		HRESULT hr;
		DirectInputJoystick* joy = reinterpret_cast<DirectInputJoystick*>(lpContext);
		hr = joy->joystick->CreateDevice(lpddi->guidInstance, &joy->joystickDevice, NULL );
		Assert(hr == DI_OK);
		if( FAILED(hr) ) {  
			return DIENUM_CONTINUE;
		}

		//�W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
		joy->joyCaps.dwSize = sizeof(DIDEVCAPS);
		hr = joy->joystickDevice->GetCapabilities( &joy->joyCaps );
		Assert(hr == DI_OK);
		if (FAILED(hr)) {//�f�o�C�X�̔\�͂����Ȃ�����
			return DIENUM_CONTINUE;
		}

		// ���̃f�o�C�X���g�p
		return DIENUM_STOP;

	}

	//-----------------------------------------------------------------------------------------
	// �W���C�X�e�B�b�N�̎���񋓂���֐�
	int  CALLBACK DirectInputJoystick::EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
		HRESULT hr;

		// ���̒l�͈̔͂�ݒ�i-2000�`2000�j
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize	    = sizeof(diprg); 
		diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
		diprg.diph.dwObj	= lpddoi->dwType;
		diprg.diph.dwHow	= DIPH_BYID;
		diprg.lMin	= -2000;
		diprg.lMax	= +2000;

		DirectInputJoystick* joy = reinterpret_cast<DirectInputJoystick*>(pvRef);
		hr = joy->joystickDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		Assert(hr == DI_OK);
		if (FAILED(hr)) {
			return DIENUM_STOP;
		}

		return DIENUM_CONTINUE;
	}

}