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
#include "Primitive/Rect2i.h"
namespace Nyx {
	//-----------------------------------------------------------------------------------------
	Window::Window(HWND hWnd, std::wstring caption_, int x, int y, int width, int height, int id_)
		:title(caption_), id(id_),hooklist(), guiEventList(NULL), userEventList(NULL)  {
			//フックリストが初期化されていなければ、初期化する
			if (guiEventList ==NULL) {
				guiEventList = new Dispatcher();
			}
			//フックリストが初期化されていなければ、初期化する
			if (userEventList ==NULL) {
				userEventList = new Dispatcher();
			}

			//メンバの初期化
			title += TEXT("　 (C)opyright t.hayamizu.");
			
			OnCreate(hWnd,x, y, width, height);
	}    

	//-----------------------------------------------------------------------------------------
	//
	Window::~Window() {
		if (atom) {
			::UnregisterClass((LPCTSTR)atom, ::GetModuleHandle(NULL));
		}

		SafeDelete(guiEventList);
		SafeDelete(userEventList);
	}


	//-----------------------------------------------------------------------------------------
	//
	bool Window::OnCreate(HWND _hwnd, int x, int y, int width, int height) {
		//ウインドウクラスの作成
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		WNDCLASSEX winc;
		winc.cbSize			= sizeof(WNDCLASSEX);
		winc.style			= CS_HREDRAW | CS_VREDRAW;
		winc.lpfnWndProc	= GlobalProcedure;
		winc.cbClsExtra		= winc.cbWndExtra	= 0;
		winc.hInstance		= hInstance;
		winc.hIcon			= LoadIcon(NULL , IDI_APPLICATION);
		winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
		winc.hbrBackground	= (HBRUSH)COLOR_BACKGROUND + 1;
		winc.lpszMenuName	= NULL;
		winc.lpszClassName	= title.c_str();
		winc.hIconSm		= NULL;
		atom = RegisterClassEx(&winc);

		//ウインドウの生成
		hwnd = CreateWindowEx(
			WS_EX_LEFT,
			title.c_str(),
			title.c_str(), //タイトルバーにこの名前が表示されます
			WS_OVERLAPPEDWINDOW , //ウィンドウの種類
			//WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU, //ウィンドウの種類
			x,	//Ｘ座標
			y,	//Ｙ座標
			width,	//幅
			height,	//高さ
			_hwnd, //親ウィンドウのハンドル、親を作るときはNULL
			NULL, //メニューハンドル、クラスメニューを使うときはNULL
			hInstance, //インスタンスハンドル
			NULL);

		if (!hwnd) {
			::MessageBox(NULL, TEXT("失敗しました"), TEXT("error"), MB_OK);
		}

		::SetWindowLong(hwnd, GWL_USERDATA, (long)this);
		
		//自分をフックする
		Regist(this);
		
		Show();
		return true;
	}


	//---------------------------------------------------------------------------------------
	HWND Window::GetHandle() {
		Assert(hwnd != NULL);
		return hwnd;
	}

	//----------------------------------------------------------------
	void Window::Show(){
		Assert(hwnd != NULL);
		isShow = true;
		::ShowWindow(hwnd, SW_SHOW);
	}

	//----------------------------------------------------------------
	void Window::Hide(){
		Assert(hwnd != NULL);
		isShow = false;
		::ShowWindow(hwnd, SW_HIDE);
	}

	//----------------------------------------------------------------
	void Window::Update() {
		Assert(hwnd != NULL);
		::UpdateWindow(hwnd);
	}

	//----------------------------------------------------------------
	bool Window::IsShow() {
		return isShow;
	}

