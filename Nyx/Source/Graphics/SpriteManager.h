#ifndef NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#define NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#include "ResourceCache.h"

namespace Nyx {

	class SpriteManager {
	public:
		SpriteManager();
		std::shared_ptr<Sprite> CreateSprite(int width, int height, const Color4c& color);
		std::shared_ptr<Sprite> CreateSprite(int width, int height, const std::wstring& fileName);
		std::shared_ptr<SpriteCache> Load(const std::wstring& txtFileName, int width, int height);
	};
}
#endif