#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_CAPACITY_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_CAPACITY_H_
#include "GraphicsDeviceType.h"

namespace nyx {

	class graphics_capacity 
	{
	public:
		graphics_capacity();

		void set_adapter_index(uint32_t adapterIndex);
		
		void set_window_mode(WINDOW_MODE windowMode); 

		void lookup_graphics_device();
		
		uint32_t get_adapter_count();
		
		back_buffer_format get_back_buffer_format();
		
		stencil_buffer_format get_depth_stencil_buffer_format();
		
		bool get_supported_multisampling_level(uint64_t samplingLevel, format_type formatType, uint64_t* quality);
	private:
		struct PImpl;
		std::shared_ptr<PImpl>  pimpl_;
	};
}
#endif