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
			//メンバ初期化
			::ZeroMemory(&joyCaps_, sizeof(joyCaps_));
			allowRange_ = range;
			SetButtonMax(buttonNum);

			//DirectInputオブジェクトの作成
			LPDIRECTINPUT8 joystick = NULL;
			HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&joystick, NULL );
			if(FAILED(hr)) 
			{
				DebugOutput::Trace("DirectInputオブジェクトの生成に失敗しました。");
				throw Nyx::COMException("DirectInputオブジェクトの生成に失敗しました。", hr);
			}

			//デバイスの列挙
			hr = joystick->EnumDevices(
				DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,(void *)this, DIEDFL_ATTACHEDONLY );
			if( FAILED(hr))
			{
				DebugOutput::Trace("制御モードの設定に失敗しました。");
				throw Nyx::COMException("制御モードの設定に失敗しました。", hr);
			}

			//ジョイスティックデバイスが作成できた
			if (joystickDevice_ != nullptr ) {
				hr = joystickDevice_->SetDataFormat(&c_dfDIJoystick2);
				if( FAILED(hr))
				{
					DebugOutput::Trace("データ形式の設定に失敗しました。");
					throw Nyx::COMException("データ形式の設定に失敗しました。", hr);
				}

				//モードを設定（フォアグラウンド＆非排他モード）
				hr = joystickDevice_->SetCooperativeLevel(hwnd_, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
				if( FAILED(hr))
				{
					DebugOutput::Trace("制御モードの設定に失敗しました。");
					throw Nyx::COMException("制御モードの設定に失敗しました。", hr);

				}
				// コールバック関数を使って各軸のモードを設定
				hr = joystickDevice_->EnumObjects(EnumAxesCallback,(void*)this, DIDFT_AXIS);
				if( FAILED(hr))
				{
					DebugOutput::Trace("軸モードの設定に失敗しました。");
					throw Nyx::COMException("軸モードの設定に失敗しました。", hr);
				}


				//初期化成功
				isInitialized =true;
			}
			else {
				joystickDevice_= nullptr;
			}
		}



		bool Update() {
			HRESULT hr;
			//バッファフリップや
			Flip();


			//Acquireしとらんのか
			if  (isAcquire_ == false ) {
				if (Acquire() == false)  {
					::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BufferSize);
					return false;  
				}
			}

			//ジョイスティックをポールしなはれ
			hr = joystickDevice_->Poll();
			if (FAILED(hr)) {
				if (!Acquire()) {
					return false;
				}
			}

			//ジョイスティックの状態とるよ
			DIJOYSTATE2 dijs= {};
			ZeroMemory(&dijs, sizeof(DIJOYSTATE2));
			hr = joystickDevice_->GetDeviceState(sizeof(DIJOYSTATE2),&dijs );
			if(hr == DIERR_INPUTLOST) {
				// 失敗したらAcquireする
				if (!Acquire()) {
					//acquireでけへんかった。
					//isAcquire = false;
					return true;
				}
				//	一回はok
				hr = joystickDevice_->GetDeviceState(sizeof(DIJOYSTATE2),&dijs);
			} 

			if (SUCCEEDED(hr)) {
				//キーバッファを更新する前に、一度クリアしておく
				::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BufferSize);
				//キーバッファ更新してくよー
				//0~3はジョイスティックの軸の状態なんやで0番目から上下左右の順番にはいっとるよ
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

				//4番目以降はジョイスティックボタンの状態や
				//デフォルトは３２個や．必要に応じてSetButtonでボタン数を適当に調整せいよ
				int buttonNum = GetButtonMax();
				for (int i=0; i < buttonNum; i++) {
					keyBuffer_[flipCounter_][4 + i] = (dijs.rgbButtons[i] & 0x80);
				}

			}
			if (hr != DI_OK) {
				//	バッファをクリアして戻る。（画面外にフォーカスが移ったときに押しっぱなし
				//	になるのを防ぐため）
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
			// DirectInputのデバイスを解放
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
			// 列挙されたジョイスティックへのインターフェイスを取得する。
			HRESULT hr;
			PImpl* joy = reinterpret_cast<PImpl*>(lpContext);
			LPDIRECTINPUTDEVICE8 joyDevice;
			hr = joy->joystick_->CreateDevice(lpddi->guidInstance, &joyDevice, NULL );
			if( FAILED(hr)) {  
				return DIENUM_CONTINUE;
			}

			//ジョイスティックの能力を調べる
			joy->joyCaps_.dwSize = sizeof(DIDEVCAPS);
			hr = joyDevice->GetCapabilities( &joy->joyCaps_);
			if (FAILED(hr)) {//デバイスの能力を取れなかった
				return DIENUM_CONTINUE;
			}

			// このデバイスを使用
			joy->joystickDevice_ = DirectInputDevicePtr(joyDevice, false);
			return DIENUM_STOP;

		}

		//-----------------------------------------------------------------------------------------
		// ジョイスティックの軸を列挙する関数
		static int  CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
			HRESULT hr;

			// 軸の値の範囲を設定（-2000～2000）
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