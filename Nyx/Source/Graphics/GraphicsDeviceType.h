#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_TYPE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_TYPE_H_

namespace Nyx {

	///グラフィクスデバイスの種類
	enum class GraphicsDeviceType 
	{
		DX9				= 0x00,
		DX10			= 0x01,
		DX11			= 0x02,
		OepnGL			= 0x03,
	};

}
#endif