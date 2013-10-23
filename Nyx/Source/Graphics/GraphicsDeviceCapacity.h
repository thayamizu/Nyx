#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_CAPACITY_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_CAPACITY_H_
#include "GraphicsDeviceType.h"

namespace Nyx {

	class GraphicsDeviceCapacity 
	{
	public:
		GraphicsDeviceCapacity();
		void LookupGraphicsDeviceCapacity(uint adapterIndex);
		BackBufferFormat GetBackBufferFormat(uint adapterIndex, WindowMode windowMode);
		StencilBufferFormat GetStencilBufferFormat();


	private:
		struct PImpl;
		std::shared_ptr<PImpl>  pimpl_;
	};
}
#endif