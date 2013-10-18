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

	
	///サンプラーステート
	enum class SamplerState
	{
		AddressU		=  1,
		AddressV		=  2,
		AddressW		=  3,
		BorderColor		=  5,
		MagFilter       =  6,
		MinFilter		=  7,
		MipFilter		=  8,
		MaxAnisotropy   =  9,
		MaxMipmap       = 11,
		SRGBTexture		= 12
	};


	///ミップマップレベル
	typedef int MipmapLevel;
	
	
	///アドレッシングモード
	enum class AddressingMode
	{
		Wrap			= 1,
		Mirror			= 2,
		Clamp			= 3,
		Border			= 4,
		MirrorOnce		= 5
	};


	///テクスチャフィルタリングモード
	enum class TextureFilteringMode
	{
		Linear			= 0x00,
		Bilinear        = 0x01
	};


	///ブレンディングモード
	enum class BlendingMode
	{
		Alpha		= 0x00,
		Add			= 0x01,
		Sub			= 0x02,
		Mul			= 0x03,
		Inverse		= 0x04,
		NoBlend		= 0x05
	};

}
#endif