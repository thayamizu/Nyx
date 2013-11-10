#ifndef NYX_CORE_INCLUDED_TEXTURE_TEXT_H_
#define NYX_CORE_INCLUDED_TEXTURE_TEXT_H_
#include "FontInfo.h"
#include "IResource.h"
#include "IRenderable.h"

namespace Nyx {
	class TextureText : public IRenderable, public IResource {
	public:
		TextureText(std::wstring text, const FontInfo& fontInfo);
		void Set(std::wstring text, const FontInfo& fontInfo);
		
		void SetRect(const Rect2i& rect);
		Rect2i GetRect() const ;
		
		void SetTextSpeed(size_t speed);
		size_t GetTextSpeed() const;

		void SetFontInfo(size_t index, const FontInfo& color);
		FontInfo GetFontInfo(size_t index);
		
		void SetColor(size_t index, const Color4c& color);
		Color4c GetColor(size_t index);
		
		void Render(const Matrix44& matrix) const;
		std::shared_ptr<TextureFont> GetChar(size_t index);

		void Release();
		void Recovery();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif