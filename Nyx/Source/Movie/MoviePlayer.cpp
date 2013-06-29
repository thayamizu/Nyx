#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Movie/IMoviePlayer.h"
#include "Movie/DSMoviePlayer.h"
#include "Movie/MoviePlayer.h"

namespace Nyx 
{
	//-----------------------------------------------------------------------------------
	MoviePlayer::MoviePlayer() 
		:player_(nullptr) {
		player_  = std::make_shared<DSMoviePlayer>();
	}

	//-----------------------------------------------------------------------------------
	MoviePlayer::MoviePlayer(const std::wstring & name)
		:player_(nullptr) {
		player_  =std::make_shared<DSMoviePlayer>(name);
	}

	//-----------------------------------------------------------------------------------
	bool MoviePlayer::Open(const std::wstring& name) {
		Assert(player_ != nullptr);
		return player_->Open(name);
	}


	//-----------------------------------------------------------------------------------
	bool MoviePlayer::Close()  {
		Assert(player_ != nullptr);
		return player_->Close();
	}


	//-----------------------------------------------------------------------------------
	void MoviePlayer::Play() {
		Assert(player_ != nullptr);
		player_->Play();
	}


	//-----------------------------------------------------------------------------------
	void MoviePlayer::Stop() {
		Assert(player_ != nullptr);
		player_->Stop();
	}


	//-----------------------------------------------------------------------------------
	void MoviePlayer::Pause() {
		Assert(player_ != nullptr);
		player_->Pause();
	}


	//-----------------------------------------------------------------------------------
	void MoviePlayer::Resume() {
		player_->Resume();
	}

};