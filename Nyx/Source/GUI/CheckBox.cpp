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
#include "Primitive/Rect2i.h"
#include "Primitive/Point2i.h"

namespace Nyx {
	//---------------------------------------------------------------------------------------
	CheckBox::CheckBox(HWND _hwnd, std::wstring _label, int _x, int _y, int _width, int _height, int _id) 
		:hwnd(NULL), label(_label), id(_id), atom(NULL), isShow(false), userData(NULL)
	{
		OnCreate(_hwnd, _label, _x, _y, _width, _height, _id);
	}

	//---------------------------------------------------------------------------------------
	bool CheckBox::OnCreate(HWND _hwnd, std::wstring _label, int _x, int _y, int _width, int _height, int _id) {

		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd = CreateWindow(
			TEXT("BUTTON"),
			_label.c_str(), //�^�C�g���o�[�ɂ��̖��O���\������܂�
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, //�E�B���h�E�̎��
			_x,	//�w���W
			_y,	//�x���W
			_width,	//��
			_height,	//����
			_hwnd, //�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
			(HMENU)_id, //���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
			hInstance, //�C���X�^���X�n���h��
			NULL);

		Assert(hwnd != NULL);
		if (!hwnd) {
			::MessageBox(NULL, TEXT("���s���܂���"), TEXT("error"), MB_OK);
			return false;
		}
		Show();
		return true;
	}
	//---------------------------------------------------------------------------------------
	CheckBox::~CheckBox() {
		if (atom) ::UnregisterClass((LPCTSTR)atom, ::GetModuleHandle(NULL));
	}

	//---------------------------------------------------------------------------------------
	HWND CheckBox::GetHandle() {
		Assert(hwnd != NULL);
		return hwnd;
	}

	//----------------------------------------------------------------
	void CheckBox::Show(){
		Assert(hwnd!=NULL);
		isShow = true;
		::ShowWindow(hwnd, SW_SHOW);
	}

	//----------------------------------------------------------------
	void CheckBox::Hide(){
		Assert(hwnd != NULL);
		isShow=false;
		::ShowWindow(hwnd, SW_HIDE);
	}

	//----------------------------------------------------------------
	void CheckBox::Update() {
		Assert(hwnd != NULL);
		::UpdateWindow(hwnd);
	}

	//----------------------------------------------------------------
	bool CheckBox::IsShow() {
		return isShow;
	}

	//----------------------------------------------------------------
	void CheckBox::Activate() {
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, true);
	}

	//----------------------------------------------------------------
	void CheckBox::Unactivate() {
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, false);
	}

	//----------------------------------------------------------------
	bool CheckBox::IsActivate() const {
		Assert(hwnd != NULL);
		return static_cast<bool>(::IsWindowEnabled(hwnd));
	}

	//----------------------------------------------------------------
	ControlType::enum_t CheckBox::GetType() const{
		return ControlType::CheckBox;
	}

	//----------------------------------------------------------------
	void* CheckBox::GetUserData() const {
		return userData;
	}

	//----------------------------------------------------------------
	void CheckBox::SetUserData(void * data) {
		userData = data;
	}

	//----------------------------------------------------------------
	uint CheckBox::GetID() const {
		return id;
	}

	//----------------------------------------------------------------
	void CheckBox::SetID(uint _id)  {
		id = _id;
	}

	//----------------------------------------------------------------
	void CheckBox::GetSize(Rect2i* rect) const {
		Assert(hwnd != NULL);
		RECT r;
		::GetWindowRect(hwnd, &r);

		//
		rect->x = r.left;
		rect->y = r.top;
		rect->width  = r.right  - r.left;
		rect->height = r.bottom - r.top;
	}

	//----------------------------------------------------------------
	void CheckBox::SetSize(const Rect2i& rect) {
		Assert(hwnd != NULL);
		::SetWindowPos(hwnd, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void CheckBox::GetPosition(Point2i* p) const {
		Assert(hwnd != NULL);
		RECT _r;
		::GetWindowRect(hwnd, &_r);

		p->x = _r.left;
		p->y = _r.top;
	}

	//----------------------------------------------------------------
	void CheckBox::SetPosition(const Point2i& p) {
		Assert(hwnd != NULL);
		Rect2i r;
		GetSize(&r);

		::SetWindowPos(hwnd, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	std::wstring CheckBox::GetLabel() const {
		return label;
	}

	//----------------------------------------------------------------
	void CheckBox::SetLabel(const std::wstring& _label) {
		Assert(hwnd != NULL);
		label = _label;
		SetWindowText(hwnd, label.c_str());
	}

	//----------------------------------------------------------------
	bool CheckBox::IsChecked() const {
		Assert(hwnd != NULL);
		LRESULT result = ::SendMessage(hwnd, BM_GETCHECK, 0, 0);
		return result == BST_CHECKED;
	}
}