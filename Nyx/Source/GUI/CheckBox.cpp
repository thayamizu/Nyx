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
#include "GUI/CheckBox.h"
#include "Debug/Assert.h"
#include "Primitive/Rect.h"
#include "Primitive/Vector2.h"

namespace Nyx {
	//---------------------------------------------------------------------------------------
	CheckBox::CheckBox(HWND hwnd, std::wstring label, int x, int y, int width, int height, int id) 
		:hwnd_(NULL), label_(label), id_(id), atom_(NULL), isShow_(false), userData_(NULL)	{
		OnCreate(hwnd, label, x, y, width, height, id);
	}

	//---------------------------------------------------------------------------------------
	bool CheckBox::OnCreate(HWND hwnd, std::wstring label, int x, int y, int width, int height, int id) {

		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd_ = CreateWindow(TEXT("BUTTON"), label.c_str(), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 
			x, y, width, height, hwnd, (HMENU)id,  hInstance, NULL);

		Assert(hwnd_ != NULL);
		if (!hwnd_) {
			::MessageBox(NULL, TEXT("失敗しました"), TEXT("error"), MB_OK);
			return false;
		}
		Show();
		return true;
	}
	//---------------------------------------------------------------------------------------
	CheckBox::~CheckBox() {
		if (atom_) {
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}
	}

	//---------------------------------------------------------------------------------------
	HWND CheckBox::GetHandle() {
		Assert(hwnd_ != NULL);
		return hwnd_;
	}

	//----------------------------------------------------------------
	void CheckBox::Show(){
		Assert(hwnd_ !=NULL);
		isShow_ = true;
		::ShowWindow(hwnd_, SW_SHOW);
	}

	//----------------------------------------------------------------
	void CheckBox::Hide(){
		Assert(hwnd_ != NULL);
		isShow_=false;
		::ShowWindow(hwnd_, SW_HIDE);
	}

	//----------------------------------------------------------------
	void CheckBox::Update() {
		Assert(hwnd_ != NULL);
		::UpdateWindow(hwnd_);
	}

	//----------------------------------------------------------------
	bool CheckBox::IsShow() {
		return isShow_;
	}

	//----------------------------------------------------------------
	void CheckBox::Activate() {
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//----------------------------------------------------------------
	void CheckBox::Unactivate() {
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}

	//----------------------------------------------------------------
	bool CheckBox::IsActivate() const {
		Assert(hwnd_ != NULL);
		return IsWindowEnabled(hwnd_) != 0;
	}

	//----------------------------------------------------------------
	ControlType CheckBox::GetType() const{
		return ControlType_CheckBox;
	}

	//----------------------------------------------------------------
	std::shared_ptr<void> CheckBox::GetUserData() const {
		return userData_;
	}

	//----------------------------------------------------------------
	void CheckBox::SetUserData(std::shared_ptr<void> data) {
		userData_ = data;
	}

	//----------------------------------------------------------------
	uint CheckBox::GetID() const {
		return id_;
	}

	//----------------------------------------------------------------
	void CheckBox::SetID(uint id)  {
		id_ = id;
	}

	//----------------------------------------------------------------
	void CheckBox::GetSize(Rect2i& rect) const {
		Assert(hwnd_ != NULL);
		RECT r;
		::GetWindowRect(hwnd_, &r);

		//
		rect.x = r.left;
		rect.y = r.top;
		rect.width  = r.right  - r.left;
		rect.height = r.bottom - r.top;
	}

	//----------------------------------------------------------------
	void CheckBox::SetSize(const Rect2i& rect) {
		Assert(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void CheckBox::GetPosition(Point2i& p) const {
		Assert(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	//----------------------------------------------------------------
	void CheckBox::SetPosition(const Point2i& p) {
		Assert(hwnd_ != NULL);
		Rect2i r;
		GetSize(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	std::wstring CheckBox::GetLabel() const {
		return label_;
	}

	//----------------------------------------------------------------
	void CheckBox::SetLabel(const std::wstring& label) {
		Assert(hwnd_ != NULL);
		label_ = label;
		SetWindowText(hwnd_, label_.c_str());
	}

	//----------------------------------------------------------------
	bool CheckBox::IsChecked() const {
		Assert(hwnd_ != NULL);
		LRESULT result = ::SendMessage(hwnd_, BM_GETCHECK, 0, 0);
		return result == BST_CHECKED;
	}
}