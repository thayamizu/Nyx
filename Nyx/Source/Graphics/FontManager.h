#ifndef NYX_CORE_INCLUDED_FONT_MANAGER_H_
#define NYX_CORE_INCLUDED_FONT_MANAGER_H_
#include "FontInfo.h"
#include "TextureFont.h"
#include "TextureText.h"

namespace Nyx {

	class FontManager {
	public:

		/**
		* テクスチャによる文字を生成します
		* @param wchar_t 文字
		* @param const FontInfo& フォント情報
		* @return std::shared_ptr<TextureFont>
		*/
		static std::shared_ptr<TextureFont> CreateChar(wchar_t chara, const FontInfo& fontInfo);
		

		/**
		* テクスチャによる文字を生成します
		* @param wchar_t 文字
		* @param const FontInfo& フォント情報
		* @return std::shared_ptr<TextureFont>
		*/
		static std::shared_ptr<TextureText> CreateText(const std::wstring& text,  const FontInfo& fontInfo);


		/**
		* キャッシュから指定したリソースを削除します
		* @param const std::wstring& ファイル名
		*/
		static void Delete(const std::wstring& key);


		/**
		*
		*/
		static std::shared_ptr<TextureFont> GetItem(wchar_t chara);
	private:
		/**
		* コンストラクタ
		*/
		FontManager() {}
		std::wstring txtFileName_;
	};
}
#endif