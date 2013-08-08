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

namespace Nyx {
	//---------------------------------------------------------------------------------------
	CheckBox::CheckBox(HWND hwnd, std::wstring label, int x, int y, int width, int height, int id) 
		:hwnd_(NULL), label_(label), id_(id), atom_(NULL), isShow_(false), userData_(NULL)	{
		OnCreate(hwnd, label, x, y, width, height, id);
	}

	//---------------------------------------------------------------------------------------
	bool CheckBox::OnCreate(HWND hwnd, std::wstring label, int x, int y, int width, int height, int id) {

		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd_ = CreateWindow(TEXT("BUTTON"), label.c_str(), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 
			x, y, width, height, hwnd, (HMENU)id,  hInstance, NULL);

		Assert(hwnd_ != NULL);
		if (!hwnd_) {
			::MessageBox(NULL, TEXT("���s���܂���"), TEXT("error"), MB_OK);
			return false;
		}
		Show();
		return true;
	}
	//---------------------------------------------------------------------------------------
	CheckBox::~CheckBox() {
		if (atom_) {
			::UnregisterClass((LPCTSTR)atom_, ::GetModuleHandle(NULL));
		}
	}

	//---------------------------------------------------------------------------------------
	HWND CheckBox::GetHandle() {
		Assert(hwnd_ != NULL);
		return hwnd_;
	}

	//----------------------------------------------------------------
	void CheckBox::Show(){
		Assert(hwnd_ !=NULL);
		isShow_ = true;
		::ShowWindow(hwnd_, SW_SHOW);
	}

	//----------------------------------------------------------------
	void CheckBox::Hide(){
		Assert(hwnd_ != NULL);
		isShow_=false;
		::ShowWindow(hwnd_, SW_HIDE);
	}

	//----------------------------------------------------------------
	void CheckBox::Update() {
		Assert(hwnd_ != NULL);
		::UpdateWindow(hwnd_);
	}

	//----------------------------------------------------------------
	bool CheckBox::IsShow() {
		return isShow_;
	}

	//----------------------------------------------------------------
	void CheckBox::Activate() {
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, true);
	}

	//----------------------------------------------------------------
	void CheckBox::Unactivate() {
		Assert(hwnd_ != NULL);
		::EnableWindow(hwnd_, false);
	}

	//----------------------------------------------------------------
	bool CheckBox::IsActivate() const {
		Assert(hwnd_ != NULL);
		return IsWindowEnabled(hwnd_) != 0;
	}

	//----------------------------------------------------------------
	ControlType CheckBox::GetType() const{
		return ControlType_CheckBox;
	}

	//----------------------------------------------------------------
	std::shared_ptr<void> CheckBox::GetUserData() const {
		return userData_;
	}

	//----------------------------------------------------------------
	void CheckBox::SetUserData(std::shared_ptr<void> data) {
		userData_ = data;
	}

	//----------------------------------------------------------------
	uint CheckBox::GetID() const {
		return id_;
	}

	//----------------------------------------------------------------
	void CheckBox::SetID(uint id)  {
		id_ = id;
	}

	//----------------------------------------------------------------
	void CheckBox::GetSize(Rect2i& rect) const {
		Assert(hwnd_ != NULL);
		RECT r;
		::GetWindowRect(hwnd_, &r);

		//
		rect.x = r.left;
		rect.y = r.top;
		rect.width  = r.right  - r.left;
		rect.height = r.bottom - r.top;
	}

	//----------------------------------------------------------------
	void CheckBox::SetSize(const Rect2i& rect) {
		Assert(hwnd_ != NULL);
		::SetWindowPos(hwnd_, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void CheckBox::GetPosition(Point2i& p) const {
		Assert(hwnd_ != NULL);
		RECT _r;
		::GetWindowRect(hwnd_, &_r);

		p.x = _r.left;
		p.y = _r.top;
	}

	//----------------------------------------------------------------
	void CheckBox::SetPosition(const Point2i& p) {
		Assert(hwnd_ != NULL);
		Rect2i r;
		GetSize(r);

		::SetWindowPos(hwnd_, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	std::wstring CheckBox::GetLabel() const {
		return label_;
	}

	//----------------------------------------------------------------
	void CheckBox::SetLabel(const std::wstring& label) {
		Assert(hwnd_ != NULL);
		label_ = label;
		SetWindowText(hwnd_, label_.c_str());
	}

	//----------------------------------------------------------------
	bool CheckBox::IsChecked() const {
		Assert(hwnd_ != NULL);
		LRESULT result = ::SendMessage(hwnd_, BM_GETCHECK, 0, 0);
		return result == BST_CHECKED;
	}
}