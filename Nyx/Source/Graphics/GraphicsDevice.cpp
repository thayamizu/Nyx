#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Utility/Exception.h"
#include "GUI/Window.h"
#include "GraphicsDevice.h"
#include "GraphicsDeviceDesc.h"
#include "GraphicsDeviceType.h"
#include "detail/DX9/DirectGraphicsDevice.h"
#include "Primitive/Color4.h"

namespace Nyx
{
	struct GraphicsDevice::PImpl
	{
		PImpl()
			:isInitialized_(false) {

				render_ = [](){};
		}



		bool Initialize(std::shared_ptr<Window> window, WindowMode windowMode) {
			auto hwnd = window->GetHandle();
			Assert(hwnd != nullptr);

			window->GetSize(windowSize_);

			// Direct3Dオブジェクトの作成
			auto  d3d = Direct3DCreate9(D3D_SDK_VERSION);
			Assert(d3d != NULL);

			//プライマリディスプレイのアダプタディスプレイモードを取得
			D3DDISPLAYMODE display = {};
			ZeroMemory(&display,sizeof(D3DDISPLAYMODE));
			auto hr = d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display);
			if (FAILED(hr)) {
				DebugOutput::Trace("プライマリディスプレイのアダプタの取得に失敗しました。[%s][%s]", __FILE__, __LINE__);
				throw Nyx::COMException("プライマリディスプレイのアダプタの取得に失敗しました。", hr);
			}

			// D3DPresentParametersの設定
			D3DPRESENT_PARAMETERS presentParameter = {};
			ZeroMemory(&presentParameter, sizeof(D3DPRESENT_PARAMETERS));

			//(ウインドウ・モード用)
			presentParameter.BackBufferWidth			= windowSize_.width;
			presentParameter.BackBufferHeight			= windowSize_.height;
			presentParameter.BackBufferFormat			= display.Format;
			presentParameter.BackBufferCount			= 1;
			presentParameter.MultiSampleType			= D3DMULTISAMPLE_NONE;
			presentParameter.MultiSampleQuality			= 0;
			presentParameter.SwapEffect					= D3DSWAPEFFECT_DISCARD;
			presentParameter.hDeviceWindow				= hwnd;
			presentParameter.Windowed					= windowMode == WindowMode::Default ? true: false;
			presentParameter.EnableAutoDepthStencil		= true;
			presentParameter.AutoDepthStencilFormat		= D3DFMT_D16;
			presentParameter.Flags						= 0;
			presentParameter.FullScreen_RefreshRateInHz = 0;
			presentParameter.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

			//Direct3DDeviceオブジェクトの生成
			LPDIRECT3DDEVICE9 d3dDevice = nullptr;
			hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
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
						Assert(hr == S_OK);
					}
				}
			}
			hr = d3dDevice->Reset(&presentParameter);
			if (FAILED(hr)) {
				DebugOutput::Trace("デバイスのリセットに失敗しました。[%s][%s]",__FILE__, __LINE__);
				throw Nyx::COMException("デバイスのリセットに失敗しました。", hr);
			}

			d3d_ = D3d9Ptr(d3d, true);
			d3dDevice_ = D3dDevice9Ptr(d3dDevice, true);


			return isInitialized_ = true;
		}

		bool IsInitialized() {
			return isInitialized_;
		}

		void Render(const Color4c& clearColor) {
			Assert(d3dDevice_ != nullptr);

			d3dDevice_->Clear(
				NULL, 
				NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
				D3DCOLOR_ARGB(clearColor.a, clearColor.r, clearColor.g, clearColor.b), 
				1.f, NULL);

			d3dDevice_->BeginScene();

			render_();

			d3dDevice_->EndScene();

			d3dDevice_->Present( NULL , NULL , NULL , NULL );
		}

		void SetRenderer(std::function<void(void)> render) {
			render_ = render;
		}
	private:
		std::function<void(void)> render_;
		Rect2i windowSize_;
		bool isInitialized_;
		bool isWindowed_;
		bool isLostDevice_;
		bool isShowCursor_;
		std::shared_ptr<Window> window_;
		D3d9Ptr d3d_;
		D3dDevice9Ptr d3dDevice_;
	};


	GraphicsDevice::GraphicsDevice()
		:pimpl_(new PImpl())
	{

	}

	GraphicsDevice::GraphicsDevice(std::shared_ptr<Window> window, WindowMode windowMode)
		:pimpl_(new PImpl())
	{
		auto result = pimpl_->Initialize(window, windowMode);
		Assert(result  == true);
	}

	bool GraphicsDevice::Initialize(std::shared_ptr<Window> window, WindowMode windowMode)
	{
		Assert(pimpl_ != nullptr);
		if (pimpl_->IsInitialized()) {
			return pimpl_->IsInitialized();
		}

		pimpl_->Initialize(window, windowMode);
		return pimpl_->IsInitialized();
	}

	void GraphicsDevice::Render(const Color4c& color) 
	{
		pimpl_->Render(color);
	}


	void GraphicsDevice::OnRender(std::function<void(void)> render) 
	{
		pimpl_->SetRenderer(render);
	}
}