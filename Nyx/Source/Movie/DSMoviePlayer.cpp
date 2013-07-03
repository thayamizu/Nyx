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


			IBaseFilter *pBaseFilter = NULL;
			hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, 
				CLSCTX_INPROC, IID_IBaseFilter, (void**)&pBaseFilter); 
			if (FAILED(hr)) {
				DebugOutput::Trace("IBaseFilter�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("IBaseFilter�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			baseFilter_ = IBaseFilterPtr(pBaseFilter);

			hr = graphBuilder_->AddFilter(baseFilter_.get(), L"Video Mixing Renderer9");
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}

			// �����_�����O ���[�h��ݒ肷��B
			IVMRFilterConfig* pRenderingConfig = NULL;
			hr = baseFilter_->QueryInterface(IID_IVMRFilterConfig, (LPVOID*)&pRenderingConfig);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}


			hr = pRenderingConfig->SetRenderingMode(VMRMode_Windowless);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			pRenderingConfig->Release();

			// �E�B���h�E��ݒ肷��B
			IVMRWindowlessControl *pWindowlessControl = NULL;
			hr = baseFilter_->QueryInterface(IID_IVMRWindowlessControl, (LPVOID*)&pWindowlessControl);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			windowlessControl_ = IVMRWindowlessControlPtr(pWindowlessControl);

			hr = windowlessControl_->SetVideoClippingWindow(hwnd);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}

			IBaseFilter *pSource;
			hr  = graphBuilder_->AddSourceFilter(L"���삩�̂�.mp4", L"���삩�̂�.mp4", &pSource);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			sourceFilter_ = IBaseFilterPtr(pSource);

			
			ICaptureGraphBuilder2 *pCGB2 = NULL;
			hr = CoCreateInstance( CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pCGB2);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			captureGraphBuilder_ = ICaptureGraphBuilder2Ptr(pCGB2);

			hr = captureGraphBuilder_->SetFiltergraph(graphBuilder_.get());
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			hr = pCGB2->RenderStream(0, 0, sourceFilter_.get(), 0, baseFilter_.get());
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}
			// �l�C�e�B�u �r�f�I �T�C�Y���擾����B
			long width, height;
			hr = windowlessControl_->GetNativeVideoSize(&width, &height, NULL, NULL);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
			}

			RECT src = {};
			src.right = width;
			src.bottom = height;

			RECT dest = {};
			dest.right = 800;
			dest.bottom = 600;
			hr = windowlessControl_->SetVideoPosition(&src, &dest);
			if (FAILED(hr)) {
				DebugOutput::Trace("AddFilter���\�b�h�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("AddFilter���\�b�h�Ɏ��s���܂����B", hr);
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
			DebugOutput::Trace("����̍Đ��Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("����̍Đ��Ɏ��s���܂����B", hr);
		}
	}


	//-----------------------------------------------------------------------------------
	void DSMoviePlayer::Stop() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Stop();
		if (FAILED(hr)) {
			DebugOutput::Trace("����̒�~�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("����̒�~�Ɏ��s���܂����B", hr);
		}
	}


	//-----------------------------------------------------------------------------------
	void DSMoviePlayer::Pause() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr  =mediaControl_->Pause();
		if (FAILED(hr)) {
			DebugOutput::Trace("����̈ꎞ��~�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("����̈ꎞ��~�Ɏ��s���܂����B", hr);
		}
	}


	//-----------------------------------------------------------------------------------
	void DSMoviePlayer::Resume() {
		Assert(mediaControl_ != nullptr);
		HRESULT hr = mediaControl_->Run();
		if (FAILED(hr)) {
			DebugOutput::Trace("����̍ĊJ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("����̍ĊJ�Ɏ��s���܂����B", hr);
		}
	}
};