#ifndef NYX_CORE_INCLUDED_PARTICLE_SYSTEM_H_
#define NYX_CORE_INCLUDED_PARTICLE_SYSTEM_H_
#include "IRenderable.h"

namespace Nyx {

	class ParticleSystem : public IRenderable{
	public:
		ParticleSystem();
		void CreateParticle();
		void Update();
		void SetColor();
		void GetColor();
		void AddForce();
		void Render(const Matrix44& world);
	private:
	};
}
#endif