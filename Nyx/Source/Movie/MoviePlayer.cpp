#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "GUI/Window.h"
#include "Movie/MoviePlayer.h"
#include "DirectShowDefinition.h"

namespace nyx {

	struct movie_player::PImpl {
		//-----------------------------------------------------------------------------------
		//
		PImpl()
			: mediaControl_(nullptr), mediaEvent_(nullptr), windowlessControl_(nullptr), graphBuilder_(nullptr), 
			captureGraphBuilder_(nullptr), videoMixingRenderer_(nullptr), sourceFilter_(nullptr), isInitialized_(false) {

		}


		//-----------------------------------------------------------------------------------
		//
		PImpl(nyx::window& wnd, const std::wstring& fileName)
			: mediaControl_(nullptr), mediaEvent_(nullptr), windowlessControl_(nullptr), graphBuilder_(nullptr), 
			captureGraphBuilder_(nullptr), videoMixingRenderer_(nullptr), sourceFilter_(nullptr), isInitialized_(false) {
				try {
					//動画再生用のフィルタグラフを初期化
					if (initialize(wnd)) {
						//動画を開く
						open(fileName);
					}

				}
				catch(com_exception e) {
					throw e;
				}
		}

		//-----------------------------------------------------------------------------------
		//
		~PImpl() {
			release();
		}

		//-----------------------------------------------------------------------------------
		bool is_initialized() {
			return isInitialized_;
		}

