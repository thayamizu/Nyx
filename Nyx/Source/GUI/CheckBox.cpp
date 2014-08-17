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
			::MessageBox(NULL, TEXT("���s���܂���"), TEXT("error"), MB_OK);
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