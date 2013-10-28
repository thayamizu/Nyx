#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Utility/Exception.h"
#include "GraphicsDeviceDesc.h"
#include "GraphicsDeviceCapacity.h"
#include "detail/DX9/DirectXDefinition.h"

namespace Nyx
{
	struct GraphicsDeviceCapacity::PImpl
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
				DebugOutput::Trace("プライマリディスプレイのアダプタの取得に失敗しました。[%s][%s]", __FILE__, __LINE__);
				throw Nyx::COMException("プライマリディスプレイのアダプタの取得に失敗しました。", hr);
			}

			//デバイス能力の取得
			ZeroMemory(&deviceCaps_,sizeof(D3DCAPS9));
			hr = d3d->GetDeviceCaps(adapter, D3DDEVTYPE_HAL, &deviceCaps_);
			if (FAILED(hr)) {
				DebugOutput::Trace("プライマリディスプレイのアダプタの取得に失敗しました。[%s][%s]", __FILE__, __LINE__);
				throw Nyx::COMException("プライマリディスプレイのアダプタの取得に失敗しました。", hr);
			}
		}

		void SetAdapterIndex(uint adapterIndex) {
			adapterIndex_ = adapterIndex;
		}
		
		void SetWindowMode(WindowMode windowMode) {
			windowMode_ = windowMode;
		}


		BackBufferFormat GetBackBufferFormat() {
			auto d3d = D3d9Driver::GetD3d9();

			std::vector<D3DFORMAT> backbufferFormatList;
			if (windowMode_ == WindowMode::FullScreen) {
				backbufferFormatList.push_back(D3DFMT_A2B10G10R10);
			}
			backbufferFormatList.push_back(D3DFMT_A8R8G8B8);
			backbufferFormatList.push_back(D3DFMT_X8R8G8B8);
			backbufferFormatList.push_back(D3DFMT_A1R5G5B5);
			backbufferFormatList.push_back(D3DFMT_X1R5G5B5);
			backbufferFormatList.push_back(D3DFMT_R5G6B5);


			//ディスプレイのアダプタに最適なバックバッファフォーマットを取得する
			BackBufferFormat result = 0; 
			auto adapter    = adapterIndex_;
			auto isWindowed = (windowMode_ == WindowMode::Windowed);
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


		StencilBufferFormat GetDepthStencilFormat() {
			auto d3d = D3d9Driver::GetD3d9();

			std::vector<D3DFORMAT> depthStencilFormatList;
			depthStencilFormatList.push_back(D3DFMT_D24S8);
			depthStencilFormatList.push_back(D3DFMT_D24X4S4);
			depthStencilFormatList.push_back(D3DFMT_D24FS8);
			depthStencilFormatList.push_back(D3DFMT_D15S1);


			//ディスプレイのアダプタに最適なステンシルバッファフォーマットを取得する
			StencilBufferFormat result = 0; 
			auto isWindowed    = (windowMode_ == WindowMode::Windowed);
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
			}

			return result;
		}


		bool CheckBufferFormat(const FormatType backBufferFormat) {
			auto isWindowed = windowMode_ == WindowMode::Default ? true: false;
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


		bool GetSupportedMultiSamplingQuality(ulong samplingLevel, FormatType formatType, ulong* quality) {
			auto d3d    = D3d9Driver::GetD3d9();
			auto format = static_cast<D3DFORMAT>(formatType);
			auto isWindowed = windowMode_ == WindowMode::Default;
			auto hr  = d3d->CheckDeviceMultiSampleType(
				adapterIndex_, 
				D3DDEVTYPE_HAL, 
				format, isWindowed, 
				static_cast<D3DMULTISAMPLE_TYPE>(samplingLevel), 
				quality);

			return SUCCEEDED(hr);
		}

		uint			 adapterIndex_;
		bool             isInitialized_;
		uint             adapterCount_;
		D3DCAPS9         deviceCaps_;
		D3DDISPLAYMODE   displayMode_;
		WindowMode       windowMode_;
	};

	GraphicsDeviceCapacity::GraphicsDeviceCapacity()
		: pimpl_ (std::make_shared<PImpl>())
	{
		Assert(pimpl_ != nullptr);
	}


	void GraphicsDeviceCapacity::SetAdapterIndex(uint adapterIndex) {
		Assert(pimpl_->isInitialized_ == true);
		pimpl_->SetAdapterIndex(adapterIndex);
	}


	void GraphicsDeviceCapacity::SetWindowMode(WindowMode windowMode) {
		Assert(pimpl_->isInitialized_ == true);
		pimpl_->SetWindowMode(windowMode);
	}

	void GraphicsDeviceCapacity::LookupGraphicsDeviceCapacity()
	{	
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized_);
		Assert(pimpl_->adapterIndex_ >= 0);
		Assert(pimpl_->adapterIndex_ <  pimpl_->adapterCount_);

		pimpl_->LookupGraphicsDeviceCapacity();
	}	
	

	//-----------------------------------------------------------------------------------
	//
	uint GraphicsDeviceCapacity::GetAdapterCount() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized_);
		return pimpl_->adapterCount_;
	}


	//-----------------------------------------------------------------------------------
	//
	BackBufferFormat GraphicsDeviceCapacity::GetBackBufferFormat()
	{
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized_);
		return pimpl_->GetBackBufferFormat();
	}


	//-----------------------------------------------------------------------------------
	//
	BackBufferFormat GraphicsDeviceCapacity::GetDepthStencilBufferFormat()
	{
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized_);
		return pimpl_->GetDepthStencilFormat();
	}
	


	//-----------------------------------------------------------------------------------
	//
	bool GraphicsDeviceCapacity::GetSupportedMultiSamplingQuality(ulong samplingLevel, FormatType formatType, ulong* quality) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized_);
		Assert(0 <= samplingLevel && samplingLevel < 16);

		return pimpl_->GetSupportedMultiSamplingQuality(samplingLevel, formatType, quality);
	}

}