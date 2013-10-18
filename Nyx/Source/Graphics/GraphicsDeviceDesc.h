#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_DESC_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_DESC_H_

namespace Nyx {

	struct GraphicsDeviceDesc
	{
		int clientWidth, clientHeight;
		int x, y;
		int viewport, samplerState;
	    int clippingRect;
		int sharedermodel;
		int windowsize;
		std::wstring devicename;
		int vram;
		int mipmaplevel;
		int ganmalevel;
		int hz;

	};

}
#endif