/********************************************************************************
*
*  The MIT License
*
* Copyright (c) 2010-2011 t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
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
			//�t�b�N���X�g������������Ă��Ȃ���΁A����������
			if (guiEventList ==NULL) {
				guiEventList = new Dispatcher();
			}
			//�t�b�N���X�g������������Ă��Ȃ���΁A����������
			if (userEventList ==NULL) {
				userEventList = new Dispatcher();
			}

			//�����o�̏�����
			title += TEXT("�@ (C)opyright t.hayamizu.");
			
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
		//�E�C���h�E�N���X�̍쐬
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

		//�E�C���h�E�̐���
		hwnd = CreateWindowEx(
			WS_EX_LEFT,
			title.c_str(),
			title.c_str(), //�^�C�g���o�[�ɂ��̖��O���\������܂�
			WS_OVERLAPPEDWINDOW , //�E�B���h�E�̎��
			//WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU, //�E�B���h�E�̎��
			x,	//�w���W
			y,	//�x���W
			width,	//��
			height,	//����
			_hwnd, //�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
			NULL, //���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
			hInstance, //�C���X�^���X�n���h��
			NULL);

		if (!hwnd) {
			::MessageBox(NULL, TEXT("���s���܂���"), TEXT("error"), MB_OK);
		}

		::SetWindowLong(hwnd, GWL_USERDATA, (long)this);
		
		//�������t�b�N����
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

		//���݂̃E�C���h�E�̕��E�������擾����
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
		//OS���̃��b�Z�[�W����
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

		//�E�C���h�E�f�[�^���擾
		Window* window = (Window*)::GetWindowLong(hWnd, GWL_USERDATA);
		if (window == NULL) {
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		//���b�Z�[�W�����Ă����R���g���[�������
		HookListIterator it = window->hooklist.find(LOWORD(wParam));
		if (it == window->hooklist.end()) {
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		//���b�Z�[�W�f�B�X�p�b�`
		bool result = false;
		EventArgs event(msg, wParam, lParam, &result);
		IControl * control = it->second;

		//-------------------------------------------------------------------------------------
		//GUI�C�x���g���b�Z�[�W����
		//-------------------------------------------------------------------------------------
		window->guiEventList->Dispatch(control, &event);
		if (result) {
			return 0;
		}

		//-------------------------------------------------------------------------------------
		//���[�U�[�C�x���g���b�Z�[�W����
		//-------------------------------------------------------------------------------------
		window->userEventList->Dispatch(control, &event);
		if (result) {
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}