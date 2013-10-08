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
			// DirectInputの作成
			LPDIRECTINPUT8 mouse = nullptr;
			HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mouse_, NULL);
			if (FAILED(hr)) {
				DebugOutput::Trace("DirectInputオブジェクトの生成に失敗しました。");
				throw Nyx::COMException("DirectInputオブジェクトの生成に失敗しました。", hr);
			}

			// デバイス・オブジェクトを作成
			LPDIRECTINPUTDEVICE8 mouseDevice;
			hr = mouse->CreateDevice(GUID_SysMouse, &mouseDevice, NULL); 
			if (FAILED(hr)) {
				DebugOutput::Trace("DirectInputDeviceオブジェクトの生成に失敗しました。");
				throw Nyx::COMException("DirectInputDeviceオブジェクトの生成に失敗しました。", hr);
			}

			// データ形式を設定
			hr = mouseDevice->SetDataFormat(&c_dfDIMouse2);
			if (FAILED(hr)) {
				DebugOutput::Trace("データ形式の設定に失敗しました。");
				throw Nyx::COMException("データ形式の設定に失敗しました。", hr);
			}

			//モードを設定（フォアグラウンド＆非排他モード）
			hr = mouseDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr)) {
				DebugOutput::Trace("制御モードの設定に失敗しました。");
				throw Nyx::COMException("制御モードの設定に失敗しました。", hr);
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
				DebugOutput::Trace("軸モードの設定に失敗しました。");
				throw Nyx::COMException("軸モードの設定に失敗しました。", hr);
			}

			// バッファリング・データを取得するため、バッファ・サイズを設定
			diprop.dwData = BufferSize;
			hr = mouseDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
			if (FAILED(hr)) {
				DebugOutput::Trace("バッファサイズの設定に失敗しました。");
				throw Nyx::COMException("バッファサイズの設定に失敗しました。", hr);
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
				//acquireしとらんのか
				if (!Acquire()) { 
					::ZeroMemory(&mouseState_, sizeof(mouseState_));
					return false;//acuire失敗。
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
				//	バッファをクリアして戻る。（画面外にフォーカスが移ったときに押しっぱなし
				//	になるのを防ぐため）
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
			Nyx::DebugOutput::Trace("マウスデバイスの初期化に失敗しました。");
			throw Nyx::COMException("マウスの初期化に失敗しました。", 0);
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