#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Utility/Exception.h"
#include "GraphicsDeviceCapacity.h"
#include "detail/DX9/DirectXDefinition.h"

namespace nyx
{
	struct graphics_capacity::PImpl
	{
		PImpl():
			isInitialized_(false), adapterIndex_(0), adapterCount_(), deviceCaps_(), displayMode_()
		{
			auto d3d = D3d9Driver::GetD3d9();
			adapterCount_ = d3d->GetAdapterCount();

			isInitialized_ = true;
		}

		void LookupGraphicsDeviceCapacity() {
			auto d3d = D3d9Driver::GetD3d9();

			//プライマリディスプレイのアダプタディスプレイモードを取得
			auto adapter = adapterIndex_;
			ZeroMemory(&displayMode_,sizeof(D3DDISPLAYMODE));
			auto hr = d3d->GetAdapterDisplayMode(adapter, &displayMode_);
			if (FAILED(hr)) {
				debug_out::trace("プライマリディスプレイのアダプタの取得に失敗しました。[%s][%s]", __FILE__, __LINE__);
				throw nyx::com_exception("プライマリディスプレイのアダプタの取得に失敗しました。", hr);
			}

			//デバイス能力の取得
			ZeroMemory(&deviceCaps_,sizeof(D3DCAPS9));
			hr = d3d->GetDeviceCaps(adapter, D3DDEVTYPE_HAL, &deviceCaps_);
			if (FAILED(hr)) {
				debug_out::trace("プライマリディスプレイのアダプタの取得に失敗しました。[%s][%s]", __FILE__, __LINE__);
				throw nyx::com_exception("プライマリディスプレイのアダプタの取得に失敗しました。", hr);
			}
		}

		void SetAdapterIndex(uint32_t adapterIndex) {
			adapterIndex_ = adapterIndex;
		}
		
		void SetWindowMode(WINDOW_MODE windowMode) {
			windowMode_ = windowMode;
		}


		back_buffer_format GetBackBufferFormat() {
			auto d3d = D3d9Driver::GetD3d9();

			std::vector<D3DFORMAT> backbufferFormatList;
			if (windowMode_ == WINDOW_MODE::WINDOW_MODE_FULL_SCREEN) {
				backbufferFormatList.push_back(D3DFMT_A2B10G10R10);
			}
			backbufferFormatList.push_back(D3DFMT_A8R8G8B8);
			backbufferFormatList.push_back(D3DFMT_X8R8G8B8);
			backbufferFormatList.push_back(D3DFMT_A1R5G5B5);
			backbufferFormatList.push_back(D3DFMT_X1R5G5B5);
			backbufferFormatList.push_back(D3DFMT_R5G6B5);


			//ディスプレイのアダプタに最適なバックバッファフォーマットを取得する
			back_buffer_format result = 0; 
			auto adapter    = adapterIndex_;
			auto isWindowed = (windowMode_ == WINDOW_MODE::WINDOW_MODE_WINDOWED);
			auto displayFormat = displayMode_.Format;
			for (auto it = backbufferFormatList.begin(); it != backbufferFormatList.end(); ++it) {
				auto backbufferFormat = *it;
				auto hr = d3d->CheckDeviceType(adapter, 
					D3DDEVTYPE_HAL,
					displayFormat, 
					backbufferFormat,
					isWindowed
					);
				if (SUCCEEDED(hr)) {
					result = backbufferFormat;
					break;			
				}
			}

			return result;
		}


