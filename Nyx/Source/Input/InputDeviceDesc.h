#ifndef NYX_CORE_INCLUDED_INPUT_DEVICE_DESC_H_
#define NYX_CORE_INCLUDED_INPUT_DEVICE_DESC_H_
#include <memory>

namespace nyx {

	struct input_device_desc {
		float range;
		int   button;
		void* handle;
	};

}
#endif