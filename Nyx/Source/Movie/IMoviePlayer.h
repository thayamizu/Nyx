#ifndef NYX_CORE_IMOVIE_PLAYER_H_
#define NYX_CORE_IMOVIE_PLAYER_H_

namespace Nyx
{
	///動画再生に必要な機能を提供
	class IMoviePlayer 
	{
	public:
		virtual ~IMoviePlayer() {}

			/**
		*
		*@return 
		*/
		virtual bool Open(const std::wstring& name) = 0;
			
		/**
		*
		*@return 
		*/
		virtual bool Close() = 0;
		/**
		*
		*@return 
		*/
		virtual bool Play()  = 0;

		/**
		*
		*@return 
		*/
		virtual bool Stop()  = 0;

		/**
		*
		*@return 
		*/
		virtual bool Pause()  = 0;

		/**
		*
		*@return 
		*/
		virtual bool Resume() = 0;

		/**
		*
		*@return 
		*/
		virtual bool IsPause()   = 0;

		/**
		*
		*@return 
		*/
		virtual bool IsPlaying() = 0;

		/**
		*
		*@return
		*/
		virtual bool IsOpened() =0;
	};
}
#endif