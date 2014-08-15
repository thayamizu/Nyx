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
					//����Đ��p�̃t�B���^�O���t��������
					if (initialize(wnd)) {
						//������J��
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

			//GraphBuilder ���\�z
			IGraphBuilder *pGraphBuilder = NULL;
			HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL,
				CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID *)&pGraphBuilder);
			if (FAILED(hr)) {
				debug_out::trace("GraphBuilder�̍쐬�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("GraphBuilder�̍쐬�Ɏ��s���܂����B", hr);
			}
			graphBuilder_ = IGraphBuilderPtr(pGraphBuilder);

			//MediaControl�C���^�t�F�[�X���擾
			IMediaControl *pMediaControl = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaControl,
				(LPVOID *)&pMediaControl);
			if (FAILED(hr)) {
				debug_out::trace("IMediaControl�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("IMediaControl�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			mediaControl_ = IMediaControlPtr(pMediaControl);

			//IMediaEventEx�C���^�t�F�[�X���擾
			IMediaEventEx *pMediaEvent = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaEventEx,
				(LPVOID *)&pMediaEvent);
			if (FAILED(hr)) {
				debug_out::trace("IMediaEventEx�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("IMediaEventEx�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			mediaEvent_ = IMediaEventExPtr(pMediaEvent);


			//VidoMixingRenderer���擾
			IBaseFilter *pBaseFilter = NULL;
			hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, 
				CLSCTX_INPROC, IID_IBaseFilter, (void**)&pBaseFilter); 
			if (FAILED(hr)) {
				debug_out::trace("IBaseFilter�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("IBaseFilter�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			videoMixingRenderer_ = IBaseFilterPtr(pBaseFilter);


			//GraphBuilder�� VideoMixingRenderer�t�B���^��ǉ�
			hr = graphBuilder_->AddFilter(videoMixingRenderer_.get(), L"Video Mixing Renderer9");
			if (FAILED(hr)) {
				debug_out::trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}

			// �����_�����O ���[�h��ݒ肷��B
			IVMRFilterConfig* pRenderingConfig = NULL;
			hr = videoMixingRenderer_->QueryInterface(IID_IVMRFilterConfig, (LPVOID*)&pRenderingConfig);
			if (FAILED(hr)) {
				debug_out::trace("IVMRFilterConfig�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("IVMRFilterConfig�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			hr = pRenderingConfig->SetRenderingMode(VMRMode_Windowless);
			if (FAILED(hr)) {
				debug_out::trace("SetRenderingMode���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("SetRenderingMode���\�b�h�Ɏ��s���܂����B", hr);
			}
			pRenderingConfig->Release();


			// �Đ��E�C���h�E��ݒ肷��B
			IVMRWindowlessControl *pWindowlessControl = NULL;
			hr = videoMixingRenderer_->QueryInterface(IID_IVMRWindowlessControl, (LPVOID*)&pWindowlessControl);
			if (FAILED(hr)) {
				debug_out::trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			windowlessControl_ = IVMRWindowlessControlPtr(pWindowlessControl);
			hr = windowlessControl_->SetVideoClippingWindow(wnd.get_handle());
			if (FAILED(hr)) {
				debug_out::trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}

			//CaptureGraphBuilder2�C���^�t�F�[�X�̎擾
			ICaptureGraphBuilder2 *pCGB2 = NULL;
			hr = CoCreateInstance( CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pCGB2);
			if (FAILED(hr)) {
				debug_out::trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			captureGraphBuilder_ = ICaptureGraphBuilder2Ptr(pCGB2);


			//�t�B���^�O���t�ɃO���t�r���_�[��ǉ�
			hr = captureGraphBuilder_->SetFiltergraph(graphBuilder_.get());
			if (FAILED(hr)) {
				debug_out::trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}

			//�N���C�A���g�E�C���h�E�̃T�C�Y���o���Ă���
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
			//�\�[�X�t�B���^�Ƀt�@�C����ڑ�����
			IBaseFilter *pSource = NULL;
			HRESULT hr  = graphBuilder_->AddSourceFilter(fileName.c_str(), fileName.c_str(), &pSource);
			if (FAILED(hr)) {
				debug_out::trace("AddSourceFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("AddSourceFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			sourceFilter_ = IBaseFilterPtr(pSource);


			// �l�C�e�B�u �r�f�I �T�C�Y���擾����B
			long width, height;
			hr = windowlessControl_->GetNativeVideoSize(&width, &height, NULL, NULL);
			if (FAILED(hr)) {
				debug_out::trace("GetNativeVideoSize���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("GetNativeVideoSize���\�b�h�Ɏ��s���܂����B", hr);
			}

			//�]������`��ݒ�
			RECT src = {0, 0, width, height};
			hr = windowlessControl_->SetVideoPosition(&src, &clientRect_);
			if (FAILED(hr)) {
				debug_out::trace("SetVideoPosition���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("SetVideoPosition���\�b�h�Ɏ��s���܂����B", hr);
			}


			//�r�f�I�����_���Ƀ\�[�X�t�B���^��ڑ�
			hr = captureGraphBuilder_->RenderStream(0,  &MEDIATYPE_Video, pSource, 0, videoMixingRenderer_.get());
			if (FAILED(hr)) {
				debug_out::trace("RenderStream���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("RenderStream���\�b�h�Ɏ��s���܂����B", hr);
			}


			//�I�[�f�B�I�����_���Ƀ\�[�X�t�B���^��ڑ�
			hr = captureGraphBuilder_->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0);
			if (FAILED(hr)) {
				debug_out::trace("RenderStream���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("RenderStream���\�b�h�Ɏ��s���܂����B", hr);
			}
		}


		//-----------------------------------------------------------------------------------
		//
		void play() {
			NYX_ASSERT(mediaControl_ != nullptr);
			HRESULT hr = mediaControl_->Run();
			if (FAILED(hr)) {
				debug_out::trace("����̍Đ��Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("����̍Đ��Ɏ��s���܂����B", hr);
			}
		}



		//-----------------------------------------------------------------------------------
		//
		void stop() {
			NYX_ASSERT(mediaControl_ != nullptr);
			HRESULT hr = mediaControl_->Stop();
			if (FAILED(hr)) {
				debug_out::trace("����̒�~�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("����̒�~�Ɏ��s���܂����B", hr);
			}
		}


		//-----------------------------------------------------------------------------------
		//
		void pause() {
			NYX_ASSERT(mediaControl_ != nullptr);
			HRESULT hr  =mediaControl_->Pause();
			if (FAILED(hr)) {
				debug_out::trace("����̈ꎞ��~�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("����̈ꎞ��~�Ɏ��s���܂����B", hr);
			}
		}


		//-----------------------------------------------------------------------------------
		//
		void resume() {
			NYX_ASSERT(mediaControl_ != nullptr);
			HRESULT hr = mediaControl_->Run();
			if (FAILED(hr)) {
				debug_out::trace("����̍ĊJ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("����̍ĊJ�Ɏ��s���܂����B", hr);
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
				debug_out::trace("�A�X�y�N�g��̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("�A�X�y�N�g��̐ݒ�Ɏ��s���܂����B", hr);
			}
		}


		//-----------------------------------------------------------------------------------
		//
		bool get_aspect_ratio_mode() const {
			NYX_ASSERT(windowlessControl_ != nullptr);
			uint64_t mode = 0;
			HRESULT hr = this->windowlessControl_->GetAspectRatioMode(&mode);
			if (FAILED(hr)) {
				debug_out::trace("�A�X�y�N�g��̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw com_exception("�A�X�y�N�g��̎擾�Ɏ��s���܂����B", hr);
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