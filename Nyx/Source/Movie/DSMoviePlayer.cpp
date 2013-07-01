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
				DebugOutput::Trace("動画の再生に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("動画の再生に失敗しました。", hr);
			}
			graphBuilder_ = IGraphBuilderPtr(pGraphBuilder);

			IMediaControl *pMediaControl = NULL;
			hr = pGraphBuilder->QueryInterface(IID_IMediaControl,
				(LPVOID *)&pMediaControl);
			if (FAILED(hr)) {
				DebugOutput::Trace("動画の再生に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("動画の再生に失敗しました。", hr);
			}
			mediaControl_ = IMediaControlPtr(pMediaControl);

			IMediaEventEx *pMediaEvent = NULL;
			pGraphBuilder->QueryInterface(IID_IMediaEventEx,
				(LPVOID *)&pMediaEvent);
			if (FAILED(hr)) {
				DebugOutput::Trace("動画の再生に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("動画の再生に失敗しました。", hr);
			}
			mediaEvent_ = IMediaEventExPtr(pMediaEvent);


			IVideoWindow *pVideoWindow = NULL;
			pGraphBuilder->QueryInterface(IID_IVideoWindow,
				(LPVOID *)&pVideoWindow);
			if (FAILED(hr)) {
				DebugOutput::Trace("動画の再生に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("動画の再生に失敗しました。", hr);
			}
			hr = pVideoWindow->put_Owner((OAHWND)(window.GetHandle()));
			if (FAILED(hr)) {
				DebugOutput::Trace("動画の再生に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("動画の再生に失敗しました。", hr);
			}
			pVideoWindow->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS);
			if (FAILED(hr)) {
				DebugOutput::Trace("動画の再生に失敗しました。[%s:%d]", __FILE__, __LINE__);
				throw COMException("動画の再生に失敗しました。", hr);
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