#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_

namespace Nyx {

	class GraphicsDevice
	{
	public:
		GraphicsDevice();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};

}
#endif