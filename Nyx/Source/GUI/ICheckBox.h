#ifndef NYX_CORE_INCLUDED_ICHECKBOX_H_
#define NYX_CORE_INCLUDED_ICHECKBOX_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"

namespace nyx
{
	///チェックボックスインタフェース
	class icheckbox : public iwidget{
	public:
		//----------------------------------------------------------------
		//構築・破壊
		//----------------------------------------------------------------
		/**
		* デストラクタ
		*/
		virtual ~icheckbox() {}

		//----------------------------------------------------------------
		// チェックボックス固有の操作
		//----------------------------------------------------------------
		/**
		* ラベルの取得
		* @return std::wstring& ラベル
		*/
		virtual std::wstring get_label() const = 0;

		/**
		* ラベルの設定
		* @param const std::wstring& ラベル
		*/
		virtual void set_label(const std::wstring& label) = 0;

		/**
		* ボタンがチェック状態かどうか
		* @return bool trueならチェックされている
		*/
		virtual bool is_checked() const = 0;
	};
}
#endif