#include "PCH/PCH.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "detail/DX9/DirectXDefinition.h"

namespace Nyx {
	//----------------------------------------------------------------------------------------
	//
	SpriteManager::SpriteManager() {
	}


	//----------------------------------------------------------------------------------------
	//
	std::shared_ptr<Sprite> SpriteManager::CreateSprite(int width, int height, const Color4c& color) {
		auto cache = D3d9ResourceCache::GetCache();
		auto resource = std::make_shared<Sprite>(width, height, color);
		
		cache->Add(std::make_shared<ResourceHandle>(L"0", resource));
		return resource;
	}

	//----------------------------------------------------------------------------------------
	//
	std::shared_ptr<Sprite> SpriteManager::CreateSprite(int width, int height, const std::wstring& fileName)
	{
		auto cache = D3d9ResourceCache::GetCache();
		auto resource = std::make_shared<Sprite>(width, height, fileName);

		cache->Add(std::make_shared<ResourceHandle>(fileName, resource));
		return resource;
	}


	//----------------------------------------------------------------------------------------
	//
	SpriteCache  SpriteManager::Load(const std::wstring& fileName, int width, int height) {
		auto d3dcache = D3d9ResourceCache::GetCache();///d3dリソースの管理
		SpriteCache cache;

		std::wstring line;
		std::wifstream ifs;
		ifs.open(fileName);
		while (ifs >> line) {
			auto resource = std::make_shared<Sprite>(width, height, line);
			d3dcache->Add(std::make_shared<ResourceHandle>(line, resource));
			cache.push_back(resource);
		}

		return cache;
	}

	//----------------------------------------------------------------------------------------
	//
	void Delete(const std::wstring& fileName) {
		auto d3dcache = D3d9ResourceCache::GetCache();///d3dリソースの管理
		d3dcache->Delete(fileName);
	}
}