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
			isInitialized_(false), adapterCount_(), deviceCaps_(), displayMode_()
		{
		}

		bool             isInitialized_;
		uint             adapterCount_;
		D3DCAPS9         deviceCaps_;
		D3DDISPLAYMODE   displayMode_;
	};

	GraphicsDeviceCapacity::GraphicsDeviceCapacity()
		: pimpl_ (std::make_shared<PImpl>())
	{
		Assert(pimpl_ != nullptr);
		auto d3d = D3d9Driver::GetD3d9();
		pimpl_->adapterCount_ = d3d->GetAdapterCount();
	}

	void GraphicsDeviceCapacity::LookupGraphicsDeviceCapacity(const uint adapter = 0)
	{
		Assert(adapter >= 0);
		Assert(adapter <  pimpl_->adapterCount_);

		auto d3d = D3d9Driver::GetD3d9();

		//プライマリディスプレイのアダプタディスプレイモードを取得
		ZeroMemory(&pimpl_->displayMode_,sizeof(D3DDISPLAYMODE));
		auto hr = d3d->GetAdapterDisplayMode(adapter, &pimpl_->displayMode_);
		if (FAILED(hr)) {
			DebugOutput::Trace("プライマリディスプレイのアダプタの取得に失敗しました。[%s][%s]", __FILE__, __LINE__);
			throw Nyx::COMException("プライマリディスプレイのアダプタの取得に失敗しました。", hr);
		}

		//デバイス能力の取得
		ZeroMemory(&pimpl_->deviceCaps_,sizeof(D3DCAPS9));
		hr = d3d->GetDeviceCaps(adapter, D3DDEVTYPE_HAL, &pimpl_->deviceCaps_);
		if (FAILED(hr)) {
			DebugOutput::Trace("プライマリディスプレイのアダプタの取得に失敗しました。[%s][%s]", __FILE__, __LINE__);
			throw Nyx::COMException("プライマリディスプレイのアダプタの取得に失敗しました。", hr);
		}
	}	
	
	BackBufferFormat GraphicsDeviceCapacity::GetBackBufferFormat(uint adapterIndex, WindowMode windowMode)
	{
		auto d3d = D3d9Driver::GetD3d9();

		std::vector<D3DFORMAT> backbufferFormatList;
		if (windowMode == WindowMode::FullScreen) {
			backbufferFormatList.push_back(D3DFMT_A2B10G10R10);
		}
		backbufferFormatList.push_back(D3DFMT_A8R8G8B8);
		backbufferFormatList.push_back(D3DFMT_X8R8G8B8);
		backbufferFormatList.push_back(D3DFMT_A1R5G5B5);
		backbufferFormatList.push_back(D3DFMT_X1R5G5B5);
		backbufferFormatList.push_back(D3DFMT_R5G6B5);

		
		//ディスプレイのアダプタに最適なバックバッファフォーマットを取得する
		BackBufferFormat result = 0; 
		auto isWindowed = (windowMode == WindowMode::Windowed);
		auto displayFormat= pimpl_->displayMode_.Format;
		for (auto it = backbufferFormatList.begin(); it != backbufferFormatList.end(); ++it) {
			auto backbufferFormat = *it;
			auto hr = d3d->CheckDeviceType(adapterIndex, 
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
}