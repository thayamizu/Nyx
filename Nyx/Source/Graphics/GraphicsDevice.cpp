#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Utility/Exception.h"
#include "GUI/Window.h"
#include "GraphicsDevice.h"
#include "GraphicsDeviceCapacity.h"
#include "GraphicsDeviceType.h"
#include "detail/DX9/DirectXDefinition.h"
#include "Primitive/Color4.h"

namespace nyx
{
	//実装
	struct graphics_device::PImpl
	{
		std::vector<vector3f> verticies_;
		std::shared_ptr<void> obj_;
		std::function<void(std::shared_ptr<void>)> render_;
		rect2i windowSize_;
		bool isInitialized_;
		WINDOW_MODE windowMode_;
		bool isLostDevice_;
		bool isShowCursor_;
		std::shared_ptr<window> window_;
		std::shared_ptr<graphics_capacity> capacity_;
		sampling_level multiSamplingLevel_;
		D3dStateBlock9Ptr stateBlock_;
		PImpl()
			:isInitialized_(false), capacity_(std::make_shared<graphics_capacity>()), stateBlock_(nullptr) {

			
				isLostDevice_ = false;

		}


		//-----------------------------------------------------------------------------------
		//
		bool Initialize(std::shared_ptr<window> window, WINDOW_MODE windowMode, sampling_level samplingLevel) {
			window_ = window;
			NYX_ASSERT(window_ != nullptr);

			//ウインドウ情報
			window->get_size(windowSize_);
			windowMode_ = windowMode;
			
			//デバイスロスト
			isLostDevice_ = false;

			//サンプリングレベル
			multiSamplingLevel_ = samplingLevel;

			//デバイスキャパシティの取得
			capacity_->set_adapter_index(0);
			capacity_->set_window_mode(windowMode_);
			capacity_->lookup_graphics_device();


			return isInitialized_ = InitializeD3d9(window_, windowMode_, capacity_,  multiSamplingLevel_);
		}



		//-----------------------------------------------------------------------------------
		//
		bool IsInitialized() {
			return isInitialized_;
		}



		//-----------------------------------------------------------------------------------
		//
		void Clear(const color4c& clearColor) {

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

			auto hr = d3dDevice->BeginScene();
			render_(obj_);
			d3dDevice->EndScene();
			
			hr = d3dDevice->Present( NULL , NULL , NULL , NULL );
			if (hr == D3DERR_DEVICELOST) {
				OnDeviceLost();
			}
		}

		void SetRenderer(std::function<void(std::shared_ptr<void>)> render) {
			render_ = render;
		}


		//-----------------------------------------------------------------------------------
		WINDOW_MODE GetWindowMode() {
			return windowMode_;
		}

		//-----------------------------------------------------------------------------------
		void SetWindowMode(WINDOW_MODE windowMode) {
			windowMode_ = windowMode;
			capacity_->set_window_mode(windowMode);
		}

		//-----------------------------------------------------------------------------------
		// フルスクリーン<->ウインドウの切り替え
		bool ChangeDisplayMode() {
			if (windowMode_ == WINDOW_MODE::WINDOW_MODE_DEFAULT) {
				SetWindowMode(WINDOW_MODE::WINDOW_MODE_FULL_SCREEN);
			}
			else {
				SetWindowMode(WINDOW_MODE::WINDOW_MODE_DEFAULT);
			}


			return OnDeviceReset();
		}


