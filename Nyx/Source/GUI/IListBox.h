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
		//----------------------------------------------------------------
		//構築・破壊
		//----------------------------------------------------------------
		/**
		* デストラクタ
		*/
		virtual ~ilist_box() {} 

		//----------------------------------------------------------------
		//リストボックス固有の操作
		//----------------------------------------------------------------
		/**
		* リストボックスにアイテムを追加する
		*/
		virtual void add(const std::wstring& item) = 0;

		/**
		* リストボックスのアイテムを削除する
		*/
		virtual void remove() = 0;

		/**
		* リストボックスのアイテムをクリアする
		*/
		virtual void clear() = 0;

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