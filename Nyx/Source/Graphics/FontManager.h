#ifndef NYX_CORE_INCLUDED_FONT_MANAGER_H_
#define NYX_CORE_INCLUDED_FONT_MANAGER_H_
#include "FontInfo.h"
#include "TextureFont.h"
#include "TextureText.h"

namespace nyx {

	class font_factory {
	public:

		/**
		* テクスチャによる文字を生成します
		* @param wchar_t 文字
		* @param const FontInfo& フォント情報
		* @return std::shared_ptr<TextureFont>
		*/
		static std::shared_ptr<texture_font> make_texture_char(wchar_t chara, const font_info& fontInfo);
		

		/**
		* テクスチャによる文字を生成します
		* @param wchar_t 文字
		* @param const FontInfo& フォント情報
		* @return std::shared_ptr<TextureFont>
		*/
		static std::shared_ptr<texture_text> make_texture_text(const std::wstring& text,  const font_info& fontInfo);


		/**
		* キャッシュから指定したリソースを削除します
		* @param const std::wstring& ファイル名
		*/
		static void remove(const std::wstring& key);


		/**
		*
		*/
		static std::shared_ptr<texture_font> get_item(wchar_t chara);
	private:
		/**
		* コンストラクタ
		*/
		font_factory() {}
		std::wstring txtFileName_;
	};
}
#endif