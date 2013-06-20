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
	PushButton::PushButton(HWND _hwnd, const std::wstring& _label, int x, int y, int width, int height, int _id)
		:label(_label), hwnd(NULL), id(_id), atom(NULL), isShow(false), isActivate(true)
	{

			OnCreate(_hwnd, _label, x, y, width, height);
	}       

	//------------------------------------------------------------------------------
	PushButton::~PushButton() 
	{
		if (atom) { 
			::UnregisterClass((LPCTSTR)atom, ::GetModuleHandle(NULL));
		}
	}

	//------------------------------------------------------------------------------
	bool PushButton::OnCreate(HWND _hwnd, const std::wstring& _label, int x, int y, int width, int height) {
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		hwnd = CreateWindow(
			TEXT("BUTTON"),
			_label.c_str(), //�^�C�g���o�[�ɂ��̖��O���\������܂�
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //�E�B���h�E�̎��
			x,	//�w���W
			y,	//�x���W
			width,	//��
			height,	//����
			_hwnd, //�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
			(HMENU)id, //���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
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
	void PushButton::Show() 
	{
		Assert(hwnd != NULL);
		isShow = true;
		::ShowWindow(hwnd, SW_SHOW);   
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Hide() 
	{
		Assert(hwnd != NULL);
		isShow = false;
		::ShowWindow(hwnd, SW_HIDE);   
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Update() 
	{
		Assert(hwnd != NULL);
		::UpdateWindow(hwnd);
	}
	
	//---------------------------------------------------------------------------------------
	bool PushButton::IsShow() 
	{
		return isShow;
	}
	
	//---------------------------------------------------------------------------------------
	void PushButton::Activate() 
	{
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, true);
	}

	//---------------------------------------------------------------------------------------
	void PushButton::Unactivate() 
	{
		Assert(hwnd != NULL);
		::EnableWindow(hwnd, false);
	}

	//---------------------------------------------------------------------------------------
	bool PushButton::IsActivate() 
		const 
	{
		Assert(hwnd != NULL);
		return IsWindowEnabled(hwnd) != 0;
	}

	//---------------------------------------------------------------------------------------
	HWND  PushButton::GetHandle() 
	{
		Assert(hwnd != NULL);
		return hwnd;
	}

	//---------------------------------------------------------------------------------------
	ControlType::enum_t PushButton::GetType() 
		const 
	{
		return ControlType::PushButton;
	}

	//---------------------------------------------------------------------------------------
	void* PushButton::GetUserData() 
		const 
	{
		return userData;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetUserData(void * data) 
	{
		userData = data;
	}

	//---------------------------------------------------------------------------------------
	uint PushButton::GetID() 
		const 
	{
		return id;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetID(uint _id)  
	{
		id = _id;
	}
	//---------------------------------------------------------------------------------------
	void PushButton::GetSize(Rect2i* rect)
		const 
	{
		Assert(hwnd != NULL);
		RECT r;
		::GetWindowRect(hwnd, &r);

		//
		rect->x = r.left;
		rect->y = r.top;
		rect->width  = r.right  - r.left;
		rect->height = r.bottom - r.top;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetSize(const Rect2i& rect) 
	{
			Assert(hwnd != NULL);
		::SetWindowPos(hwnd, NULL, rect.x, rect.y, rect.width, rect.height, SWP_SHOWWINDOW);
	}

	//---------------------------------------------------------------------------------------
	void PushButton::GetPosition(Point2i* p) 
		const 
	{
			Assert(hwnd != NULL);
		RECT _r;
		::GetWindowRect(hwnd, &_r);

		p->x = _r.left;
		p->y = _r.top;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetPosition(const Point2i& p) 
	{
		Assert(hwnd != NULL);
		Rect2i r;
		GetSize(&r);

		::SetWindowPos(hwnd, NULL, p.x, p.y, r.width, r.height, SWP_SHOWWINDOW);
	}

	//---------------------------------------------------------------------------------------
	std::wstring PushButton::GetLabel() 
		const
	{
		return label;
	}

	//---------------------------------------------------------------------------------------
	void PushButton::SetLabel(const std::wstring& _label)
	{
		label = _label;
		SetWindowText(hwnd, label.c_str());
	}
}