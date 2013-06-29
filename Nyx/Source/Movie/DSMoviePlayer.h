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
		DSMoviePlayer(const std::wstring & name);

		/**
		* ����t�@�C�����J���܂�
		* @param const std::wstring& �t�@�C����
		* @return bool(true�Ȃ琬��)
		*/
		bool Open(const std::wstring& name);


		/**
		* ����t�@�C������܂�
		* @param const std::wstring& �t�@�C����
		* @return bool(true�Ȃ琬��)
		*/
		bool Close();


		/**
		* ������Đ����܂�
		*/
		void Play();


		/**
		* ������~���܂�
		*/
		void Stop();


		/**
		* ������ꎞ��~���܂�
		*/
		void Pause();


		/**
		* ����Đ������W���[�����܂�
		*/
		void Resume();
	private:
	};
}
#endif