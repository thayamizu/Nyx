#ifndef NYX_CORE_INCLUDED_CORE_SPRITE_LOADER_H_
#define NYX_CORE_INCLUDED_CORE_SPRITE_LOADER_H_

namespace Nyx {

	class Sprite;
	class SpriteCache;
	class SpriteManager {
	public:
		std::shared_ptr<Sprite>      CreateSprite(std::wstring fileName);
		std::shared_ptr<SpriteCache> Load(std::wstring fileName);
	};
}
#endif