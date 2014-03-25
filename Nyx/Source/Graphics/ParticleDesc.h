#ifndef NYX_CORE_INCLUDED_PARTICLE_DESC_H_
#define NYX_CORE_INCLUDED_PARTICLE_DESC_H_

namespace Nyx {

	struct ParticleDesc {
		int emission;
		int life;
		int color;
		float x, y, z;
	};
}
#endif