#ifndef NYX_CORE_MOVIE_PLAYER_H_
#define NYX_CORE_MOVIE_PLAYER_H_

namespace Nyx
{
	class IMoviePlayer;
	class MoviePlayer {
	public:
		/*
		* コンストラクタ
		*/
		MoviePlayer();


		/**
		* コンストラクタ
		* @param const std::wstring& ファイル名
		*/
		MoviePlayer(const std::wstring & name);


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
		std::shared_ptr<IMoviePlayer> player_; ///< 動画プレイヤー実装
	};
}
#endif