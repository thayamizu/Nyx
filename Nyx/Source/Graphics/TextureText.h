#ifndef NYX_CORE_INCLUDED_TEXTURE_TEXT_H_
#define NYX_CORE_INCLUDED_TEXTURE_TEXT_H_
#include "ITexture.h"
#include "FontInfo.h"

namespace Nyx {
	class FontTextureText : public ITexture {
	public:
		FontTextureText(std::wstring text, const FontInfo& fontInfo);
		void Render(const Matrix44& matrix);
		std::shared_ptr<TextureFont> GetChar(size_t index);
	private:
		void SetRect(const Rect2i& rect) {}
		Rect2i GetRect() {}
		std::vector<std::shared_ptr<TextureFont>> string_;
	};
}
#endif