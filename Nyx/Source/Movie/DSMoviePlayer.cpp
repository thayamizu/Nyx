#include "PCH/PCH.h"
#include "Movie/DSMoviePlayer.h"

namespace Nyx 
{
	//-----------------------------------------------------------------------------------
	DSMoviePlayer::DSMoviePlayer() 
	{
	}

	//-----------------------------------------------------------------------------------
	DSMoviePlayer::DSMoviePlayer(const std::wstring & name)
	{
		Open(name);
	}

	//-----------------------------------------------------------------------------------
	DSMoviePlayer::~DSMoviePlayer()
	{
	}

	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::Open(const std::wstring& name)
	{
		name;
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::Close()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::Play()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::Stop()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::Pause()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::Resume()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::IsPause()
	{
		return false;
	}

	//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::IsPlaying()
	{
		return false;
	}

//-----------------------------------------------------------------------------------
	bool DSMoviePlayer::IsOpened()
	{
		return false;
	}
};