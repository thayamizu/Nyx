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
#include "Mouse.h"
#include "InputDeviceDesc.h"
#include "DirectInputDefinition.h"

namespace nyx {


	const int mouse::BUFFER_SIZE			= 8;
	const int mouse::INPUT_DEVICE_NUM		= 16;
	const int mouse::MOUSE_BUTTON_MAX		= 8;

	struct mouse::PImpl {
		bool isInitialized;

		PImpl() : 
			hwnd_(nullptr), position_(), isAcquire_(false), isInitialized(false),
			wheelState_(),
			mouseState_(),
			mouse_(nullptr),
			mouseDevice_(nullptr)
		{

		}

		//-------------------------------------------------------------------------------------------------------
		//
		void initialize(HWND hwnd) 
		{
			hwnd_ = hwnd;
			// DirectInput�̍쐬
			LPDIRECTINPUT8 mouse = nullptr;
			HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mouse, NULL);
			if (FAILED(hr)) {
				debug_out::trace("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
				throw nyx::com_exception("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B", hr);
			}

			// �f�o�C�X�E�I�u�W�F�N�g���쐬
			LPDIRECTINPUTDEVICE8 mouseDevice;
			hr = mouse->CreateDevice(GUID_SysMouse, &mouseDevice, NULL); 
			if (FAILED(hr)) {
				debug_out::trace("DirectInputDevice�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
				throw nyx::com_exception("DirectInputDevice�I�u�W�F�N�g�̐����Ɏ��s���܂����B", hr);
			}

			// �f�[�^�`����ݒ�
			hr = mouseDevice->SetDataFormat(&c_dfDIMouse2);
			if (FAILED(hr)) {
				debug_out::trace("�f�[�^�`���̐ݒ�Ɏ��s���܂����B");
				throw nyx::com_exception("�f�[�^�`���̐ݒ�Ɏ��s���܂����B", hr);
			}

			//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
			hr = mouseDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr)) {
				debug_out::trace("���䃂�[�h�̐ݒ�Ɏ��s���܂����B");
				throw nyx::com_exception("���䃂�[�h�̐ݒ�Ɏ��s���܂����B", hr);
			}

			// �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
			DIPROPDWORD diprop = {};
			diprop.diph.dwSize	= sizeof(diprop); 
			diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
			diprop.diph.dwObj	= 0;
			diprop.diph.dwHow	= DIPH_DEVICE;
			diprop.dwData		= DIPROPAXISMODE_REL;
			//	diprop.dwData		= DIPROPAXISMODE_ABS;	// ��Βl���[�h�͎�����g���Ȃ�
			hr = mouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
			if (FAILED(hr)) {
				debug_out::trace("�����[�h�̐ݒ�Ɏ��s���܂����B");
				throw nyx::com_exception("�����[�h�̐ݒ�Ɏ��s���܂����B", hr);
			}

			// �o�b�t�@�����O�E�f�[�^���擾���邽�߁A�o�b�t�@�E�T�C�Y��ݒ�
			diprop.dwData = BUFFER_SIZE;
			hr = mouseDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
			if (FAILED(hr)) {
				debug_out::trace("�o�b�t�@�T�C�Y�̐ݒ�Ɏ��s���܂����B");
				throw nyx::com_exception("�o�b�t�@�T�C�Y�̐ݒ�Ɏ��s���܂����B", hr);
			}


			mouse_ = DirectInputPtr(mouse, false);
			mouseDevice_ = DirectInputDevicePtr(mouseDevice, false);

			isInitialized = true;

		}

		//-------------------------------------------------------------------------------------------------------
		//
		~PImpl() {
			release();
		}

