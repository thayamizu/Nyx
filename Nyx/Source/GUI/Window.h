/********************************************************************************
*
*  The MIT License
*
* Copyright (c) 2010-2011 t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_WINDOW_H_
#define NYX_CORE_INCLUDED_WINDOW_H_
#include "GUI/Dispatcher.h"
#include "GUI/IWindow.h"

namespace nyx {

	///ウインドウ
	class window : public iwindow
	{
		typedef std::unordered_map<uint32_t, iwidget&> hook_list;
		typedef std::unordered_map<uint32_t, iwidget&>::iterator hook_list_iterator;
	public:
		//---------------------------------------------------------------------------------------
		//生成・破壊
		//---------------------------------------------------------------------------------------
		/**
		*
		*/
		window(window_handle handle, const std::wstring& caption, const std::wstring& icon,  int x=0,int y=0, int width=800, int height=600);
		/**
		*
		*/
		~window();

		/**
		*
		*/
		bool create(window_handle hwnd, int x = 0, int y = 0, int width = 800, int height = 600);

		//--------------------------------------------------------------------------------------
		//ハンドルの取得
		//---------------------------------------------------------------------------------------
		/**
		* ウインドウハンドルの取得
		* @return HWND
		*/
		window_handle get_handle();

		//---------------------------------------------------------------------------------------
		//描画・更新
		//---------------------------------------------------------------------------------------
		/**
		* ウインドウを表示する
		*/
		void show();
		/**
		* ウインドウを隠す
		*/
		void hide();
		/**
		* ウインドウを更新する
		*/
		void update();
		/**
		* ウインドウが表示されているか
		* @return trueならウインドウは表示されている
		*/
		bool is_show();

		void show_cursor(bool isShowCursor);

		//---------------------------------------------------------------------------------------
		//コントロールの有効化と無効化
		//---------------------------------------------------------------------------------------
		/**
		* コントロールを有効化する
		*/
		void activate();

		/**
		* コントロールを無効化する
		*/
		void unactivate();

		/**
		* コントロールが有効かどうか
		* @return bool trueならコントロールは有効
		*/
		bool is_activate() const;


		//---------------------------------------------------------------------------------------
		//値の取得・設定
		//---------------------------------------------------------------------------------------
		/**
		* コントロールのタイプを取得する
		* @return ControlType::enum_tの値
		*/
		WIDGET_TYPE get_type() const;

		/**
		* ユーザーデータを取得する
		* @return void*
		*/
		std::shared_ptr<void> get_user_data() const;

		/**
		* ユーザーデータを設定する
		* @param void* ユーザーデータ
		*/
		void set_user_data(const std::shared_ptr<void>& data) ;

		/**
		* コントロールのIDを取得する
		* @return uint コントロールのID
		*/
		uint32_t get_id() const;

		/**
		* コントロールのIDを設定する
		* @return コントロールのID
		*/
		void set_id(uint32_t id)  ;

		/**
		* ウインドウのクライアント領域のサイズを取得する
		* @param Rect2i* ウインドウのクライアント領域のサイズ
		*/
		void get_size(rect2i& rect) const;

		/**
		* ウインドウのクライアント領域のサイズを設定する
		* @param Rect2i& ウインドウのクライアント領域のサイズ
		*/
		void set_size(const rect2i& rect);

		/**
		* ウインドウの位置を取得する
		* @param Point2i& p
		*/
		void get_position(point2i& p) const;

		/**
		* ウインドウの位置を設定する
		*/
		void set_position(const point2i& p);
		//---------------------------------------------------------------------------------------
		//コントロールの登録と削除
		//---------------------------------------------------------------------------------------
		/**
		* コントロールの登録
		*/
		void register_widget(iwidget& control);

		/**
		*　コントロールの削除
		*/
		void unregister_widget(iwidget& control);

	
		/**
		* メニューを取得する
		*/
		menu_handle get_menu();

		/**
		* メニューを設定する
		* 
		*/
		void set_menu(menu_handle menu);

		/**
		* メッセージ処理
		* @return bool
		*/
		bool process_message();

		void on_mouse_down(const gui_callback& callback);

		void on_mouse_up(const gui_callback& callback);

		void on_paint(const gui_callback& callback);

		void dispatch(WIDGET_EVENT_TYPE evenType, event_args& e);
	private:
		/**
		* ウインドウプロ―シージャ
		* 実際の処理は，Dispatcherにまかせます
		* @param HWND
		* @param UINT
		* @param WPARAM
		* @param LPARAM
		* @return LRESULT
		*/
		static LRESULT __stdcall global_procedure(HWND hWnd, UINT msg,WPARAM wParam, LPARAM lParam);

	private:
		///ウインドウの表示状態
		bool isShow;
		/// ハンドルインスタンス
		HWND hwnd_;
		///ウインドウID
		uint32_t id_;
		///ウインドウスタイル
		uint64_t style_;
		///アトム
		ATOM atom_;
		///タイトル
		std::wstring caption_;
		///アイコンリソース
		std::wstring icon_;
		///ユーザーデータ
		std::shared_ptr<void> userData_;
		///ウインドウに結びつけらている子コントロールのリスト
		hook_list childControl_;
		///ディスパッチャにフックされているGUIイベントのリスト
		std::shared_ptr<dispatcher> guiEventList_;
	};
}

#endif