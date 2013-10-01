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
#include "DirectInputJoystick.h"


namespace Nyx {
	int DirectInputJoystick::joystickNum = 0;
	//-----------------------------------------------------------------------------------------
	//
	DirectInputJoystick::DirectInputJoystick(HWND hwnd_, int range) 
		: IJoystick(), allowRange(range), joystick(NULL), joystickDevice(NULL), isAcquire(false), isInitialized(false) {
			//JOYINFO joyInfo;
			//メンバ初期化
			::ZeroMemory(&joyCaps, sizeof(joyCaps));

			SetButtonMax(32);
			//	if (joyGetPos(joystickNum++, &joyInfo) != JOYERR_NOERROR) {return;}



			//DirectInputオブジェクトの作成
			HRESULT hr;
			hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&joystick, NULL );

			Assert(hr == DI_OK);
			if(FAILED(hr)) 
			{
				DebugOutput::DebugMessage("DirectInputの初期化に失敗しました");
			}

			//デバイスの列挙
			hr = joystick->EnumDevices(
				DI8DEVCLASS_GAMECTRL, DirectInputJoystick::EnumJoysticksCallback,(void *)this, DIEDFL_ATTACHEDONLY );
			Assert(hr == DI_OK);
			if( FAILED(hr))
			{
				DebugOutput::DebugMessage("ジョイスティックが接続されていません");
			}

			//ジョイスティックデバイスが作成できた
			if (joystickDevice != NULL ) {
				hr = joystickDevice->SetDataFormat(&c_dfDIJoystick2);
				Assert(hr == DI_OK);
				if( FAILED(hr))
				{
					DebugOutput::DebugMessage("ジョイスティックのデータフォーマットを設定できませんでした");
				}

				//モードを設定（フォアグラウンド＆非排他モード）
				hr = joystickDevice->SetCooperativeLevel(hwnd_, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
				Assert(hr == DI_OK);
				if( FAILED(hr))
				{
					DebugOutput::DebugMessage("ジョイスティックのモード設定に失敗しました");

				}
				// コールバック関数を使って各軸のモードを設定
				hr = joystickDevice->EnumObjects(Joystick::EnumAxesCallback,(void*)this, DIDFT_AXIS);
				Assert(hr == DI_OK);
				if( FAILED(hr))
				{
					DebugOutput::DebugMessage("ジョイスティックの軸モード設定に失敗しました");
				}


				//初期化成功
				isInitialized =true;
			}
			else {
				joystickDevice=NULL;
				//SafeRelease
			}

	}

	//-----------------------------------------------------------------------------------------
	//
	DirectInputJoystick::~DirectInputJoystick()  {
		Release();
	}
	bool DirectInputJoystick::Update() {
		HRESULT hr;
		//バッファフリップや
		Flip();


		//Acquireしとらんのか
		if  (isAcquire == false ) {
			if (Acquire() == false)  {
				::ZeroMemory((LPVOID)&(keyBuffer[flipCounter][0]), bufferSize);
				return false;  
			}
		}

		//ジョイスティックをポールしなはれ
		hr = joystickDevice->Poll();
		if (FAILED(hr)) {
			if (!Acquire()) {
				return false;
			}
		}

		//ジョイスティックの状態とるよ
		DIJOYSTATE2 dijs;
		ZeroMemory(&dijs, sizeof(DIJOYSTATE2));
		hr = joystickDevice->GetDeviceState(sizeof(DIJOYSTATE2),&dijs );
		if(hr == DIERR_INPUTLOST) {
			// 失敗したらAcquireする
			if (!Acquire()) {
				//acquireでけへんかった。
				//isAcquire = false;
				return true;
			}
			//	一回はok
			hr = joystickDevice->GetDeviceState(sizeof(DIJOYSTATE2),&dijs);
		} 

		if (SUCCEEDED(hr)) {
			//キーバッファを更新する前に、一度クリアしておく
			::ZeroMemory((LPVOID)&(keyBuffer[flipCounter][0]), bufferSize);
			//キーバッファ更新してくよー
			//0~3はジョイスティックの軸の状態なんやで0番目から上下左右の順番にはいっとるよ
			if (dijs.lY >= allowRange) {
				keyBuffer[flipCounter][0] = 0x80;
			}
			if (dijs.lY <= -allowRange) {
				keyBuffer[flipCounter][1] = 0x80;
			}
			if (dijs.lX >= allowRange) {
				keyBuffer[flipCounter][2] = 0x80;
			}
			if (dijs.lX <= -allowRange) {
				keyBuffer[flipCounter][3] = 0x80;
			}

			//4番目以降はジョイスティックボタンの状態や
			//デフォルトは３２個や．必要に応じてSetButtonでボタン数を適当に調整せいよ
			for (int i=0; i<buttonNum; i++) {
				keyBuffer[flipCounter][4+i] = dijs.rgbButtons[i]&0x80;
			}

		}
		if (hr != DI_OK) {
			//	バッファをクリアして戻る。（画面外にフォーカスが移ったときに押しっぱなし
			//	になるのを防ぐため）
			::ZeroMemory((LPVOID)&(keyBuffer[flipCounter][0]), bufferSize);
			return false;       
		}

		return true;
	}

