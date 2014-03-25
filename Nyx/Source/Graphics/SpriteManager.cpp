#include "PCH/PCH.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "detail/DX9/DirectXDefinition.h"

namespace Nyx {
	//----------------------------------------------------------------------------------------
	//
	std::shared_ptr<Sprite> SpriteManager::CreateSprite(int width, int height, const Color4c& color) {
		auto resource = std::make_shared<Sprite>(width, height, color);
		ResourceCache::Add(std::make_shared<ResourceHandle>(L"0" , resource));
		return resource;
	}

	//----------------------------------------------------------------------------------------
	//
	std::shared_ptr<Sprite> SpriteManager::CreateSprite(const std::wstring& fileName)
	{
		if (ResourceCache::Find(fileName)) {
			return std::static_pointer_cast<Sprite>(ResourceCache::GetHandle(fileName)->GetResource());
		}

		auto resource = std::make_shared<Sprite>(fileName);
		ResourceCache::Add(std::make_shared<ResourceHandle>(fileName, resource));
		return resource;
	}


	//----------------------------------------------------------------------------------------
	//
	void  SpriteManager::Load(const std::wstring& fileName) {
		std::wstring line;
		std::wifstream ifs;
		ifs.open(fileName);
		while (ifs >> line) {
			if (ResourceCache::Find(line)) {
				continue;
			}

			auto resource = std::make_shared<Sprite>(line);
			ResourceCache::Add(std::make_shared<ResourceHandle>(line, resource));
		}
	}

	//----------------------------------------------------------------------------------------
	//
	void SpriteManager::Delete(const std::wstring& fileName) {
		ResourceCache::Delete(fileName);
	}

	std::shared_ptr<Sprite> SpriteManager::GetItem(const std::wstring& resourceName) {
		return std::static_pointer_cast<Sprite>(ResourceCache::GetHandle(resourceName)->GetResource());
	}
}