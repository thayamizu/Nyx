#include "PCH/PCH.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "ResourceCache.h"
#include "ResourceHandle.h"

namespace Nyx {
	SpriteManager::SpriteManager() {}


	std::shared_ptr<Sprite> SpriteManager::CreateSprite(int width, int height, const Color4c& color) {
		return std::make_shared<Sprite>(width, height, color);
	}

	std::shared_ptr<Sprite> SpriteManager::CreateSprite( int width, int height, const std::wstring& fileName) {
		return std::make_shared<Sprite>(width, height, fileName);
	}

	std::shared_ptr<ResourceCache> SpriteManager::Load(const std::wstring& fileName, int width, int height) {
		auto cache = std::make_shared<ResourceCache>();

		std::wstring line;
		std::wifstream ifs;
		ifs.open(fileName);
		while (ifs >> line) {
			auto resource = std::make_shared<Sprite>(width, height, line);

			cache->Add(std::make_shared<ResourceHandle>(line, resource));
		}
		return cache;
	}
}