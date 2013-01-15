#ifndef NYX_CORE_DSMOVIE_PLAYER_H_
#define NYX_CORE_DSMOVIE_PLAYER_H_
#include "Utility/Type.h"
#include "Movie/IMoviePlayer.h"

namespace Nyx
{
	class DSMoviePlayer : public IMoviePlayer 
	{
	public:
		DSMoviePlayer(); 
		DSMoviePlayer(const tstring & name);
		~DSMoviePlayer();
		bool Open(const tstring& name);
	bool Close();
		
		bool Play();
		bool Stop();
		bool Pause();
		bool Resume();

		bool IsPause();
		bool IsPlaying();
		bool IsOpened();
	};
}
#endif