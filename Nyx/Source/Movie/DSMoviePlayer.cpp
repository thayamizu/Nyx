#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "GUI/Window.h"
#include "Movie/DSMoviePlayer.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------
	DSMoviePlayer::DSMoviePlayer(const std::wstring & name, Window& window)
		:mediaControl_(nullptr), mediaEvent_(nullptr), videoWindow_(nullptr), graphBuilder_(nullptr){

			Assert(graphBuilder_  == nullptr);
			Assert(mediaControl_  == nullptr);
			Assert(mediaEvent_    == nullptr);
			Assert(videoWindow_   == nullptr);

			IGraphBuilder *pGraphBuilder = NULL;
			HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL,
				CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID *)&pGraphBuilder);
			if (FAILED(hr)) {
				DebugOutput::Trace("����̍Đ��Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("����̍Đ��Ɏ��s���܂����B", hr);
			}
			graphBuilder_ = IGraphBuilderPtr(pGraphBuilder);

			IMediaControl *pMediaControl = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaControl,
				(LPVOID *)&pMediaControl);
			if (FAILED(hr)) {
				DebugOutput::Trace("����̍Đ��Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("����̍Đ��Ɏ��s���܂����B", hr);
			}
			mediaControl_ = IMediaControlPtr(pMediaControl);

			IMediaEventEx *pMediaEvent = NULL;
			pGraphBuilder->QueryInterface(IID_IMediaEventEx,
				(LPVOID *)&pMediaEvent);
			if (FAILED(hr)) {
				DebugOutput::Trace("����̍Đ��Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("����̍Đ��Ɏ��s���܂����B", hr);
			}
			mediaEvent_ = IMediaEventExPtr(pMediaEvent);


			IVideoWindow *pVideoWindow = NULL;
			pGraphBuilder->QueryInterface(IID_IVideoWindow,
				(LPVOID *)&pVideoWindow);
			if (FAILED(hr)) {
				DebugOutput::Trace("����̍Đ��Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("����̍Đ��Ɏ��s���܂����B", hr);
			}
			hr = pVideoWindow->put_Owner((OAHWND)(window.GetHandle()));
			if (FAILED(hr)) {
				DebugOutput::Trace("����̍Đ��Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("����̍Đ��Ɏ��s���܂����B", hr);
			}
			pVideoWindow->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS);
			if (FAILED(hr)) {
				DebugOutput::Trace("����̍Đ��Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
				throw COMException("����̍Đ��Ɏ��s���܂����B", hr);
			}
			Assert(graphBuilder_  != nullptr);
			Assert(mediaControl_  != nullptr);
			Assert(mediaEvent_    != nullptr);
			Assert(videoWindow_   != nullptr);
	}


	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::Open(const std::wstring& fileName) {
		BSTR  name = ::SysAllocString(fileName.c_str());
		HRESULT hr = mediaControl_->RenderFile(name);
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