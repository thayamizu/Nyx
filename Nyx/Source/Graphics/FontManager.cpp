#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "FontManager.h"
#include "detail/DX9/DirectXDefinition.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	//
	std::shared_ptr<TextureFont> FontManager::CreateChar(wchar_t chara, const FontInfo& fontInfo) {
		//ÉäÉ\Å[ÉXÇçÏê¨
		auto resource = std::make_shared<TextureFont>(chara, fontInfo);
		ResourceCache::Add(std::make_shared<ResourceHandle>(&chara, resource));

		return resource;
	}

	//-----------------------------------------------------------------------------------------
	//
	std::shared_ptr<TextureText> FontManager::CreateText(const std::wstring& text, const FontInfo& fontInfo) {
		TextureFontList resource;
		for (auto chara : text) {
			resource.push_back(CreateChar(chara, fontInfo));
		}

		return std::make_shared<TextureText>(resource);
	}


	////-----------------------------------------------------------------------------------------
	////
	//void FontManager::Load(const std::wstring& txtFileName, const FontInfo& fontInfo) {

	//	std::wstring line;
	//	std::wifstream ifs;
	//	ifs.open(txtFileName);
	//	while (ifs >> line) {
	//		for (auto chara : line) {
	//			CreateChar(chara, fontInfo);
	//		}
	//	}
	//}


	//-----------------------------------------------------------------------------------------
	//
	void FontManager::Delete(const std::wstring& key) {
		ResourceCache::Delete(key);
	}

	//-----------------------------------------------------------------------------------------
	//
	std::shared_ptr<TextureFont> FontManager::GetItem(wchar_t chara) {
		if (ResourceCache::Find(&chara) == false) {
			return nullptr;
		}

		return std::static_pointer_cast<TextureFont>(ResourceCache::GetHandle(&chara)->GetResource());
	}

}