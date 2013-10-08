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

namespace Nyx {


	const int Mouse::BufferSize			= 8;
	const int Mouse::InputDeviceNum		= 16;
	const int Mouse::MouseButtonMax		= 8;

	struct Mouse::PImpl {
		bool isInitialized;

		PImpl() : 
			hwnd_(NULL), absolutePos_(), relativePos_(), isAcquire_(false),
			wheelState_(),
			mouseState_(),
			mouse_(),
			mouseDevice_()
		{

		}

		//-------------------------------------------------------------------------------------------------------
		//
		void Initialize(HWND hwnd) 
		{
			hwnd_ = hwnd;
			// DirectInput�̍쐬
			LPDIRECTINPUT8 mouse = nullptr;
			HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mouse_, NULL);
			if (FAILED(hr)) {
				DebugOutput::Trace("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
				throw Nyx::COMException("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B", hr);
			}

			// �f�o�C�X�E�I�u�W�F�N�g���쐬
			LPDIRECTINPUTDEVICE8 mouseDevice;
			hr = mouse->CreateDevice(GUID_SysMouse, &mouseDevice, NULL); 
			if (FAILED(hr)) {
				DebugOutput::Trace("DirectInputDevice�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
				throw Nyx::COMException("DirectInputDevice�I�u�W�F�N�g�̐����Ɏ��s���܂����B", hr);
			}

			// �f�[�^�`����ݒ�
			hr = mouseDevice->SetDataFormat(&c_dfDIMouse2);
			if (FAILED(hr)) {
				DebugOutput::Trace("�f�[�^�`���̐ݒ�Ɏ��s���܂����B");
				throw Nyx::COMException("�f�[�^�`���̐ݒ�Ɏ��s���܂����B", hr);
			}

			//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
			hr = mouseDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr)) {
				DebugOutput::Trace("���䃂�[�h�̐ݒ�Ɏ��s���܂����B");
				throw Nyx::COMException("���䃂�[�h�̐ݒ�Ɏ��s���܂����B", hr);
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
				DebugOutput::Trace("�����[�h�̐ݒ�Ɏ��s���܂����B");
				throw Nyx::COMException("�����[�h�̐ݒ�Ɏ��s���܂����B", hr);
			}

			// �o�b�t�@�����O�E�f�[�^���擾���邽�߁A�o�b�t�@�E�T�C�Y��ݒ�
			diprop.dwData = BufferSize;
			hr = mouseDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
			if (FAILED(hr)) {
				DebugOutput::Trace("�o�b�t�@�T�C�Y�̐ݒ�Ɏ��s���܂����B");
				throw Nyx::COMException("�o�b�t�@�T�C�Y�̐ݒ�Ɏ��s���܂����B", hr);
			}


			mouse_ = DirectInputPtr(mouse, false);
			mouseDevice_ = DirectInputDevicePtr(mouseDevice, false);

			isInitialized = true;

		}

		//-------------------------------------------------------------------------------------------------------
		//
		Mouse::PImpl::~PImpl() {
			Release();
		}

		//-------------------------------------------------------------------------------------------------------
		//
		bool Update() {
			if (isAcquire_ == false) {
				//acquire���Ƃ��̂�
				if (!Acquire()) { 
					::ZeroMemory(&mouseState_, sizeof(mouseState_));
					return false;//acuire���s�B
				}

				return true;
			}


			HRESULT hr = mouseDevice_->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState_);
			if (hr == DIERR_INPUTLOST) {
				if(!Acquire()) {
					return false;
				}
				hr = mouseDevice_->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState_);
			}
			if (hr == DI_OK) {
				relativePos_.x = static_cast<int>(mouseState_.lX);
				relativePos_.y = static_cast<int>(mouseState_.lY);
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
		bool GetMouseButton(Nyx::uchar keycode) {
			if(keycode >= MouseButtonMax) {
				return false;
			}

			return (mouseState_.rgbButtons[keycode] & 0x80) !=0;
		}
		//-------------------------------------------------------------------------------------------------------
		//
		Point2i GetRelativePos() {
			return relativePos_;
		}

		//-------------------------------------------------------------------------------------------------------
		//
		Point2i GetAbsolutePos() {
			return absolutePos_;
		}

		//-------------------------------------------------------------------------------------------------------
		//
		int GetWheelState() {
			return wheelState_;
		}

		//-------------------------------------------------------------------------------------------------------
		//
		bool Acquire() {
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
		bool Unacquire(){
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
		void Release() {
			if (mouseDevice_) {
				Unacquire();
			}
		}
	private:
		HWND hwnd_;
		Point2i absolutePos_;
		Point2i relativePos_;
		bool isAcquire_;
		int wheelState_;
		DIMOUSESTATE2 mouseState_;
		DirectInputPtr mouse_;
		DirectInputDevicePtr mouseDevice_;
	};

	//-------------------------------------------------------------------------------------------------------
	//
	Mouse::Mouse() 
		:pimpl_(std::make_shared<PImpl>())
	{
	}
	//-------------------------------------------------------------------------------------------------------
	//
	Mouse::Mouse(const InputDeviceDesc& desc) 
		:pimpl_(std::make_shared<PImpl>())
	{

		if (Initialize(desc) == false) {
			Nyx::DebugOutput::Trace("�}�E�X�f�o�C�X�̏������Ɏ��s���܂����B");
			throw Nyx::COMException("�}�E�X�̏������Ɏ��s���܂����B", 0);
		}

		Assert(pimpl_!= nullptr);
		Assert(pimpl_->isInitialized);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	Mouse::Mouse(const Mouse& other) {
		this->pimpl_ = other.pimpl_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Initialize(const InputDeviceDesc& desc) {
		Assert(pimpl_ != nullptr);
		if (IsInitialized()) {
			return IsInitialized();
		}

		pimpl_->Initialize((HWND)desc.handle.get());
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::IsInitialized() {
		return pimpl_->isInitialized;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Update() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->Update();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::GetMouseButton(Nyx::uchar keycode) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->GetMouseButton(keycode);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	Point2i Mouse::GetRelativePos() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->GetRelativePos();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	Point2i Mouse::GetAbsolutePos() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->GetAbsolutePos();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	int Mouse::GetWheelState() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->GetWheelState();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Acquire() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->Acquire();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Unacquire(){
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->Unacquire();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void Mouse::Release() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		pimpl_->Release();
	}
}