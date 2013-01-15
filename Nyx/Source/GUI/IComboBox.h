#ifndef NYX_CORE_INCLUDED_ICOMBOBOX_H_
#define NYX_CORE_INCLUDED_ICOMBOBOX_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"

namespace Nyx {

	///コンボボックスインタフェース
	class IComboBox : public IControl 
	{
	public:
		//----------------------------------------------------------------
		//構築・破壊
		//----------------------------------------------------------------
		/**
		* デストラクタ
		*/
		virtual ~IComboBox() {} 

		//----------------------------------------------------------------
		//値の追加/削除
		//----------------------------------------------------------------
		/**
		* リストボックスにアイテムを追加する
		* param const tstring& アイテム
		*/
		virtual void AddItem(const tstring& item) = 0;

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
		* @return uint インデックス
		*/
		virtual uint GetSelectedIndex() = 0 ;

		/**
		* 現在選択されているアイテム名を取得する
		* @return tstring アイテム名
		*/
		virtual tstring GetSelectedItem() = 0;
	};
}
#endif