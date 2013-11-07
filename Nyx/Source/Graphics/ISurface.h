#ifndef NYX_CORE_INCLUDED_ISURFACE_H_
#define NYX_CORE_INCLUDED_ISURFACE_H_
#include "Primitive/Rect.h"
#include "IRenderable.h"

namespace Nyx {

	///•`‰æ‰Â”\‚È‹éŒ`—Ìˆæ
	class ISurface : public IRenderable {
	public:
		/**
		*
		*/
		virtual ~ISurface() {}


		/**
		*
		*/
		virtual void SetRect(const Rect2i& rect) = 0;


		/**
		*
		*/
		virtual Rect2i GetRect() const = 0;
	};
}
#endif