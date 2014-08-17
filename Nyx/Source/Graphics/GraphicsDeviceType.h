#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_TYPE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_TYPE_H_

namespace nyx {

	///グラフィクスデバイスの種類
	enum class GRAPHICS_DEVICE_TYPE 
	{
		GRAPHICS_DEVICE_TYPE_NO_SUPPORT       = 0x00,
		GRAPHICS_DEVICE_TYPE_DX9				= 0x01,
		GRAPHICS_DEVICE_TYPE_DX10			= GRAPHICS_DEVICE_TYPE_NO_SUPPORT,
		GRAPHICS_DEVICE_TYPE_DX11			= GRAPHICS_DEVICE_TYPE_NO_SUPPORT,
		GRAPHICS_DEVICE_TYPE_OPEN_GL			= GRAPHICS_DEVICE_TYPE_NO_SUPPORT
	};


	///ウインドウモード
	enum class WINDOW_MODE
	{
		WINDOW_MODE_DEFAULT         = 1,
		WINDOW_MODE_FULL_SCREEN      = 2,
		WINDOW_MODE_WINDOWED		= WINDOW_MODE_DEFAULT,
	};
	
	///サンプラーステート
	enum class SAMPLER_STATE
	{
		SAMPLER_STATE_ADDRESS_U		=  0x01,
		SAMPLER_STATE_ADDRESS_V = 0x02,
		SAMPLER_STATE_ADDRESS_W = 0x03,
		SAMPLER_STATE_BORDER_COLOR = 0x05,
		SAMPLER_STATE_MAG_FILTER = 0x06,
		SAMPLER_STATE_MIN_FILTER = 0x07,
		SAMPLER_STATE_MIP_FILTER = 0x08,
		SAMPLER_STATE_MAX_ANISOTROPY = 0x09,
		SAMPLER_STATE_MAX_MipMap = 0x0a,
		SAMPLER_STATE_SRGB_TEXTURE = 0x0b,
		SAMPLER_STATE_NUM
	};

	///リソースタイプ
	enum class RESOURCE_TYPE 
	{
		RESOURCE_TYPE_SURFACE,
		RESOURCE_TYPE_VOLUME,
		RESOURCE_TYPE_TEXTURE,
		RESOURCE_TYPE_VOLUME_TEXTURE,
		RESOURCE_TYPE_CUBE_TEXTURE,
		RESOURCE_TYPE_VERTEX_BUFFER,
		RESOURCE_TYPE_INDEX_BUFFER
	};


	///フォーマットタイプ
	typedef uint64_t    format_type;
	typedef format_type back_buffer_format;
	typedef format_type display_format;
	typedef format_type index_buffer_format;
	typedef format_type stencil_buffer_format;
	typedef format_type vertex_buffer_format;

	///サンプリングレベル
	typedef uint64_t multi_sampling_level;

	///ミップマップレベル
	typedef uint64_t mipmap_level;
	
	///異方性フィルタリングレベル
	typedef uint64_t anisortropy_level;
	

	///ライトの種類
	enum class LIGHT_TYPE
	{
		LIGHT_TYPE_DIRECTIONAL,
		LIGHT_TYPE_POINT,
		LIGHT_TYPE_SPOT
	};
}
#endif