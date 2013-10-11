#ifndef NYX_CORE_INCLUDED_INPUT_DEVICE_DESC_H_
#define NYX_CORE_INCLUDED_INPUT_DEVICE_DESC_H_
#include <memory>

namespace Nyx {

	struct InputDeviceDesc {
		float range;
		int   button;
		void* handle;
	};

}
#endif