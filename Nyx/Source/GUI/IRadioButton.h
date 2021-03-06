#ifndef NYX_CORE_INCLUDED_IRADIO_BUTTON_H_
#define NYX_CORE_INCLUDED_IRADIO_BUTTON_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"
namespace nyx
{
	///ラジオボタンインタフェース
	class iradio_button : public iwidget
	{
	public:
		virtual ~iradio_button() {}

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