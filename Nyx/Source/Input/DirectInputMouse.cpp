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
#include "Utility/Common.h"
#include "Utility/Exception.h"
#include "DirectInputMouse.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	DirectInputMouse::DirectInputMouse(HWND hwnd_) {
		hwnd = hwnd_;
		isAcquire=false;

		HRESULT hr;
		// DirectInputの作成
		hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mouse, NULL);
		Assert(hr == DI_OK);

		// デバイス・オブジェクトを作成
		hr = mouse->CreateDevice(GUID_SysMouse, &mouseDevice, NULL); 
		Assert(hr == DI_OK);

		// データ形式を設定
		hr = mouseDevice->SetDataFormat(&c_dfDIMouse2);
		Assert(hr == DI_OK);

		//モードを設定（フォアグラウンド＆非排他モード）
		hr = mouseDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		Assert(hr == DI_OK);

		// 軸モードを設定（相対値モードに設定）
		DIPROPDWORD diprop;
		diprop.diph.dwSize	= sizeof(diprop); 
		diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
		diprop.diph.dwObj	= 0;
		diprop.diph.dwHow	= DIPH_DEVICE;
		diprop.dwData		= DIPROPAXISMODE_REL;
		//	diprop.dwData		= DIPROPAXISMODE_ABS;	// 絶対値モードは事実上使えない
		hr = mouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
		Assert(hr == DI_OK);

		// バッファリング・データを取得するため、バッファ・サイズを設定
		diprop.dwData = BufferSize;
		hr = mouseDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
		Assert(hr == DI_OK);

	}

	//-------------------------------------------------------------------------------------------------------
	//
	DirectInputMouse::~DirectInputMouse() {
		Release();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool DirectInputMouse::Update() {
		if (isAcquire == false) {
			//acquireしとらんのか
			if (!Acquire()) { 
				::ZeroMemory(&mouseState, sizeof(mouseState));
				return false;//acuire失敗。
			}

			return true;
		}


		HRESULT hr = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState);
		if (hr == DIERR_INPUTLOST) {
			if(!Acquire()) {
				return false;
			}
			hr = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState);
		}
		if (hr == DI_OK) {
			relativePos.x = static_cast<int>(mouseState.lX);
			relativePos.y = static_cast<int>(mouseState.lY);
			wheelState = mouseState.lZ;
		}
		else {
			//	バッファをクリアして戻る。（画面外にフォーカスが移ったときに押しっぱなし
			//	になるのを防ぐため）
			::ZeroMemory(&mouseState, sizeof(mouseState));
			return false;       
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------------------
	//
	bool DirectInputMouse::GetMouseButton(Nyx::uchar keycode) {
	}
	//-------------------------------------------------------------------------------------------------------
	//
	Point2i DirectInputMouse::GetRelativePos() {
	}

	//-------------------------------------------------------------------------------------------------------
	//
	Point2i DirectInputMouse::GetAbsolutePos() {
	}

	//-------------------------------------------------------------------------------------------------------
	//
	int DirectInputMouse::GetWheelState() {
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool DirectInputMouse::Acquire() {
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool DirectInputMouse::Unacquire(){
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectInputMouse::Release() {
	}
}