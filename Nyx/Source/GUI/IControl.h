#ifndef NYX_CORE_INCLUDED_ICONTROL_H_
#define NYX_CORE_INCLUDED_ICONTROL_H_
#include "Utility/Type.h"
#include "Primitive/Vector2.h"
#include "Primitive/Rect.h"
#include <Windows.h>

namespace nyx 
{
	class iwidget;
	///GUIコントロールの種別
	enum WIDGET_TYPE {
		WIDGET_TYPE_WINDOW,
		WIDGET_TYPE_CHECK_BOX,
		WIDGET_TYPE_COMBO_BOX,
		WIDGET_TYPE_LIST_BOX,
		WIDGET_TYPE_BUTTON,
		WIDGET_TYPE_RADIO_BUTTON,
		WIDGET_TYPE_NUM,
	};

	enum WIDGET_EVENT_TYPE {
		WIDGET_EVENT_TYPE_CLICK,
		WIDGET_EVENT_TYPE_CHECKED_CHANGED,
		WIDGET_EVENT_TYPE_INDEX_CHANGED,
		WIDGET_EVENT_TYPE_MOUSE_DOWN,
		WIDGET_EVENT_TYPE_MOUSE_UP,
		WIDGET_EVENT_TYPE_PAINT,
		WIDGET_EVENT_TYPE_NUM
	};

	///イベント引数
	struct event_args {
		/**
		 *デフォルトコンストラクタ
		 */
		event_args():
			message(0), wparam(NULL), lparam(NULL){
		}

		
		/**
		 *コンストラクタ
		 * @param uint
		 * @param WPARAM
		 * @param LPARAM
		 */
		event_args(uint32_t msg, WPARAM wParam, LPARAM lParam) 
			:message(msg), wparam(wParam), lparam(lParam) {
		}

		//メッセージ
		uint32_t message;

		//WPARAM
		WPARAM wparam;

		//LPARAM
		LPARAM lparam;

	};
	typedef HWND  window_handle;
	typedef HMENU menu_handle;
	typedef std::function < void(iwidget&, event_args& e)> gui_callback;
	
	///コントロールインタフェース
	class iwidget {
	public:
		virtual ~iwidget() {}
		//--------------------------------------------------------------------------------------
		//ハンドルの取得
		//---------------------------------------------------------------------------------------
		/**
		* ウインドウハンドルの取得
		* @return HWND
		*/
		virtual window_handle get_handle() = 0;

		//---------------------------------------------------------------------------------------
		//描画・更新
		//---------------------------------------------------------------------------------------
		/**
		* ウインドウを表示する
		*/
		virtual void show() = 0;


		/**
		* ウインドウを隠す
		*/
		virtual void hide() = 0;
		
		
		/**
		* ウインドウを更新する
		*/
		virtual void update() = 0;

		/**
		* ウインドウが表示されているか
		* @return trueならウインドウは表示されている
		*/
		virtual bool is_show() = 0;

		//---------------------------------------------------------------------------------------
		//コントロールの有効化と無効化
		//---------------------------------------------------------------------------------------
		/**
		* コントロールを有効化する
		*/
		virtual void activate() = 0;

		/**
		* コントロールを無効化する
		*/
		virtual void unactivate() = 0;

		/**
		* コントロールが有効かどうか
		* @return bool trueならコントロールは有効
		*/
		virtual bool is_activate() const = 0;

		//---------------------------------------------------------------------------------------
		//値の取得・設定
		//---------------------------------------------------------------------------------------
		/**
		* コントロールのタイプを取得する
		* @return ControlType::enum_tの値
		*/
		virtual WIDGET_TYPE get_type() const = 0;
		

		/**
		* ユーザーデータを取得する
		* @return void*
		*/
		virtual std::shared_ptr<void> get_user_data() const = 0;


		/**
		* ユーザーデータを設定する
		* @param void* ユーザーデータ
		*/
		virtual void set_user_data(const std::shared_ptr<void>& data) = 0;
		

		/**
		* コントロールのIDを取得する
		* @return uint コントロールのID
		*/
		virtual uint32_t get_id() const = 0;

		
		/**
		* コントロールのIDを設定する
		* @return コントロールのID
		*/
		virtual void set_id(uint32_t id) = 0;


		/**
		* ウインドウのクライアント領域のサイズを取得する
		* @param Rect2i* ウインドウのクライアント領域のサイズ
		*/
		virtual void get_size(rect2i& rect) const = 0;


		/**
		* ウインドウのクライアント領域のサイズを設定する
		* @param Rect2i& ウインドウのクライアント領域のサイズ
		*/
		virtual void set_size(const rect2i& rect) = 0;


		/**
		* ウインドウの位置を取得する
		* @param Point2i& p
		*/
		virtual void get_position(point2i& p) const = 0;


		/**
		* ウインドウの位置を設定する
		*/
		virtual void set_position(const point2i& p) = 0;

		virtual void dispatch(WIDGET_EVENT_TYPE eventType, event_args& e) = 0;
	};
};
#endif