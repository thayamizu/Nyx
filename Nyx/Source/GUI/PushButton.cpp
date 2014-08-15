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
#include "Debug/Assert.h"
#include "GUI/PushButton.h"
#include "Primitive/Rect.h"
#include "Primitive/Vector2.h"

namespace nyx {
	//------------------------------------------------------------------------------
	push_button::push_button(HWND hwnd, const std::wstring& label, int x, int y, int width, int height, int id)
		:label_(label), hwnd_(NULL), id_(id), atom_(NULL), isShow_(false), isActivate_(true)
	{

		on_create(hwnd, label, x, y, width, height, id);
	}       

	//------------------------------------------------------------------------------
	push_button::~push_button() 
	{
		if (atom_) { 
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}
	}

	//------------------------------------------------------------------------------
	bool push_button::on_create(HWND hwnd, const std::wstring& label, int x, int y, int width, int height, int id) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd_ = CreateWindow(TEXT("BUTTON"), label.c_str(), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 	
			x, y, width, height, hwnd,  (HMENU)id, hInstance, NULL);

		NYX_ASSERT(hwnd != NULL);
		if (!hwnd) {
			::MessageBox(NULL, TEXT("���s���܂���"), TEXT("error"), MB_OK);
			return false;
		}
		//�R���g���[���̕\��
		show();
		return true;
	}
	//---------------------------------------------------------------------------------------
	void push_button::show() 
	{
		NYX_ASSERT(hwnd_ != NULL);
		isShow_ = true;
		::ShowWindow(hwnd_, SW_SHOW);   
	}

	//---------------------------------------------------------------------------------------
	void push_button::hide() 
	{
		NYX_ASSERT(hwnd_ != NULL);
		isShow_ = false;
		::ShowWindow(hwnd_, SW_HIDE);   
	}

	//---------------------------------------------------------------------------------------
	void push_button::update() 
	{
		NYX_ASSERT(hwnd_ != NULL);
		::UpdateWindow(hwnd_);
	}

	//---------------------------------------------------------------------------------------
	bool push_button::is_show() 
	{
		return isShow_;
	}

	//---------------------------------------------------------------------------------------
	void push_button::activate() 
	{
		NYX_ASSERT(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//---------------------------------------------------------------------------------------
	void push_button::unactivate() 
	{
		NYX_ASSERT(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}

	//---------------------------------------------------------------------------------------
	bool push_button::is_activate() 
		const 
	{
		NYX_ASSERT(hwnd_ != NULL);
		return IsWindowEnabled(hwnd_) != 0;
	}

	//---------------------------------------------------------------------------------------
	nyx::window_handle push_button::get_handle()
{
		NYX_ASSERT(hwnd_ != NULL);
		return hwnd_;
	}

	//---------------------------------------------------------------------------------------
	WIDGET_TYPE push_button::get_type() 
		const 
	{
		return WIDGET_TYPE_BUTTON;
	}

	//---------------------------------------------------------------------------------------
	std::shared_ptr<void> push_button::get_user_data() 
		const 
	{
		return userData_;
	}

	//---------------------------------------------------------------------------------------
	void push_button::set_user_data(std::shared_ptr<void> data) 
	{
		userData_ = data;
	}

	//---------------------------------------------------------------------------------------
	uint32_t push_button::get_id() 
		const 
	{
		return id_;
	}

	//---------------------------------------------------------------------------------------
	void push_button::set_id(uint32_t id)  
	{
		id_ = id;
	}
	//---------------------------------------------------------------------------------------
	void push_button::get_size(rect2i& rect)
		const 
	{
		NYX_ASSERT(hwnd_ != NULL);
		RECT r;
		::GetWindowRect(hwnd_, &r);

		//
		rect.x = r.left;
		rect.y = r.top;
		rect.width  = r.right  - r.left;
		rect.height = r.bottom - r.top;
	}

	//---------------------------------------------------------------------------------------
	void push_button::set_size(const rect2i& rect)
	{
		NYX_ASSERT(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//---------------------------------------------------------------------------------------
	void push_button::get_position(point2i& p) 
		const 
	{
		NYX_ASSERT(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	//---------------------------------------------------------------------------------------
	void push_button::set_position(const point2i& p) 
	{
		NYX_ASSERT(hwnd_ != NULL);
		rect2i r;
		get_size(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//---------------------------------------------------------------------------------------
	std::wstring push_button::GetLabel() 
		const
	{
		return label_;
	}

	//---------------------------------------------------------------------------------------
	void push_button::SetLabel(const std::wstring& label)
	{
		label_ = label;
		SetWindowText(hwnd_, label_.c_str());
	}
}