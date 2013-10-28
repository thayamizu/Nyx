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
namespace Nyx {
	//-----------------------------------------------------------------------------------------
	Window::Window(HWND hWnd, std::wstring caption, std::wstring icon, int x, int y, int width, int height, int id)
		:hwnd_(NULL), caption_(caption), icon_(icon), id_(id), childControl_(), guiEventList_(nullptr), userEventList_(nullptr)  {
			//フックリストが初期化されていなければ、初期化する
			guiEventList_ = std::make_shared<Dispatcher>();
			
			//フックリストが初期化されていなければ、初期化する
			userEventList_ = std::make_shared<Dispatcher>();

			//コントロールの生成
			OnCreate(hWnd, x, y, width, height);
	}    

	//-----------------------------------------------------------------------------------------
	//
	Window::~Window() {
		if (atom_) {
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}

		childControl_.clear();
		userEventList_->Clear();
		guiEventList_->Clear();
	}


	//-----------------------------------------------------------------------------------------
	//
	bool Window::OnCreate(HWND hwnd, int x, int y, int width, int height) {
		//ウインドウクラスの作成
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		WNDCLASS winc;
		winc.style			= CS_HREDRAW | CS_VREDRAW;
		winc.lpfnWndProc	= GlobalProcedure;
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
		
		Show();
		return true;
	}


	//---------------------------------------------------------------------------------------
	HWND Window::GetHandle() {
		Assert(hwnd_ != NULL);
		return hwnd_;
	}

	//----------------------------------------------------------------
	void Window::Show(){
		Assert(hwnd_ != NULL);
		isShow = true;
		::ShowWindow(hwnd_, SW_SHOW);
	}

	//----------------------------------------------------------------
	void Window::Hide(){
		Assert(hwnd_ != NULL);
		isShow = false;
		::ShowWindow(hwnd_, SW_HIDE);
	}

	//----------------------------------------------------------------
	void Window::Update() {
		Assert(hwnd_ != NULL);
		::UpdateWindow(hwnd_);
	}

	//----------------------------------------------------------------
	bool Window::IsShow() {
		return isShow;
	}
	
	//----------------------------------------------------------------
	void Window::ShowCursor(bool isShowCursor) {
		::ShowCursor(isShowCursor);
	}
	
	//----------------------------------------------------------------
	void Window::Activate() {
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//----------------------------------------------------------------
	void Window::Unactivate() {
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}

	//----------------------------------------------------------------
	bool Window::IsActivate() const {
		Assert(hwnd_ != NULL);
		return ::IsWindowEnabled(hwnd_) != 0;
	}


	//----------------------------------------------------------------
	ControlType Window::GetType() const{
		return ControlType_Window;
	}

	//----------------------------------------------------------------
	std::shared_ptr<void> Window::GetUserData() const {
		return userData_;
	}

	//----------------------------------------------------------------
	void Window::SetUserData(std::shared_ptr<void> data) {
		userData_ = data;

	}

	//----------------------------------------------------------------
	uint Window::GetID() const {
		return id_;
	}

	//----------------------------------------------------------------
	void Window::SetID(uint id)  {
		id_ = id;
	}

	//----------------------------------------------------------------
	void Window::GetSize(Rect2i& rect) const {
		Assert(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		//
		rect.x      = _r.left;
		rect.y      = _r.top;
		rect.width  = _r.right  - _r.left;
		rect.height = _r.bottom - _r.top;
	}


	//----------------------------------------------------------------
	void Window::SetSize(const Rect2i& rect) {
		Assert(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void Window::GetPosition(Point2i& p) const {
		Assert(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	//----------------------------------------------------------------
	void Window::SetPosition(const Point2i& p) {
		Assert(hwnd_ != NULL);

		//現在のウインドウの幅・高さを取得する
		Rect2i r;
		GetSize(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	HMENU Window::GetMenu() {
		Assert(hwnd_ != NULL);
		return ::GetMenu(hwnd_);
	}

	//----------------------------------------------------------------
	void Window::SetMenu(HMENU menu) {
		Assert(hwnd_ != NULL);
		::SetMenu(hwnd_, menu);
	}

		//----------------------------------------------------------------
	void Window::Register(std::shared_ptr<IControl> control) {
		uint key = control->GetID();
		auto it = childControl_.find(key);
		if (it == childControl_.end()) {
			childControl_[key] = control;
		}
	}

	//----------------------------------------------------------------
	void Window::Unregister(std::shared_ptr<IControl> control) {
		auto id = control->GetID();
		auto it = childControl_.find(id);
		if (it != childControl_.end()) {
			childControl_.erase(it);
		}
	}

	//----------------------------------------------------------------
	void Window::AddGUIEvent(std::shared_ptr<IControl> control, GUICallback fp) {
		Assert(guiEventList_ != NULL);
		Register(control);
		guiEventList_->Add(control, fp);
	}

	//----------------------------------------------------------------
	void Window::DelGUIEvent(std::shared_ptr<IControl> control) {
		Assert(guiEventList_ != NULL);
		guiEventList_->Del(control);
	}

	//----------------------------------------------------------------
	void Window::ClearGUIEvent() {
		Assert(guiEventList_ != NULL);
		guiEventList_->Clear();
	}

	//----------------------------------------------------------------
	void Window::AddUserEvent(std::shared_ptr<IControl> control, GUICallback fp) {
		Assert(userEventList_ != NULL);
		Register(control);
		userEventList_->Add(control, fp);
	}

	//----------------------------------------------------------------
	void Window::DelUserEvent(std::shared_ptr<IControl> control) {
		Assert(userEventList_ != NULL);
		userEventList_->Del(control);
	}

	//----------------------------------------------------------------
	void Window::ClearUserEvent() {
		Assert(userEventList_ != NULL);
		userEventList_->Clear();
	}

	//----------------------------------------------------------------
	bool Window::ProcessMessage() {
		MSG msg;
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.message != WM_QUIT;
	}

	LRESULT __stdcall Window::GlobalProcedure(HWND hWnd, UINT msg,WPARAM wParam, LPARAM lParam) {
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
		Window* window = (Window*)::GetWindowLong(hWnd, GWL_USERDATA);
		if (window == NULL) {
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		//メッセージ送ってきたコントロールを特定
		uint controlId = LOWORD(wParam);
		HookListIterator it = window->childControl_.find(controlId);
		if (it == window->childControl_.end()) {
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		//メッセージディスパッチ
		auto sender = it->second;
		EventArgs e(msg, wParam, lParam);

		//-------------------------------------------------------------------------------------
		//GUIイベントメッセージ処理
		//-------------------------------------------------------------------------------------
		window->guiEventList_->Dispatch(sender, e);

		//-------------------------------------------------------------------------------------
		//ユーザーイベントメッセージ処理
		//-------------------------------------------------------------------------------------
		window->userEventList_->Dispatch(sender, e);

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}