		//-------------------------------------------------------------------------------------------------------
		//
		bool update() {
			if (isAcquire_ == false) {
				//acquire���Ƃ��̂�
				if (!acquire()) { 
					::ZeroMemory(&mouseState_, sizeof(mouseState_));
					return false;//acuire���s�B
				}

				return true;
			}


			HRESULT hr = mouseDevice_->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState_);
			if (hr == DIERR_INPUTLOST) {
				if(!acquire()) {
					return false;
				}
				hr = mouseDevice_->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState_);
			}
			if (hr == DI_OK) {
				wheelState_ = mouseState_.lZ;
			}
			else {
				//	�o�b�t�@���N���A���Ė߂�B�i��ʊO�Ƀt�H�[�J�X���ڂ����Ƃ��ɉ������ςȂ�
				//	�ɂȂ�̂�h�����߁j
				::ZeroMemory(&mouseState_, sizeof(mouseState_));
				return false;       
			}

		

			return true;
		}
		//-------------------------------------------------------------------------------------------------------
		//
		bool get_mouse_button(MOUSE_BUTTON button) {
			auto keycode = static_cast<uint8_t>(button);
			if(keycode >= MOUSE_BUTTON_MAX) {
				return false;
			}

			return (mouseState_.rgbButtons[keycode] & 0x80) !=0;
		}
		//-------------------------------------------------------------------------------------------------------
		//
		point2i get_position() {
			POINT pos;
			GetCursorPos(&pos);
			ScreenToClient(this->hwnd_, &pos);
			this->position_.x = pos.x;
			this->position_.y = pos.y;

			return position_;

		}

		//-------------------------------------------------------------------------------------------------------
		//
		int get_wheel_state() {
			return wheelState_;
		}

		//-------------------------------------------------------------------------------------------------------
		//
		bool acquire() {
			HRESULT hr = mouseDevice_->Acquire();
			if (hr == DI_OK) {
				isAcquire_ = true;
			}
			else {
				isAcquire_ = false;
			}

			return isAcquire_;
		}

		//-------------------------------------------------------------------------------------------------------
		//
		bool unacquire(){
			if (isAcquire_ == false ) {
				//acquire����ĂȂ�����
				return false;
			}

			HRESULT hr = mouseDevice_->Unacquire();
			if (SUCCEEDED(hr)) {
				isAcquire_ = false;
			}
			else {
				isAcquire_ = true;
			}

			return !isAcquire_;
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void release() {
			if (mouseDevice_) {
				unacquire();
			}

		}
	private:
		int  wheelState_;
		bool isAcquire_;
		char align[3];
		HWND hwnd_;
		point2i position_;
		DIMOUSESTATE2 mouseState_;
		DirectInputPtr mouse_;
		DirectInputDevicePtr mouseDevice_;
	};

	//-------------------------------------------------------------------------------------------------------
	//
	mouse::mouse() 
		:pimpl_(std::make_shared<PImpl>())
	{
	}
	//-------------------------------------------------------------------------------------------------------
	//
	mouse::mouse(const input_device_desc& desc) 
		:pimpl_(std::make_shared<PImpl>())
	{

		if (initialize(desc) == false) {
			nyx::debug_out::trace("�}�E�X�f�o�C�X�̏������Ɏ��s���܂����B");
			throw nyx::com_exception("�}�E�X�̏������Ɏ��s���܂����B", 0);
		}

		NYX_ASSERT(pimpl_!= nullptr);
		NYX_ASSERT(pimpl_->isInitialized);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	mouse::mouse(const mouse& other) {
		this->pimpl_ = other.pimpl_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool mouse::initialize(const input_device_desc& desc) {
		NYX_ASSERT(pimpl_ != nullptr);
		if (is_initialized()) {
			return is_initialized();
		}

		pimpl_->initialize((HWND)desc.handle);

		return is_initialized();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool mouse::is_initialized() {
		return pimpl_->isInitialized;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool mouse::update() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->update();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool mouse::get_mouse_button(MOUSE_BUTTON keycode) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->get_mouse_button(keycode);
	}

	
	//-------------------------------------------------------------------------------------------------------
	//
	point2i mouse::get_position() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->get_position();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	int mouse::get_wheel_state() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->get_wheel_state();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool mouse::acquire() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->acquire();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool mouse::unacquire(){
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->unacquire();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void mouse::release() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		pimpl_->release();
	}
}