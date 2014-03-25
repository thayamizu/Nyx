#ifndef NYX_CORE_INCLUDED_TEXTURE_TEXT_H_
#define NYX_CORE_INCLUDED_TEXTURE_TEXT_H_
#include "FontInfo.h"
#include "IResource.h"
#include "IRenderable.h"

namespace Nyx {

	typedef std::vector< std::shared_ptr<TextureFont> > TextureFontList;
	class TextureText : public IRenderable, public IResource {
	public:
		/**
		*
		*/
		explicit TextureText(const TextureFontList& text);

		/**
		*
		*/
		void Set(const TextureFontList& text);
		

		/**
		*
		*/
		void SetRect(const Rect2i& rect);
		

		/**
		*
		*/
		Rect2i GetRect() const ;
		

		/**
		*
		*/
		void SetTextSpeed(size_t speed);
		
		
		/**
		*
		*/
		size_t GetTextSpeed() const;


		/**
		*
		*/
		void SetFontInfo(const FontInfo& color);
		
		
		/**
		*
		*/
		void SetColor(const Color4c& color);
		
		
		/**
		*
		*/
		void NextText();

		/**
		*
		*/
		void SetTransparency(uchar transparency);


		/**
		*
		*/
		uchar GetTransparency() const;

		/**
		*
		*/
		void Render(const Matrix44& matrix) const;
		
		/**
		*
		*/
		void Release();
		
		/**
		*
		*/
		void Recovery();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif