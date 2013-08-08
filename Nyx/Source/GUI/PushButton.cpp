/********************************************************************************
*
*  The MIT License
*
* Copyright (c) 2010-2011 t.hayamizu
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
#include "GUI/PushButton.h"
#include "Object/Delegate.h"
#include "Primitive/Rect.h"
#include "Primitive/Vector2.h"

namespace Nyx {
	//------------------------------------------------------------------------------
	PushButton::PushButton(HWND hwnd, const std::wstring& label, int x, int y, int width, int height, int id)
		:label_(label), hwnd_(NULL), id_(id), atom_(NULL), isShow_(false), isActivate_(true)
	{

		OnCreate(hwnd, label, x, y, width, height, id);
	}       

	//------------------------------------------------------------------------------
	PushButton::~PushButton() 
	{
		if (atom_) { 
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}
	}

	//------------------------------------------------------------------------------
	bool PushButton::OnCreate(HWND hwnd, const std::wstring& label, int x, int y, int width, int height, int id) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd_ = CreateWindow(TEXT("BUTTON"), label.c_str(), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 	
			x, y, width, height, hwnd,  (HMENU)id, hInstance, NULL);

		Assert(hwnd != NULL);
		if (!hwnd) {
			::MessageBox(NULL, TEXT("失敗しました"), TEXT("error"), MB_OK);
			return false;
		}
		//コントロールの表示
		Show();
		return true;
	}
	//---------------------------------------------------------------------------------------
	void PushButton::Show() 
	{
		Assert(hwnd_ != NULL);
		isShow_ = true;
		::ShowWindow(hwnd_, SW_SHOW);   
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Hide() 
	{
		Assert(hwnd_ != NULL);
		isShow_ = false;
		::ShowWindow(hwnd_, SW_HIDE);   
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Update() 
	{
		Assert(hwnd_ != NULL);
		::UpdateWindow(hwnd_);
	}

	//---------------------------------------------------------------------------------------
	bool PushButton::IsShow() 
	{
		return isShow_;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Activate() 
	{
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Unactivate() 
	{
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}

	//---------------------------------------------------------------------------------------
	bool PushButton::IsActivate() 
		const 
	{
		Assert(hwnd_ != NULL);
		return IsWindowEnabled(hwnd_) != 0;
	}

	//---------------------------------------------------------------------------------------
	HWND  PushButton::GetHandle() 
	{
		Assert(hwnd_ != NULL);
		return hwnd_;
	}

	//---------------------------------------------------------------------------------------
	ControlType PushButton::GetType() 
		const 
	{
		return ControlType_PushButton;
	}

	//---------------------------------------------------------------------------------------
	std::shared_ptr<void> PushButton::GetUserData() 
		const 
	{
		return userData_;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetUserData(std::shared_ptr<void> data) 
	{
		userData_ = data;
	}

	//---------------------------------------------------------------------------------------
	uint PushButton::GetID() 
		const 
	{
		return id_;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetID(uint id)  
	{
		id_ = id;
	}
	//---------------------------------------------------------------------------------------
	void PushButton::GetSize(Rect2i& rect)
		const 
	{
		Assert(hwnd_ != NULL);
		RECT r;
		::GetWindowRect(hwnd_, &r);

		//
		rect.x = r.left;
		rect.y = r.top;
		rect.width  = r.right  - r.left;
		rect.height = r.bottom - r.top;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetSize(const Rect2i& rect) 
	{
		Assert(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//---------------------------------------------------------------------------------------
	void PushButton::GetPosition(Point2i& p) 
		const 
	{
		Assert(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetPosition(const Point2i& p) 
	{
		Assert(hwnd_ != NULL);
		Rect2i r;
		GetSize(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//---------------------------------------------------------------------------------------
	std::wstring PushButton::GetLabel() 
		const
	{
		return label_;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetLabel(const std::wstring& label)
	{
		label_ = label;
		SetWindowText(hwnd_, label_.c_str());
	}
}