#ifndef NYX_CORE_MOVIE_PLAYER_H_
#define NYX_CORE_MOVIE_PLAYER_H_

namespace Nyx
{

	class Window;
	class MoviePlayer {
	public:
		/**
		* �R���X�g���N�^
		*/
		MoviePlayer();


		/**
		* �R���X�g���N�^
		* @param const std::shared_ptr<Nyx::Window> �E�C���h�E
		* @param const std::wstring& �t�@�C����
		*/
		MoviePlayer(const std::shared_ptr<Nyx::Window> window, const std::wstring& fileName);
		
		/**
		*����������Ă��邩�ǂ���
		*/
		bool IsInitialize();

		/**
		*������
		* @param const std::shared_ptr<Nyx::Window> �E�C���h�E
		* @return bool(true�Ȃ琬��)
		*/
		bool Initialize(const std::shared_ptr<Nyx::Window> window);


		/**
		* ����t�@�C�����J���܂�
		* @param const std::wstring& �t�@�C����
		* @return bool(true�Ȃ琬��)
		*/
		void Open(const std::wstring& name);


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


		/**
		* �A�X�y�N�g��ێ����邩�ǂ������w�肵�܂��D
		* @param bool �A�X�y�N�g����ێ�����Ȃ�true
		*/
		void SetAspectRatioMode(bool mode);


		/**
		* �A�X�y�N�g��̃��[�h���擾���܂�
		* @return bool �A�X�y�N�g����ێ�����Ȃ�true
		*/
		bool GetAspectRatioMode() const;

		void Release();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif