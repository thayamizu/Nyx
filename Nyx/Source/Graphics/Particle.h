#ifndef NYX_CORE_INCLUDED_PARTICLE_H_
#define NYX_CORE_INCLUDED_PARTICLE_H_

namespace Nyx {

	struct particle_desc {
		int emission;
		int life;
		int color;
		float x, y, z;
	};
}
#endif