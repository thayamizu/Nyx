#ifndef NYX_CORE_INCLUDED_IPUSH_BUTTON_H_
#define NYX_CORE_INCLUDED_IPUSH_BUTTON_H_

#include "GUI/IControl.h"
#include "Utility/Type.h"
namespace nyx {
	
	///プッシュボタンインタフェース
	class ipush_button : public iwidget
	{
	public:
		//----------------------------------------------------------------
		//構築・破壊
		//----------------------------------------------------------------
		/**
		* デストラクタ
		*/
		virtual ~ipush_button() {}

		//----------------------------------------------------------------
		// プッシュボタン固有の操作
		//-----------------------------------------------------------------
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


		virtual void on_click(const gui_callback& callback) = 0;
	};
}
#endif