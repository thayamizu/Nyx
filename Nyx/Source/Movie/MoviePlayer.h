#ifndef NYX_CORE_MOVIE_PLAYER_H_
#define NYX_CORE_MOVIE_PLAYER_H_

namespace nyx
{

	class window;
	class movie_player {
	public:
		/**
		* �R���X�g���N�^
		*/
		movie_player();


		/**
		* �R���X�g���N�^
		* @param const std::shared_ptr<Nyx::Window> �E�C���h�E
		* @param const std::wstring& �t�@�C����
		*/
		movie_player(nyx::window& window, const std::wstring& fileName);
		
		/**
		*����������Ă��邩�ǂ���
		*/
		bool is_initialized();

		/**
		*������
		* @param const std::shared_ptr<Nyx::Window> �E�C���h�E
		* @return bool(true�Ȃ琬��)
		*/
		bool initialize(nyx::window& window);


		/**
		* ����t�@�C�����J���܂�
		* @param const std::wstring& �t�@�C����
		* @return bool(true�Ȃ琬��)
		*/
		void open(const std::wstring& name);


		/**
		* ������Đ����܂�
		*/
		void play();


		/**
		* ������~���܂�
		*/
		void stop();


		/**
		* ������ꎞ��~���܂�
		*/
		void pause();


		/**
		* ����Đ������W���[�����܂�
		*/
		void resume();


		/**
		* �A�X�y�N�g��ێ����邩�ǂ������w�肵�܂��D
		* @param bool �A�X�y�N�g����ێ�����Ȃ�true
		*/
		void set_aspect_ratio_mode(bool mode);


		/**
		* �A�X�y�N�g��̃��[�h���擾���܂�
		* @return bool �A�X�y�N�g����ێ�����Ȃ�true
		*/
		bool get_aspect_ratio_mode() const;


		void release();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif