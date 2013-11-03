#include "PCH/PCH.h"
#include "SpriteLoader.h"

namespace Nyx {
	class SpriteManager {
	public:
		std::shared_ptr<Sprite>      SpriteLoader::CreateSprite(std::wstring fileName) {
			return nullptr;
		}
		std::shared_ptr<SpriteCache> SpriteLoader::Load(std::wstring fileName) {
			return nullptr;
		}
	};
}