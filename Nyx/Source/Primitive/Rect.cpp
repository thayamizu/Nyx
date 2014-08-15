#include "PCH/PCH.h"
#include "Primitive/Rect.h"

namespace Nyx {
	//--------------------------------------------------------------------------------------
	// ’è”’è‹`
	//--------------------------------------------------------------------------------------
	template <typename T>
	const rectangle<T> rectangle<T>::ZERO = rectangle<T>(0, 0, 0, 0);

	template <typename T>
	const rectangle<T> rectangle<T>::UNIT = rectangle<T>(1, 1, 1, 1);
}