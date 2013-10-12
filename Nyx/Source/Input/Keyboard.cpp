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


			// DirectInputの作成
			LPDIRECTINPUT8 keyboard = NULL;
			HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&keyboard, NULL); 
			if (FAILED(hr)) {
				DebugOutput::Trace("DirectInputオブジェクトの生成に失敗しました。");
				throw Nyx::COMException("DirectInputオブジェクトの生成に失敗しました。", hr);
			}

			// デバイス・オブジェクトを作成
			LPDIRECTINPUTDEVICE8 keyboardDevice = NULL;
			hr = keyboard->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL); 
			if (FAILED(hr)) {
				DebugOutput::Trace("DirectInputDeviceオブジェクトの生成に失敗しました。");
				throw Nyx::COMException("DirectInputDeviceオブジェクトの生成に失敗しました。", hr);
			}


			// データ形式を設定
			hr = keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
			if (FAILED(hr)) {
				DebugOutput::Trace("データ形式の設定に失敗しました。");
				throw Nyx::COMException("データ形式の設定に失敗しました。", hr);
			}
			//モードを設定（フォアグラウンド＆非排他モード）
			hr = keyboardDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr)) {
				DebugOutput::Trace("制御モードの設定に失敗しました。");
				throw Nyx::COMException("制御モードの設定に失敗しました。", hr);
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
				DebugOutput::Trace("バッファサイズの設定に失敗しました。");
				throw Nyx::COMException("バッファサイズの設定に失敗しました。", hr);
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

			//Acquireしとらんのか
			if  (isAcquire_ == false ) {
				if (Acquire() == false)  {
					::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BufferSize);
					return false;  
				}
			}

			//キーボードの状態を読み込む
			hr = keyboardDevice_->GetDeviceState(BufferSize, (LPVOID)&(keyBuffer_[flipCounter_][0]));
			if(hr == DIERR_INPUTLOST) {
				// 失敗したらAcquireする
				if (!Acquire()) {
					//acquireでけへんかった。
					isAcquire_ = false;
					return true;
				}
				//	一回はok
				hr = keyboardDevice_->GetDeviceState(BufferSize, (LPVOID)&(keyBuffer_[flipCounter_][0]));
			} 

			if (hr != DI_OK) {
				//	バッファをクリアして戻る。（画面外にフォーカスが移ったときに押しっぱなし
				//	になるのを防ぐため）
				::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BufferSize);
				return false;       
			}

			return true;
		}


		void  Release() {
			// DirectInputのデバイスを解放
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