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
					//����Đ��p�̃t�B���^�O���t��������
					Initialize(window);

					//������J��
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

			//GraphBuilder ���\�z
			IGraphBuilder *pGraphBuilder = NULL;
			HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL,
				CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID *)&pGraphBuilder);
			if (FAILED(hr)) {
				DebugOutput::Trace("GraphBuilder�̍쐬�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("GraphBuilder�̍쐬�Ɏ��s���܂����B", hr);
			}
			graphBuilder_ = IGraphBuilderPtr(pGraphBuilder);

			//MediaControl�C���^�t�F�[�X���擾
			IMediaControl *pMediaControl = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaControl,
				(LPVOID *)&pMediaControl);
			if (FAILED(hr)) {
				DebugOutput::Trace("IMediaControl�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("IMediaControl�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			mediaControl_ = IMediaControlPtr(pMediaControl);

			//IMediaEventEx�C���^�t�F�[�X���擾
			IMediaEventEx *pMediaEvent = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaEventEx,
				(LPVOID *)&pMediaEvent);
			if (FAILED(hr)) {
				DebugOutput::Trace("IMediaEventEx�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("IMediaEventEx�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			mediaEvent_ = IMediaEventExPtr(pMediaEvent);


			//VidoMixingRenderer���擾
			IBaseFilter *pBaseFilter = NULL;
			hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, 
				CLSCTX_INPROC, IID_IBaseFilter, (void**)&pBaseFilter); 
			if (FAILED(hr)) {
				DebugOutput::Trace("IBaseFilter�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("IBaseFilter�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			videoMixingRenderer_ = IBaseFilterPtr(pBaseFilter);


			//GraphBuilder�� VideoMixingRenderer�t�B���^��ǉ�
			hr = graphBuilder_->AddFilter(videoMixingRenderer_.get(), L"Video Mixing Renderer9");
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}

			// �����_�����O ���[�h��ݒ肷��B
			IVMRFilterConfig* pRenderingConfig = NULL;
			hr = videoMixingRenderer_->QueryInterface(IID_IVMRFilterConfig, (LPVOID*)&pRenderingConfig);
			if (FAILED(hr)) {
				DebugOutput::Trace("IVMRFilterConfig�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("IVMRFilterConfig�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			hr = pRenderingConfig->SetRenderingMode(VMRMode_Windowless);
			if (FAILED(hr)) {
				DebugOutput::Trace("SetRenderingMode���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("SetRenderingMode���\�b�h�Ɏ��s���܂����B", hr);
			}
			pRenderingConfig->Release();


			// �Đ��E�C���h�E��ݒ肷��B
			IVMRWindowlessControl *pWindowlessControl = NULL;
			hr = videoMixingRenderer_->QueryInterface(IID_IVMRWindowlessControl, (LPVOID*)&pWindowlessControl);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			windowlessControl_ = IVMRWindowlessControlPtr(pWindowlessControl);
			hr = windowlessControl_->SetVideoClippingWindow(window->GetHandle());
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}

			//CaptureGraphBuilder2�C���^�t�F�[�X�̎擾
			ICaptureGraphBuilder2 *pCGB2 = NULL;
			hr = CoCreateInstance( CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pCGB2);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			captureGraphBuilder_ = ICaptureGraphBuilder2Ptr(pCGB2);


			//�t�B���^�O���t�ɃO���t�r���_�[��ǉ�
			hr = captureGraphBuilder_->SetFiltergraph(graphBuilder_.get());
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}


			//�N���C�A���g�E�C���h�E�̃T�C�Y���o���Ă���
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
		//�\�[�X�t�B���^�Ƀt�@�C����ڑ�����
		IBaseFilter *pSource = NULL;
		HRESULT hr  = graphBuilder_->AddSourceFilter(fileName.c_str(), fileName.c_str(), &pSource);
		if (FAILED(hr)) {
			DebugOutput::Trace("AddSourceFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("AddSourceFilter���\�b�h�Ɏ��s���܂����B", hr);
		}
		sourceFilter_ = IBaseFilterPtr(pSource);


		// �l�C�e�B�u �r�f�I �T�C�Y���擾����B
		long width, height;
		hr = windowlessControl_->GetNativeVideoSize(&width, &height, NULL, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
		}
		
		//�]������`��ݒ�
		RECT src = {0, 0, width, height};
		hr = windowlessControl_->SetVideoPosition(&src, &clientRect_);
		if (FAILED(hr)) {
			DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
		}

		//�r�f�I�����_���Ƀ\�[�X�t�B���^��ڑ�
		hr = captureGraphBuilder_->RenderStream(0, 0, sourceFilter_.get(), 0, videoMixingRenderer_.get());
		if (FAILED(hr)) {
			DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
		}

		
		//�I�[�f�B�I�����_���Ƀ\�[�X�t�B���^��ڑ�
		hr = captureGraphBuilder_->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0);
		if (FAILED(hr)) {
			DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
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
			DebugOutput::Trace("RemoveFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("RemoveFilter���\�b�h�Ɏ��s���܂����B", hr);
		}
	}

	
	//-----------------------------------------------------------------------------------
	//
	void DSMoviePlayer::Play() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Run();
		if (FAILED(hr)) {
			DebugOutput::Trace("����̍Đ��Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("����̍Đ��Ɏ��s���܂����B", hr);
		}
	}


	
	//-----------------------------------------------------------------------------------
	//
	void DSMoviePlayer::Stop() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Stop();
		if (FAILED(hr)) {
			DebugOutput::Trace("����̒�~�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("����̒�~�Ɏ��s���܂����B", hr);
		}
	}


	//-----------------------------------------------------------------------------------
	//
	void DSMoviePlayer::Pause() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr  =mediaControl_->Pause();
		if (FAILED(hr)) {
			DebugOutput::Trace("����̈ꎞ��~�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("����̈ꎞ��~�Ɏ��s���܂����B", hr);
		}
	}


	//-----------------------------------------------------------------------------------
	//
	void DSMoviePlayer::Resume() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Run();
		if (FAILED(hr)) {
			DebugOutput::Trace("����̍ĊJ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("����̍ĊJ�Ɏ��s���܂����B", hr);
		}
	}
};