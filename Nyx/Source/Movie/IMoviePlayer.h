#ifndef NYX_CORE_IMOVIE_PLAYER_H_
#define NYX_CORE_IMOVIE_PLAYER_H_

namespace Nyx
{
	///����Đ��ɕK�v�ȋ@�\���
	class IMoviePlayer 
	{
	public:
		/**
		* �f�X�g���N�^
		*/
		virtual ~IMoviePlayer() {}

		/**
		* ����t�@�C�����J���܂�
		* @param const std::wstring& �t�@�C����
		* @return bool(true�Ȃ琬��)
		*/
		virtual bool Open(const std::wstring& name) = 0;


		/**
		* ����t�@�C������܂�
		* @param const std::wstring& �t�@�C����
		* @return bool(true�Ȃ琬��)
		*/
		virtual bool Close() = 0;


		/**
		* ������Đ����܂�
		*/
		virtual void Play()  = 0;



		/**
		* ������Đ����܂�
		*/
		virtual void Stop()  = 0;


		/**
		* ������ꎞ��~���܂�
		*/
		virtual void Pause()  = 0;


		/**
		* ����Đ������W���[�����܂�
		*/
		virtual void Resume() = 0;

	};
}
#endif