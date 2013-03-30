#ifndef NYX_CORE_MOVIE_PLAYER_H_
#define NYX_CORE_MOVIE_PLAYER_H_

namespace Nyx
{
	class IMoviePlayer;
	class MoviePlayer 
	{
	public:
		MoviePlayer();
		MoviePlayer(const std::wstring & name);
		~MoviePlayer();

		bool Open(const std::wstring& name);
		bool Close();

		bool Play();
		bool Stop();
		bool Pause();
		bool Resume();

		bool IsPause();
		bool IsPlaying();
		bool IsOpened();

	private:
		IMoviePlayer * player;
	};
}
#endif