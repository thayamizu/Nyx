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
#include "GUI/Window.h"
#include "GUI/Dispatcher.h"
#include "Debug/Assert.h"
#include "Thread/CriticalSection.h"
#include "Primitive/Rect.h"

namespace nyx {
	//-----------------------------------------------------------------------------------------
	window::window(HWND hWnd, std::wstring caption, std::wstring icon, int x, int y, int width, int height, int id)
		:hwnd_(NULL), caption_(caption), icon_(icon), id_(id), childControl_(), guiEventList_(nullptr), userEventList_(nullptr)  {
			//フックリストが初期化されていなければ、初期化する
			guiEventList_ = std::make_shared<dispatcher>();
			
			//フックリストが初期化されていなければ、初期化する
			userEventList_ = std::make_shared<dispatcher>();

			//コントロールの生成
			on_create(hWnd, x, y, width, height);
	}    

	//-----------------------------------------------------------------------------------------
	//
	window::~window() {
		if (atom_) {
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}

		childControl_.clear();
		userEventList_->clear();
		guiEventList_->clear();
	}


	//-----------------------------------------------------------------------------------------
	//
	bool window::on_create(HWND hwnd, int x, int y, int width, int height) {
		//ウインドウクラスの作成
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		WNDCLASS winc;
		winc.style			= CS_HREDRAW | CS_VREDRAW;
		winc.lpfnWndProc	= global_procedure;
		winc.cbClsExtra		= winc.cbWndExtra	= 0;
		winc.hInstance		= hInstance;
		winc.hIcon			= LoadIcon(NULL , icon_.c_str());
		winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
		winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
		winc.lpszMenuName	= NULL;
		winc.lpszClassName	= caption_.c_str();
		atom_ = RegisterClass(&winc);

		//ウインドウの生成
		hwnd_ = CreateWindow(
			caption_.c_str(),
			caption_.c_str(), //タイトルバーにこの名前が表示されます
			WS_OVERLAPPEDWINDOW , //ウィンドウの種類
			x,	//Ｘ座標
			y,	//Ｙ座標
			width,	//幅
			height,	//高さ
			hwnd, //親ウィンドウのハンドル、親を作るときはNULL
			NULL, //メニューハンドル、クラスメニューを使うときはNULL
			hInstance, //インスタンスハンドル
			NULL);

		if (hwnd_ == NULL) {
			::MessageBox(NULL, TEXT("失敗しました"), TEXT("error"), MB_OK);
			return false;
		}

		::SetWindowLong(hwnd_, GWL_USERDATA, (long)this);
		
		show();
		return true;
	}


	//---------------------------------------------------------------------------------------
	nyx::window_handle window::get_handle()
{
		NYX_ASSERT(hwnd_ != NULL);
		return hwnd_;
	}

	//----------------------------------------------------------------
	void window::show(){
		NYX_ASSERT(hwnd_ != NULL);
		isShow = true;
		::ShowWindow(hwnd_, SW_SHOW);
	}

	//----------------------------------------------------------------
	void window::hide(){
		NYX_ASSERT(hwnd_ != NULL);
		isShow = false;
		::ShowWindow(hwnd_, SW_HIDE);
	}

	//----------------------------------------------------------------
	void window::update() {
		NYX_ASSERT(hwnd_ != NULL);
		::UpdateWindow(hwnd_);
	}

	//----------------------------------------------------------------
	bool window::is_show() {
		return isShow;
	}
	
	//----------------------------------------------------------------
	void window::show_cursor(bool isShowCursor) {
		::ShowCursor(isShowCursor);
	}
	
