#ifndef NYX_CORE_MOVIE_PLAYER_H_
#define NYX_CORE_MOVIE_PLAYER_H_

namespace Nyx
{

	class Window;
	class MoviePlayer {
	public:
		/**
		* コンストラクタ
		*/
		MoviePlayer();


		/**
		* コンストラクタ
		* @param const std::shared_ptr<Nyx::Window> ウインドウ
		* @param const std::wstring& ファイル名
		*/
		MoviePlayer(const std::shared_ptr<Nyx::Window> window, const std::wstring& fileName);
		
		/**
		*初期化されているかどうか
		*/
		bool IsInitialize();

		/**
		*初期化
		* @param const std::shared_ptr<Nyx::Window> ウインドウ
		* @return bool(trueなら成功)
		*/
		bool Initialize(const std::shared_ptr<Nyx::Window> window);


		/**
		* 動画ファイルを開きます
		* @param const std::wstring& ファイル名
		* @return bool(trueなら成功)
		*/
		void Open(const std::wstring& name);


		/**
		* 動画を再生します
		*/
		void Play();


		/**
		* 動画を停止します
		*/
		void Stop();


		/**
		* 動画を一時停止します
		*/
		void Pause();


		/**
		* 動画再生をレジュームします
		*/
		void Resume();


		/**
		* アスペクト比維持するかどうかを指定します．
		* @param bool アスペクト比を維持するならtrue
		*/
		void SetAspectRatioMode(bool mode);


		/**
		* アスペクト比のモードを取得します
		* @return bool アスペクト比を維持するならtrue
		*/
		bool GetAspectRatioMode() const;

		void Release();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif