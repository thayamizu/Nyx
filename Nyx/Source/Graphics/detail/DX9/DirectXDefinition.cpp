#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "DirectXDefinition.h"
#include "Primitive/Rect.h"
#include "Graphics/GraphicsDeviceCapacity.h"
#include "Graphics/GraphicsDeviceType.h"
#include "GUI/Window.h"

namespace nyx
{
	D3d9Ptr D3d9Driver::d3d9Ptr_             = nullptr;
	D3dDevice9Ptr D3d9Driver::d3dDevice9Ptr_ = nullptr;

	//-----------------------------------------------------------------------------------
	//
	bool InitializeD3d9(std::shared_ptr<window> window, WINDOW_MODE windowMode, std::shared_ptr<graphics_capacity> capacity, sampling_level samplingLevel) {
			// Direct3D�I�u�W�F�N�g�̍쐬
			auto  d3d = D3d9Driver::GetD3d9();
			NYX_ASSERT(d3d != nullptr);

			//Direct3DDevice�I�u�W�F�N�g�̐���
			auto hwnd = window->get_handle();
			D3DPRESENT_PARAMETERS presentParameter = BuildPresentParameter(window, windowMode, capacity, samplingLevel);
			LPDIRECT3DDEVICE9 d3dDevice = nullptr;
			auto hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&presentParameter, &d3dDevice );
			if( FAILED(hr)) {  
				hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&presentParameter, &d3dDevice);
				if( FAILED(hr)) {	  
					hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hwnd,
						D3DCREATE_HARDWARE_VERTEXPROCESSING,
						&presentParameter, &d3dDevice);
					if( FAILED(hr)){
						hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hwnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&presentParameter, &d3dDevice);
						NYX_ASSERT(hr == S_OK);
					}
				}
			}
			hr = d3dDevice->Reset(&presentParameter);
			if (FAILED(hr)) {
				debug_out::trace("�f�o�C�X�̃��Z�b�g�Ɏ��s���܂����B[%s][%s]",__FILE__, __LINE__);
				throw nyx::com_exception("�f�o�C�X�̃��Z�b�g�Ɏ��s���܂����B", hr);
			}

			D3d9Driver::d3dDevice9Ptr_ = D3dDevice9Ptr(d3dDevice, false);
			NYX_ASSERT(D3d9Driver::d3d9Ptr_ != nullptr);
			NYX_ASSERT(D3d9Driver::d3dDevice9Ptr_ != nullptr);

			return SUCCEEDED(hr);
	}
	
	

	//-----------------------------------------------------------------------------------
	//
	D3DPRESENT_PARAMETERS BuildPresentParameter(std::shared_ptr<window> window, WINDOW_MODE windowMode, std::shared_ptr<graphics_capacity> capacity, sampling_level samplingLevel) {

		// D3DPresentParameters�̐ݒ�
		D3DPRESENT_PARAMETERS presentParameter = {};
		ZeroMemory(&presentParameter, sizeof(D3DPRESENT_PARAMETERS));

		//�p�����[�^�̎擾
		auto backbufferFormat    = capacity->get_back_buffer_format();
		auto stencilBufferFormat = capacity->get_depth_stencil_buffer_format();
		auto level = static_cast<D3DMULTISAMPLE_TYPE>(samplingLevel);
		uint64_t quality = NULL;
		capacity->get_supported_multisampling_level(samplingLevel, backbufferFormat, &quality);
		if (quality != NULL) {
			--quality;
		}

		//�p�����[�^�̐ݒ�
		rect2i windowSize;
		window->get_size(windowSize);
		presentParameter.BackBufferWidth			= windowSize.width;
		presentParameter.BackBufferHeight			= windowSize.height;
		presentParameter.BackBufferFormat			= static_cast<D3DFORMAT>(backbufferFormat);
		presentParameter.BackBufferCount			= 1;
		presentParameter.MultiSampleType			= level;
		presentParameter.MultiSampleQuality			= quality;
		presentParameter.SwapEffect					= D3DSWAPEFFECT_DISCARD;
		presentParameter.hDeviceWindow				= window->get_handle();
		presentParameter.Windowed					= windowMode == WINDOW_MODE::WINDOW_MODE_DEFAULT ? true: false;
		presentParameter.EnableAutoDepthStencil		= true;
		presentParameter.AutoDepthStencilFormat		= static_cast<D3DFORMAT>(stencilBufferFormat);
		presentParameter.Flags						= NULL;
		presentParameter.FullScreen_RefreshRateInHz = NULL;
		presentParameter.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

		return presentParameter;
	}
}