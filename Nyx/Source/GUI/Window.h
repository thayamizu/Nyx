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
#ifndef NYX_CORE_INCLUDED_WINDOW_H_
#define NYX_CORE_INCLUDED_WINDOW_H_
#include "GUI/Dispatcher.h"
#include "GUI/IWindow.h"

namespace Nyx {

	///�E�C���h�E
	class Window : public IWindow
	{
		typedef std::unordered_map<uint, std::shared_ptr<IControl>> HookList;
		typedef std::unordered_map<uint, std::shared_ptr<IControl>>::iterator HookListIterator;
	public:
		//---------------------------------------------------------------------------------------
		//�����E�j��
		//---------------------------------------------------------------------------------------
		/**
		*
		*/
		Window(HWND hWnd, const std::wstring caption, std::wstring icon,  int x=0,int y=0, int width=800, int height=600,int id=0);
		/**
		*
		*/
		~Window();

		/**
		*
		*/
		bool OnCreate(HWND hwnd, int x=0, int y=0, int width=800, int height=600);

		//--------------------------------------------------------------------------------------
		//�n���h���̎擾
		//---------------------------------------------------------------------------------------
		/**
		* �E�C���h�E�n���h���̎擾
		* @return HWND
		*/
		HWND GetHandle();

		//---------------------------------------------------------------------------------------
		//�`��E�X�V
		//---------------------------------------------------------------------------------------
		/**
		* �E�C���h�E��\������
		*/
		void Show();
		/**
		* �E�C���h�E���B��
		*/
		void Hide();
		/**
		* �E�C���h�E���X�V����
		*/
		void Update();
		/**
		* �E�C���h�E���\������Ă��邩
		* @return true�Ȃ�E�C���h�E�͕\������Ă���
		*/
		bool IsShow();

		void ShowCursor(bool isShowCursor);

		//---------------------------------------------------------------------------------------
		//�R���g���[���̗L�����Ɩ�����
		//---------------------------------------------------------------------------------------
		/**
		* �R���g���[����L��������
		*/
		void Activate();

		/**
		* �R���g���[���𖳌�������
		*/
		void Unactivate();

		/**
		* �R���g���[�����L�����ǂ���
		* @return bool true�Ȃ�R���g���[���͗L��
		*/
		bool IsActivate() const;


		//---------------------------------------------------------------------------------------
		//�l�̎擾�E�ݒ�
		//---------------------------------------------------------------------------------------
		/**
		* �R���g���[���̃^�C�v���擾����
		* @return ControlType::enum_t�̒l
		*/
		ControlType GetType() const;

		/**
		* ���[�U�[�f�[�^���擾����
		* @return void*
		*/
		std::shared_ptr<void> GetUserData() const;

		/**
		* ���[�U�[�f�[�^��ݒ肷��
		* @param void* ���[�U�[�f�[�^
		*/
		void SetUserData(std::shared_ptr<void> data) ;

		/**
		* �R���g���[����ID���擾����
		* @return uint �R���g���[����ID
		*/
		uint GetID() const;

		/**
		* �R���g���[����ID��ݒ肷��
		* @return �R���g���[����ID
		*/
		void SetID(uint id)  ;

		/**
		* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y���擾����
		* @param Rect2i* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y
		*/
		void GetSize(Rect2i& rect) const;

		/**
		* �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y��ݒ肷��
		* @param Rect2i& �E�C���h�E�̃N���C�A���g�̈�̃T�C�Y
		*/
		void SetSize(const Rect2i& rect);

		/**
		* �E�C���h�E�̈ʒu���擾����
		* @param Point2i& p
		*/
		void GetPosition(Point2i& p) const;

		/**
		* �E�C���h�E�̈ʒu��ݒ肷��
		*/
		void SetPosition(const Point2i& p);
		//---------------------------------------------------------------------------------------
		//�R���g���[���̓o�^�ƍ폜
		//---------------------------------------------------------------------------------------
		/**
		* �R���g���[���̓o�^
		*/
		void Register(std::shared_ptr<IControl> control);

		/**
		*�@�R���g���[���̍폜
		*/
		void Unregister(std::shared_ptr<IControl> control);

		//---------------------------------------------------------------------------------------
		//�C�x���g�̓o�^�ƍ폜
		//---------------------------------------------------------------------------------------
		/**
		*
		*/
		void AddGUIEvent(std::shared_ptr<IControl> colntrol, GUICallback callback);

		/**
		*
		*/
		void DelGUIEvent(std::shared_ptr<IControl> colntrol);

		/**
		*
		*/
		void ClearGUIEvent();

		/**
		*
		*/
		void AddUserEvent(std::shared_ptr<IControl> control, GUICallback callback);

		/**
		*
		*/
		void DelUserEvent(std::shared_ptr<IControl> colntrol);

		/**
		*
		*/
		void ClearUserEvent();

		//----------------------------------------------------------------
		//�E�C���h�E�ŗL�̑���
		//----------------------------------------------------------------
		/**
		* ���j���[���擾����
		*/
		HMENU GetMenu();

		/**
		* ���j���[��ݒ肷��
		* 
		*/
		void SetMenu(HMENU menu);

		/**
		* ���b�Z�[�W����
		* @return bool
		*/
		bool ProcessMessage();


	private:
		/**
		* �E�C���h�E�v���\�V�[�W��
		* ���ۂ̏����́CDispatcher�ɂ܂����܂�
		* @param HWND
		* @param UINT
		* @param WPARAM
		* @param LPARAM
		* @return LRESULT
		*/
		static LRESULT __stdcall GlobalProcedure(HWND hWnd, UINT msg,WPARAM wParam, LPARAM lParam);

	private:
		///�E�C���h�E�̕\�����
		bool isShow;
		/// �n���h���C���X�^���X
		HWND hwnd_;
		///�E�C���h�EID
		uint id_;
		///�E�C���h�E�X�^�C��
		ulong style_;
		///�A�g��
		ATOM atom_;
		///�^�C�g��
		std::wstring caption_;
		///�A�C�R�����\�[�X
		std::wstring icon_;
		///���[�U�[�f�[�^
		std::shared_ptr<void> userData_;
		///�E�C���h�E�Ɍ��т���Ă���q�R���g���[���̃��X�g
		HookList childControl_;
		///�f�B�X�p�b�`���Ƀt�b�N����Ă���GUI�C�x���g�̃��X�g
		std::shared_ptr<Dispatcher> guiEventList_;
		///�f�B�X�p�b�`���Ƀt�b�N����Ă��郆�[�U�[�C�x���g�̃��X�g
		std::shared_ptr<Dispatcher> userEventList_;
	};
}

#endif