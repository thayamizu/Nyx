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
#include "Window.h"

namespace nyx {
	//---------------------------------------------------------------------------------------
	//生成・破棄
	//---------------------------------------------------------------------------------------
	list_box::list_box(std::shared_ptr<window>& parent, std::wstring label, int x, int y, int width, int height, bool isOwnerDraw)
		:hwnd_(NULL), label_(label), isShow_(true), atom_(NULL), isActivate_(true), userData_(nullptr), guiEventList_(std::make_shared<dispatcher>()) {

		parent->register_widget(*this);
		create(parent->get_handle(), label, x, y, width, height, isOwnerDraw);
	}       
	list_box::~list_box() {
		if (atom_) {
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}
	}

	bool list_box::create(window_handle hwnd, std::wstring label, int x, int y, int width, int height, bool isOwnerDraw) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);

		DWORD listboxStyle;
		if (isOwnerDraw) {
			listboxStyle = WS_CHILD | WS_VISIBLE | LBS_STANDARD & ~LBS_SORT | BS_OWNERDRAW;

		}
		else {
			listboxStyle = WS_CHILD | WS_VISIBLE | LBS_STANDARD & ~LBS_SORT;
		}

		hwnd_ = CreateWindow(TEXT("LISTBOX"), label.c_str(), listboxStyle,
			x, y, width, height, hwnd, (HMENU)id_, hInstance, NULL);

		NYX_ASSERT(hwnd_ != NULL);
		if (!hwnd_) {
			::MessageBox(NULL, TEXT("失敗しました"), TEXT("error"), MB_OK);

			return false;
		}

		//コントロールの表示
		show();
		return true;
	}

	//---------------------------------------------------------------------------------------
	nyx::window_handle list_box::get_handle()
{
		NYX_ASSERT(hwnd_ != NULL);
		return hwnd_;
	}

	//----------------------------------------------------------------
	void list_box::show(){
		NYX_ASSERT(hwnd_ != NULL);
		isShow_ = true;
		::ShowWindow(hwnd_, SW_SHOW);  
	}

	//----------------------------------------------------------------
	void list_box::hide(){
		NYX_ASSERT(hwnd_ != NULL);
		isShow_ = false;
		::ShowWindow(hwnd_, SW_HIDE); 
	}

	//----------------------------------------------------------------
	void list_box::update() {
		NYX_ASSERT(hwnd_ != NULL);
		::UpdateWindow(hwnd_);
	}

	//----------------------------------------------------------------
	bool list_box::is_show() {
		return isShow_;
	}

	//----------------------------------------------------------------
	void list_box::activate() {
		NYX_ASSERT(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//----------------------------------------------------------------
	void list_box::unactivate() {
		NYX_ASSERT(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}
	//----------------------------------------------------------------
	bool list_box::is_activate() const {
		NYX_ASSERT(hwnd_ != NULL);
		return IsWindowEnabled(hwnd_) != 0;
	}

	//----------------------------------------------------------------
	WIDGET_TYPE list_box::get_type() const{
		return WIDGET_TYPE_LIST_BOX;
	}

	//----------------------------------------------------------------
	std::shared_ptr<void> list_box::get_user_data() const {
		return userData_;
	}

	//----------------------------------------------------------------
	void list_box::set_user_data(const std::shared_ptr<void>& data) {
		userData_ = data;
	}

	//----------------------------------------------------------------
	uint32_t list_box::get_id() const {
		return id_;
	}

	//----------------------------------------------------------------
	void list_box::set_id(uint32_t id)  {
		id_ = id;
	}

	//----------------------------------------------------------------
	void list_box::get_size(rect2i& rect) const {
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
	void list_box::set_size(const rect2i& rect) {
		NYX_ASSERT(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}


	//----------------------------------------------------------------
	void list_box::get_position(point2i& p) const {
		NYX_ASSERT(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	void list_box::set_position(const point2i& p) {
		NYX_ASSERT(hwnd_ != NULL);
		rect2i r;
		get_size(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);

	}
	//----------------------------------------------------------------
	void list_box::add_item(const std::wstring& item) {
		SendMessage(hwnd_, LB_ADDSTRING, 0, (LPARAM)item.c_str());
	}

	//----------------------------------------------------------------
	void list_box::remove_item() {
		int index = SendMessage(hwnd_, LB_GETCURSEL, 0, 0);
		if (index == LB_ERR) return;

		SendMessage(hwnd_, LB_DELETESTRING, index, 0);
	}

	//----------------------------------------------------------------
	void list_box::clear_item() {
		SendMessage(hwnd_, LB_RESETCONTENT, 0, 0);
	}


	//----------------------------------------------------------------
	uint32_t list_box::get_select_index() {
		return SendMessage(hwnd_, LB_GETCURSEL, 0, 0);
	}


	//----------------------------------------------------------------
	std::wstring list_box::get_select_item() {
		uint32_t index = get_select_index();
		
		SendMessage(hwnd_, LB_GETTEXT, index, 0);
		return TEXT("");
	}

	//----------------------------------------------------------------
	void list_box::on_paint(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_PAINT, callback);
	}

	//----------------------------------------------------------------
	void list_box::on_click(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_CLICK, callback);
	}

	//----------------------------------------------------------------
	void list_box::on_index_changed(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_INDEX_CHANGED, callback);
	}

	//----------------------------------------------------------------
	void list_box::dispatch(WIDGET_EVENT_TYPE eventType, event_args& e) {
		NYX_ASSERT(guiEventList_ != nullptr);
		if (eventType != WIDGET_EVENT_TYPE_NUM) {
			this->guiEventList_->dispatch(eventType, *this, e);
		}
	}
}