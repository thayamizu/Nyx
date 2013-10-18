#ifndef NYX_CORE_INCLUDED_SPRITE_H_
#define NYX_CORE_INCLUDED_SPRITE_H_
#include "ISprite.h"


namespace Nyx {

	class Sprite : public ISprite
	{
	public:
		Sprite();
		~Sprite();

	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}

#endif