	//----------------------------------------------------------------
	void Window::Activate() {
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, true);
	}

	//----------------------------------------------------------------
	void Window::Unactivate() {
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, false);
	}

	//----------------------------------------------------------------
	bool Window::IsActivate() const {
		Assert(hwnd != NULL);
		return ::IsWindowEnabled(hwnd);
	}


	//----------------------------------------------------------------
	ControlType::enum_t Window::GetType() const{
		return ControlType::Window;
	}

	//----------------------------------------------------------------
	void* Window::GetUserData() const {
		return userData;
	}

	//----------------------------------------------------------------
	void Window::SetUserData(void * data) {
		userData = data;

	}

	//----------------------------------------------------------------
	uint Window::GetID() const {
		return id;
	}

	//----------------------------------------------------------------
	void Window::SetID(uint _id)  {
		id = _id;
	}

	//----------------------------------------------------------------
	void Window::GetSize(Rect2i* rect) const {
		Assert(hwnd != NULL);
		RECT _r;
		::GetWindowRect(hwnd, &_r);

		//
		rect->x = _r.left;
		rect->y = _r.top;
		rect->width  = _r.right  - _r.left;
		rect->height = _r.bottom - _r.top;
	}

	//----------------------------------------------------------------
	void Window::SetSize(const Rect2i& rect) {
		Assert(hwnd != NULL);
		::SetWindowPos(hwnd, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void Window::GetPosition(Point2i* p) const {
		Assert(hwnd != NULL);
		RECT _r;
		::GetWindowRect(hwnd, &_r);

		p->x = _r.left;
		p->y = _r.top;
	}

	//----------------------------------------------------------------
	void Window::SetPosition(const Point2i& p) {
		Assert(hwnd != NULL);

		//現在のウインドウの幅・高さを取得する
		Rect2i r;
		GetSize(&r);

		::SetWindowPos(hwnd, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	HMENU Window::GetMenu() {
		Assert(hwnd != NULL);
		return ::GetMenu(hwnd);
	}

	//----------------------------------------------------------------
	void Window::SetMenu(HMENU menu) {
		Assert(hwnd != NULL);
		::SetMenu(hwnd, menu);
	}

	//----------------------------------------------------------------
	HICON Window::GetIcon() {
		return NULL;
	}

	//----------------------------------------------------------------
	void Window::SetIcon(std::wstring icon) {
		Assert(userEventList != NULL);
		LoadIcon(GetModuleHandle(NULL), icon.c_str());
	}

	//----------------------------------------------------------------
	void Window::Regist(IControl* control) {
		uint key = control->GetID();
		HookListIterator it = hooklist.find(key);
		if (it == hooklist.end()) {
			hooklist[key] = control;
		}
	}

	//----------------------------------------------------------------
	void Window::Unregist(IControl* control) {
		HookListIterator it = hooklist.find(control->GetID());
		if (it != hooklist.end()) {
			hooklist.erase(it);
		}
	}

	//----------------------------------------------------------------
	void Window::AddGUIEvent(IControl* control, Delegate2<IControl*, EventArgs*>* fp) {
		Assert(guiEventList != NULL);
		Regist(control);
		guiEventList->Add(control, fp);
	}

	//----------------------------------------------------------------
	void Window::DelGUIEvent(IControl* control) {
		Assert(guiEventList != NULL);
		guiEventList->Del(control);
	}

	//----------------------------------------------------------------
	void Window::ClearGUIEvent() {
		Assert(guiEventList != NULL);
		guiEventList->Clear();
	}

	//----------------------------------------------------------------
	void Window::AddUserEvent(IControl* control, Delegate2<IControl*, EventArgs*>* fp) {
		Assert(userEventList != NULL);
		Regist(control);
		userEventList->Add(control, fp);
	}

	//----------------------------------------------------------------
	void Window::DelUserEvent(IControl* control) {
		Assert(userEventList != NULL);
		userEventList->Del(control);
	}

	//----------------------------------------------------------------
	void Window::ClearUserEvent() {
		Assert(userEventList != NULL);
		userEventList->Clear();
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
		HookListIterator it = window->hooklist.find(LOWORD(wParam));
		if (it == window->hooklist.end()) {
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		//メッセージディスパッチ
		bool result = false;
		EventArgs event(msg, wParam, lParam, &result);
		IControl * control = it->second;

		//-------------------------------------------------------------------------------------
		//GUIイベントメッセージ処理
		//-------------------------------------------------------------------------------------
		window->guiEventList->Dispatch(control, &event);
		if (result) {
			return 0;
		}

		//-------------------------------------------------------------------------------------
		//ユーザーイベントメッセージ処理
		//-------------------------------------------------------------------------------------
		window->userEventList->Dispatch(control, &event);
		if (result) {
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}