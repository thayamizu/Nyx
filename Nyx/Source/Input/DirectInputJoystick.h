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
#ifndef NYX_CORE_INCLUDED_DIRECT_INPUT_JOYSTICK_H_
#define NYX_CORE_INCLUDED_DIRECT_INPUT_JOYSTICK_H_

#include "PCH/PCH.h"
#include "IKeyBase.h"
#include "DirectInputDefinition.h"

namespace Nyx {
	/// ジョイスティックインタフェース
	class IJoystick : public IKeyBase {
	public:
		/**
		*
		*/
		IJoystick():IKeyBase()  { }
		/**
		*
		*/
		~IJoystick() { }

		/**
		*
		*/
		virtual bool Update() = 0;
		/**
		*
		*/
		virtual bool SetButtonMax(uchar num) = 0;
		/**
		*
		*/
		virtual uchar GetButtonMax() = 0;
	};

	/////ジョイスティックヌルデバイス
	//class JoystickNullDevice: public IJoystick {
	//public:
	//	JoystickNullDevice();
	//	~JoystickNullDevice();
	//	/**
	//	*/
	//	bool Update();
	//	bool SetButtonMax(uchar num);
	//	uchar GetButtonMax();
	//	uchar GetJoyCount();
	//};

	//JoystickNullDevice::JoystickNullDevice(){}
	//JoystickNullDevice::~JoystickNullDevice(){}
	//
	//bool JoystickNullDevice::Update() {
	//	return false;
	//}
	//
	//bool JoystickNullDevice::SetButtonMax(uchar num) {
	//	return false;
	//}
	//
	//uchar JoystickNullDevice::GetButtonMax() {
	//	return 0;
	//}



	///DirectInputを使ったジョイスティック入力
	class DirectInputJoystick : public IJoystick {
	public:
		//--------------------------------------------------------
		//構築・破壊
		//--------------------------------------------------------
		DirectInputJoystick(HWND hwnd_, int range) ;
		~DirectInputJoystick() ;

		//--------------------------------------------------------
		//取得・更新
		//--------------------------------------------------------
		bool Update();
		void Release();
		bool Acquire();
		bool Unacquire();
		bool IsInitialized();
		//--------------------------------------------------------
		//ボタンの設定
		//--------------------------------------------------------
		bool SetButtonMax(uchar );
		uchar GetButtonMax();
	public:
		static int CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void* pContext);
		static int CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, void* pvRef);

		static int joystickNum;
	private:
			struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif