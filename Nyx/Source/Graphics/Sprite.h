#ifndef NYX_CORE_INCLUDED_SPRITE_H_
#define NYX_CORE_INCLUDED_SPRITE_H_
#include "IRenderable.h"
#include "IResource.h"
#include "Primitive/Color4.h"
#include "Primitive/Rect.h"

namespace Nyx {

	class Sprite : public IRenderable, public IResource
	{
	public:
		Sprite(int width, int height, const std::wstring& fileName);
		Sprite(int width, int height, const Color4c& color);
		~Sprite();
		void Fill(const Color4c& color);
		void SetColor(const Color4c& color);
		Color4c GetColor() const;
		void SetRect(const Rect2i& rect);
		Rect2i GetRect() const;
		void Render(const Matrix44& matrix) const;

		void Release();
		void Recovery();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}

#endif