	//-----------------------------------------------------------------------------------------
	//
	void  DirectInputJoystick::Release() {
		// DirectInputのデバイスを解放
		if (joystickDevice) {
			joystickDevice->Unacquire();
		}
		SafeRelease(joystickDevice);
		SafeRelease(joystick);
	}

	//-----------------------------------------------------------------------------------------
	//
	bool DirectInputJoystick::Acquire() {
		HRESULT hr = joystickDevice->Acquire();
		if (hr==DI_OK) {
			isAcquire = true;
		} else {
			isAcquire = false;
		}
		return isAcquire;
	}

	//-----------------------------------------------------------------------------------------
	//
	bool DirectInputJoystick::Unacquire() {
		if (isAcquire == false) {
			//acquireされとらん
			return false;
		}

		HRESULT hr = joystickDevice->Unacquire();
		if (hr==DI_OK) {
			isAcquire = false;
		} else {
			isAcquire = true;
		}
		return !isAcquire;

	}
	bool DirectInputJoystick::IsInitialized() {
		return isInitialized;
	}

	//-----------------------------------------------------------------------------------------
	//
	bool DirectInputJoystick::SetButtonMax(uchar num) {
		buttonNum = num;
		return true;
	}

	//-----------------------------------------------------------------------------------------
	//
	uchar DirectInputJoystick::GetButtonMax() {
		return buttonNum;
	}

	//-----------------------------------------------------------------------------------------
	//
	int CALLBACK DirectInputJoystick::EnumJoysticksCallback(const DIDEVICEINSTANCE* lpddi, VOID* lpContext) {
		// 列挙されたジョイスティックへのインターフェイスを取得する。
		HRESULT hr;
		DirectInputJoystick* joy = reinterpret_cast<DirectInputJoystick*>(lpContext);
		hr = joy->joystick->CreateDevice(lpddi->guidInstance, &joy->joystickDevice, NULL );
		Assert(hr == DI_OK);
		if( FAILED(hr) ) {  
			return DIENUM_CONTINUE;
		}

		//ジョイスティックの能力を調べる
		joy->joyCaps.dwSize = sizeof(DIDEVCAPS);
		hr = joy->joystickDevice->GetCapabilities( &joy->joyCaps );
		Assert(hr == DI_OK);
		if (FAILED(hr)) {//デバイスの能力を取れなかった
			return DIENUM_CONTINUE;
		}

		// このデバイスを使用
		return DIENUM_STOP;

	}

	//-----------------------------------------------------------------------------------------
	// ジョイスティックの軸を列挙する関数
	int  CALLBACK DirectInputJoystick::EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
		HRESULT hr;

		// 軸の値の範囲を設定（-2000～2000）
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize	    = sizeof(diprg); 
		diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
		diprg.diph.dwObj	= lpddoi->dwType;
		diprg.diph.dwHow	= DIPH_BYID;
		diprg.lMin	= -2000;
		diprg.lMax	= +2000;

		DirectInputJoystick* joy = reinterpret_cast<DirectInputJoystick*>(pvRef);
		hr = joy->joystickDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		Assert(hr == DI_OK);
		if (FAILED(hr)) {
			return DIENUM_STOP;
		}

		return DIENUM_CONTINUE;
	}

}