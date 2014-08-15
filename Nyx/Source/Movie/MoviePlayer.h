#ifndef NYX_CORE_MOVIE_PLAYER_H_
#define NYX_CORE_MOVIE_PLAYER_H_

namespace nyx
{

	class window;
	class movie_player {
	public:
		/**
		* コンストラクタ
		*/
		movie_player();


		/**
		* コンストラクタ
		* @param const std::shared_ptr<Nyx::Window> ウインドウ
		* @param const std::wstring& ファイル名
		*/
		movie_player(nyx::window& window, const std::wstring& fileName);
		
		/**
		*初期化されているかどうか
		*/
		bool is_initialized();

		/**
		*初期化
		* @param const std::shared_ptr<Nyx::Window> ウインドウ
		* @return bool(trueなら成功)
		*/
		bool initialize(nyx::window& window);


		/**
		* 動画ファイルを開きます
		* @param const std::wstring& ファイル名
		* @return bool(trueなら成功)
		*/
		void open(const std::wstring& name);


		/**
		* 動画を再生します
		*/
		void play();


		/**
		* 動画を停止します
		*/
		void stop();


		/**
		* 動画を一時停止します
		*/
		void pause();


		/**
		* 動画再生をレジュームします
		*/
		void resume();


		/**
		* アスペクト比維持するかどうかを指定します．
		* @param bool アスペクト比を維持するならtrue
		*/
		void set_aspect_ratio_mode(bool mode);


		/**
		* アスペクト比のモードを取得します
		* @return bool アスペクト比を維持するならtrue
		*/
		bool get_aspect_ratio_mode() const;


		void release();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif