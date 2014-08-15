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


namespace nyx {
	struct keyboard::PImpl : public ikey_base {
		bool isInitialized;
		PImpl() 
			: isInitialized(false), 
			isAcquire_(false), 
			keyboard_(nullptr), 
			keyboardDevice_(nullptr), 
			ikey_base() 
		{
		}

		void initialize(HWND hwnd_) {


			// DirectInput�̍쐬
			LPDIRECTINPUT8 keyboard = NULL;
			HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&keyboard, NULL); 
			if (FAILED(hr)) {
				debug_out::trace("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
				throw nyx::com_exception("DirectInput�I�u�W�F�N�g�̐����Ɏ��s���܂����B", hr);
			}

			// �f�o�C�X�E�I�u�W�F�N�g���쐬
			LPDIRECTINPUTDEVICE8 keyboardDevice = NULL;
			hr = keyboard->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL); 
			if (FAILED(hr)) {
				debug_out::trace("DirectInputDevice�I�u�W�F�N�g�̐����Ɏ��s���܂����B");
				throw nyx::com_exception("DirectInputDevice�I�u�W�F�N�g�̐����Ɏ��s���܂����B", hr);
			}


			// �f�[�^�`����ݒ�
			hr = keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
			if (FAILED(hr)) {
				debug_out::trace("�f�[�^�`���̐ݒ�Ɏ��s���܂����B");
				throw nyx::com_exception("�f�[�^�`���̐ݒ�Ɏ��s���܂����B", hr);
			}
			//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
			hr = keyboardDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr)) {
				debug_out::trace("���䃂�[�h�̐ݒ�Ɏ��s���܂����B");
				throw nyx::com_exception("���䃂�[�h�̐ݒ�Ɏ��s���܂����B", hr);
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
				debug_out::trace("�o�b�t�@�T�C�Y�̐ݒ�Ɏ��s���܂����B");
				throw nyx::com_exception("�o�b�t�@�T�C�Y�̐ݒ�Ɏ��s���܂����B", hr);
			}


			keyboard_ = DirectInputPtr(keyboard, false);
			keyboardDevice_ = DirectInputDevicePtr(keyboardDevice, false);

			isInitialized = true;
		}
		
		
		~PImpl()  {
			release();
		}


		bool update() {
			HRESULT hr;
			flip();

			//Acquire���Ƃ��̂�
			if  (isAcquire_ == false ) {
				if (acquire() == false)  {
					::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BUFFER_SIZE);
					return false;  
				}
			}

			//�L�[�{�[�h�̏�Ԃ�ǂݍ���
			hr = keyboardDevice_->GetDeviceState(BUFFER_SIZE, (LPVOID)&(keyBuffer_[flipCounter_][0]));
			if(hr == DIERR_INPUTLOST) {
				// ���s������Acquire����
				if (!acquire()) {
					//acquire�ł��ւ񂩂����B
					isAcquire_ = false;
					return true;
				}
				//	����ok
				hr = keyboardDevice_->GetDeviceState(BUFFER_SIZE, (LPVOID)&(keyBuffer_[flipCounter_][0]));
			} 

			if (hr != DI_OK) {
				//	�o�b�t�@���N���A���Ė߂�B�i��ʊO�Ƀt�H�[�J�X���ڂ����Ƃ��ɉ������ςȂ�
				//	�ɂȂ�̂�h�����߁j
				::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BUFFER_SIZE);
				return false;       
			}

			return true;
		}


		void  release() {
			// DirectInput�̃f�o�C�X�����
			if (keyboardDevice_) {
				keyboardDevice_->Unacquire();
			}
		}

		bool acquire() {
			HRESULT hr = keyboardDevice_->Acquire();
			if (hr==DI_OK) {
				isAcquire_ = true;
			} else {
				isAcquire_ = false;
			}
			return isAcquire_;
		}

		bool unacquire() {
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

	keyboard::keyboard() 
		: pimpl_(std::make_shared<PImpl>()) {
	}



	keyboard::keyboard(const input_device_desc& desc) 
		: pimpl_(std::make_shared<PImpl>()) {

			initialize(desc);

			NYX_ASSERT(pimpl_!= nullptr);
			NYX_ASSERT(pimpl_->isInitialized);
	}

	bool keyboard::is_initialized() {
		NYX_ASSERT(pimpl_ != nullptr);

		return pimpl_->isInitialized;
	}

	bool keyboard::initialize(const input_device_desc& desc) {
		NYX_ASSERT(pimpl_ != nullptr);
		if (is_initialized()) {
			return is_initialized();
		}		

		pimpl_->initialize((HWND)desc.handle);

		return pimpl_->isInitialized;
	}


	bool keyboard::update() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->update();
	}


	uint8_t* keyboard::get_key_buffer() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->get_key_buffer();
	}


	bool keyboard::is_pushed(KEYCODE keycode) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		uint8_t key = static_cast<uint8_t>(keycode);
		return pimpl_->is_pushed(key);
	}


	bool keyboard::is_pressed(KEYCODE keycode) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		uint8_t key = static_cast<uint8_t>(keycode);
		return pimpl_->is_pressed(key);
	}


	void  keyboard::release() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		pimpl_->release();
	}


	bool keyboard::acquire() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->acquire();
	}


	bool keyboard::unqcquire() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized);

		return pimpl_->unacquire();
	}
}