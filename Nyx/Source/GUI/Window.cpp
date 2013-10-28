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
#include "Primitive/Rect.h"
namespace Nyx {
	//-----------------------------------------------------------------------------------------
	Window::Window(HWND hWnd, std::wstring caption, std::wstring icon, int x, int y, int width, int height, int id)
		:hwnd_(NULL), caption_(caption), icon_(icon), id_(id), childControl_(), guiEventList_(nullptr), userEventList_(nullptr)  {
			//�t�b�N���X�g������������Ă��Ȃ���΁A����������
			guiEventList_ = std::make_shared<Dispatcher>();
			
			//�t�b�N���X�g������������Ă��Ȃ���΁A����������
			userEventList_ = std::make_shared<Dispatcher>();

			//�R���g���[���̐���
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
		//�E�C���h�E�N���X�̍쐬
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

		//�E�C���h�E�̐���
		hwnd_ = CreateWindow(
			caption_.c_str(),
			caption_.c_str(), //�^�C�g���o�[�ɂ��̖��O���\������܂�
			WS_OVERLAPPEDWINDOW , //�E�B���h�E�̎��
			x,	//�w���W
			y,	//�x���W
			width,	//��
			height,	//����
			hwnd, //�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
			NULL, //���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
			hInstance, //�C���X�^���X�n���h��
			NULL);

		if (hwnd_ == NULL) {
			::MessageBox(NULL, TEXT("���s���܂���"), TEXT("error"), MB_OK);
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

		//���݂̃E�C���h�E�̕��E�������擾����
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
		uint controlId = LOWORD(wParam);
		HookListIterator it = window->childControl_.find(controlId);
		if (it == window->childControl_.end()) {
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		//���b�Z�[�W�f�B�X�p�b�`
		auto sender = it->second;
		EventArgs e(msg, wParam, lParam);

		//-------------------------------------------------------------------------------------
		//GUI�C�x���g���b�Z�[�W����
		//-------------------------------------------------------------------------------------
		window->guiEventList_->Dispatch(sender, e);

		//-------------------------------------------------------------------------------------
		//���[�U�[�C�x���g���b�Z�[�W����
		//-------------------------------------------------------------------------------------
		window->userEventList_->Dispatch(sender, e);

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}