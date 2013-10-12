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
#include "IKeyBase.h"
#include "Keyboard.h"
#include "InputDeviceDesc.h"
#include "DirectInputDefinition.h"


namespace Nyx {
	struct Keyboard::PImpl : public IKeyBase {
		bool isInitialized;
		PImpl() 
			: isInitialized(false), 
			isAcquire_(false), 
			keyboard_(nullptr), 
			keyboardDevice_(nullptr), 
			IKeyBase() 
		{
		}

		void Initialize(HWND hwnd_) {


			// DirectInput�̍쐬
			LPDIRECTINPUT8 keyboard = NULL;
			HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&keyboard, NULL); 
			if (FAILED(hr)) {
				DebugOutput::Trace("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
				throw Nyx::COMException("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B", hr);
			}

			// �f�o�C�X�E�I�u�W�F�N�g���쐬
			LPDIRECTINPUTDEVICE8 keyboardDevice = NULL;
			hr = keyboard->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL); 
			if (FAILED(hr)) {
				DebugOutput::Trace("DirectInputDevice�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
				throw Nyx::COMException("DirectInputDevice�I�u�W�F�N�g�̐����Ɏ��s���܂����B", hr);
			}


			// �f�[�^�`����ݒ�
			hr = keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
			if (FAILED(hr)) {
				DebugOutput::Trace("�f�[�^�`���̐ݒ�Ɏ��s���܂����B");
				throw Nyx::COMException("�f�[�^�`���̐ݒ�Ɏ��s���܂����B", hr);
			}
			//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
			hr = keyboardDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr)) {
				DebugOutput::Trace("���䃂�[�h�̐ݒ�Ɏ��s���܂����B");
				throw Nyx::COMException("���䃂�[�h�̐ݒ�Ɏ��s���܂����B", hr);
			}
			// �o�b�t�@�����O�E�f�[�^���擾���邽�߁A�o�b�t�@�E�T�C�Y��ݒ�
			DIPROPDWORD diprop = {};
			diprop.diph.dwSize	= sizeof(diprop); 
			diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
			diprop.diph.dwObj	= 0;
			diprop.diph.dwHow	= DIPH_DEVICE;
			diprop.dwData = 255;
			hr = keyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
			if (FAILED(hr)) {
				DebugOutput::Trace("�o�b�t�@�T�C�Y�̐ݒ�Ɏ��s���܂����B");
				throw Nyx::COMException("�o�b�t�@�T�C�Y�̐ݒ�Ɏ��s���܂����B", hr);
			}


			keyboard_ = DirectInputPtr(keyboard, false);
			keyboardDevice_ = DirectInputDevicePtr(keyboardDevice, false);

			isInitialized = true;
		}
		
		
		~PImpl()  {
			Release();
		}


		bool Update() {
			HRESULT hr;
			Flip();

			//Acquire���Ƃ��̂�
			if  (isAcquire_ == false ) {
				if (Acquire() == false)  {
					::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BufferSize);
					return false;  
				}
			}

			//�L�[�{�[�h�̏�Ԃ�ǂݍ���
			hr = keyboardDevice_->GetDeviceState(BufferSize, (LPVOID)&(keyBuffer_[flipCounter_][0]));
			if(hr == DIERR_INPUTLOST) {
				// ���s������Acquire����
				if (!Acquire()) {
					//acquire�ł��ւ񂩂����B
					isAcquire_ = false;
					return true;
				}
				//	����ok
				hr = keyboardDevice_->GetDeviceState(BufferSize, (LPVOID)&(keyBuffer_[flipCounter_][0]));
			} 

			if (hr != DI_OK) {
				//	�o�b�t�@���N���A���Ė߂�B�i��ʊO�Ƀt�H�[�J�X���ڂ����Ƃ��ɉ������ςȂ�
				//	�ɂȂ�̂�h�����߁j
				::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BufferSize);
				return false;       
			}

			return true;
		}


		void  Release() {
			// DirectInput�̃f�o�C�X�����
			if (keyboardDevice_) {
				keyboardDevice_->Unacquire();
			}
		}

		bool Acquire() {
			HRESULT hr = keyboardDevice_->Acquire();
			if (hr==DI_OK) {
				isAcquire_ = true;
			} else {
				isAcquire_ = false;
			}
			return isAcquire_;
		}

		bool Unacquire() {
			if (isAcquire_ == false) {
				//acquire����Ƃ��
				return false;
			}

			HRESULT hr = keyboardDevice_->Unacquire();
			if (hr==DI_OK) {
				isAcquire_ = false;
			} else {
				isAcquire_ = true;
			}
			return !isAcquire_;
		}
	private:
		bool isAcquire_;
		DirectInputPtr keyboard_;
		DirectInputDevicePtr keyboardDevice_;
	};

	Keyboard::Keyboard() 
		: pimpl_(std::make_shared<PImpl>()) {
	}



	Keyboard::Keyboard(const InputDeviceDesc& desc) 
		: pimpl_(std::make_shared<PImpl>()) {

			Initialize(desc);

			Assert(pimpl_!= nullptr);
			Assert(pimpl_->isInitialized);
	}

	bool Keyboard::IsInitialized() {
		Assert(pimpl_ != nullptr);

		return pimpl_->isInitialized;
	}

	bool Keyboard::Initialize(const InputDeviceDesc& desc) {
		Assert(pimpl_ != nullptr);
		if (IsInitialized()) {
			return IsInitialized();
		}		

		pimpl_->Initialize((HWND)desc.handle);

		return pimpl_->isInitialized;
	}


	bool Keyboard::Update() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->Update();
	}


	uchar* Keyboard::GetKeyBuffer() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->GetKeyBuffer();
	}


	bool Keyboard::IsPushed(KeyCode keycode) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		uchar key = static_cast<uchar>(keycode);
		return pimpl_->IsPushed(key);
	}


	bool Keyboard::IsPressed(KeyCode keycode) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		uchar key = static_cast<uchar>(keycode);
		return pimpl_->IsPressed(key);
	}


	void  Keyboard::Release() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		pimpl_->Release();
	}


	bool Keyboard::Acquire() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->Acquire();
	}


	bool Keyboard::Unacquire() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);

		return pimpl_->Unacquire();
	}
}