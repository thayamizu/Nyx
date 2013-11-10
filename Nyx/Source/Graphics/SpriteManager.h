#ifndef NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#define NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#include "ResourceCache.h"

namespace Nyx {

	typedef std::vector <std::shared_ptr<Sprite>> SpriteCache;

	///スプライトマネージャ
	class SpriteManager {
	public:
		/**
		* コンストラクタ
		*/
		SpriteManager();

		/**
		* スプライトを生成します
		* @param int スプライトの幅
		* @param int スプライトの高さ
		* @param std::wstring ファイル名
		* @return std::shared_ptr<Sprite>
		*/
		std::shared_ptr<Sprite> CreateSprite(int width, int height, const Color4c& color);
		
		/**
		* スプライトを生成します
		* @param int スプライトの幅
		* @param int スプライトの高さ
		* @param const Color4c& 色
		* @return std::shared_ptr<Sprite>
		*/
		std::shared_ptr<Sprite> CreateSprite(int width, int height, const std::wstring& fileName);
		
		/**
		* テキストファイルからまとめてキャッシュにロードします
		* @param const std::wstring& テキストファイル名
		* @param int スプライトの幅
		* @param int スプライトの高さ
		* @return std::vector<std::shared_ptr<Sprite>>
		*/
		SpriteCache Load(const std::wstring& txtFileName, int width, int height);

		/**
		* キャッシュから指定したリソースを削除します
		* @param const std::wstring& ファイル名
		*/
		void Delete(const std::wstring& fileName);
	};
}
#endif