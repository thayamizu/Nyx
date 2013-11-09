#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_TYPE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_TYPE_H_

namespace Nyx {

	///グラフィクスデバイスの種類
	enum class GraphicsDeviceType 
	{
		NoSupport       = 0x00,
		DX9				= 0x01,
		DX10			= NoSupport,
		DX11			= NoSupport,
		OepnGL			= NoSupport
	};


	///ウインドウモード
	enum class WindowMode
	{
		Default         = 1,
		FullScreen      = 2,
		Windowed		= Default,
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

	///リソースタイプ
	enum class ResourceType 
	{
		Surface,
		Volume,
		Texture,
		VolumeTextre,
		CubeTexture,
		VertexBuffer,
		IndexBuffer

	};


	///フォーマットタイプ
	typedef ulong      FormatType;
	typedef FormatType BackBufferFormat;
	typedef FormatType DisplayFormat;
	typedef FormatType IndexBufferFormat;
	typedef FormatType StencilBufferFormat;
	typedef FormatType VertexBufferFormat;

	///サンプリングレベル
	typedef ulong MultiSamplingLevel;

	///ミップマップレベル
	typedef ulong MipmapLevel;
	
	///異方性フィルタリングレベル
	typedef ulong AnisotropyLevel;
	

	///ライトの種類
	enum class LightType
	{
		DirectionalLight,
		PointLight,
		SpotLight
	};
}
#endif