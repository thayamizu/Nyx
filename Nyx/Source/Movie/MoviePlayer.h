#ifndef NYX_CORE_MOVIE_PLAYER_H_
#define NYX_CORE_MOVIE_PLAYER_H_

namespace Nyx
{
	class IMoviePlayer;
	class MoviePlayer {
	public:
		/*
		* �R���X�g���N�^
		*/
		MoviePlayer();


		/**
		* �R���X�g���N�^
		* @param const std::wstring& �t�@�C����
		*/
		MoviePlayer(const std::wstring & name);


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
		std::shared_ptr<IMoviePlayer> player_; ///< ����v���C���[����
	};
}
#endif