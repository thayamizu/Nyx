/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
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


			// DirectInputの作成
			LPDIRECTINPUT8 keyboard = NULL;
			HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&keyboard, NULL); 
			if (FAILED(hr)) {
				debug_out::trace("DirectInputオブジェクトの生成に失敗しました。");
				throw nyx::com_exception("DirectInputオブジェクトの生成に失敗しました。", hr);
			}

			// デバイス・オブジェクトを作成
			LPDIRECTINPUTDEVICE8 keyboardDevice = NULL;
			hr = keyboard->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL); 
			if (FAILED(hr)) {
				debug_out::trace("DirectInputDeviceオブジェクトの生成に失敗しました。");
				throw nyx::com_exception("DirectInputDeviceオブジェクトの生成に失敗しました。", hr);
			}


			// データ形式を設定
			hr = keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
			if (FAILED(hr)) {
				debug_out::trace("データ形式の設定に失敗しました。");
				throw nyx::com_exception("データ形式の設定に失敗しました。", hr);
			}
			//モードを設定（フォアグラウンド＆非排他モード）
			hr = keyboardDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr)) {
				debug_out::trace("制御モードの設定に失敗しました。");
				throw nyx::com_exception("制御モードの設定に失敗しました。", hr);
			}
			// バッファリング・データを取得するため、バッファ・サイズを設定
			DIPROPDWORD diprop = {};
			diprop.diph.dwSize	= sizeof(diprop); 
			diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
			diprop.diph.dwObj	= 0;
			diprop.diph.dwHow	= DIPH_DEVICE;
			diprop.dwData = 255;
			hr = keyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
			if (FAILED(hr)) {
				debug_out::trace("バッファサイズの設定に失敗しました。");
				throw nyx::com_exception("バッファサイズの設定に失敗しました。", hr);
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

			//Acquireしとらんのか
			if  (isAcquire_ == false ) {
				if (acquire() == false)  {
					::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BUFFER_SIZE);
					return false;  
				}
			}

			//キーボードの状態を読み込む
			hr = keyboardDevice_->GetDeviceState(BUFFER_SIZE, (LPVOID)&(keyBuffer_[flipCounter_][0]));
			if(hr == DIERR_INPUTLOST) {
				// 失敗したらAcquireする
				if (!acquire()) {
					//acquireでけへんかった。
					isAcquire_ = false;
					return true;
				}
				//	一回はok
				hr = keyboardDevice_->GetDeviceState(BUFFER_SIZE, (LPVOID)&(keyBuffer_[flipCounter_][0]));
			} 

			if (hr != DI_OK) {
				//	バッファをクリアして戻る。（画面外にフォーカスが移ったときに押しっぱなし
				//	になるのを防ぐため）
				::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BUFFER_SIZE);
				return false;       
			}

			return true;
		}


		void  release() {
			// DirectInputのデバイスを解放
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
				//acquireされとらん
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