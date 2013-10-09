#ifndef NYX_CORE_MOVIE_PLAYER_H_
#define NYX_CORE_MOVIE_PLAYER_H_
#include "DirectShowDefinition.h"


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
		*初期化
		* @param const std::shared_ptr<Nyx::Window> ウインドウ
		* @return bool(trueなら成功)
		*/
		void Initialize(const std::shared_ptr<Nyx::Window> window);


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
	private:
		IMediaControlPtr  mediaControl_;
		IMediaEventExPtr  mediaEvent_;
		IGraphBuilderPtr  graphBuilder_;
		IBaseFilterPtr    videoMixingRenderer_;
		IBaseFilterPtr    sourceFilter_;
		IVMRWindowlessControlPtr   windowlessControl_;
		ICaptureGraphBuilder2Ptr   captureGraphBuilder_;
		RECT clientRect_; 
	};
}
#endif