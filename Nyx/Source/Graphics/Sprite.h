#ifndef NYX_CORE_INCLUDED_SPRITE_H_
#define NYX_CORE_INCLUDED_SPRITE_H_
#include "ISprite.h"
#include "Primitive/Color4.h"
#include "Primitive/Rect.h"
#include "Primitive/Vector2.h"

namespace Nyx {

	class Sprite
	{
	public:
		Sprite(size_t width, size_t height);
		Sprite(const std::wstring , size_t width,  size_t height);

		void SetColor(const Color4c& color);
		void SetRect(const Rect2f& rect);
		void Render(float x, float y, float rad);
		void Render(const Vector2f& position, float rad);

		void OnLostDevice();
		void OnResetDevice();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}

#endif