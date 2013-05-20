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
#include "Primitive/Rect2i.h"
#include "Primitive/Point2i.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	RadioButton::RadioButton(HWND _hwnd, std::wstring _label, int _x, int _y, int _width, int _height, int _id)
		:label(_label), hwnd(NULL), id(_id), atom(NULL), isShow(false), userData(NULL) {

			OnCreate(_hwnd, _label, _x, _y, _width, _height, _id);
	}       

	//-----------------------------------------------------------------------------------------
	RadioButton::~RadioButton() {
		if (atom) ::UnregisterClass((LPCTSTR)atom, ::GetModuleHandle(NULL));
	}

	//-----------------------------------------------------------------------------------------
	bool RadioButton::OnCreate(HWND _hwnd, std::wstring _label, int _x, int _y, int _width, int _height, int _id) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd = CreateWindow(
			TEXT("BUTTON"),
			_label.c_str(), //�^�C�g���o�[�ɂ��̖��O���\������܂�
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, //�E�B���h�E�̎��
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

		//�R���g���[���̕\��
		Show();
		return true;
	}

	//---------------------------------------------------------------------------------------
	HWND RadioButton::GetHandle() {
		Assert(hwnd != NULL);
		return hwnd;
	}

	//----------------------------------------------------------------
	void RadioButton::Show() {
		Assert(hwnd != NULL);
		isShow = true;
		::ShowWindow(hwnd, SW_SHOW);  
	}

	//----------------------------------------------------------------
	void RadioButton::Hide(){
		Assert(hwnd != NULL);
		isShow = false;
		::ShowWindow(hwnd, SW_HIDE);  
	}

	//----------------------------------------------------------------
	void RadioButton::Update() {
		Assert(hwnd != NULL);
		::UpdateWindow(hwnd);

	}

	//----------------------------------------------------------------
	bool RadioButton::IsShow() {
		return isShow;
	}

	//----------------------------------------------------------------
	void RadioButton::Activate() {
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, true);
	}

	//----------------------------------------------------------------
	void RadioButton::Unactivate() {
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, false);
	}

	//----------------------------------------------------------------
	bool RadioButton::IsActivate() const {
		Assert(hwnd != NULL);
		return static_cast<bool>(::IsWindowEnabled(hwnd));
	}

	//----------------------------------------------------------------
	ControlType::enum_t RadioButton::GetType() const{
		return ControlType::RadioButton;
	}

	//----------------------------------------------------------------
	void* RadioButton::GetUserData() const {
		return userData;
	}

	//----------------------------------------------------------------
	void RadioButton::SetUserData(void * data) {
		userData = data;
	}

	//----------------------------------------------------------------
	uint RadioButton::GetID() const {
		return id;
	}

	//----------------------------------------------------------------
	void RadioButton::SetID(uint _id)  {
		id = _id;
	}

	//----------------------------------------------------------------
	void RadioButton::GetSize(Rect2i* rect) const {
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
	void RadioButton::SetSize(const Rect2i& rect) {
		Assert(hwnd != NULL);
		::SetWindowPos(hwnd, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	void RadioButton::GetPosition(Point2i* p) const {
		Assert(hwnd != NULL);
		RECT _r;
		::GetWindowRect(hwnd, &_r);

		p->x = _r.left;
		p->y = _r.top;
	}

	//----------------------------------------------------------------
	void RadioButton::SetPosition(const Point2i& p) {
		Assert(hwnd != NULL);
		Rect2i r;
		GetSize(&r);

		::SetWindowPos(hwnd, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//----------------------------------------------------------------
	std::wstring RadioButton::GetLabel() const  {
		return label;
	}

	//----------------------------------------------------------------
	void RadioButton::SetLabel(const std::wstring& _label) {
		label = _label;
		SetWindowText(hwnd, label.c_str());
	}

	//----------------------------------------------------------------
	bool RadioButton::IsChecked() const {
		LRESULT result = ::SendMessage(hwnd, BST_CHECKED, 0, 0);
		return result == BST_CHECKED;
	}
}