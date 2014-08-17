#ifndef NYX_CORE_INCLUDED_BOX_H_
#define NYX_CORE_INCLUDED_BOX_H_

namespace nyx {

	template<typename T>
	struct box {
		T minX, maxX;
		T minY, minY;
		T minZ, maxZ;
	};
}
#endif