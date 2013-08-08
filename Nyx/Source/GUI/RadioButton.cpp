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
#include "GUI/RadioButton.h"
#include "Debug/Assert.h"
#include "Primitive/Rect.h"
#include "Primitive/Vector2.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	RadioButton::RadioButton(HWND hwnd, std::wstring label, int x, int y, int width, int height, int id)
		:label_(label), hwnd_(NULL), id_(id), atom_(NULL), isShow_(false), userData_(NULL) {

			OnCreate(hwnd, label_, x, y, width, height, id);
	}       

	//-----------------------------------------------------------------------------------------
	RadioButton::~RadioButton() {
		if (atom_) {
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}
	}

	//-----------------------------------------------------------------------------------------
	bool RadioButton::OnCreate(HWND hwnd, std::wstring label, int x, int y, int width, int height, int id) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd_ = CreateWindow(
			TEXT("BUTTON"), label.c_str(), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, //ウィンドウの種類
			x, y, width, height, hwnd, (HMENU)id, hInstance, NULL);

		Assert(hwnd_ != NULL);
		if (!hwnd_) {
			::MessageBox(NULL, TEXT("失敗しました"), TEXT("error"), MB_OK);
			return false;
		}

		//コントロールの表示
		Show();
		return true;
	}

	//---------------------------------------------------------------------------------------
	HWND RadioButton::GetHandle() {
		Assert(hwnd_ != NULL);
		return hwnd_;
	}

	//----------------------------------------------------------------
	void RadioButton::Show() {
		Assert(hwnd_ != NULL);
		isShow_ = true;
		::ShowWindow(hwnd_, SW_SHOW);  
	}

	//----------------------------------------------------------------
	void RadioButton::Hide(){
		Assert(hwnd_ != NULL);
		isShow_ = false;
		::ShowWindow(hwnd_, SW_HIDE);  
	}

	//----------------------------------------------------------------
	void RadioButton::Update() {
		Assert(hwnd_ != NULL);
		::UpdateWindow(hwnd_);

	}

	//----------------------------------------------------------------
	bool RadioButton::IsShow() {
		return isShow_;
	}

	//----------------------------------------------------------------
	void RadioButton::Activate() {
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//----------------------------------------------------------------
	void RadioButton::Unactivate() {
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}

	//----------------------------------------------------------------
	bool RadioButton::IsActivate() const {
		Assert(hwnd_ != NULL);
		return IsWindowEnabled(hwnd_) != 0;
	}

	//----------------------------------------------------------------
	ControlType RadioButton::GetType() const{
		return ControlType_RadioButton;
	}

	//----------------------------------------------------------------
	std::shared_ptr<void> RadioButton::GetUserData() const {
		return userData_;
	}

	//----------------------------------------------------------------
	void RadioButton::SetUserData(std::shared_ptr<void> data) {
		userData_ = data;
	}

	//----------------------------------------------------------------
	uint RadioButton::GetID() const {
		return id_;
	}

	//----------------------------------------------------------------
	void RadioButton::SetID(uint id)  {
		id_ = id;
	}

	//----------------------------------------------------------------
	void RadioButton::GetSize(Rect2i& rect) const {
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
	void RadioButton::SetSize(const Rect2i& rect) {
		Assert(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void RadioButton::GetPosition(Point2i& p) const {
		Assert(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	//----------------------------------------------------------------
	void RadioButton::SetPosition(const Point2i& p) {
		Assert(hwnd_ != NULL);
		Rect2i r;
		GetSize(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	std::wstring RadioButton::GetLabel() const  {
		return label_;
	}

	//----------------------------------------------------------------
	void RadioButton::SetLabel(const std::wstring& label) {
		label_ = label;
		SetWindowText(hwnd_, label.c_str());
	}

	//----------------------------------------------------------------
	bool RadioButton::IsChecked() const {
		LRESULT result = ::SendMessage(hwnd_, BST_CHECKED, 0, 0);
		return result == BST_CHECKED;
	}
}