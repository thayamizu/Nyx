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
#include "Input/IKeyBase.h"
#include "Input/Keyboard.h"

namespace Nyx {
	Keyboard::Keyboard(HWND hwnd_) : IKeyBase(), isAcquire(false) {


		// DirectInputの作成
		HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&keyboard, NULL); 
		Assert(hr == DI_OK); 

		// デバイス・オブジェクトを作成
		hr = keyboard->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL); 
		Assert(hr== DI_OK);

		// データ形式を設定
		hr = keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
		Assert(hr == DI_OK);

		//モードを設定（フォアグラウンド＆非排他モード）
		hr = keyboardDevice->SetCooperativeLevel(hwnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		Assert(hr == DI_OK);

		// バッファリング・データを取得するため、バッファ・サイズを設定
		DIPROPDWORD diprop;
		diprop.diph.dwSize	= sizeof(diprop); 
		diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
		diprop.diph.dwObj	= 0;
		diprop.diph.dwHow	= DIPH_DEVICE;
		diprop.dwData = 255;
		hr = keyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
		Assert(hr == DI_OK);

	}
	Keyboard::~Keyboard()  {
		Release();
	}
	bool Keyboard::Update() {
		HRESULT hr;
		Flip();

		//Acquireしとらんのか
		if  (isAcquire == false ) {
			if (Acquire() == false)  {
				::ZeroMemory((LPVOID)&(keyBuffer[flipCounter][0]), bufferSize);
				return false;  
			}
		}

		//キーボードの状態を読み込む
		hr = keyboardDevice->GetDeviceState(bufferSize, (LPVOID)&(keyBuffer[flipCounter][0]));
		if(hr == DIERR_INPUTLOST) {
			// 失敗したらAcquireする
			if (!Acquire()) {
				//acquireでけへんかった。
				isAcquire = false;
				return true;
			}
			//	一回はok
			hr = keyboardDevice->GetDeviceState(bufferSize, (LPVOID)&(keyBuffer[flipCounter][0]));
		} 

		if (hr != DI_OK) {
			//	バッファをクリアして戻る。（画面外にフォーカスが移ったときに押しっぱなし
			//	になるのを防ぐため）
			::ZeroMemory((LPVOID)&(keyBuffer[flipCounter][0]), bufferSize);
			return false;       
		}

		return true;
	}


	void  Keyboard::Release() {
		// DirectInputのデバイスを解放
		if (keyboardDevice) {
			keyboardDevice->Unacquire();
		}
		SafeRelease(keyboardDevice);
		SafeRelease(keyboard);
	}

	bool Keyboard::Acquire() {
		HRESULT hr = keyboardDevice->Acquire();
		if (hr==DI_OK) {
			isAcquire = true;
		} else {
			isAcquire = false;
		}
		return isAcquire;
	}

	bool Keyboard::Unacquire() {
		if (isAcquire == false) {
			//acquireされとらん
			return false;
		}

		HRESULT hr = keyboardDevice->Unacquire();
		if (hr==DI_OK) {
			isAcquire = false;
		} else {
			isAcquire = true;
		}
		return !isAcquire;
	}
}