#include "PCH/PCH.h"
#include "Primitive/Rect.h"

namespace Nyx {
	//--------------------------------------------------------------------------------------
	// ’è”’è‹`
	//--------------------------------------------------------------------------------------
	template <typename T>
	const Rect<T> Rect<T>::Zero = Rect<T>(0, 0, 0, 0);

	template <typename T>
	const Rect<T> Rect<T>::Unit = Rect<T>(1, 1, 1, 1);
}