	//----------------------------------------------------------------
	void window::activate() {
		NYX_ASSERT(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//----------------------------------------------------------------
	void window::unactivate() {
		NYX_ASSERT(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}

	//----------------------------------------------------------------
	bool window::is_activate() const {
		NYX_ASSERT(hwnd_ != NULL);
		return ::IsWindowEnabled(hwnd_) != 0;
	}


	//----------------------------------------------------------------
	WIDGET_TYPE window::get_type() const{
		return WIDGET_TYPE_WINDOW;
	}

	//----------------------------------------------------------------
	std::shared_ptr<void> window::get_user_data() const {
		return userData_;
	}

	//----------------------------------------------------------------
	void window::set_user_data(std::shared_ptr<void> data) {
		userData_ = data;

	}

	//----------------------------------------------------------------
	uint32_t window::get_id() const {
		return id_;
	}

	//----------------------------------------------------------------
	void window::set_id(uint32_t id)  {
		id_ = id;
	}

	//----------------------------------------------------------------
	void window::get_size(rect2i& rect) const {
		NYX_ASSERT(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		//
		rect.x      = _r.left;
		rect.y      = _r.top;
		rect.width  = _r.right  - _r.left;
		rect.height = _r.bottom - _r.top;
	}


	//----------------------------------------------------------------
	void window::set_size(const rect2i& rect) {
		NYX_ASSERT(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void window::get_position(point2i& p) const {
		NYX_ASSERT(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	//----------------------------------------------------------------
	void window::set_position(const point2i& p) {
		NYX_ASSERT(hwnd_ != NULL);

		//現在のウインドウの幅・高さを取得する
		rect2i r;
		get_size(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	HMENU window::get_menu() {
		NYX_ASSERT(hwnd_ != NULL);
		return ::GetMenu(hwnd_);
	}

	//----------------------------------------------------------------
	void window::set_menu(HMENU menu) {
		NYX_ASSERT(hwnd_ != NULL);
		::SetMenu(hwnd_, menu);
	}

		//----------------------------------------------------------------
	void window::register_widget(std::shared_ptr<iwidget> control) {
		uint32_t key = control->get_id();
		auto it = childControl_.find(key);
		if (it == childControl_.end()) {
			childControl_[key] = control;
		}
	}

	//----------------------------------------------------------------
	void window::unregister_widget(std::shared_ptr<iwidget> control) {
		auto id = control->get_id();
		auto it = childControl_.find(id);
		if (it != childControl_.end()) {
			childControl_.erase(it);
		}
	}

	//----------------------------------------------------------------
	void window::add_event(std::shared_ptr<iwidget> control, gui_callback fp) {
		NYX_ASSERT(guiEventList_ != NULL);
		register_widget(control);
		guiEventList_->add(control, fp);
	}

	//----------------------------------------------------------------
	void window::del_event(std::shared_ptr<iwidget> control) {
		NYX_ASSERT(guiEventList_ != NULL);
		guiEventList_->remove(control);
	}

	//----------------------------------------------------------------
	void window::clear_event() {
		NYX_ASSERT(guiEventList_ != NULL);
		guiEventList_->clear();
	}

	//----------------------------------------------------------------
	void window::add_user_event(std::shared_ptr<iwidget> control, gui_callback fp) {
		NYX_ASSERT(userEventList_ != NULL);
		register_widget(control);
		userEventList_->add(control, fp);
	}

	//----------------------------------------------------------------
	void window::del_user_event(std::shared_ptr<iwidget> control) {
		NYX_ASSERT(userEventList_ != NULL);
		userEventList_->remove(control);
	}

	//----------------------------------------------------------------
	void window::clear_user_event() {
		NYX_ASSERT(userEventList_ != NULL);
		userEventList_->clear();
	}

	//----------------------------------------------------------------
	bool window::process_message() {
		MSG msg;
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.message != WM_QUIT;
	}

	LRESULT __stdcall window::global_procedure(HWND hWnd, UINT msg,WPARAM wParam, LPARAM lParam) {
		//-------------------------------------------------------------------------------------
		//OS側のメッセージ処理
		//-------------------------------------------------------------------------------------
		switch(msg) 
		{
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			::SetCapture( hWnd );
			break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			::ReleaseCapture();
			break;
		case WM_IME_SETCONTEXT:
			lParam = 0;
			break;
		case WM_DESTROY:	
			PostQuitMessage(0);
			return 0;
		case WM_CLOSE:
			::DestroyWindow(hWnd);
			hWnd = NULL;
			return 0;
		}

		//ウインドウデータを取得
		window* win= (window*)GetWindowLongW(hWnd, GWL_USERDATA);
		if (win == NULL) {
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		//メッセージ送ってきたコントロールを特定
		uint32_t controlId = LOWORD(wParam);
		if (win->childControl_.size() > 0) {
			hook_list_iterator it = win->childControl_.find(controlId);
			if (it == win->childControl_.end()) {
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

			//メッセージディスパッチ
			auto sender = it->second;
			event_args e(msg, wParam, lParam);

			//-------------------------------------------------------------------------------------
			//GUIイベントメッセージ処理
			//-------------------------------------------------------------------------------------
			win->guiEventList_->dispatch(sender, e);

			//-------------------------------------------------------------------------------------
			//ユーザーイベントメッセージ処理
			//-------------------------------------------------------------------------------------
			win->userEventList_->dispatch(sender, e);
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}