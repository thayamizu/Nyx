#ifndef NYX_CORE_INCLUDED_ILISTBOX_H_
#define NYX_CORE_INCLUDED_ILISTBOX_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"

namespace Nyx 
{

	///リストボックスインタフェース
	class IListBox : public IControl
	{
	public:
		//----------------------------------------------------------------
		//構築・破壊
		//----------------------------------------------------------------
		/**
		* デストラクタ
		*/
		virtual ~IListBox() {} 

		//----------------------------------------------------------------
		//リストボックス固有の操作
		//----------------------------------------------------------------
		/**
		* リストボックスにアイテムを追加する
		*/
		virtual void AddItem(const std::wstring& item) = 0;

		/**
		* リストボックスのアイテムを削除する
		*/
		virtual void DeleteItem() = 0;

		/**
		* リストボックスのアイテムをクリアする
		*/
		virtual void ClearItem() = 0;

		/**
		* 現在選択されているアイテムのインデックスを取得する
		*/
		virtual uint GetSelectedIndex() = 0 ;

		/**
		* 現在選択されているアイテム名を取得する
		* @return std::wstring
		*/
		virtual std::wstring GetSelectedItem() = 0;
	};
}

#endif