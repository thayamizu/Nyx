#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_TYPE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_TYPE_H_

namespace Nyx {

	///�O���t�B�N�X�f�o�C�X�̎��
	enum class GraphicsDeviceType 
	{
		NoSupport       = 0x00,
		DX9				= 0x01,
		DX10			= NoSupport,
		DX11			= NoSupport,
		OepnGL			= NoSupport
	};


	///�E�C���h�E���[�h
	enum class WindowMode
	{
		Default         = 1,
		FullScreen      = 2,
		Windowed		= Default,
	};
	
	///�T���v���[�X�e�[�g
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

	///���\�[�X�^�C�v
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


	///�t�H�[�}�b�g�^�C�v
	typedef ulong      FormatType;
	typedef FormatType BackBufferFormat;
	typedef FormatType DisplayFormat;
	typedef FormatType IndexBufferFormat;
	typedef FormatType StencilBufferFormat;
	typedef FormatType VertexBufferFormat;

	///�T���v�����O���x��
	typedef ulong MultiSamplingLevel;

	///�~�b�v�}�b�v���x��
	typedef ulong MipmapLevel;
	
	///�ٕ����t�B���^�����O���x��
	typedef ulong AnisotropyLevel;
	

	///�A�h���b�V���O���[�h
	enum class AddressingMode
	{
		Wrap			= 1,
		Mirror			= 2,
		Clamp			= 3,
		Border			= 4,
		MirrorOnce		= 5
	};


	///�e�N�X�`���t�B���^�����O���[�h
	enum class TextureFilteringMode
	{
		Linear			= 0x00,
		Bilinear        = 0x01
	};


	///�u�����f�B���O���[�h
	enum class BlendingMode
	{
		Alpha		= 0x00,
		Add			= 0x01,
		Sub			= 0x02,
		Mul			= 0x03,
		Inverse		= 0x04,
		NoBlend		= 0x05
	};


	///���C�g�̎��
	enum class LightType
	{
		DirectionalLight,
		PointLight,
		SpotLight
	};

	///�}�e���A���J���[�̎��
	enum class MaterialColor
	{
		Ambient,
		Diffuse,
		Specular,
	};	

}
#endif