		//-----------------------------------------------------------------------------------
		//
		void SetViewport(const rect2i& rect, float minZ, float maxZ) {
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
		void SetWorldMatrix(const matrix& world) {
			D3DXMATRIX w = {};
			CopyMemory(&w, world.mat_, sizeof(D3DMATRIX));

			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			d3dDevice->SetTransform(D3DTS_WORLD, &w);
		}

		//-----------------------------------------------------------------------------------
		//
		void SetProjectionMatrix(const matrix& proj) {
			D3DXMATRIX p = {};
			CopyMemory(&p, proj.mat_, sizeof(D3DMATRIX));

			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			d3dDevice->SetTransform(D3DTS_PROJECTION, &p);
		}

		//-----------------------------------------------------------------------------------
		//
		void SetViewMatrix(const matrix& view) {
			D3DXMATRIX v = {};
			CopyMemory(&v, view.mat_, sizeof(D3DMATRIX));

			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			d3dDevice->SetTransform(D3DTS_VIEW, &v);
		}

		void EnableZBuffer(bool enable) {
			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			d3dDevice->SetRenderState(D3DRS_ZENABLE, enable);
		}
		//-----------------------------------------------------------------------------------
		//
		void BeginStateBlock() {
			LPDIRECT3DSTATEBLOCK9 stateBlock;
			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			d3dDevice->CreateStateBlock(D3DSBT_ALL, &stateBlock);

			stateBlock_ = D3dStateBlock9Ptr(stateBlock, false);
		}

		//-----------------------------------------------------------------------------------
		//
		void EndStateBlock() {
			stateBlock_.reset();
		}

		//-----------------------------------------------------------------------------------
		//
		void ApplyStateBlock() {
			if (stateBlock_ == nullptr) {
				return;
			}
			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			stateBlock_->Apply();
		}
		//-----------------------------------------------------------------------------------
		//
		void OnRender(std::function<void(std::shared_ptr<void>)> render) {
			render_ = render;
		}


		//-----------------------------------------------------------------------------------
		//
		bool OnDeviceReset() {
			resource_cache::release();

			auto d3dpp = BuildPresentParameter(window_, windowMode_, capacity_, multiSamplingLevel_);
			auto hr = D3d9Driver::GetD3dDevice9()->Reset(&d3dpp);
			auto result = true;

			if (FAILED(hr)) {
				debug_out::trace("デバイスリセットに失敗しました。[%s][%s][%d]", DXGetErrorStringA(hr), __FILE__, __LINE__);
				result = false;
			}
			else {
				//ビューポートの設定
				SetViewport(windowSize_, 0.f, 1.f);

				resource_cache::recover();
			}

			
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


	graphics_device::graphics_device()
		:pimpl_(new PImpl())
	{

	}

	graphics_device::graphics_device(std::shared_ptr<window> window, WINDOW_MODE windowMode  = WINDOW_MODE::WINDOW_MODE_DEFAULT, sampling_level level = 0)
		:pimpl_(new PImpl())
	{
		auto result = pimpl_->Initialize(window, windowMode, level);
		NYX_ASSERT(result  == true);
	}

	bool graphics_device::initialize(std::shared_ptr<window> window, WINDOW_MODE windowMode  = WINDOW_MODE::WINDOW_MODE_DEFAULT, sampling_level level = 0)
	{
		NYX_ASSERT(pimpl_ != nullptr);
		if (pimpl_->IsInitialized()) {
			return pimpl_->IsInitialized();
		}

		pimpl_->Initialize(window, windowMode, level);
		return pimpl_->IsInitialized();
	}

	WINDOW_MODE graphics_device::get_window_mode() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->IsInitialized());

		return pimpl_->GetWindowMode();
	}

	void graphics_device::change_window_mode() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->IsInitialized());

		pimpl_->ChangeDisplayMode();
	}


	void graphics_device::clear(const color4c& color) 
	{
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);

		pimpl_->Clear(color);
	}

	void graphics_device::render() 
	{
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		pimpl_->Render();
	}

	void graphics_device::on_render(std::function<void(std::shared_ptr<void>)> scene)
	{
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		pimpl_->SetRenderer(scene);
	}

	void graphics_device::set_view_port(const rect2i& rect, float minZ, float maxZ)
	{
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		pimpl_->SetViewport(rect, minZ, maxZ);
	}


	//ステート
	void graphics_device::enable_z_buffer(bool enable) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		pimpl_->EnableZBuffer(enable);
	}
	

	//トランスフォーム
	void graphics_device::set_world(const matrix& world) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		pimpl_->SetWorldMatrix(world);
	}

	void graphics_device::set_modelview(const matrix& view) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		pimpl_->SetViewMatrix(view);

	}
	void graphics_device::set_projection(const matrix& proj) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		pimpl_->SetProjectionMatrix(proj);
	}

	void graphics_device::begin_state_block() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		pimpl_->BeginStateBlock();
	}
	void graphics_device::end_state_block() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		pimpl_->EndStateBlock();
	}
	void graphics_device::apply_state_block() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		pimpl_->ApplyStateBlock();
	}

	void graphics_device::set_vertex_buffer(std::vector<vector3f> verticies) {
		pimpl_->verticies_ = verticies;
	}

	void graphics_device::set_scene(std::shared_ptr<void> obj) {
		pimpl_->obj_ = obj;
	}
}