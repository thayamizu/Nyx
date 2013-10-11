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
#include "IJoystick.h"
#include "Joystick.h"
#include "InputDeviceDesc.h"
#include "DirectInputDefinition.h"
#include "KeyCode.h"

namespace Nyx {

	struct Joystick::PImpl : public IJoystick {
		bool isInitialized;

		PImpl() 
			:isInitialized(false), IJoystick(), allowRange_(0), joystick_(nullptr), joystickDevice_(nullptr), isAcquire_(false)
		{
		}
		~PImpl() 
		{

		}
		//-----------------------------------------------------------------------------------------
		//
		void Initialize(HWND hwnd_, float range, int buttonNum) 
		{
			//�����o������
			::ZeroMemory(&joyCaps_, sizeof(joyCaps_));
			allowRange_ = range;
			SetButtonMax(buttonNum);

			//DirectInput�I�u�W�F�N�g�̍쐬
			LPDIRECTINPUT8 joystick = NULL;
			HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&joystick, NULL );
			if(FAILED(hr)) 
			{
				DebugOutput::Trace("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
				throw Nyx::COMException("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B", hr);
			}

			//�f�o�C�X�̗�
			hr = joystick->EnumDevices(
				DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,(void *)this, DIEDFL_ATTACHEDONLY );
			if( FAILED(hr))
			{
				DebugOutput::Trace("���䃂�[�h�̐ݒ�Ɏ��s���܂����B");
				throw Nyx::COMException("���䃂�[�h�̐ݒ�Ɏ��s���܂����B", hr);
			}

			//�W���C�X�e�B�b�N�f�o�C�X���쐬�ł���
			if (joystickDevice_ != nullptr ) {
				hr = joystickDevice_->SetDataFormat(&c_dfDIJoystick2);
				if( FAILED(hr))
				{
					DebugOutput::Trace("�f�[�^�`���̐ݒ�Ɏ��s���܂����B");
					throw Nyx::COMException("�f�[�^�`���̐ݒ�Ɏ��s���܂����B", hr);
				}

				//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
				hr = joystickDevice_->SetCooperativeLevel(hwnd_, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
				if( FAILED(hr))
				{
					DebugOutput::Trace("���䃂�[�h�̐ݒ�Ɏ��s���܂����B");
					throw Nyx::COMException("���䃂�[�h�̐ݒ�Ɏ��s���܂����B", hr);

				}
				// �R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
				hr = joystickDevice_->EnumObjects(EnumAxesCallback,(void*)this, DIDFT_AXIS);
				if( FAILED(hr))
				{
					DebugOutput::Trace("�����[�h�̐ݒ�Ɏ��s���܂����B");
					throw Nyx::COMException("�����[�h�̐ݒ�Ɏ��s���܂����B", hr);
				}


				//����������
				isInitialized =true;
			}
			else {
				joystickDevice_= nullptr;
			}
		}



		bool Update() {
			HRESULT hr;
			//�o�b�t�@�t���b�v��
			Flip();


			//Acquire���Ƃ��̂�
			if  (isAcquire_ == false ) {
				if (Acquire() == false)  {
					::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BufferSize);
					return false;  
				}
			}

			//�W���C�X�e�B�b�N���|�[�����Ȃ͂�
			hr = joystickDevice_->Poll();
			if (FAILED(hr)) {
				if (!Acquire()) {
					return false;
				}
			}

			//�W���C�X�e�B�b�N�̏�ԂƂ��
			DIJOYSTATE2 dijs= {};
			ZeroMemory(&dijs, sizeof(DIJOYSTATE2));
			hr = joystickDevice_->GetDeviceState(sizeof(DIJOYSTATE2),&dijs );
			if(hr == DIERR_INPUTLOST) {
				// ���s������Acquire����
				if (!Acquire()) {
					//acquire�ł��ւ񂩂����B
					//isAcquire = false;
					return true;
				}
				//	����ok
				hr = joystickDevice_->GetDeviceState(sizeof(DIJOYSTATE2),&dijs);
			} 

			if (SUCCEEDED(hr)) {
				//�L�[�o�b�t�@���X�V����O�ɁA��x�N���A���Ă���
				::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BufferSize);
				//�L�[�o�b�t�@�X�V���Ă���[
				//0~3�̓W���C�X�e�B�b�N�̎��̏�ԂȂ���0�Ԗڂ���㉺���E�̏��Ԃɂ͂����Ƃ��
				if (dijs.lY >= allowRange_) {
					keyBuffer_[flipCounter_][0] = 0x80;
				}
				if (dijs.lY <= -allowRange_) {
					keyBuffer_[flipCounter_][1] = 0x80;
				}
				if (dijs.lX >= allowRange_) {
					keyBuffer_[flipCounter_][2] = 0x80;
				}
				if (dijs.lX <= -allowRange_) {
					keyBuffer_[flipCounter_][3] = 0x80;
				}

				//4�Ԗڈȍ~�̓W���C�X�e�B�b�N�{�^���̏�Ԃ�
				//�f�t�H���g�͂R�Q��D�K�v�ɉ�����SetButton�Ń{�^������K���ɒ���������
				int buttonNum = GetButtonMax();
				for (int i=0; i < buttonNum; i++) {
					keyBuffer_[flipCounter_][4 + i] = (dijs.rgbButtons[i] & 0x80);
				}

			}
			if (hr != DI_OK) {
				//	�o�b�t�@���N���A���Ė߂�B�i��ʊO�Ƀt�H�[�J�X���ڂ����Ƃ��ɉ������ςȂ�
				//	�ɂȂ�̂�h�����߁j
				::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BufferSize);
				return false;       
			}

