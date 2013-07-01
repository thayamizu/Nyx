#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "GUI/Window.h"
#include "Movie/DSMoviePlayer.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------
	DSMoviePlayer::DSMoviePlayer(const std::wstring & name)
		:mediaControl_(nullptr), mediaEvent_(nullptr), videoWindow_(nullptr), graphBuilder_(nullptr){

			Assert(graphBuilder_  == nullptr);
			Assert(mediaControl_  == nullptr);
			Assert(mediaEvent_    == nullptr);
			Assert(videoWindow_   == nullptr);

			IGraphBuilder *pGraphBuilder = NULL;
			HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL,
				CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID *)&pGraphBuilder);
			if (FAILED(hr)) {
				DebugOutput::Trace("GraphBuilder�̍쐬�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("GraphBuilder�̍쐬�Ɏ��s���܂����B", hr);
			}
			graphBuilder_ = IGraphBuilderPtr(pGraphBuilder);

			IMediaControl *pMediaControl = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaControl,
				(LPVOID *)&pMediaControl);
			if (FAILED(hr)) {
				DebugOutput::Trace("IMediaControl�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("IMediaControl�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			mediaControl_ = IMediaControlPtr(pMediaControl);

			IMediaEventEx *pMediaEvent = NULL;
			pGraphBuilder->QueryInterface(IID_IMediaEventEx,
				(LPVOID *)&pMediaEvent);
			if (FAILED(hr)) {
				DebugOutput::Trace("IMediaEventEx�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("IMediaEventEx�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			mediaEvent_ = IMediaEventExPtr(pMediaEvent);


			IVideoWindow *pVideoWindow = NULL;
			pGraphBuilder->QueryInterface(IID_IVideoWindow,
				(LPVOID *)&pVideoWindow);
			if (FAILED(hr)) {
				DebugOutput::Trace("IVideoWindow�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("IVideoWindow�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
			}
			videoWindow_ = IVideoWindowPtr(pVideoWindow);

			Assert(graphBuilder_  != nullptr);
			Assert(mediaControl_  != nullptr);
			Assert(mediaEvent_    != nullptr);
			Assert(videoWindow_   != nullptr);
	}


	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::Open(const std::wstring& fileName, Nyx::Window& window) {
		BSTR  name = ::SysAllocString(fileName.c_str());
		HRESULT hr = mediaControl_->RenderFile(name);
		if (FAILED(hr)) {
			return false;
		}
		return true;

		hr = videoWindow_->put_Owner((OAHWND)window.GetHandle());
		if (FAILED(hr)) {
			DebugOutput::Trace("�o�̓E�C���h�E�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("�o�̓E�C���h�E�̐ݒ�Ɏ��s���܂����B", hr);
		}
		hr = videoWindow_->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS);
		if (FAILED(hr)) {
			DebugOutput::Trace("�E�C���h�E�X�^�C���̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("�E�C���h�E�X�^�C���̐ݒ�Ɏ��s���܂����B", hr);
		}
		Rect2i rect;
		window.GetSize(&rect);
		videoWindow_->SetWindowPosition(0, 0,
			rect.width, rect.height);

		videoWindow_->SetWindowForeground(OATRUE);
		videoWindow_->put_Visible(OATRUE);
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