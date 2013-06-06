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
#include "GUI/ListBox.h"
#include "Debug/Assert.h"
#include "Primitive/Rect2i.h"
#include "Primitive/Point2i.h"

namespace Nyx {
	//---------------------------------------------------------------------------------------
	//�����E�j��
	//---------------------------------------------------------------------------------------
	ListBox::ListBox(HWND _hwnd, std::wstring _label, int _x, int _y, int _width, int _height, int _id)
		:label(_label), id(_id){

			OnCreate(_hwnd, label, _x, _y, _width, _height, _id);
	}       
	ListBox::~ListBox() {
		if (atom) ::UnregisterClass((LPCTSTR)atom, ::GetModuleHandle(NULL));
	}

	bool ListBox::OnCreate(HWND _hwnd, std::wstring _label, int _x, int _y, int _width, int _height, int _id) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd = CreateWindow(
			TEXT("LISTBOX"),
			_label.c_str(), //�^�C�g���o�[�ɂ��̖��O���\������܂�
			WS_CHILD | WS_VISIBLE | LBS_STANDARD & ~LBS_SORT, //�E�B���h�E�̎��
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
	HWND ListBox::GetHandle() {
		Assert(hwnd != NULL);
		return hwnd;
	}

	//----------------------------------------------------------------
	void ListBox::Show(){
		Assert(hwnd != NULL);
		isShow = true;
		::ShowWindow(hwnd, SW_SHOW);  
	}

	//----------------------------------------------------------------
	void ListBox::Hide(){
		Assert(hwnd != NULL);
		isShow = false;
		::ShowWindow(hwnd, SW_HIDE); 
	}

	//----------------------------------------------------------------
	void ListBox::Update() {
		Assert(hwnd != NULL);
		::UpdateWindow(hwnd);
	}

	//----------------------------------------------------------------
	bool ListBox::IsShow() {
		return isShow;
	}

	//----------------------------------------------------------------
	void ListBox::Activate() {
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, true);
	}

	//----------------------------------------------------------------
	void ListBox::Unactivate() {
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, false);
	}
	//----------------------------------------------------------------
	bool ListBox::IsActivate() const {
		Assert(hwnd != NULL);
		return IsWindowEnabled(hwnd) != 0;
	}

	//----------------------------------------------------------------
	ControlType::enum_t ListBox::GetType() const{
		return ControlType::ListBox;
	}

	//----------------------------------------------------------------
	void* ListBox::GetUserData() const {
		return userData;
	}

	//----------------------------------------------------------------
	void ListBox::SetUserData(void * data) {
		userData = data;
	}

	//----------------------------------------------------------------
	uint ListBox::GetID() const {
		return id;
	}

	//----------------------------------------------------------------
	void ListBox::SetID(uint _id)  {
		id = _id;
	}

	//----------------------------------------------------------------
	void ListBox::GetSize(Rect2i* rect) const {
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
	void ListBox::SetSize(const Rect2i& rect) {
		Assert(hwnd != NULL);
		::SetWindowPos(hwnd, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}
	//----------------------------------------------------------------
	void ListBox::GetPosition(Point2i* p) const {
			Assert(hwnd != NULL);
		RECT _r;
		::GetWindowRect(hwnd, &_r);

		p->x = _r.left;
		p->y = _r.top;
	}

	void ListBox::SetPosition(const Point2i& p) {
			Assert(hwnd != NULL);
		Rect2i r;
		GetSize(&r);

		::SetWindowPos(hwnd, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);

	}
	//----------------------------------------------------------------
	void ListBox::AddItem(const std::wstring& item) {
		SendMessage(hwnd, LB_ADDSTRING, 0, (LPARAM)item.c_str());
	}

	//----------------------------------------------------------------
	void ListBox::DeleteItem() {
		int index = SendMessage(hwnd, LB_GETCURSEL, 0, 0);
		if (index == LB_ERR) return;

		SendMessage(hwnd, LB_DELETESTRING, index, 0);
	}

	//----------------------------------------------------------------
	void ListBox::ClearItem() {
		SendMessage(hwnd, LB_RESETCONTENT, 0, 0);
	}


	//----------------------------------------------------------------
	uint ListBox::GetSelectedIndex() {
		return SendMessage(hwnd, LB_GETCURSEL, 0, 0);
	}


	//----------------------------------------------------------------
	std::wstring ListBox::GetSelectedItem() {
		uint index = GetSelectedIndex();
		
		SendMessage(hwnd, LB_GETTEXT, index, 0);
		return TEXT("");
	}
}