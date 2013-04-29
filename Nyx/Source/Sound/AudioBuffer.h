#ifndef NYX_CORE_INCLUDED_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_AUDIO_BUFFER_H_

#include "IAudioBuffer.h"

namespace Nyx
{
	template<typename T>
	class AudioBuffer {
		static_assert(std::is_base_of<IAudioBuffer, T>::value, "T is base of IAudioBuffer");
	public:
		AudioBuffer() 
			:isLoop(false), isPause(false), isPlay_(false),
			pan_(0), volume_(100) {
		}

		/**
		*　再生
		*/
		void Play()  {
			buffer_->Play();
		}


		/**
		*　停止
		*/
		void Stop()  {
			buffer->Stop();
		}


		/**
		*　レジューム
		*/
		void Resume()  {
			buffer->Resume();
		}


		/**
		*　リセット
		*/
		void Reset()   {
			buffer->Reset();
		} 

		/**
		* パンを設定する
		* @param int パン
		*/
		void SetPan(long pan) {
			pan_ = pan;
		}

		/**
		* パンを取得する
		* @return long パン
		*/
		long GetPan() const  {
			return pan_;
		}

		/**
		*　ボリュームを設定する
		* @return int　ボリューム
		*/
		void SetVolume(long volume)  {
			volume_ = volume;
		}

		/**
		* ボリュームを取得する
		* @return int ボリューム
		*/
		long GetVolume() const  {
			return volume_;
		}

		/**
		* ループ再生かどうか判定
		* @return bool　ループ再生ならtrue
		*/
		bool IsLooping()  {
			return isLoop_;
		}

		/**
		* 再生中かどうか
		* @return bool 再生中ならtrue
		*/
		bool IsPlaying()  const {
			return isPlay_
		}

		/**
		* ポーズ中かどうか
		* @return bool ポーズ中ならtrue
		*/
		bool IsPause() const  {
			return isPause_;
		}

		/**
		* ループ再生するかどうかを設定
		* @param bool ループ再生ならtrue
		*/
		void SetLooping(bool loop)  {
			isLoop = loop;
		}

		/**
		* 再生中かどうか
		* @param bool 再生中ならtrue
		*/
		void SetPlaying(bool play)  {
			isPlay_ = play;
		}

		/**
		* ポーズ中かどうか
		* @param bool ポーズ中ならtrue
		*/
		void SetPause(bool pause)   {
			isPause = pause;
		}
	private:
		bool isLoop_;
		bool isPause_;
		bool isPlay_;
		long volume_;
		long pan_;
		std::shared_ptr<T> buffer_;
	};
}

#endif