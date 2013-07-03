#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "GUI/Window.h"
#include "Movie/DSMoviePlayer.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------
	DSMoviePlayer::DSMoviePlayer(HWND hwnd)
		:mediaControl_(nullptr), mediaEvent_(nullptr), windowlessControl_(nullptr), graphBuilder_(nullptr) {
			Assert(graphBuilder_  == nullptr);
			Assert(mediaControl_  == nullptr);
			Assert(mediaEvent_    == nullptr);
			Assert(windowlessControl_   == nullptr);

			//GraphBuilder を構築
			IGraphBuilder *pGraphBuilder = NULL;
			HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL,
				CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID *)&pGraphBuilder);
			if (FAILED(hr)) {
				DebugOutput::Trace("GraphBuilderの作成に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("GraphBuilderの作成に失敗しました。", hr);
			}
			graphBuilder_ = IGraphBuilderPtr(pGraphBuilder);

			//MediaControlインタフェースを取得
			IMediaControl *pMediaControl = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaControl,
				(LPVOID *)&pMediaControl);
			if (FAILED(hr)) {
				DebugOutput::Trace("IMediaControlインタフェースの取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("IMediaControlインタフェースの取得に失敗しました。", hr);
			}
			mediaControl_ = IMediaControlPtr(pMediaControl);

			//IMediaEventExインタフェースを取得
			IMediaEventEx *pMediaEvent = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaEventEx,
				(LPVOID *)&pMediaEvent);
			if (FAILED(hr)) {
				DebugOutput::Trace("IMediaEventExインタフェースの取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("IMediaEventExインタフェースの取得に失敗しました。", hr);
			}
			mediaEvent_ = IMediaEventExPtr(pMediaEvent);


			IBaseFilter *pBaseFilter = NULL;
			hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, 
				CLSCTX_INPROC, IID_IBaseFilter, (void**)&pBaseFilter); 
			if (FAILED(hr)) {
				DebugOutput::Trace("IBaseFilterインタフェースの取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("IBaseFilterインタフェースの取得に失敗しました。", hr);
			}
			baseFilter_ = IBaseFilterPtr(pBaseFilter);

			hr = graphBuilder_->AddFilter(baseFilter_.get(), L"Video Mixing Renderer9");
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}

			// レンダリング モードを設定する。
			IVMRFilterConfig* pRenderingConfig = NULL;
			hr = baseFilter_->QueryInterface(IID_IVMRFilterConfig, (LPVOID*)&pRenderingConfig);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}


			hr = pRenderingConfig->SetRenderingMode(VMRMode_Windowless);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}
			pRenderingConfig->Release();

			// ウィンドウを設定する。
			IVMRWindowlessControl *pWindowlessControl = NULL;
			hr = baseFilter_->QueryInterface(IID_IVMRWindowlessControl, (LPVOID*)&pWindowlessControl);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}
			windowlessControl_ = IVMRWindowlessControlPtr(pWindowlessControl);

			hr = windowlessControl_->SetVideoClippingWindow(hwnd);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}

			IBaseFilter *pSource;
			hr  = graphBuilder_->AddSourceFilter(L"中川かのん.mp4", L"中川かのん.mp4", &pSource);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}
			sourceFilter_ = IBaseFilterPtr(pSource);

			
			ICaptureGraphBuilder2 *pCGB2 = NULL;
			hr = CoCreateInstance( CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pCGB2);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}
			captureGraphBuilder_ = ICaptureGraphBuilder2Ptr(pCGB2);

			hr = captureGraphBuilder_->SetFiltergraph(graphBuilder_.get());
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}
			hr = pCGB2->RenderStream(0, 0, sourceFilter_.get(), 0, baseFilter_.get());
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}
			// ネイティブ ビデオ サイズを取得する。
			long width, height;
			hr = windowlessControl_->GetNativeVideoSize(&width, &height, NULL, NULL);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}

			RECT src = {};
			src.right = width;
			src.bottom = height;

			RECT dest = {};
			dest.right = 800;
			dest.bottom = 600;
			hr = windowlessControl_->SetVideoPosition(&src, &dest);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}
			pCGB2->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0);
			Assert(graphBuilder_  != nullptr);
			Assert(mediaControl_  != nullptr);
			Assert(mediaEvent_    != nullptr);
			Assert(windowlessControl_   != nullptr);
	}


	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::Open(const std::wstring& fileName) {
		BSTR  name = ::SysAllocString(fileName.c_str());
		
		HRESULT hr = graphBuilder_->RenderFile(name, NULL);
		if (FAILED(hr)) {
			return false;
		}

       
		return true;
	}


	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::Close() {
		return true;
	}


	//-----------------------------------------------------------------------------------
	void DSMoviePlayer::Play() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Run();
		if (FAILED(hr)) {
			DebugOutput::Trace("動画の再生に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("動画の再生に失敗しました。", hr);
		}
	}


	//-----------------------------------------------------------------------------------
	void DSMoviePlayer::Stop() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Stop();
		if (FAILED(hr)) {
			DebugOutput::Trace("動画の停止に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("動画の停止に失敗しました。", hr);
		}
	}


	//-----------------------------------------------------------------------------------
	void DSMoviePlayer::Pause() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr  =mediaControl_->Pause();
		if (FAILED(hr)) {
			DebugOutput::Trace("動画の一時停止に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("動画の一時停止に失敗しました。", hr);
		}
	}


	//-----------------------------------------------------------------------------------
	void DSMoviePlayer::Resume() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Run();
		if (FAILED(hr)) {
			DebugOutput::Trace("動画の再開に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("動画の再開に失敗しました。", hr);
		}
	}
};