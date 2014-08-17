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
#include "Window.h"

namespace nyx {
	//---------------------------------------------------------------------------------------
	check_box::check_box(const std::shared_ptr<window>& parent, const std::wstring& label, int x, int y, int width, int height, bool isOwnerDraw) 
		:hwnd_(NULL), label_(label), atom_(NULL), isShow_(false), userData_(NULL),guiEventList_(std::make_shared<dispatcher>())	{
		parent->register_widget(*this);
		create(parent->get_handle(), label, x, y, width, height, isOwnerDraw);
	}

	//---------------------------------------------------------------------------------------
	bool check_box::create(window_handle hwnd, const std::wstring& label, int x, int y, int width, int height, bool isOwnerDraw) {

		HINSTANCE hInstance = ::GetModuleHandle(NULL);
	
		DWORD checkBoxStyle;
		if (isOwnerDraw) {
			checkBoxStyle = WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_OWNERDRAW;
		}
		else {
			checkBoxStyle = WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX;
		}

		hwnd_ = CreateWindow(TEXT("BUTTON"), label.c_str(), checkBoxStyle, 
			x, y, width, height, hwnd, (HMENU)id_,  hInstance, NULL);

		NYX_ASSERT(hwnd_ != NULL);
		if (!hwnd_) {
			::MessageBox(NULL, TEXT("失敗しました"), TEXT("error"), MB_OK);
			return false;
		}
		show();
		return true;
	}
	//---------------------------------------------------------------------------------------
	check_box::~check_box() {
		if (atom_) {
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}
	}

	//---------------------------------------------------------------------------------------
	nyx::window_handle check_box::get_handle()
{
		NYX_ASSERT(hwnd_ != NULL);
		return hwnd_;
	}

	//----------------------------------------------------------------
	void check_box::show(){
		NYX_ASSERT(hwnd_ !=NULL);
		isShow_ = true;
		::ShowWindow(hwnd_, SW_SHOW);
	}

	//----------------------------------------------------------------
	void check_box::hide(){
		NYX_ASSERT(hwnd_ != NULL);
		isShow_=false;
		::ShowWindow(hwnd_, SW_HIDE);
	}

	//----------------------------------------------------------------
	void check_box::update() {
		NYX_ASSERT(hwnd_ != NULL);
		::UpdateWindow(hwnd_);
	}

	//----------------------------------------------------------------
	bool check_box::is_show() {
		return isShow_;
	}

	//----------------------------------------------------------------
	void check_box::activate() {
		NYX_ASSERT(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//----------------------------------------------------------------
	void check_box::unactivate() {
		NYX_ASSERT(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}

	//----------------------------------------------------------------
	bool check_box::is_activate() const {
		NYX_ASSERT(hwnd_ != NULL);
		return IsWindowEnabled(hwnd_) != 0;
	}

	//----------------------------------------------------------------
	WIDGET_TYPE check_box::get_type() const{
		return WIDGET_TYPE_CHECK_BOX;
	}

	//----------------------------------------------------------------
	std::shared_ptr<void> check_box::get_user_data() const {
		return userData_;
	}

	//----------------------------------------------------------------
	void check_box::set_user_data(const std::shared_ptr<void>& data) {
		userData_ = data;
	}

	//----------------------------------------------------------------
	uint32_t check_box::get_id() const {
		return id_;
	}

	//----------------------------------------------------------------
	void check_box::set_id(uint32_t id)  {
		id_ = id;
	}

	//----------------------------------------------------------------
	void check_box::get_size(rect2i& rect) const {
		NYX_ASSERT(hwnd_ != NULL);
		RECT r;
		::GetWindowRect(hwnd_, &r);

		//
		rect.x = r.left;
		rect.y = r.top;
		rect.width  = r.right  - r.left;
		rect.height = r.bottom - r.top;
	}

	//----------------------------------------------------------------
	void check_box::set_size(const rect2i& rect) {
		NYX_ASSERT(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void check_box::get_position(point2i& p) const {
		NYX_ASSERT(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	//----------------------------------------------------------------
	void check_box::set_position(const point2i& p) {
		NYX_ASSERT(hwnd_ != NULL);
		rect2i r;
		get_size(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	std::wstring check_box::get_label() const {
		return label_;
	}

	//----------------------------------------------------------------
	void check_box::set_label(const std::wstring& label) {
		NYX_ASSERT(hwnd_ != NULL);
		label_ = label;
		SetWindowText(hwnd_, label_.c_str());
	}

	//----------------------------------------------------------------
	bool check_box::is_checked() const {
		NYX_ASSERT(hwnd_ != NULL);
		LRESULT result = ::SendMessage(hwnd_, BM_GETCHECK, 0, 0);
		return result == BST_CHECKED;
	}

	//----------------------------------------------------------------
	void check_box::on_paint(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_PAINT, callback);
	}
	
	//----------------------------------------------------------------
	void check_box::on_click(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_CLICK, callback);
	}

	//----------------------------------------------------------------
	void check_box::on_checked_changed(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_CHECKED_CHANGED, callback);
	}

	//----------------------------------------------------------------
	void check_box::dispatch(WIDGET_EVENT_TYPE eventType, event_args& e){
		NYX_ASSERT(guiEventList_ != nullptr);
		if (eventType != WIDGET_EVENT_TYPE_NUM) {
			this->guiEventList_->dispatch(eventType, *this, e);
		}
	}
}