			return true;
		}


		//-----------------------------------------------------------------------------------------
		//
		float GetAxis() {
			return 1.f;
		}
		
		//-----------------------------------------------------------------------------------------
		//
		void  Release() {
			// DirectInput�̃f�o�C�X�����
			if (joystickDevice_) {
				joystickDevice_->Unacquire();
			}
		}

		//-----------------------------------------------------------------------------------------
		//
		bool Acquire() {
			HRESULT hr = joystickDevice_->Acquire();
			if (SUCCEEDED(hr)) {
				isAcquire_ = true;
			} else {
				isAcquire_ = false;
			}
			return isAcquire_;
		}

		//-----------------------------------------------------------------------------------------
		//
		bool Unacquire() {
			if (isAcquire_ == false) {
				return false;
			}

			HRESULT hr = joystickDevice_->Unacquire();
			if (SUCCEEDED(hr)) {
				isAcquire_ = false;
			} else {
				isAcquire_ = true;
			}
			return !isAcquire_;

		}

		//-----------------------------------------------------------------------------------------
		//
		static int CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* lpddi, VOID* lpContext) {
			// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾����B
			HRESULT hr;
			PImpl* joy = reinterpret_cast<PImpl*>(lpContext);
			LPDIRECTINPUTDEVICE8 joyDevice;
			hr = joy->joystick_->CreateDevice(lpddi->guidInstance, &joyDevice, NULL );
			if( FAILED(hr)) {  
				return DIENUM_CONTINUE;
			}

			//�W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
			joy->joyCaps_.dwSize = sizeof(DIDEVCAPS);
			hr = joyDevice->GetCapabilities( &joy->joyCaps_);
			if (FAILED(hr)) {//�f�o�C�X�̔\�͂����Ȃ�����
				return DIENUM_CONTINUE;
			}

			// ���̃f�o�C�X���g�p
			joy->joystickDevice_ = DirectInputDevicePtr(joyDevice, false);
			return DIENUM_STOP;

		}

		//-----------------------------------------------------------------------------------------
		// �W���C�X�e�B�b�N�̎���񋓂���֐�
		static int  CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
			HRESULT hr;

			// ���̒l�͈̔͂�ݒ�i-2000�`2000�j
			DIPROPRANGE diprg = {};
			ZeroMemory(&diprg, sizeof(diprg));
			diprg.diph.dwSize	    = sizeof(diprg); 
			diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
			diprg.diph.dwObj		= lpddoi->dwType;
			diprg.diph.dwHow		= DIPH_BYID;
			diprg.lMin				= -2000;
			diprg.lMax				= +2000;

			PImpl* joy = reinterpret_cast<PImpl*>(pvRef);
			hr = joy->joystickDevice_->SetProperty(DIPROP_RANGE, &diprg.diph);
			if (FAILED(hr)) {
				return DIENUM_STOP;
			}

			return DIENUM_CONTINUE;
		}
	private:
		bool isAcquire_;
		float allowRange_;
		DIDEVCAPS joyCaps_;
		DirectInputPtr joystick_;
		DirectInputDevicePtr joystickDevice_;
	};

	//-----------------------------------------------------------------------------------------
	//
	Joystick::Joystick()
		:pimpl_(std::make_shared<PImpl>())
	{
	}

	//-----------------------------------------------------------------------------------------
	//
	Joystick::~Joystick()  {
		pimpl_->Release();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::IsInitialized() {
		return pimpl_->isInitialized;
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::Initialize(const InputDeviceDesc& desc) {
		Assert(pimpl_ != nullptr);
		if (IsInitialized()) {
			return IsInitialized();
		}		

		pimpl_->Initialize((HWND)desc.handle, desc.range, desc.button);

		return pimpl_->isInitialized;
	}
	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::Update() {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->Update();
	}

	//-----------------------------------------------------------------------------------------
	//
	void  Joystick::Release() {
		Assert(pimpl_!= nullptr);

		return pimpl_->Release();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::Acquire() {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->Acquire();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::Unacquire() {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->Unacquire();
	}

	//-----------------------------------------------------------------------------------------
	//
	float Joystick::GetAxis() {
		return 1.0f;
	}

	//-----------------------------------------------------------------------------------------
	//
	uchar* Joystick::GetKeyBuffer() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->GetKeyBuffer();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::IsPushed(KeyCode keycode) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->IsPushed(keycode);
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::IsPressed(KeyCode keycode) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->IsPressed(keycode);
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::SetButtonMax(size_t num) {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->SetButtonMax(num);
	}

	//-----------------------------------------------------------------------------------------
	//
	size_t Joystick::GetButtonMax() {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->GetButtonMax();
	}
}