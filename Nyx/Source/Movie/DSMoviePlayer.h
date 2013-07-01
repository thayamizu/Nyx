#ifndef NYX_CORE_DSMOVIE_PLAYER_H_
#define NYX_CORE_DSMOVIE_PLAYER_H_
#include "DirectShowDefinition.h"
#include "Movie/IMoviePlayer.h"

namespace Nyx
{
	class Window;
	class DSMoviePlayer : public IMoviePlayer {
	public:
		DSMoviePlayer(const std::wstring & name, Nyx::Window& window);

		/**
		* 動画ファイルを開きます
		* @param const std::wstring& ファイル名
		* @return bool(trueなら成功)
		*/
		bool Open(const std::wstring& name);


		/**
		* 動画ファイルを閉じます
		* @param const std::wstring& ファイル名
		* @return bool(trueなら成功)
		*/
		bool Close();


		/**
		* 動画を再生します
		*/
		void Play();


		/**
		* 動画を停止します
		*/
		void Stop();


		/**
		* 動画を一時停止します
		*/
		void Pause();


		/**
		* 動画再生をレジュームします
		*/
		void Resume();
	private:
		IMediaControlPtr  mediaControl_;
		IMediaEventExPtr  mediaEvent_;
		IGraphBuilderPtr  graphBuilder_;
		IVideoWindowPtr   videoWindow_;
	};
}
#endif