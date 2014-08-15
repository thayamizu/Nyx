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
			// DirectInputの作成
			LPDIRECTINPUT8 mouse = nullptr;
			HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mouse, NULL);
			if (FAILED(hr)) {
				debug_out::trace("DirectInputオブジェクトの生成に失敗しました。");
				throw nyx::com_exception("DirectInputオブジェクトの生成に失敗しました。", hr);
			}

			// デバイス・オブジェクトを作成
			LPDIRECTINPUTDEVICE8 mouseDevice;
			hr = mouse->CreateDevice(GUID_SysMouse, &mouseDevice, NULL); 
			if (FAILED(hr)) {
				debug_out::trace("DirectInputDeviceオブジェクトの生成に失敗しました。");
				throw nyx::com_exception("DirectInputDeviceオブジェクトの生成に失敗しました。", hr);
			}

			// データ形式を設定
			hr = mouseDevice->SetDataFormat(&c_dfDIMouse2);
			if (FAILED(hr)) {
				debug_out::trace("データ形式の設定に失敗しました。");
				throw nyx::com_exception("データ形式の設定に失敗しました。", hr);
			}

			//モードを設定（フォアグラウンド＆非排他モード）
			hr = mouseDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr)) {
				debug_out::trace("制御モードの設定に失敗しました。");
				throw nyx::com_exception("制御モードの設定に失敗しました。", hr);
			}

			// 軸モードを設定（相対値モードに設定）
			DIPROPDWORD diprop = {};
			diprop.diph.dwSize	= sizeof(diprop); 
			diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
			diprop.diph.dwObj	= 0;
			diprop.diph.dwHow	= DIPH_DEVICE;
			diprop.dwData		= DIPROPAXISMODE_REL;
			//	diprop.dwData		= DIPROPAXISMODE_ABS;	// 絶対値モードは事実上使えない
			hr = mouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
			if (FAILED(hr)) {
				debug_out::trace("軸モードの設定に失敗しました。");
				throw nyx::com_exception("軸モードの設定に失敗しました。", hr);
			}

			// バッファリング・データを取得するため、バッファ・サイズを設定
			diprop.dwData = BUFFER_SIZE;
			hr = mouseDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
			if (FAILED(hr)) {
				debug_out::trace("バッファサイズの設定に失敗しました。");
				throw nyx::com_exception("バッファサイズの設定に失敗しました。", hr);
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
				//acquireしとらんのか
				if (!acquire()) { 
					::ZeroMemory(&mouseState_, sizeof(mouseState_));
					return false;//acuire失敗。
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
				//	バッファをクリアして戻る。（画面外にフォーカスが移ったときに押しっぱなし
				//	になるのを防ぐため）
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
				//acquireされてないんやで
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
			nyx::debug_out::trace("マウスデバイスの初期化に失敗しました。");
			throw nyx::com_exception("マウスの初期化に失敗しました。", 0);
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