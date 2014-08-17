#ifndef NYX_CORE_INCLUDED_ILISTBOX_H_
#define NYX_CORE_INCLUDED_ILISTBOX_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"

namespace nyx 
{

	///リストボックスインタフェース
	class ilist_box : public iwidget
	{
	public:
		/**
		* デストラクタ
		*/
		virtual ~ilist_box() {} 

		/**
		* リストボックスにアイテムを追加する
		*/
		virtual void add_item(const std::wstring& item) = 0;

		/**
		* リストボックスのアイテムを削除する
		*/
		virtual void remove_item() = 0;

		/**
		* リストボックスのアイテムをクリアする
		*/
		virtual void clear_item() = 0;

		/**
		* 現在選択されているアイテムのインデックスを取得する
		*/
		virtual uint32_t get_select_index() = 0 ;

		/**
		* 現在選択されているアイテム名を取得する
		* @return std::wstring
		*/
		virtual std::wstring get_select_item() = 0;
	};
}

#endif