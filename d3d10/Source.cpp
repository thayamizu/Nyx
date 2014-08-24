#include <D3D10.h>
#include <D3DX10.h>
#include <Windows.h>
#include <DxErr.h>


#include "../Nyx/Source/NyxCore.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "dxerr.lib")

#if defined (_DEBUG) || defined(DEBUG)
	#pragma comment(lib, "d3dx10d.lib")
	#pragma comment(lib, "../Lib/Debug/Nyx_MTd.lib")
#else
	#pragma comment(lib, "d3dx10.lib")
	#pragma comment(lib, "../Lib/Release/Nyx_MT.lib")
#endif

int main()
{
	auto fpsTimer = nyx::fps_timer(120);
	auto mainWindow = std::make_shared<nyx::window>(nullptr, L"ウインドウ", L"");
	
	DXGI_SWAP_CHAIN_DESC swapChainDesc =
	{ { 800, 600, { 60, 1 }, DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED, DXGI_MODE_SCALING_CENTERED },
	{ 1, 0 }, DXGI_USAGE_RENDER_TARGET_OUTPUT, 1, mainWindow->get_handle(), true, DXGI_SWAP_EFFECT_DISCARD, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
	};

	ID3D10Device* d3d10Device = nullptr;
	IDXGISwapChain *swapChain = nullptr;

	HRESULT hr = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, 
		NULL, NULL, D3D10_SDK_VERSION, &swapChainDesc, &swapChain, &d3d10Device);
	if (FAILED(hr)) {
		nyx::debug_out::trace("failed create device\r");
		exit(-1);
	}

	ID3D10Texture2D * backBuffer = nullptr;
	ID3D10RenderTargetView * renderTargetView = nullptr;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (void**)&backBuffer);
	if (FAILED(hr)) {
		nyx::debug_out::trace("failed create back buffer");
		exit(-1);
	}
	hr = d3d10Device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	if (FAILED(hr)) {
		nyx::debug_out::trace("failed create render target view");
		exit(-1);
	}
	d3d10Device->OMSetRenderTargets(1, &renderTargetView, NULL);

	backBuffer->Release();
	D3D10_VIEWPORT viewPort = { 0, 0, 800, 600, 0.f, 1.f };
	d3d10Device->RSSetViewports(1, &viewPort);


	while (mainWindow->process_message()) {
		fpsTimer.wait_frame();

		float clearColor[4] = { 0.f, 0.125f, 0.6f, 1.0f };
		d3d10Device->ClearRenderTargetView(renderTargetView, clearColor);
		swapChain->Present(0, 0);
	}

	return 0;
}