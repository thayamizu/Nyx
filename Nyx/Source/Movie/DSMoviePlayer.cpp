#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "GUI/Window.h"
#include "Movie/DSMoviePlayer.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------
	//
	DSMoviePlayer::DSMoviePlayer()
			: mediaControl_(nullptr), mediaEvent_(nullptr), windowlessControl_(nullptr), graphBuilder_(nullptr), 
			captureGraphBuilder_(nullptr), videoMixingRenderer_(nullptr), sourceFilter_(nullptr) {

	}


	//-----------------------------------------------------------------------------------
	//
	DSMoviePlayer::DSMoviePlayer(const std::shared_ptr<Nyx::Window> window, const std::wstring& fileName)
		: mediaControl_(nullptr), mediaEvent_(nullptr), windowlessControl_(nullptr), graphBuilder_(nullptr), 
			captureGraphBuilder_(nullptr), videoMixingRenderer_(nullptr), sourceFilter_(nullptr) {
				try {
					//動画再生用のフィルタグラフを初期化
					Initialize(window);

					//動画を開く
					Open(fileName);
				}
				catch(COMException e) {
					throw e;
				}
	}
	


	//-----------------------------------------------------------------------------------
	void DSMoviePlayer::Initialize(const std::shared_ptr<Nyx::Window> window) {
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


			//VidoMixingRendererを取得
			IBaseFilter *pBaseFilter = NULL;
			hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, 
				CLSCTX_INPROC, IID_IBaseFilter, (void**)&pBaseFilter); 
			if (FAILED(hr)) {
				DebugOutput::Trace("IBaseFilterインタフェースの取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("IBaseFilterインタフェースの取得に失敗しました。", hr);
			}
			videoMixingRenderer_ = IBaseFilterPtr(pBaseFilter);


			//GraphBuilderに VideoMixingRendererフィルタを追加
			hr = graphBuilder_->AddFilter(videoMixingRenderer_.get(), L"Video Mixing Renderer9");
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}

			// レンダリング モードを設定する。
			IVMRFilterConfig* pRenderingConfig = NULL;
			hr = videoMixingRenderer_->QueryInterface(IID_IVMRFilterConfig, (LPVOID*)&pRenderingConfig);
			if (FAILED(hr)) {
				DebugOutput::Trace("IVMRFilterConfigインタフェースの取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("IVMRFilterConfigインタフェースの取得に失敗しました。", hr);
			}
			hr = pRenderingConfig->SetRenderingMode(VMRMode_Windowless);
			if (FAILED(hr)) {
				DebugOutput::Trace("SetRenderingModeメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("SetRenderingModeメソッドに失敗しました。", hr);
			}
			pRenderingConfig->Release();


			// 再生ウインドウを設定する。
			IVMRWindowlessControl *pWindowlessControl = NULL;
			hr = videoMixingRenderer_->QueryInterface(IID_IVMRWindowlessControl, (LPVOID*)&pWindowlessControl);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}
			windowlessControl_ = IVMRWindowlessControlPtr(pWindowlessControl);
			hr = windowlessControl_->SetVideoClippingWindow(window->GetHandle());
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}

			//CaptureGraphBuilder2インタフェースの取得
			ICaptureGraphBuilder2 *pCGB2 = NULL;
			hr = CoCreateInstance( CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pCGB2);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}
			captureGraphBuilder_ = ICaptureGraphBuilder2Ptr(pCGB2);


			//フィルタグラフにグラフビルダーを追加
			hr = captureGraphBuilder_->SetFiltergraph(graphBuilder_.get());
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilterメソッドに失敗しました。", hr);
			}


			//クライアントウインドウのサイズを覚えておく
			Rect2i clientSize;
			window->GetSize(&clientSize);
			SetRect(&clientRect_, 0, 0, clientSize.width, clientSize.height);

			Assert(graphBuilder_  != nullptr);
			Assert(mediaControl_  != nullptr);
			Assert(mediaEvent_    != nullptr);
			Assert(windowlessControl_     != nullptr);
			Assert(captureGraphBuilder_   != nullptr);
			Assert(videoMixingRenderer_   != nullptr);
	}


	//-----------------------------------------------------------------------------------
	void DSMoviePlayer::Open(const std::wstring& fileName) {
		//ソースフィルタにファイルを接続する
		IBaseFilter *pSource = NULL;
		HRESULT hr  = graphBuilder_->AddSourceFilter(fileName.c_str(), fileName.c_str(), &pSource);
		if (FAILED(hr)) {
			DebugOutput::Trace("AddSourceFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("AddSourceFilterメソッドに失敗しました。", hr);
		}
		sourceFilter_ = IBaseFilterPtr(pSource);


		// ネイティブ ビデオ サイズを取得する。
		long width, height;
		hr = windowlessControl_->GetNativeVideoSize(&width, &height, NULL, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("AddFilterメソッドに失敗しました。", hr);
		}
		
		//転送元矩形を設定
		RECT src = {0, 0, width, height};
		hr = windowlessControl_->SetVideoPosition(&src, &clientRect_);
		if (FAILED(hr)) {
			DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("AddFilterメソッドに失敗しました。", hr);
		}

		//ビデオレンダラにソースフィルタを接続
		hr = captureGraphBuilder_->RenderStream(0, 0, sourceFilter_.get(), 0, videoMixingRenderer_.get());
		if (FAILED(hr)) {
			DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("AddFilterメソッドに失敗しました。", hr);
		}

		
		//オーディオレンダラにソースフィルタを接続
		hr = captureGraphBuilder_->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0);
		if (FAILED(hr)) {
			DebugOutput::Trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("AddFilterメソッドに失敗しました。", hr);
		}

		return true;
	}


	//-----------------------------------------------------------------------------------
	//
	void DSMoviePlayer::Close() {
		Assert(sourceFilter_ != nullptr);
		Assert(graphBuilder_ != nullptr);
		HRESULT hr = graphBuilder_->RemoveFilter(sourceFilter_.get());
		if (FAILED(hr)) {
			DebugOutput::Trace("RemoveFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("RemoveFilterメソッドに失敗しました。", hr);
		}
	}

	
	//-----------------------------------------------------------------------------------
	//
	void DSMoviePlayer::Play() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Run();
		if (FAILED(hr)) {
			DebugOutput::Trace("動画の再生に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("動画の再生に失敗しました。", hr);
		}
	}


	
	//-----------------------------------------------------------------------------------
	//
	void DSMoviePlayer::Stop() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Stop();
		if (FAILED(hr)) {
			DebugOutput::Trace("動画の停止に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("動画の停止に失敗しました。", hr);
		}
	}


	//-----------------------------------------------------------------------------------
	//
	void DSMoviePlayer::Pause() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr  =mediaControl_->Pause();
		if (FAILED(hr)) {
			DebugOutput::Trace("動画の一時停止に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("動画の一時停止に失敗しました。", hr);
		}
	}


	//-----------------------------------------------------------------------------------
	//
	void DSMoviePlayer::Resume() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Run();
		if (FAILED(hr)) {
			DebugOutput::Trace("動画の再開に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("動画の再開に失敗しました。", hr);
		}
	}
};