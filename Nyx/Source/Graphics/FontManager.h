#ifndef NYX_CORE_INCLUDED_FONT_MANAGER_H_
#define NYX_CORE_INCLUDED_FONT_MANAGER_H_
#include "FontInfo.h"
#include "TextureFont.h"
#include "TextureText.h"

namespace Nyx {

	class FontManager {
		/**
		* コンストラクタ
		*/
		FontManager();

		/**
		* テクスチャによる文字を生成します
		* @param wchar_t 文字
		* @param const FontInfo& フォント情報
		* @return std::shared_ptr<TextureFont>
		*/
		std::shared_ptr<TextureFont> CreateChar(wchar_t chara, const FontInfo& fontInfo);

		/**
		* テクスチャによるテキストを生成します
		* @param const wstring& テキスト
		* @param const FontInfo& フォント情報
		* @return std::shared_ptr<TextureText>
		*/
		std::shared_ptr<TextureText> CreateText(const std::wstring& text, const FontInfo& fontInfo);

		/**
		* テキストファイルからまとめてキャッシュにロードします
		* @param const std::wstring& テキストファイル名
		* @param int スプライトの幅
		* @param int スプライトの高さ
		* @return std::vector<std::shared_ptr<Sprite>>
		*/
		std::shared_ptr<TextureText> Load(const std::wstring& txtFileName, const FontInfo& fontInfo);


		/**
		* キャッシュから指定したリソースを削除します
		* @param const std::wstring& ファイル名
		*/
		void Delete(const std::wstring& key);
	};
}
#endif