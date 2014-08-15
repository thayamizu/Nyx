#include "PCH/PCH.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "detail/DX9/DirectXDefinition.h"
#include "ResourceCache.h"
#include "ResourceHandle.h"

namespace nyx {
	//----------------------------------------------------------------------------------------
	//
	std::shared_ptr<sprite> sprite_factory::make_sprite(int width, int height, const color4c& color) {
		auto resource = std::make_shared<sprite>(width, height, color);
		resource_cache::add(std::make_shared<resource_handle>(L"0" , resource));
		return resource;
	}

	//----------------------------------------------------------------------------------------
	//
	std::shared_ptr<sprite> sprite_factory::make_sprite(const std::wstring& fileName)
	{
		if (resource_cache::find(fileName)) {
			return std::static_pointer_cast<sprite>(resource_cache::get_handle(fileName)->get_resource());
		}

		auto resource = std::make_shared<sprite>(fileName);
		resource_cache::add(std::make_shared<resource_handle>(fileName, resource));
		return resource;
	}


	//----------------------------------------------------------------------------------------
	//
	void  sprite_factory::load_sprite(const std::wstring& fileName) {
		std::wstring line;
		std::wifstream ifs;
		ifs.open(fileName);
		while (ifs >> line) {
			if (resource_cache::find(line)) {
				continue;
			}

			auto resource = std::make_shared<sprite>(line);
			resource_cache::add(std::make_shared<resource_handle>(line, resource));
		}
	}

	//----------------------------------------------------------------------------------------
	//
	void sprite_factory::remove(const std::wstring& fileName) {
		resource_cache::remove(fileName);
	}

	std::shared_ptr<sprite> sprite_factory::get_item(const std::wstring& resourceName) {
		return std::static_pointer_cast<sprite>(resource_cache::get_handle(resourceName)->get_resource());
	}
}