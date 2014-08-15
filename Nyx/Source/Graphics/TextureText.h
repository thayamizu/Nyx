#ifndef NYX_CORE_INCLUDED_TEXTURE_TEXT_H_
#define NYX_CORE_INCLUDED_TEXTURE_TEXT_H_
#include "FontInfo.h"
#include "IResource.h"
#include "IRenderable.h"

namespace nyx {

	typedef std::vector< std::shared_ptr<texture_font> > TextureFontList;
	class texture_text : public irenderable, public iresource {
	public:
		/**
		*
		*/
		explicit texture_text(const TextureFontList& text);

		/**
		*
		*/
		void set(const TextureFontList& text);
		

		/**
		*
		*/
		void set_rect(const rect2i& rect);
		

		/**
		*
		*/
		rect2i get_rect() const ;
		

		/**
		*
		*/
		void set_text_speed(size_t speed);
		
		
		/**
		*
		*/
		size_t get_text_speed() const;


		/**
		*
		*/
		void set_font_info(const font_info& color);
		
		
		/**
		*
		*/
		void set_color(const color4c& color);
		
		
		/**
		*
		*/
		void next();

		/**
		*
		*/
		void set_transparency(uint8_t transparency);


		/**
		*
		*/
		uint8_t get_transparency() const;

		/**
		*
		*/
		void render(const matrix& matrix) const;
		
		/**
		*
		*/
		void release();
		
		/**
		*
		*/
		void recovery();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif