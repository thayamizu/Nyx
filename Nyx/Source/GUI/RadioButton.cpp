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
#include "GUI/RadioButton.h"
#include "Debug/Assert.h"
#include "Primitive/Rect.h"
#include "Primitive/Vector2.h"
#include "Window.h"
#include "Dispatcher.h"

namespace nyx {
	//-----------------------------------------------------------------------------------------
	radio_button::radio_button(std::shared_ptr<window>& parent, std::wstring label, int x, int y, int width, int height, bool isOwnerDraw)
		: label_(label), hwnd_(NULL), atom_(NULL), isShow_(false), userData_(nullptr), guiEventList_(std::make_shared<dispatcher>()) {

		parent->register_widget(*this);
		create(parent->get_handle(), label_, x, y, width, height, isOwnerDraw);
	}       

	//-----------------------------------------------------------------------------------------
	radio_button::~radio_button() {
		if (atom_) {
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}
	}

	//-----------------------------------------------------------------------------------------
	bool radio_button::create(window_handle hwnd, std::wstring label, int x, int y, int width, int height, bool isOwnerDraw) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);

		DWORD radioButtonStyle;
		if (isOwnerDraw) {
			radioButtonStyle = WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_OWNERDRAW;
		}
		else {
			radioButtonStyle = WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON;
		}
		hwnd_ = CreateWindow(
			TEXT("BUTTON"), label.c_str(), radioButtonStyle, //�E�B���h�E�̎��
			x, y, width, height, hwnd, (HMENU)id_, hInstance, NULL);

		NYX_ASSERT(hwnd_ != NULL);
		if (!hwnd_) {
			::MessageBox(NULL, TEXT("���s���܂���"), TEXT("error"), MB_OK);
			return false;
		}

		//�R���g���[���̕\��
		show();
		return true;
	}

	//---------------------------------------------------------------------------------------
	nyx::window_handle radio_button::get_handle()
{
		NYX_ASSERT(hwnd_ != NULL);
		return hwnd_;
	}

	//----------------------------------------------------------------
	void radio_button::show() {
		NYX_ASSERT(hwnd_ != NULL);
		isShow_ = true;
		::ShowWindow(hwnd_, SW_SHOW);  
	}

	//----------------------------------------------------------------
	void radio_button::hide(){
		NYX_ASSERT(hwnd_ != NULL);
		isShow_ = false;
		::ShowWindow(hwnd_, SW_HIDE);  
	}

	//----------------------------------------------------------------
	void radio_button::update() {
		NYX_ASSERT(hwnd_ != NULL);
		::UpdateWindow(hwnd_);

	}

	//----------------------------------------------------------------
	bool radio_button::is_show() {
		return isShow_;
	}

	//----------------------------------------------------------------
	void radio_button::activate() {
		NYX_ASSERT(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//----------------------------------------------------------------
	void radio_button::unactivate() {
		NYX_ASSERT(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}

	//----------------------------------------------------------------
	bool radio_button::is_activate() const {
		NYX_ASSERT(hwnd_ != NULL);
		return IsWindowEnabled(hwnd_) != 0;
	}

	//----------------------------------------------------------------
	WIDGET_TYPE radio_button::get_type() const{
		return WIDGET_TYPE_RADIO_BUTTON;
	}

	//----------------------------------------------------------------
	std::shared_ptr<void> radio_button::get_user_data() const {
		return userData_;
	}

	//----------------------------------------------------------------
	void radio_button::set_user_data(const std::shared_ptr<void>& data) {
		userData_ = data;
	}

	//----------------------------------------------------------------
	uint32_t radio_button::get_id() const {
		return id_;
	}

	//----------------------------------------------------------------
	void radio_button::set_id(uint32_t id)  {
		id_ = id;
	}

	//----------------------------------------------------------------
	void radio_button::get_size(rect2i& rect) const {
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
	void radio_button::set_size(const rect2i& rect) {
		NYX_ASSERT(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void radio_button::get_position(point2i& p) const {
		NYX_ASSERT(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	//----------------------------------------------------------------
	void radio_button::set_position(const point2i& p) {
		NYX_ASSERT(hwnd_ != NULL);
		rect2i r;
		get_size(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	std::wstring radio_button::get_label() const  {
		return label_;
	}

	//----------------------------------------------------------------
	void radio_button::set_label(const std::wstring& label) {
		label_ = label;
		SetWindowText(hwnd_, label.c_str());
	}

	//----------------------------------------------------------------
	bool radio_button::is_checked() const {
		LRESULT result = ::SendMessage(hwnd_, BST_CHECKED, 0, 0);
		return result == BST_CHECKED;
	}

	//----------------------------------------------------------------
	void radio_button::on_checked_changed(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_CHECKED_CHANGED, callback);
	}

	//----------------------------------------------------------------
	void radio_button::on_click(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_CLICK, callback);
	}

	//----------------------------------------------------------------
	void radio_button::on_paint(const gui_callback& callback) {
		NYX_ASSERT(guiEventList_ != nullptr);
		this->guiEventList_->add_callback(WIDGET_EVENT_TYPE_PAINT, callback);
	}

	//----------------------------------------------------------------
	void radio_button::dispatch(WIDGET_EVENT_TYPE eventType, event_args& e) {
		NYX_ASSERT(guiEventList_ != nullptr);
		if (eventType != WIDGET_EVENT_TYPE_NUM) {
			this->guiEventList_->dispatch(eventType, *this, e);
		}
	}
}