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
			//メンバ初期化
			::ZeroMemory(&joyCaps_, sizeof(joyCaps_));
			allowRange_ = range;
			set_button_num(buttonNum);

			//DirectInputオブジェクトの作成
			LPDIRECTINPUT8 joystick = NULL;
			HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&joystick, NULL );
			if(FAILED(hr)) 
			{
				debug_out::trace("DirectInputオブジェクトの生成に失敗しました。");
				throw nyx::com_exception("DirectInputオブジェクトの生成に失敗しました。", hr);
			}
			joystick_ = DirectInputPtr(joystick);

			//デバイスの列挙
			hr = joystick_->EnumDevices(
				DI8DEVCLASS_GAMECTRL, enum_joysticks_callback,(void *)this, DIEDFL_ATTACHEDONLY );
			if( FAILED(hr))
			{
				debug_out::trace("制御モードの設定に失敗しました。");
				throw nyx::com_exception("制御モードの設定に失敗しました。", hr);
			}

			//ジョイスティックデバイスが作成できた
			if (joystickDevice_ != nullptr ) {
				hr = joystickDevice_->SetDataFormat(&c_dfDIJoystick2);
				if( FAILED(hr))
				{
					debug_out::trace("データ形式の設定に失敗しました。");
					throw nyx::com_exception("データ形式の設定に失敗しました。", hr);
				}

				//モードを設定（フォアグラウンド＆非排他モード）
				hr = joystickDevice_->SetCooperativeLevel(hwnd_, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
				if( FAILED(hr))
				{
					debug_out::trace("制御モードの設定に失敗しました。");
					throw nyx::com_exception("制御モードの設定に失敗しました。", hr);

				}
				// コールバック関数を使って各軸のモードを設定
				hr = joystickDevice_->EnumObjects(enum_axis_callback,(void*)this, DIDFT_AXIS);
				if( FAILED(hr))
				{
					debug_out::trace("軸モードの設定に失敗しました。");
					throw nyx::com_exception("軸モードの設定に失敗しました。", hr);
				}


				//初期化成功
				isInitialized =true;
			}
			else {
				joystickDevice_= nullptr;
			}
		}



		bool update() {
			HRESULT hr;
			//バッファフリップや
			flip();


			//Acquireしとらんのか
			if  (isAcquire_ == false ) {
				if (acquire() == false)  {
					::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BUFFER_SIZE);
					return false;  
				}
			}

			//ジョイスティックをポールしなはれ
			hr = joystickDevice_->Poll();
			if (FAILED(hr)) {
				if (!acquire()) {
					return false;
				}
			}

			//ジョイスティックの状態とるよ
			DIJOYSTATE2 dijs= {};
			ZeroMemory(&dijs, sizeof(DIJOYSTATE2));
			hr = joystickDevice_->GetDeviceState(sizeof(DIJOYSTATE2),&dijs );
			if(hr == DIERR_INPUTLOST) {
				// 失敗したらAcquireする
				if (!acquire()) {
					//acquireでけへんかった。
					//isAcquire = false;
					return true;
				}
				//	一回はok
				hr = joystickDevice_->GetDeviceState(sizeof(DIJOYSTATE2),&dijs);
			} 

			if (SUCCEEDED(hr)) {
				//キーバッファを更新する前に、一度クリアしておく
				::ZeroMemory((LPVOID)&(keyBuffer_[flipCounter_][0]), BUFFER_SIZE);
				//キーバッファ更新してくよー
				//0~3はジョイスティックの軸の状態なんやで0番目かx, x, y, -y, z, -zの順番にはいっとるよ
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

				//4番目以降はジョイスティックボタンの状態や
				//デフォルトは３２個や．必要に応じてSetButtonでボタン数を適当に調整せいよ
				int buttonNum = get_button_num();
				for (int i=0; i < buttonNum; i++) {
					keyBuffer_[flipCounter_][6 + i] = (dijs.rgbButtons[i] & 0x80);
				}

			}
			if (FAILED(hr)) {
				//	バッファをクリアして戻る。（画面外にフォーカスが移ったときに押しっぱなし
				//	になるのを防ぐため）
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
			// DirectInputのデバイスを解放
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
		static int  CALLBACK enum_axis_callback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
			HRESULT hr;

			// 軸の値の範囲を設定（-2000～2000）
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