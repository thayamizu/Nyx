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
#include "Primitive/Rect2i.h"
#include "Primitive/Point2i.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	RadioButton::RadioButton(HWND _hwnd, std::wstring _label, int _x, int _y, int _width, int _height, int _id)
		:label(_label), hwnd(NULL), id(_id), atom(NULL), isShow(false), userData(NULL) {

			OnCreate(_hwnd, _label, _x, _y, _width, _height, _id);
	}       

	//-----------------------------------------------------------------------------------------
	RadioButton::~RadioButton() {
		if (atom) ::UnregisterClass((LPCTSTR)atom, ::GetModuleHandle(NULL));
	}

	//-----------------------------------------------------------------------------------------
	bool RadioButton::OnCreate(HWND _hwnd, std::wstring _label, int _x, int _y, int _width, int _height, int _id) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd = CreateWindow(
			TEXT("BUTTON"),
			_label.c_str(), //タイトルバーにこの名前が表示されます
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, //ウィンドウの種類
			_x,	//Ｘ座標
			_y,	//Ｙ座標
			_width,	//幅
			_height,	//高さ
			_hwnd, //親ウィンドウのハンドル、親を作るときはNULL
			(HMENU)_id, //メニューハンドル、クラスメニューを使うときはNULL
			hInstance, //インスタンスハンドル
			NULL);

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
	HWND RadioButton::GetHandle() {
		Assert(hwnd != NULL);
		return hwnd;
	}

	//----------------------------------------------------------------
	void RadioButton::Show() {
		Assert(hwnd != NULL);
		isShow = true;
		::ShowWindow(hwnd, SW_SHOW);  
	}

	//----------------------------------------------------------------
	void RadioButton::Hide(){
		Assert(hwnd != NULL);
		isShow = false;
		::ShowWindow(hwnd, SW_HIDE);  
	}

	//----------------------------------------------------------------
	void RadioButton::Update() {
		Assert(hwnd != NULL);
		::UpdateWindow(hwnd);

	}

	//----------------------------------------------------------------
	bool RadioButton::IsShow() {
		return isShow;
	}

	//----------------------------------------------------------------
	void RadioButton::Activate() {
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, true);
	}

	//----------------------------------------------------------------
	void RadioButton::Unactivate() {
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, false);
	}

	//----------------------------------------------------------------
	bool RadioButton::IsActivate() const {
		Assert(hwnd != NULL);
		return static_cast<bool>(::IsWindowEnabled(hwnd));
	}

	//----------------------------------------------------------------
	ControlType::enum_t RadioButton::GetType() const{
		return ControlType::RadioButton;
	}

	//----------------------------------------------------------------
	void* RadioButton::GetUserData() const {
		return userData;
	}

	//----------------------------------------------------------------
	void RadioButton::SetUserData(void * data) {
		userData = data;
	}

	//----------------------------------------------------------------
	uint RadioButton::GetID() const {
		return id;
	}

	//----------------------------------------------------------------
	void RadioButton::SetID(uint _id)  {
		id = _id;
	}

	//----------------------------------------------------------------
	void RadioButton::GetSize(Rect2i* rect) const {
		Assert(hwnd != NULL);
		RECT r;
		::GetWindowRect(hwnd, &r);

		//
		rect->x = r.left;
		rect->y = r.top;
		rect->width  = r.right  - r.left;
		rect->height = r.bottom - r.top;
	}

	//----------------------------------------------------------------
	void RadioButton::SetSize(const Rect2i& rect) {
		Assert(hwnd != NULL);
		::SetWindowPos(hwnd, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void RadioButton::GetPosition(Point2i* p) const {
		Assert(hwnd != NULL);
		RECT _r;
		::GetWindowRect(hwnd, &_r);

		p->x = _r.left;
		p->y = _r.top;
	}

	//----------------------------------------------------------------
	void RadioButton::SetPosition(const Point2i& p) {
		Assert(hwnd != NULL);
		Rect2i r;
		GetSize(&r);

		::SetWindowPos(hwnd, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	std::wstring RadioButton::GetLabel() const  {
		return label;
	}

	//----------------------------------------------------------------
	void RadioButton::SetLabel(const std::wstring& _label) {
		label = _label;
		SetWindowText(hwnd, label.c_str());
	}

	//----------------------------------------------------------------
	bool RadioButton::IsChecked() const {
		LRESULT result = ::SendMessage(hwnd, BST_CHECKED, 0, 0);
		return result == BST_CHECKED;
	}
}