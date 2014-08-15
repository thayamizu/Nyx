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
#include "Primitive/Vector3.h"


namespace nyx {

	struct joystick::PImpl : public ijoystick {
		bool isInitialized;

		PImpl() 
			:isInitialized(false), ijoystick(), allowRange_(0), joystick_(nullptr), joystickDevice_(nullptr), isAcquire_(false), axis_()
		{
		}
		~PImpl() 
		{

		}
		//-----------------------------------------------------------------------------------------
		//
		void initialize(HWND hwnd_, float range, int buttonNum) 
		{
			//�����o������
			::ZeroMemory(&joyCaps_, sizeof(joyCaps_));
			allowRange_ = range;
			set_button_num(buttonNum);

			//DirectInput�I�u�W�F�N�g�̍쐬
			LPDIRECTINPUT8 joystick = NULL;
			HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&joystick, NULL );
			if(FAILED(hr)) 
			{
				debug_out::trace("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
				throw nyx::com_exception("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B", hr);
			}
			joystick_ = DirectInputPtr(joystick);

			//�f�o�C�X�̗�
			hr = joystick_->EnumDevices(
				DI8DEVCLASS_GAMECTRL, enum_joysticks_callback,(void *)this, DIEDFL_ATTACHEDONLY );
			if( FAILED(hr))
			{
				debug_out::trace("���䃂�[�h�̐ݒ�Ɏ��s���܂����B");
				throw nyx::com_exception("���䃂�[�h�̐ݒ�Ɏ��s���܂����B", hr);
			}

			//�W���C�X�e�B�b�N�f�o�C�X���쐬�ł���
			if (joystickDevice_ != nullptr ) {
				hr = joystickDevice_->SetDataFormat(&c_dfDIJoystick2);
				if( FAILED(hr))
				{
					debug_out::trace("�f�[�^�`���̐ݒ�Ɏ��s���܂����B");
					throw nyx::com_exception("�f�[�^�`���̐ݒ�Ɏ��s���܂����B", hr);
				}

				//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
				hr = joystickDevice_->SetCooperativeLevel(hwnd_, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
				if( FAILED(hr))
				{
					debug_out::trace("���䃂�[�h�̐ݒ�Ɏ��s���܂����B");
					throw nyx::com_exception("���䃂�[�h�̐ݒ�Ɏ��s���܂����B", hr);

				}
				// �R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
				hr = joystickDevice_->EnumObjects(enum_axis_callback,(void*)this, DIDFT_AXIS);
				if( FAILED(hr))
				{
					debug_out::trace("�����[�h�̐ݒ�Ɏ��s���܂����B");
					throw nyx::com_exception("�����[�h�̐ݒ�Ɏ��s���܂����B", hr);
				}


				//����������
				isInitialized =true;
			}
			else {
				joystickDevice_= nullptr;
			}
		}



		bool update() {
			HRESULT hr;
			//�o�b�t�@�t���b�v��
			flip();


			//Acquire���Ƃ��̂�
			if  (isAcquire_ == false ) {
				if (acquire() == false)  {
					::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BUFFER_SIZE);
					return false;  
				}
			}

			//�W���C�X�e�B�b�N���|�[�����Ȃ͂�
			hr = joystickDevice_->Poll();
			if (FAILED(hr)) {
				if (!acquire()) {
					return false;
				}
			}

			//�W���C�X�e�B�b�N�̏�ԂƂ��
			DIJOYSTATE2 dijs= {};
			ZeroMemory(&dijs, sizeof(DIJOYSTATE2));
			hr = joystickDevice_->GetDeviceState(sizeof(DIJOYSTATE2),&dijs );
			if(hr == DIERR_INPUTLOST) {
				// ���s������Acquire����
				if (!acquire()) {
					//acquire�ł��ւ񂩂����B
					//isAcquire = false;
					return true;
				}
				//	����ok
				hr = joystickDevice_->GetDeviceState(sizeof(DIJOYSTATE2),&dijs);
			} 

			if (SUCCEEDED(hr)) {
				//�L�[�o�b�t�@���X�V����O�ɁA��x�N���A���Ă���
				::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BUFFER_SIZE);
				//�L�[�o�b�t�@�X�V���Ă���[
				//0~3�̓W���C�X�e�B�b�N�̎��̏�ԂȂ���0�Ԗڂ�x, x, y, -y, z, -z�̏��Ԃɂ͂����Ƃ��
				if (dijs.lX >= allowRange_) {
					keyBuffer_[flipCounter_][0] = 0x80;
					axis_.x = dijs.lX / 1000.f;	
				}
				if (dijs.lX <= -allowRange_) {
					keyBuffer_[flipCounter_][1] = 0x80;
					axis_.x = dijs.lX / 1000.f;	
				}
				if (dijs.lY >= allowRange_) {
					keyBuffer_[flipCounter_][2] = 0x80;
					axis_.y = dijs.lY / 1000.f;	
				}
				if (dijs.lY <= -allowRange_) {
					keyBuffer_[flipCounter_][3] = 0x80;
					axis_.y = dijs.lY / 1000.f;	
				}
				if (dijs.lZ >= allowRange_) {
					keyBuffer_[flipCounter_][4] = 0x80;
					axis_.z = dijs.lZ / 1000.f;	
				}
				if (dijs.lZ <= -allowRange_) {
					keyBuffer_[flipCounter_][5] = 0x80;
					axis_.z = dijs.lZ / 1000.f;	
				}

				//4�Ԗڈȍ~�̓W���C�X�e�B�b�N�{�^���̏�Ԃ�
				//�f�t�H���g�͂R�Q��D�K�v�ɉ�����SetButton�Ń{�^������K���ɒ���������
				int buttonNum = get_button_num();
				for (int i=0; i < buttonNum; i++) {
					keyBuffer_[flipCounter_][6 + i] = (dijs.rgbButtons[i] & 0x80);
				}

			}
			if (FAILED(hr)) {
				//	�o�b�t�@���N���A���Ė߂�B�i��ʊO�Ƀt�H�[�J�X���ڂ����Ƃ��ɉ������ςȂ�
				//	�ɂȂ�̂�h�����߁j
				::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BUFFER_SIZE);
				return false;       
			}

