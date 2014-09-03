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

namespace nyx {
	//-----------------------------------------------------------------------------------------
	window::window(window_handle handle, const std::wstring& caption, const std::wstring& icon, int x, int y, int width, int height)
		:hwnd_(NULL), caption_(caption), icon_(icon), id_(0), childControl_(), guiEventList_(nullptr) {
		//�t�b�N���X�g������������Ă��Ȃ���΁A����������
		guiEventList_ = std::make_shared<dispatcher>();

		//�R���g���[���̐���
		create(handle, x, y, width, height);
	}

	//-----------------------------------------------------------------------------------------
	//
	window::~window() {
		if (atom_) {
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}

		childControl_.clear();
		guiEventList_->clear_callback();
	}


	//-----------------------------------------------------------------------------------------
	//
	bool window::create(window_handle hwnd, int x, int y, int width, int height) {
		//�E�C���h�E�N���X�̍쐬
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		WNDCLASS winc;
		winc.style = CS_HREDRAW | CS_VREDRAW;
		winc.lpfnWndProc = global_procedure;
		winc.cbClsExtra = winc.cbWndExtra = 0;
		winc.hInstance = hInstance;
		winc.hIcon = LoadIcon(NULL, icon_.c_str());
		winc.hCursor = LoadCursor(NULL, IDC_ARROW);
		winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		winc.lpszMenuName = NULL;
		winc.lpszClassName = caption_.c_str();
		atom_ = RegisterClass(&winc);

		//�E�C���h�E�̐���
		hwnd_ = CreateWindow(
			caption_.c_str(),
			caption_.c_str(), //�^�C�g���o�[�ɂ��̖��O���\������܂�
			WS_OVERLAPPEDWINDOW, //�E�B���h�E�̎��
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
	void window::set_user_data(const std::shared_ptr<void>& data) {
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
		rect.x = _r.left;
		rect.y = _r.top;
		rect.width = _r.right - _r.left;
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

		//���݂̃E�C���h�E�̕��E�������擾����
		rect2i r;
		get_size(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	nyx::menu_handle window::get_menu()
	{
		NYX_ASSERT(hwnd_ != NULL);
		return ::GetMenu(hwnd_);
	}

	//----------------------------------------------------------------
	void window::set_menu(menu_handle menu) {
		NYX_ASSERT(hwnd_ != NULL);
		::SetMenu(hwnd_, menu);
	}

	//----------------------------------------------------------------
	void window::register_widget(iwidget& control) {
		uint32_t key = childControl_.size() + id_ + 1;
		control.set_id(key);
		auto it = childControl_.find(key);
		if (it == childControl_.end()) {
			childControl_.insert(hook_list::value_type(key, control));
		}
	}

	//----------------------------------------------------------------
	void window::unregister_widget(iwidget& control) {
		auto id = control.get_id();
		auto it = childControl_.find(id);
		if (it != childControl_.end()) {
			childControl_.erase(it);
		}
	}

	//----------------------------------------------------------------
	//
	void window::on_mouse_down(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_MOUSE_DOWN, callback);
	}

	//----------------------------------------------------------------
	//
	void window::on_mouse_up(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_MOUSE_UP, callback);
	}

	//----------------------------------------------------------------
	//
	void window::on_paint(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_PAINT, callback);
	}

	//----------------------------------------------------------------
	//
	void window::on_resize(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_RESIZE, callback);
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


	void window::dispatch(WIDGET_EVENT_TYPE eventType, event_args& e) {
		if (eventType != WIDGET_EVENT_TYPE_NUM) {
			this->guiEventList_->dispatch(eventType, *this, e);
		}
	}

	LRESULT __stdcall window::global_procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		//-------------------------------------------------------------------------------------
		//OS���̃��b�Z�[�W����
		//-------------------------------------------------------------------------------------
		WIDGET_EVENT_TYPE eventType = WIDGET_EVENT_TYPE_NUM;
		event_args e{ msg, wParam, lParam };
		int controlId = -1;
		uint32_t notifyCode = 0;
		switch (msg)
		{
		case WM_COMMAND:
			controlId = LOWORD(wParam);
			notifyCode = HIWORD(wParam);
			switch (notifyCode) {
			case BN_CLICKED:
				eventType = WIDGET_EVENT_TYPE_CLICK; break;
			case LBN_SELCHANGE:
				eventType = WIDGET_EVENT_TYPE_INDEX_CHANGED; break;
			}
			break;
		case WM_DRAWITEM:
			controlId = LOWORD(wParam);
			eventType = WIDGET_EVENT_TYPE_PAINT;
			break;
		case WM_PAINT:
			eventType = WIDGET_EVENT_TYPE_PAINT;
			break;
		case WM_SIZE:
			eventType = WIDGET_EVENT_TYPE_RESIZE;
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			eventType = WIDGET_EVENT_TYPE_MOUSE_DOWN;
			::SetCapture(hWnd);
			break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			eventType = WIDGET_EVENT_TYPE_MOUSE_UP;
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
		window* win = (window*)GetWindowLongW(hWnd, GWL_USERDATA);
		if (win == NULL) {
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		if (controlId == -1) {
			win->dispatch(eventType, e);
		}
		else {
			hook_list_iterator it = win->childControl_.find(controlId);
			if (it == win->childControl_.end()) {
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

			//���b�Z�[�W�f�B�X�p�b�`
			iwidget& sender = it->second;
			sender.dispatch(eventType, e);
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}