		//-----------------------------------------------------------------------------------
		//
		bool initialize(nyx::window& wnd) {
			if (is_initialized()) {
				return is_initialized();
			}

			NYX_ASSERT(graphBuilder_  == nullptr);
			NYX_ASSERT(mediaControl_  == nullptr);
			NYX_ASSERT(mediaEvent_    == nullptr);
			NYX_ASSERT(windowlessControl_   == nullptr);

			//GraphBuilder を構築
			IGraphBuilder *pGraphBuilder = NULL;
			HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL,
				CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID *)&pGraphBuilder);
			if (FAILED(hr)) {
				debug_out::trace("GraphBuilderの作成に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("GraphBuilderの作成に失敗しました。", hr);
			}
			graphBuilder_ = IGraphBuilderPtr(pGraphBuilder);

			//MediaControlインタフェースを取得
			IMediaControl *pMediaControl = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaControl,
				(LPVOID *)&pMediaControl);
			if (FAILED(hr)) {
				debug_out::trace("IMediaControlインタフェースの取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("IMediaControlインタフェースの取得に失敗しました。", hr);
			}
			mediaControl_ = IMediaControlPtr(pMediaControl);

			//IMediaEventExインタフェースを取得
			IMediaEventEx *pMediaEvent = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaEventEx,
				(LPVOID *)&pMediaEvent);
			if (FAILED(hr)) {
				debug_out::trace("IMediaEventExインタフェースの取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("IMediaEventExインタフェースの取得に失敗しました。", hr);
			}
			mediaEvent_ = IMediaEventExPtr(pMediaEvent);


			//VidoMixingRendererを取得
			IBaseFilter *pBaseFilter = NULL;
			hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, 
				CLSCTX_INPROC, IID_IBaseFilter, (void**)&pBaseFilter); 
			if (FAILED(hr)) {
				debug_out::trace("IBaseFilterインタフェースの取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("IBaseFilterインタフェースの取得に失敗しました。", hr);
			}
			videoMixingRenderer_ = IBaseFilterPtr(pBaseFilter);


			//GraphBuilderに VideoMixingRendererフィルタを追加
			hr = graphBuilder_->AddFilter(videoMixingRenderer_.get(), L"Video Mixing Renderer9");
			if (FAILED(hr)) {
				debug_out::trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddFilterメソッドに失敗しました。", hr);
			}

			// レンダリング モードを設定する。
			IVMRFilterConfig* pRenderingConfig = NULL;
			hr = videoMixingRenderer_->QueryInterface(IID_IVMRFilterConfig, (LPVOID*)&pRenderingConfig);
			if (FAILED(hr)) {
				debug_out::trace("IVMRFilterConfigインタフェースの取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("IVMRFilterConfigインタフェースの取得に失敗しました。", hr);
			}
			hr = pRenderingConfig->SetRenderingMode(VMRMode_Windowless);
			if (FAILED(hr)) {
				debug_out::trace("SetRenderingModeメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("SetRenderingModeメソッドに失敗しました。", hr);
			}
			pRenderingConfig->Release();


			// 再生ウインドウを設定する。
			IVMRWindowlessControl *pWindowlessControl = NULL;
			hr = videoMixingRenderer_->QueryInterface(IID_IVMRWindowlessControl, (LPVOID*)&pWindowlessControl);
			if (FAILED(hr)) {
				debug_out::trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddFilterメソッドに失敗しました。", hr);
			}
			windowlessControl_ = IVMRWindowlessControlPtr(pWindowlessControl);
			hr = windowlessControl_->SetVideoClippingWindow(wnd.get_handle());
			if (FAILED(hr)) {
				debug_out::trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddFilterメソッドに失敗しました。", hr);
			}

			//CaptureGraphBuilder2インタフェースの取得
			ICaptureGraphBuilder2 *pCGB2 = NULL;
			hr = CoCreateInstance( CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pCGB2);
			if (FAILED(hr)) {
				debug_out::trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddFilterメソッドに失敗しました。", hr);
			}
			captureGraphBuilder_ = ICaptureGraphBuilder2Ptr(pCGB2);


			//フィルタグラフにグラフビルダーを追加
			hr = captureGraphBuilder_->SetFiltergraph(graphBuilder_.get());
			if (FAILED(hr)) {
				debug_out::trace("AddFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddFilterメソッドに失敗しました。", hr);
			}

			//クライアントウインドウのサイズを覚えておく
			rect2i clientSize;
			wnd.get_size(clientSize);
			SetRect(&clientRect_, 0, 0, clientSize.width, clientSize.height);

			NYX_ASSERT(graphBuilder_  != nullptr);
			NYX_ASSERT(mediaControl_  != nullptr);
			NYX_ASSERT(mediaEvent_    != nullptr);
			NYX_ASSERT(windowlessControl_     != nullptr);
			NYX_ASSERT(captureGraphBuilder_   != nullptr);
			NYX_ASSERT(videoMixingRenderer_   != nullptr);

			isInitialized_ = true;

			return isInitialized_;
		}


		//-----------------------------------------------------------------------------------
		void open(const std::wstring& fileName) {
			//ソースフィルタにファイルを接続する
			IBaseFilter *pSource = NULL;
			HRESULT hr  = graphBuilder_->AddSourceFilter(fileName.c_str(), fileName.c_str(), &pSource);
			if (FAILED(hr)) {
				debug_out::trace("AddSourceFilterメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddSourceFilterメソッドに失敗しました。", hr);
			}
			sourceFilter_ = IBaseFilterPtr(pSource);


			// ネイティブ ビデオ サイズを取得する。
			long width, height;
			hr = windowlessControl_->GetNativeVideoSize(&width, &height, NULL, NULL);
			if (FAILED(hr)) {
				debug_out::trace("GetNativeVideoSizeメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("GetNativeVideoSizeメソッドに失敗しました。", hr);
			}

			//転送元矩形を設定
			RECT src = {0, 0, width, height};
			hr = windowlessControl_->SetVideoPosition(&src, &clientRect_);
			if (FAILED(hr)) {
				debug_out::trace("SetVideoPositionメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("SetVideoPositionメソッドに失敗しました。", hr);
			}


			//ビデオレンダラにソースフィルタを接続
			hr = captureGraphBuilder_->RenderStream(0,  &MEDIATYPE_Video, pSource, 0, videoMixingRenderer_.get());
			if (FAILED(hr)) {
				debug_out::trace("RenderStreamメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("RenderStreamメソッドに失敗しました。", hr);
			}


			//オーディオレンダラにソースフィルタを接続
			hr = captureGraphBuilder_->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0);
			if (FAILED(hr)) {
				debug_out::trace("RenderStreamメソッドに失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("RenderStreamメソッドに失敗しました。", hr);
			}
		}


		//-----------------------------------------------------------------------------------
		//
		void play() {
			NYX_ASSERT(mediaControl_ != nullptr);
			HRESULT hr = mediaControl_->Run();
			if (FAILED(hr)) {
				debug_out::trace("動画の再生に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("動画の再生に失敗しました。", hr);
			}
		}



		//-----------------------------------------------------------------------------------
		//
		void stop() {
			NYX_ASSERT(mediaControl_ != nullptr);
			HRESULT hr = mediaControl_->Stop();
			if (FAILED(hr)) {
				debug_out::trace("動画の停止に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("動画の停止に失敗しました。", hr);
			}
		}


		//-----------------------------------------------------------------------------------
		//
		void pause() {
			NYX_ASSERT(mediaControl_ != nullptr);
			HRESULT hr  =mediaControl_->Pause();
			if (FAILED(hr)) {
				debug_out::trace("動画の一時停止に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("動画の一時停止に失敗しました。", hr);
			}
		}


		//-----------------------------------------------------------------------------------
		//
		void resume() {
			NYX_ASSERT(mediaControl_ != nullptr);
			HRESULT hr = mediaControl_->Run();
			if (FAILED(hr)) {
				debug_out::trace("動画の再開に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("動画の再開に失敗しました。", hr);
			}
		}


		//-----------------------------------------------------------------------------------
		//
		void set_aspect_ratio_mode(bool mode) {
			NYX_ASSERT(windowlessControl_ != nullptr);
			HRESULT hr ;
			if (mode) {
				hr = this->windowlessControl_->SetAspectRatioMode(VMR_ARMODE_LETTER_BOX);
			}
			else {
				hr = this->windowlessControl_->SetAspectRatioMode(VMR_ARMODE_NONE);
			}

			if (FAILED(hr)) {
				debug_out::trace("アスペクト比の設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("アスペクト比の設定に失敗しました。", hr);
			}
		}


		//-----------------------------------------------------------------------------------
		//
		bool get_aspect_ratio_mode() const {
			NYX_ASSERT(windowlessControl_ != nullptr);
			uint64_t mode = 0;
			HRESULT hr = this->windowlessControl_->GetAspectRatioMode(&mode);
			if (FAILED(hr)) {
				debug_out::trace("アスペクト比の取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw com_exception("アスペクト比の取得に失敗しました。", hr);
			}

			return mode == VMR_ARMODE_LETTER_BOX ? true : false;
		}

		void release() {
			mediaControl_.reset();
			mediaEvent_.reset();
			graphBuilder_.reset();
			videoMixingRenderer_.reset();
			windowlessControl_.reset();
			captureGraphBuilder_.reset();
		}
	private:
		bool isInitialized_;
		char alignment_[3];
		RECT clientRect_; 
		IMediaControlPtr  mediaControl_;
		IMediaEventExPtr  mediaEvent_;
		IGraphBuilderPtr  graphBuilder_;
		IBaseFilterPtr    videoMixingRenderer_;
		IBaseFilterPtr    sourceFilter_;
		IVMRWindowlessControlPtr   windowlessControl_;
		ICaptureGraphBuilder2Ptr   captureGraphBuilder_;
	};

	//-----------------------------------------------------------------------------------
	//
	movie_player::movie_player()
		: pimpl_(std::make_shared<PImpl>()){
	}


	//-----------------------------------------------------------------------------------
	//
	movie_player::movie_player(nyx::window& window, const std::wstring& fileName)
		: pimpl_(std::make_shared<PImpl>(window, fileName)) {
	}


	//-----------------------------------------------------------------------------------
	bool movie_player::is_initialized() {
		return this->pimpl_->is_initialized();
	}

	//-----------------------------------------------------------------------------------
	bool movie_player::initialize(nyx::window& wnd) {
		return this->pimpl_->initialize(wnd);
	}


	//-----------------------------------------------------------------------------------
	void movie_player::open(const std::wstring& fileName) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->is_initialized());
		this->pimpl_->open(fileName);
	}


	//-----------------------------------------------------------------------------------
	//
	void movie_player::play() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->is_initialized());	
		this->pimpl_->play();
	}



	//-----------------------------------------------------------------------------------
	//
	void movie_player::stop() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->is_initialized());	
		this->pimpl_->stop();
	}


	//-----------------------------------------------------------------------------------
	//
	void movie_player::pause() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->is_initialized());	
		this->pimpl_->pause();
	}


	//-----------------------------------------------------------------------------------
	//
	void movie_player::resume() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->is_initialized());	
		this->pimpl_->resume();
	}


	//-----------------------------------------------------------------------------------
	//
	void movie_player::set_aspect_ratio_mode(bool mode) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->is_initialized());	
		this->pimpl_->set_aspect_ratio_mode(mode);
	}


	//-----------------------------------------------------------------------------------
	//
	bool movie_player::get_aspect_ratio_mode() const {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->is_initialized());	
		return this->pimpl_->get_aspect_ratio_mode();
	}

	void movie_player::release() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->is_initialized());	
		this->pimpl_->release();
	}
};