			return true;
		}


		//-----------------------------------------------------------------------------------------
		//
		axis3f get_axis() {
			return axis_;
		}

		//-----------------------------------------------------------------------------------------
		//
		void  release() {
			// DirectInput�̃f�o�C�X�����
			if (joystickDevice_) {
				joystickDevice_->Unacquire();
			}
		}

		//-----------------------------------------------------------------------------------------
		//
		bool acquire() {
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
		bool unacquire() {
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
		static int CALLBACK enum_joysticks_callback(const DIDEVICEINSTANCE* lpddi, VOID* lpContext) {
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
		static int  CALLBACK enum_axis_callback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
			HRESULT hr;

			// ���̒l�͈̔͂�ݒ�i-2000�`2000�j
			DIPROPRANGE diprg = {};
			ZeroMemory(&diprg, sizeof(diprg));
			diprg.diph.dwSize	    = sizeof(diprg); 
			diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
			diprg.diph.dwObj		= lpddoi->dwType;
			diprg.diph.dwHow		= DIPH_BYID;
			diprg.lMin				= -1000;
			diprg.lMax				= +1000;

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
		axis3f    axis_;
		DirectInputPtr joystick_;
		DirectInputDevicePtr joystickDevice_;
	};

	//-----------------------------------------------------------------------------------------
	//
	joystick::joystick()
		:pimpl_(std::make_shared<PImpl>())
	{
	}

	//-----------------------------------------------------------------------------------------
	//
	joystick::joystick(const input_device_desc& desc)
		:pimpl_(std::make_shared<PImpl>())
	{
		NYX_ASSERT(pimpl_ != nullptr);
		initialize(desc);

		NYX_ASSERT(pimpl_!= nullptr);
	}

	//-----------------------------------------------------------------------------------------
	//
	joystick::~joystick()  {
		pimpl_->release();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool joystick::is_initialized() {
		return pimpl_->isInitialized;
	}

	//-----------------------------------------------------------------------------------------
	//
	bool joystick::initialize(const input_device_desc& desc) {
		NYX_ASSERT(pimpl_ != nullptr);
		if (is_initialized()) {
			return is_initialized();
		}		

		pimpl_->initialize((HWND)desc.handle, desc.range, desc.button);

		return pimpl_->isInitialized;
	}
	//-----------------------------------------------------------------------------------------
	//
	bool joystick::update() {
		NYX_ASSERT(pimpl_!= nullptr);
		if (pimpl_->isInitialized == false) {
			return false;
		}

		return pimpl_->update();
	}

	//-----------------------------------------------------------------------------------------
	//
	void  joystick::release() {
		NYX_ASSERT(pimpl_!= nullptr);

		return pimpl_->release();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool joystick::acquire() {
		NYX_ASSERT(pimpl_!= nullptr);
		if (pimpl_->isInitialized == false) {
			return false;
		}


		return pimpl_->acquire();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool joystick::unacquire() {
		NYX_ASSERT(pimpl_!= nullptr);
		if (pimpl_->isInitialized == false) {
			return false;
		}


		return pimpl_->unacquire();
	}

	//-----------------------------------------------------------------------------------------
	//
	axis3f joystick::get_axis() {
		NYX_ASSERT(pimpl_ != nullptr);
		if (pimpl_->isInitialized == false) {
			return axis3f(-1.f, -1.f, -1.f);
		}


		return pimpl_->get_axis();
	}

	//-----------------------------------------------------------------------------------------
	//
	uint8_t* joystick::get_key_buffer() {
		NYX_ASSERT(pimpl_ != nullptr);
		if (pimpl_->isInitialized == false) {
			return nullptr;
		}


		return pimpl_->get_key_buffer();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool joystick::is_pushed(JOYSTICK_BUTTON keycode) {
		NYX_ASSERT(pimpl_ != nullptr);
		if (pimpl_->isInitialized == false) {
			return false;
		}


		uint8_t key = static_cast<uint8_t>(keycode);
		return pimpl_->is_pushed(key);
	}

	//-----------------------------------------------------------------------------------------
	//
	bool joystick::is_pressed(JOYSTICK_BUTTON keycode) {
		NYX_ASSERT(pimpl_ != nullptr);
		if (pimpl_->isInitialized == false) {
			return false;
		}


		uint8_t key = static_cast<uint8_t>(keycode);
		return pimpl_->is_pressed(key);
	}

	//-----------------------------------------------------------------------------------------
	//
	void joystick::set_button_num(const size_t num) {
		NYX_ASSERT(pimpl_!= nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		pimpl_->set_button_num(num);
	}

	//-----------------------------------------------------------------------------------------
	//
	size_t joystick::get_button_num() {
		NYX_ASSERT(pimpl_!= nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->get_button_num();
	}
}