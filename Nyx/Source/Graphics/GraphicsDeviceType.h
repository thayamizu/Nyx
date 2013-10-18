#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_TYPE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_TYPE_H_

namespace Nyx {

	///�O���t�B�N�X�f�o�C�X�̎��
	enum class GraphicsDeviceType 
	{
		DX9				= 0x00,
		DX10			= 0x01,
		DX11			= 0x02,
		OepnGL			= 0x03,
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


	///�~�b�v�}�b�v���x��
	typedef int MipmapLevel;
	
	
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

}
#endif