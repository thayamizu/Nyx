#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Utility/Exception.h"
#include "GUI/Window.h"
#include "GraphicsDevice.h"
#include "GraphicsDeviceCapacity.h"
#include "GraphicsDeviceDesc.h"
#include "GraphicsDeviceType.h"
#include "detail/DX9/DirectGraphicsDevice.h"
#include "Primitive/Color4.h"

namespace Nyx
{
	struct GraphicsDevice::PImpl
	{

		PImpl()
			:isInitialized_(false), capacity_(std::make_shared<GraphicsDeviceCapacity>()) {

				render_ = [](){};
				capacity_->LookupGraphicsDeviceCapacity(0);
		}



		bool Initialize(std::shared_ptr<Window> window, WindowMode windowMode) {
			auto hwnd = window->GetHandle();
			Assert(hwnd != nullptr);

			window->GetSize(windowSize_);
			windowMode_ = windowMode;


			// Direct3Dオブジェクトの作成
			auto  d3d = D3d9Driver::GetD3d9();
			Assert(d3d != NULL);

			auto backbufferFormat = capacity_->GetBackBufferFormat(0, windowMode);

			// D3DPresentParametersの設定
			D3DPRESENT_PARAMETERS presentParameter = {};
			ZeroMemory(&presentParameter, sizeof(D3DPRESENT_PARAMETERS));

			//パラメータの設定
			presentParameter.BackBufferWidth			= windowSize_.width;
			presentParameter.BackBufferHeight			= windowSize_.height;
			presentParameter.BackBufferFormat			= static_cast<D3DFORMAT>(backbufferFormat);
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
						Assert(hr == S_OK);
					}
				}
			}
			hr = d3dDevice->Reset(&presentParameter);
			if (FAILED(hr)) {
				DebugOutput::Trace("デバイスのリセットに失敗しました。[%s][%s]",__FILE__, __LINE__);
				throw Nyx::COMException("デバイスのリセットに失敗しました。", hr);
			}

			d3dDevice_ = D3dDevice9Ptr(d3dDevice, true);

			return isInitialized_ = true;
		}

		bool IsInitialized() {
			return isInitialized_;
		}

		void Clear(const Color4c& clearColor) {
			Assert(d3dDevice_ != nullptr);

			d3dDevice_->Clear(
				NULL, 
				NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
				D3DCOLOR_ARGB(clearColor.a, clearColor.r, clearColor.g, clearColor.b), 
				1.f, NULL);

		}

		void Render() {
			Assert(d3dDevice_ != nullptr);

			d3dDevice_->BeginScene();

			render_();

			d3dDevice_->EndScene();

			d3dDevice_->Present( NULL , NULL , NULL , NULL );
		}

		void SetRenderer(std::function<void(void)> render) {
			render_ = render;
		}

		void ShowCursor(bool showCursor) {
			Assert(d3dDevice_ != nullptr);

			isShowCursor_ = showCursor;
			d3dDevice_->ShowCursor(showCursor);
		}

		WindowMode GetWindowMode() {
			return windowMode_;
		}


		// フルスクリーン<->ウインドウの切り替え
		bool ChangeDisplayMode() {
			return true;
		}

		D3DPRESENT_PARAMETERS BuildD3dPrsentParamaeter() {
		
		}

		std::function<void(void)> render_;
		Rect2i windowSize_;
		bool isInitialized_;
		WindowMode windowMode_;
		bool isLostDevice_;
		bool isShowCursor_;
		std::shared_ptr<Window> window_;
		std::shared_ptr<GraphicsDeviceCapacity> capacity_;
		D3d9Ptr d3d_;
		D3dDevice9Ptr d3dDevice_;

	};


	GraphicsDevice::GraphicsDevice()
		:pimpl_(new PImpl())
	{

	}

	GraphicsDevice::GraphicsDevice(std::shared_ptr<Window> window, WindowMode windowMode  = WindowMode::Default)
		:pimpl_(new PImpl())
	{
		auto result = pimpl_->Initialize(window, windowMode);
		Assert(result  == true);
	}

	bool GraphicsDevice::Initialize(std::shared_ptr<Window> window, WindowMode windowMode  = WindowMode::Default)
	{
		Assert(pimpl_ != nullptr);
		if (pimpl_->IsInitialized()) {
			return pimpl_->IsInitialized();
		}

		pimpl_->Initialize(window, windowMode);
		return pimpl_->IsInitialized();
	}

	void GraphicsDevice::Clear(const Color4c& color) 
	{
		Assert(pimpl_ != nullptr);
		pimpl_->Clear(color);
	}

	void GraphicsDevice::Render() 
	{
		Assert(pimpl_ != nullptr);
		pimpl_->Render();
	}


	void GraphicsDevice::OnRender(std::function<void(void)> render) 
	{
		Assert(pimpl_ != nullptr);
		pimpl_->SetRenderer(render);
	}
}