		stencil_buffer_format GetDepthStencilFormat() {
			auto d3d = D3d9Driver::GetD3d9();

			std::vector<D3DFORMAT> depthStencilFormatList;
			depthStencilFormatList.push_back(D3DFMT_D24S8);
			depthStencilFormatList.push_back(D3DFMT_D24X4S4);
			depthStencilFormatList.push_back(D3DFMT_D24FS8);
			depthStencilFormatList.push_back(D3DFMT_D15S1);


			//ディスプレイのアダプタに最適なステンシルバッファフォーマットを取得する
			stencil_buffer_format result = 0; 
			auto displayFormat = displayMode_.Format;
			for (auto it = depthStencilFormatList.begin(); it != depthStencilFormatList.end(); ++it) {
				auto depthStencilFormat = *it;
				auto hr = d3d->CheckDeviceFormat(
					adapterIndex_, 
					D3DDEVTYPE_HAL,
					displayFormat,
					D3DUSAGE_DEPTHSTENCIL, 
					D3DRTYPE_SURFACE,
					depthStencilFormat
					);
				if (FAILED(hr)) {
					continue;
				}

				auto backBufferFormat = static_cast<D3DFORMAT>(GetBackBufferFormat());
				hr = d3d->CheckDepthStencilMatch(
					adapterIndex_,
					D3DDEVTYPE_HAL,
					displayFormat,
					backBufferFormat,
					depthStencilFormat);
				if (FAILED(hr)) {
					continue;
				} 

				result = depthStencilFormat;
				break;
			}

			return result;
		}


		bool CheckBufferFormat(const format_type backBufferFormat) {
			auto isWindowed = windowMode_ == WINDOW_MODE::WINDOW_MODE_DEFAULT ? true: false;
			auto format     = static_cast<D3DFORMAT>(backBufferFormat);

			auto d3d = D3d9Driver::GetD3d9();
			auto hr = d3d->CheckDeviceType(adapterIndex_, 
				D3DDEVTYPE_HAL,
				displayMode_.Format, 
				format,
				isWindowed
				);

			return SUCCEEDED(hr);
		}


		bool GetSupportedMultiSamplingQuality(uint64_t samplingLevel, format_type formatType, uint64_t* quality) {
			auto d3d    = D3d9Driver::GetD3d9();
			auto format = static_cast<D3DFORMAT>(formatType);
			auto isWindowed = windowMode_ == WINDOW_MODE::WINDOW_MODE_DEFAULT;
			auto hr  = d3d->CheckDeviceMultiSampleType(
				adapterIndex_, 
				D3DDEVTYPE_HAL, 
				format, isWindowed, 
				static_cast<D3DMULTISAMPLE_TYPE>(samplingLevel), 
				quality);

			return SUCCEEDED(hr);
		}

		uint32_t			 adapterIndex_;
		bool             isInitialized_;
		uint32_t             adapterCount_;
		D3DCAPS9         deviceCaps_;
		D3DDISPLAYMODE   displayMode_;
		WINDOW_MODE       windowMode_;
	};

	graphics_capacity::graphics_capacity()
		: pimpl_ (std::make_shared<PImpl>())
	{
		NYX_ASSERT(pimpl_ != nullptr);
	}


	void graphics_capacity::set_adapter_index(uint32_t adapterIndex) {
		NYX_ASSERT(pimpl_->isInitialized_ == true);
		pimpl_->SetAdapterIndex(adapterIndex);
	}


	void graphics_capacity::set_window_mode(WINDOW_MODE windowMode) {
		NYX_ASSERT(pimpl_->isInitialized_ == true);
		pimpl_->SetWindowMode(windowMode);
	}

	void graphics_capacity::lookup_graphics_device()
	{	
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		NYX_ASSERT(pimpl_->adapterIndex_ >= 0);
		NYX_ASSERT(pimpl_->adapterIndex_ <  pimpl_->adapterCount_);

		pimpl_->LookupGraphicsDeviceCapacity();
	}	
	

	//-----------------------------------------------------------------------------------
	//
	uint32_t graphics_capacity::get_adapter_count() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		return pimpl_->adapterCount_;
	}


	//-----------------------------------------------------------------------------------
	//
	back_buffer_format graphics_capacity::get_back_buffer_format()
	{
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		return pimpl_->GetBackBufferFormat();
	}


	//-----------------------------------------------------------------------------------
	//
	back_buffer_format graphics_capacity::get_depth_stencil_buffer_format()
	{
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		return pimpl_->GetDepthStencilFormat();
	}
	


	//-----------------------------------------------------------------------------------
	//
	bool graphics_capacity::get_supported_multisampling_level(uint64_t samplingLevel, format_type formatType, uint64_t* quality) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->isInitialized_);
		NYX_ASSERT(0 <= samplingLevel && samplingLevel < 16);

		return pimpl_->GetSupportedMultiSamplingQuality(samplingLevel, formatType, quality);
	}

}