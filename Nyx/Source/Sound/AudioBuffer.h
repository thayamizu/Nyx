#ifndef NYX_CORE_INCLUDED_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_AUDIO_BUFFER_H_

#include "IAudioBuffer.h"

namespace Nyx
{
	struct AudioBufferDesc;

	///オーディオバッファ
	class AudioBuffer {
	public:
		/**
		* コンストラクタ
		*/
		AudioBuffer();
		

		/**
		* コンストラクタ
		* @param const AudioBuffer& オーディオバッファ記述子
		*/
		AudioBuffer(const AudioBufferDesc& bufferDesc);


		/**
		* バッファの生成
		* @param const AudioBuffer& オーディオバッファ記述子
		*/
		void CreateBuffer(const AudioBufferDesc& bufferDesc);


		/**
		*　オーディオバッファを再生します
		*/
		void Play();


		/**
		*　オーディオバッファを停止します
		*/
		void Stop();


		/**
		*　オーディオバッファをレジュームします
		*/
		void Resume();


		/**
		*　オーディオバッファをリセットします
		*/
		void Reset();

		/**
		* オーディオバッファのパン値を設定します
		* @param int パン
		*/
		void SetPan(long pan);


		/**
		* オーディオバッファのパン値を取得します
		* @return long パン
		*/
		long GetPan() const;


		/**
		* オーディオバッファのボリューム値を設定します
		* @return int　ボリューム
		*/
		void SetVolume(long volume);


		/**
		* オーディオバッファのボリューム値を取得します
		* @return int ボリューム
		*/
		long GetVolume() const;


		/**
		* オーディオバッファがループ再生かどうか判定します
		* @return bool　ループ再生ならtrue
		*/
		bool IsLooping();

		
		/**
		* オーディオバッファをループ再生するかどうかを設定します
		* @param bool ループ再生ならtrue
		*/
		void SetLooping(bool loop);

		
		/**
		* オーディオバッファが再生中かどうか判定します
		* @return bool 再生中ならtrue
		*/
		bool IsPlaying() const;


		/**
		* オーディオバッファがポーズ中かどうか判定します
		* @return bool ポーズ中ならtrue
		*/
		bool IsPause() const;
	

		/**
		* オーディオバッファをポーズします
		* @param bool ポーズ中ならtrue
		*/
		void SetPause(bool pause);
	

		/**
		* ファイル名を取得します
		* @return const std::wstring& ファイル名
		*/
		const std::wstring& GetName() const;

	private:
		bool isLoop_;
		bool isPause_;
		bool isPlay_;
		std::wstring fileName;
		std::shared_ptr<IAudioBuffer> audio_;
	};
}

#endif