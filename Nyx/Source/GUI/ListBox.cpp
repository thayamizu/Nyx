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
#include "GUI/ListBox.h"
#include "Debug/Assert.h"
#include "Primitive/Rect.h"
#include "Primitive/Vector2.h"

namespace Nyx {
	//---------------------------------------------------------------------------------------
	//生成・破棄
	//---------------------------------------------------------------------------------------
	ListBox::ListBox(HWND hwnd, std::wstring label, int x, int y, int width, int height, int id)
		:label_(label), id_(id){

			OnCreate(hwnd, label, x, y, width, height, id);
	}       
	ListBox::~ListBox() {
		if (atom_) {
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}
	}

	bool ListBox::OnCreate(HWND hwnd, std::wstring label, int x, int y, int width, int height, int id) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd_ = CreateWindow(TEXT("LISTBOX"), label.c_str(), WS_CHILD | WS_VISIBLE | LBS_STANDARD & ~LBS_SORT, 
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
	HWND ListBox::GetHandle() {
		Assert(hwnd_ != NULL);
		return hwnd_;
	}

	//----------------------------------------------------------------
	void ListBox::Show(){
		Assert(hwnd_ != NULL);
		isShow_ = true;
		::ShowWindow(hwnd_, SW_SHOW);  
	}

	//----------------------------------------------------------------
	void ListBox::Hide(){
		Assert(hwnd_ != NULL);
		isShow_ = false;
		::ShowWindow(hwnd_, SW_HIDE); 
	}

	//----------------------------------------------------------------
	void ListBox::Update() {
		Assert(hwnd_ != NULL);
		::UpdateWindow(hwnd_);
	}

	//----------------------------------------------------------------
	bool ListBox::IsShow() {
		return isShow_;
	}

	//----------------------------------------------------------------
	void ListBox::Activate() {
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//----------------------------------------------------------------
	void ListBox::Unactivate() {
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}
	//----------------------------------------------------------------
	bool ListBox::IsActivate() const {
		Assert(hwnd_ != NULL);
		return IsWindowEnabled(hwnd_) != 0;
	}

	//----------------------------------------------------------------
	ControlType ListBox::GetType() const{
		return ControlType_ListBox;
	}

	//----------------------------------------------------------------
	std::shared_ptr<void> ListBox::GetUserData() const {
		return userData_;
	}

	//----------------------------------------------------------------
	void ListBox::SetUserData(std::shared_ptr<void> data) {
		userData_ = data;
	}

	//----------------------------------------------------------------
	uint ListBox::GetID() const {
		return id_;
	}

	//----------------------------------------------------------------
	void ListBox::SetID(uint id)  {
		id_ = id;
	}

	//----------------------------------------------------------------
	void ListBox::GetSize(Rect2i& rect) const {
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
	void ListBox::SetSize(const Rect2i& rect) {
		Assert(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}


	//----------------------------------------------------------------
	void ListBox::GetPosition(Point2i& p) const {
		Assert(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	void ListBox::SetPosition(const Point2i& p) {
		Assert(hwnd_ != NULL);
		Rect2i r;
		GetSize(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);

	}
	//----------------------------------------------------------------
	void ListBox::AddItem(const std::wstring& item) {
		SendMessage(hwnd_, LB_ADDSTRING, 0, (LPARAM)item.c_str());
	}

	//----------------------------------------------------------------
	void ListBox::DeleteItem() {
		int index = SendMessage(hwnd_, LB_GETCURSEL, 0, 0);
		if (index == LB_ERR) return;

		SendMessage(hwnd_, LB_DELETESTRING, index, 0);
	}

	//----------------------------------------------------------------
	void ListBox::ClearItem() {
		SendMessage(hwnd_, LB_RESETCONTENT, 0, 0);
	}


	//----------------------------------------------------------------
	uint ListBox::GetSelectedIndex() {
		return SendMessage(hwnd_, LB_GETCURSEL, 0, 0);
	}


	//----------------------------------------------------------------
	std::wstring ListBox::GetSelectedItem() {
		uint index = GetSelectedIndex();
		
		SendMessage(hwnd_, LB_GETTEXT, index, 0);
		return TEXT("");
	}
}