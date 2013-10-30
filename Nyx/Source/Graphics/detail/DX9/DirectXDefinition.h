/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_DIRECT_GRAPHICS_9_DEFINITION_H_
#define NYX_CORE_INCLUDED_DIRECT_GRAPHICS_9_DEFINITION_H_
#include <memory>
//boost/intrusive_ptr
#include <boost/intrusive_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

//D3D9
#include <D3D9.h>
#include <D3DX9.h>

//dx error
#include <DXErr.h>
#include "Debug/Assert.h"


#include "Graphics/GraphicsDeviceCapacity.h"
#include "Graphics/GraphicsDeviceType.h"
namespace Nyx {
	//�^��`
	//--------------------------------------------------------------
	//Direct 3D
	typedef boost::intrusive_ptr<IDirect3D9>			D3d9Ptr;
	typedef boost::intrusive_ptr<IDirect3DDevice9>		D3dDevice9Ptr;
	typedef	LPDIRECT3DTEXTURE9							D3DTexture;

	class Window;
	class GraphicsDeviceCapacity;
	
	///d3d9�I�u�W�F�N�g�̃V���O���g��
	class D3d9Driver : boost::noncopyable
	{
	public:
	
		/**
		* IDirect3D9�C���^�t�F�[�X���擾���܂�
		* @return D3d9Ptr
		*/
		static D3d9Ptr GetD3d9() {
			if (d3d9Ptr_ == nullptr) {
				auto  d3d = Direct3DCreate9(D3D_SDK_VERSION);
				d3d9Ptr_ = D3d9Ptr(d3d, true);
			}
			return d3d9Ptr_;
		}

		/**
		* IDirect3DDevice9�C���^�t�F�[�X���擾���܂�
		* @return D3dDevice9Ptr;
		*/
		static D3dDevice9Ptr GetD3dDevice9() {
			Assert(d3dDevice9Ptr_ != nullptr);
			return d3dDevice9Ptr_;
		}
	private:
		friend bool InitializeD3d9(std::shared_ptr<Window> window, WindowMode windowMode, std::shared_ptr<GraphicsDeviceCapacity> capacity, MultiSamplingLevel samplingLevel);
	
		static D3d9Ptr        d3d9Ptr_;
		static D3dDevice9Ptr  d3dDevice9Ptr_;
	};


	/**
	* DirectGraphics9�����������܂�
	* @param std::shared_ptr<Window>
	* @param WinodwMode
	* @param std::shared_ptr<GraphicsDeviceCapacity>
	* @param MutiSamplingLevel
	*/
	bool InitializeD3d9(std::shared_ptr<Window> window, WindowMode windowMode, std::shared_ptr<GraphicsDeviceCapacity> capacity, MultiSamplingLevel samplingLevel);
	

	/**
	* PRESENT_PARAMETER�\���̂��\�z���܂�
	* @param std::shared_ptr<Window>
	* @param WinodwMode
	* @param std::shared_ptr<GraphicsDeviceCapacity>
	* @param MutiSamplingLevel
	*/
	D3DPRESENT_PARAMETERS BuildPresentParameter(std::shared_ptr<Window> window, WindowMode windowMode, std::shared_ptr<GraphicsDeviceCapacity> capacity,  MultiSamplingLevel samplingLevel);
}

#endif