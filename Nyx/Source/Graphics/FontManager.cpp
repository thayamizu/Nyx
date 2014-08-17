#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "FontManager.h"
#include "detail/DX9/DirectXDefinition.h"

namespace nyx {
	//-----------------------------------------------------------------------------------------
	//
	std::shared_ptr<texture_font> font_factory::make_texture_char(wchar_t chara, const font_info& fontInfo) {
		//ÉäÉ\Å[ÉXÇçÏê¨
		auto resource = std::make_shared<texture_font>(chara, fontInfo);
		resource_cache::add(std::make_shared<resource_handle>(&chara, resource));

		return resource;
	}

	//-----------------------------------------------------------------------------------------
	//
	std::shared_ptr<texture_text> font_factory::make_texture_text(const std::wstring& text, const font_info& fontInfo) {
		texture_font_list resource;
		for (auto chara : text) {
			resource.push_back(make_texture_char(chara, fontInfo));
		}

		return std::make_shared<texture_text>(resource);
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
	void font_factory::remove(const std::wstring& key) {
		resource_cache::remove(key);
	}

	//-----------------------------------------------------------------------------------------
	//
	std::shared_ptr<texture_font> font_factory::get_item(wchar_t chara) {
		if (resource_cache::find(&chara) == false) {
			return nullptr;
		}

		return std::static_pointer_cast<texture_font>(resource_cache::get_handle(&chara)->get_resource());
	}

}