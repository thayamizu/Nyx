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
	//実装
	struct GraphicsDevice::PImpl
	{
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
		MultiSamplingLevel multiSamplingLevel_;
		PImpl()
			:isInitialized_(false), capacity_(std::make_shared<GraphicsDeviceCapacity>()) {

				render_ = [](){};
				isLostDevice_ = false;

		}


		//-----------------------------------------------------------------------------------
		//
		bool Initialize(std::shared_ptr<Window> window, WindowMode windowMode, MultiSamplingLevel samplingLevel) {
			window_ = window;
			auto hwnd = window->GetHandle();
			Assert(hwnd != nullptr);

			//ウインドウ情報
			window->GetSize(windowSize_);
			windowMode_ = windowMode;
			//
			isLostDevice_ = false;

			//
			multiSamplingLevel_ = samplingLevel;

			//デバイスキャパシティの取得
			capacity_->SetAdapterIndex(0);
			capacity_->SetWindowMode(windowMode_);
			capacity_->LookupGraphicsDeviceCapacity();

			// Direct3Dオブジェクトの作成
			auto  d3d = D3d9Driver::GetD3d9();
			Assert(d3d != NULL);

			//Direct3DDeviceオブジェクトの生成
			D3DPRESENT_PARAMETERS presentParameter = BuildPresentParameter(samplingLevel);
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
			d3dDevice_->ShowCursor(FALSE);

			return isInitialized_ = true;
		}



		//-----------------------------------------------------------------------------------
		//
		bool IsInitialized() {
			return isInitialized_;
		}



		//-----------------------------------------------------------------------------------
		//
		void Clear(const Color4c& clearColor) {
			Assert(d3dDevice_ != nullptr);

			d3dDevice_->Clear(
				NULL, 
				NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
				D3DCOLOR_ARGB(clearColor.a, clearColor.r, clearColor.g, clearColor.b), 
				1.f, NULL);
		}



		//-----------------------------------------------------------------------------------
		//
		void Render() {
			Assert(d3dDevice_ != nullptr);

			d3dDevice_->BeginScene();

			render_();

			d3dDevice_->EndScene();

			auto hr = d3dDevice_->Present( NULL , NULL , NULL , NULL );
			if (hr == D3DERR_DEVICELOST) {
				OnDeviceLost();
			}
		}

		void SetRenderer(std::function<void(void)> render) {
			render_ = render;
		}


		//-----------------------------------------------------------------------------------
		WindowMode GetWindowMode() {
			return windowMode_;
		}

		//-----------------------------------------------------------------------------------
		void SetWindowMode(WindowMode windowMode) {
			windowMode_ = windowMode;
			capacity_->SetWindowMode(windowMode);
		}

		//-----------------------------------------------------------------------------------
		// フルスクリーン<->ウインドウの切り替え
		bool ChangeDisplayMode() {
			if (windowMode_ == WindowMode::Default) {
				SetWindowMode(WindowMode::FullScreen);
			}
			else {
				SetWindowMode(WindowMode::Default);
			}


			return OnDeviceReset();
		}


		//-----------------------------------------------------------------------------------
		//
		void SetViewport(const Rect2i& rect, float minZ, float maxZ) {
			D3DVIEWPORT9 vp = {};
			ZeroMemory(&vp, sizeof(D3DVIEWPORT9));
			vp.X  = rect.x;
			vp.Y  = rect.y;
			vp.Width  = rect.width;
			vp.Height = rect.height;
			vp.MinZ=minZ;
			vp.MaxZ=maxZ;
			d3dDevice_->SetViewport(&vp);
		}



		//-----------------------------------------------------------------------------------
		//
		void OnRender(std::function<void(void)> render) {
			render_ = render;
		}


		//-----------------------------------------------------------------------------------
		//
		bool OnDeviceReset() {
			auto d3dpp = BuildPresentParameter(multiSamplingLevel_);
			auto hr = d3dDevice_->Reset(&d3dpp);
			auto result = true;

			switch(hr) {
			case D3DERR_INVALIDCALL: 
				DebugOutput::DebugMessage("無効な呼び出しです");
				result =  false;
			case D3DERR_DEVICELOST:
				DebugOutput::DebugMessage("デバイスロスト");
				isLostDevice_= true;
				result =  false;
			case D3DERR_DRIVERINTERNALERROR: 
				DebugOutput::DebugMessage("ドライバー内部エラー");
				PostQuitMessage(0);//強制終了
				result =  false;
			}

			//ビューポートの設定
			SetViewport(windowSize_, 0.f, 1.f);

			return result;
		}


		//-----------------------------------------------------------------------------------
		//
		bool OnDeviceLost() {
			// デバイスのリセットが出来るかを調べる
			if (d3dDevice_->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
				// デバイスをリセットする
				if (OnDeviceReset()) {
					isLostDevice_ = false;
				}
				else {
					return false;	
				}
			}
			else {
				return false;
			}
			return true;;
		}


		//-----------------------------------------------------------------------------------
		//
		D3DPRESENT_PARAMETERS BuildPresentParameter(MultiSamplingLevel samplingLevel) {

			// D3DPresentParametersの設定
			D3DPRESENT_PARAMETERS presentParameter = {};
			ZeroMemory(&presentParameter, sizeof(D3DPRESENT_PARAMETERS));

			//パラメータの取得
			auto backbufferFormat    = capacity_->GetBackBufferFormat();
			auto stencilBufferFormat = capacity_->GetDepthStencilBufferFormat();
			auto level = static_cast<D3DMULTISAMPLE_TYPE>(samplingLevel);
			ulong quality = NULL;
			capacity_->GetSupportedMultiSamplingQuality(samplingLevel, backbufferFormat, &quality);
			if (quality != NULL) {
				--quality;
			}

			//パラメータの設定
			presentParameter.BackBufferWidth			= windowSize_.width;
			presentParameter.BackBufferHeight			= windowSize_.height;
			presentParameter.BackBufferFormat			= static_cast<D3DFORMAT>(backbufferFormat);
			presentParameter.BackBufferCount			= 1;
			presentParameter.MultiSampleType			= level;
			presentParameter.MultiSampleQuality			= quality;
			presentParameter.SwapEffect					= D3DSWAPEFFECT_DISCARD;
			presentParameter.hDeviceWindow				= window_->GetHandle();
			presentParameter.Windowed					= windowMode_ == WindowMode::Default ? true: false;
			presentParameter.EnableAutoDepthStencil		= true;
			presentParameter.AutoDepthStencilFormat		= static_cast<D3DFORMAT>(stencilBufferFormat);
			presentParameter.Flags						= NULL;
			presentParameter.FullScreen_RefreshRateInHz = NULL;
			presentParameter.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;


			return presentParameter;
		}
	};


	GraphicsDevice::GraphicsDevice()
		:pimpl_(new PImpl())
	{

	}

	GraphicsDevice::GraphicsDevice(std::shared_ptr<Window> window, WindowMode windowMode  = WindowMode::Default, MultiSamplingLevel level = 0)
		:pimpl_(new PImpl())
	{
		auto result = pimpl_->Initialize(window, windowMode, level);
		Assert(result  == true);
	}

	bool GraphicsDevice::Initialize(std::shared_ptr<Window> window, WindowMode windowMode  = WindowMode::Default, MultiSamplingLevel level = 0)
	{
		Assert(pimpl_ != nullptr);
		if (pimpl_->IsInitialized()) {
			return pimpl_->IsInitialized();
		}

		pimpl_->Initialize(window, windowMode, level);
		return pimpl_->IsInitialized();
	}

	WindowMode GraphicsDevice::GetWindowMode() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->IsInitialized());

		return pimpl_->GetWindowMode();
	}

	void GraphicsDevice::ChangeWindowMode() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->IsInitialized());

		pimpl_->ChangeDisplayMode();
	}


	void GraphicsDevice::Clear(const Color4c& color) 
	{
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized_);

		pimpl_->Clear(color);
	}

	void GraphicsDevice::Render() 
	{
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized_);
		pimpl_->Render();
	}


	void GraphicsDevice::SetViewport(const Rect2i& rect, float minZ, float maxZ)
	{
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized_);
		pimpl_->SetViewport(rect, minZ, maxZ);
	}
}