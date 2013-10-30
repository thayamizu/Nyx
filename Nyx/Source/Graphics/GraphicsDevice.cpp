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
			Assert(window_ != nullptr);

			//ウインドウ情報
			window->GetSize(windowSize_);
			windowMode_ = windowMode;
			
			//デバイスロスト
			isLostDevice_ = false;

			//サンプリングレベル
			multiSamplingLevel_ = samplingLevel;

			//デバイスキャパシティの取得
			capacity_->SetAdapterIndex(0);
			capacity_->SetWindowMode(windowMode_);
			capacity_->LookupGraphicsDeviceCapacity();


			return isInitialized_ = InitializeD3d9(window_, windowMode_, capacity_,  multiSamplingLevel_);
		}



		//-----------------------------------------------------------------------------------
		//
		bool IsInitialized() {
			return isInitialized_;
		}



		//-----------------------------------------------------------------------------------
		//
		void Clear(const Color4c& clearColor) {

			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			d3dDevice->Clear(
				NULL, 
				NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
				D3DCOLOR_ARGB(clearColor.a, clearColor.r, clearColor.g, clearColor.b), 
				1.f, NULL);
		}



		//-----------------------------------------------------------------------------------
		//
		void Render() {
			auto d3dDevice = D3d9Driver::GetD3dDevice9();

			d3dDevice->BeginScene();

			render_();

			d3dDevice->EndScene();

			auto hr = d3dDevice->Present( NULL , NULL , NULL , NULL );
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

			
			D3d9Driver::GetD3dDevice9()->SetViewport(&vp);
		}



		//-----------------------------------------------------------------------------------
		//
		void OnRender(std::function<void(void)> render) {
			render_ = render;
		}


		//-----------------------------------------------------------------------------------
		//
		bool OnDeviceReset() {
			auto d3dpp = BuildPresentParameter(window_, windowMode_, capacity_, multiSamplingLevel_);
			auto hr = D3d9Driver::GetD3dDevice9()->Reset(&d3dpp);
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
			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			if (d3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
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