#ifndef NYX_CORE_INCLUDED_ICONTROL_H_
#define NYX_CORE_INCLUDED_ICONTROL_H_
#include "Object/Delegate.h"
#include "Utility/Type.h"
#include "Primitive/Vector2.h"
#include "Primitive/Rect.h"
#include <Windows.h>
namespace Nyx 
{

	///GUIコントロールの種別
	enum ControlType {
		ControlType_Window,
		ControlType_CheckBox,
		ControlType_Combobox,
		ControlType_ListBox,
		ControlType_PushButton,
		ControlType_RadioButton,
		ControlType_ControlTypeNum,
	};

	///イベント引数
	struct EventArgs {
		/**
		 *デフォルトコンストラクタ
		 */
		EventArgs():
			message(0), wparam(NULL), lparam(NULL){
		}

		
		/**
		 *コンストラクタ
		 * @param uint
		 * @param WPARAM
		 * @param LPARAM
		 */
		EventArgs(uint msg, WPARAM wParam, LPARAM lParam) 
			:message(msg), wparam(wParam), lparam(lParam) {
		}

		//メッセージ
		uint message;

		//WPARAM
		WPARAM wparam;

		//LPARAM
		LPARAM lparam;
	};


	///コントロールインタフェース
	class IControl {
	public:
		virtual ~IControl() {}
		//--------------------------------------------------------------------------------------
		//ハンドルの取得
		//---------------------------------------------------------------------------------------
		/**
		* ウインドウハンドルの取得
		* @return HWND
		*/
		virtual HWND GetHandle() = 0;

		//---------------------------------------------------------------------------------------
		//描画・更新
		//---------------------------------------------------------------------------------------
		/**
		* ウインドウを表示する
		*/
		virtual void Show() = 0;


		/**
		* ウインドウを隠す
		*/
		virtual void Hide() = 0;
		
		
		/**
		* ウインドウを更新する
		*/
		virtual void Update() = 0;

		/**
		* ウインドウが表示されているか
		* @return trueならウインドウは表示されている
		*/
		virtual bool IsShow() = 0;

		//---------------------------------------------------------------------------------------
		//コントロールの有効化と無効化
		//---------------------------------------------------------------------------------------
		/**
		* コントロールを有効化する
		*/
		virtual void Activate() = 0;

		/**
		* コントロールを無効化する
		*/
		virtual void Unactivate() = 0;

		/**
		* コントロールが有効かどうか
		* @return bool trueならコントロールは有効
		*/
		virtual bool IsActivate() const = 0;

		//---------------------------------------------------------------------------------------
		//値の取得・設定
		//---------------------------------------------------------------------------------------
		/**
		* コントロールのタイプを取得する
		* @return ControlType::enum_tの値
		*/
		virtual ControlType GetType() const = 0;
		

		/**
		* ユーザーデータを取得する
		* @return void*
		*/
		virtual std::shared_ptr<void> GetUserData() const = 0;


		/**
		* ユーザーデータを設定する
		* @param void* ユーザーデータ
		*/
		virtual void SetUserData(std::shared_ptr<void> data)  = 0;
		

		/**
		* コントロールのIDを取得する
		* @return uint コントロールのID
		*/
		virtual uint GetID() const = 0;

		
		/**
		* コントロールのIDを設定する
		* @return コントロールのID
		*/
		virtual void SetID(size_t id)   = 0;


		/**
		* ウインドウのクライアント領域のサイズを取得する
		* @param Rect2i* ウインドウのクライアント領域のサイズ
		*/
		virtual void GetSize(Rect2i& rect) const = 0;


		/**
		* ウインドウのクライアント領域のサイズを設定する
		* @param Rect2i& ウインドウのクライアント領域のサイズ
		*/
		virtual void SetSize(const Rect2i& rect) = 0;


		/**
		* ウインドウの位置を取得する
		* @param Point2i& p
		*/
		virtual void GetPosition(Point2i& p) const = 0;


		/**
		* ウインドウの位置を設定する
		*/
		virtual void SetPosition(const Point2i& p) = 0;
	};
};
#endif