#ifndef NYX_CORE_IMOVIE_PLAYER_H_
#define NYX_CORE_IMOVIE_PLAYER_H_

namespace Nyx
{
	///動画再生に必要な機能を提供
	class IMoviePlayer 
	{
	public:
		/**
		* デストラクタ
		*/
		virtual ~IMoviePlayer() {}

		/**
		* 動画ファイルを開きます
		* @param const std::wstring& ファイル名
		* @return bool(trueなら成功)
		*/
		virtual bool Open(const std::wstring& name) = 0;


		/**
		* 動画ファイルを閉じます
		* @param const std::wstring& ファイル名
		* @return bool(trueなら成功)
		*/
		virtual bool Close() = 0;


		/**
		* 動画を再生します
		*/
		virtual void Play()  = 0;



		/**
		* 動画を再生します
		*/
		virtual void Stop()  = 0;


		/**
		* 動画を一時停止します
		*/
		virtual void Pause()  = 0;


		/**
		* 動画再生をレジュームします
		*/
		virtual void Resume() = 0;

	};
}
#endif