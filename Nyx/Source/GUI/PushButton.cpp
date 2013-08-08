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
#include "Object/Delegate.h"
#include "Primitive/Rect.h"
#include "Primitive/Vector2.h"

namespace Nyx {
	//------------------------------------------------------------------------------
	PushButton::PushButton(HWND hwnd, const std::wstring& label, int x, int y, int width, int height, int id)
		:label_(label), hwnd_(NULL), id_(id), atom_(NULL), isShow_(false), isActivate_(true)
	{

		OnCreate(hwnd, label, x, y, width, height, id);
	}       

	//------------------------------------------------------------------------------
	PushButton::~PushButton() 
	{
		if (atom_) { 
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}
	}

	//------------------------------------------------------------------------------
	bool PushButton::OnCreate(HWND hwnd, const std::wstring& label, int x, int y, int width, int height, int id) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd_ = CreateWindow(TEXT("BUTTON"), label.c_str(), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 	
			x, y, width, height, hwnd,  (HMENU)id, hInstance, NULL);

		Assert(hwnd != NULL);
		if (!hwnd) {
			::MessageBox(NULL, TEXT("���s���܂���"), TEXT("error"), MB_OK);
			return false;
		}
		//�R���g���[���̕\��
		Show();
		return true;
	}
	//---------------------------------------------------------------------------------------
	void PushButton::Show() 
	{
		Assert(hwnd_ != NULL);
		isShow_ = true;
		::ShowWindow(hwnd_, SW_SHOW);   
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Hide() 
	{
		Assert(hwnd_ != NULL);
		isShow_ = false;
		::ShowWindow(hwnd_, SW_HIDE);   
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Update() 
	{
		Assert(hwnd_ != NULL);
		::UpdateWindow(hwnd_);
	}

	//---------------------------------------------------------------------------------------
	bool PushButton::IsShow() 
	{
		return isShow_;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Activate() 
	{
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Unactivate() 
	{
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}

	//---------------------------------------------------------------------------------------
	bool PushButton::IsActivate() 
		const 
	{
		Assert(hwnd_ != NULL);
		return IsWindowEnabled(hwnd_) != 0;
	}

	//---------------------------------------------------------------------------------------
	HWND  PushButton::GetHandle() 
	{
		Assert(hwnd_ != NULL);
		return hwnd_;
	}

	//---------------------------------------------------------------------------------------
	ControlType PushButton::GetType() 
		const 
	{
		return ControlType_PushButton;
	}

	//---------------------------------------------------------------------------------------
	std::shared_ptr<void> PushButton::GetUserData() 
		const 
	{
		return userData_;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetUserData(std::shared_ptr<void> data) 
	{
		userData_ = data;
	}

	//---------------------------------------------------------------------------------------
	uint PushButton::GetID() 
		const 
	{
		return id_;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetID(uint id)  
	{
		id_ = id;
	}
	//---------------------------------------------------------------------------------------
	void PushButton::GetSize(Rect2i& rect)
		const 
	{
		Assert(hwnd_ != NULL);
		RECT r;
		::GetWindowRect(hwnd_, &r);

		//
		rect.x = r.left;
		rect.y = r.top;
		rect.width  = r.right  - r.left;
		rect.height = r.bottom - r.top;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetSize(const Rect2i& rect) 
	{
		Assert(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//---------------------------------------------------------------------------------------
	void PushButton::GetPosition(Point2i& p) 
		const 
	{
		Assert(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetPosition(const Point2i& p) 
	{
		Assert(hwnd_ != NULL);
		Rect2i r;
		GetSize(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//---------------------------------------------------------------------------------------
	std::wstring PushButton::GetLabel() 
		const
	{
		return label_;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetLabel(const std::wstring& label)
	{
		label_ = label;
		SetWindowText(hwnd_, label_.c_str());
	}
}