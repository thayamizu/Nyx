#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "FontManager.h"
#include "detail/DX9/DirectXDefinition.h"

namespace Nyx {

	//-----------------------------------------------------------------------------------------
	//
	FontManager::FontManager() {

	}

	//-----------------------------------------------------------------------------------------
	//
	std::shared_ptr<TextureFont> FontManager::CreateChar(wchar_t chara, const FontInfo& fontInfo) {
		return std::make_shared<TextureFont>(chara, fontInfo);
	}

	//-----------------------------------------------------------------------------------------
	//
	std::shared_ptr<TextureText> FontManager::CreateText(const std::wstring& text, const FontInfo& fontInfo) {
		return std::make_shared<TextureText>(text, fontInfo);

	}

	//-----------------------------------------------------------------------------------------
	//
	std::shared_ptr<TextureText> FontManager::Load(const std::wstring& txtFileName, const FontInfo& fontInfo) {
		return std::make_shared<TextureText>(txtFileName, fontInfo);
	}


	//-----------------------------------------------------------------------------------------
	//
	void FontManager::Delete(const std::wstring& key) {

	}
}