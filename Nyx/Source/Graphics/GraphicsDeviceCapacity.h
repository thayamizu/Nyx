#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_CAPACITY_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_CAPACITY_H_
#include "GraphicsDeviceType.h"

namespace Nyx {

	class GraphicsDeviceCapacity 
	{
	public:
		GraphicsDeviceCapacity();

		void SetAdapterIndex(uint adapterIndex);
		
		void SetWindowMode(WindowMode windowMode); 

		void LookupGraphicsDeviceCapacity();
		
		uint GetAdapterCount();
		
		BackBufferFormat GetBackBufferFormat();
		
		StencilBufferFormat GetDepthStencilBufferFormat();
		
		bool GetSupportedMultiSamplingQuality(ulong samplingLevel, FormatType formatType, ulong* quality);
	private:
		struct PImpl;
		std::shared_ptr<PImpl>  pimpl_;
	};
}
#endif