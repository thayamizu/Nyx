#ifndef NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#define NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#include "ResourceCache.h"
#include "Utility/NonCopyable.h"

namespace nyx {

	///スプライトマネージャ
	class sprite_factory : noncopyable {
	public:
		/**
		* スプライトを生成します
		* @param int スプライトの幅
		* @param int スプライトの高さ
		* @param std::wstring ファイル名
		* @return std::shared_ptr<Sprite>
		*/
		static std::shared_ptr<sprite> make_sprite(int width, int height, const color4c& color);
		
		/**
		* スプライトを生成します
		* @return std::shared_ptr<Sprite>
		*/
		static std::shared_ptr<sprite> make_sprite(const std::wstring& fileName);
		
		/**
		* テキストファイルからまとめてキャッシュにロードします
		* @param const std::wstring& テキストファイル名
		* @param int スプライトの幅
		* @param int スプライトの高さ
		* @return std::vector<std::shared_ptr<Sprite>>
		*/
		static void load_sprite(const std::wstring& txtFileName);

		/**
		* キャッシュから指定したリソースを削除します
		* @param const std::wstring& ファイル名
		*/
		static void remove(const std::wstring& resourceName);

		/**
		* キャッシュから指定したリソースを削除します
		* @param const std::wstring& ファイル名
		*/
		static std::shared_ptr<sprite> get_item(const std::wstring& resourceName);
	private:
		/**
		* コンストラクタ
		*/
		sprite_factory() {}
	};
}
#endif