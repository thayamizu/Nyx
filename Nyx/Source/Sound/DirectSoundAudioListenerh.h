#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_AUDIO_LISTENER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_AUDIO_LISTENER_H_
#include "IAudioListener.h"
#include "DirectSoundDefinition.h"

namespace Nyx {
	class DirectSoundAudioListener : public IAudioListener{
	public:
		DirectSoundAudioListener(DirectSoundPtr dsound);
		virtual ~DirectSoundAudioListener();
		/**
		* リスナーの位置を取得します
		* @return Vecto3f リスナーの位置ベクトル
		*/
		Vector3f GetPosition() const ;


		/**
		*　リスナーの位置を設定します
		* @param const Vector3f&　リスナーの位置ベクトル
		*/
		void SetPosition(const Vector3f& pos) ;


		/**
		* 速度ベクトルを取得します
		* @return Vector3f　リスナーの速度ベクトル
		*/
		Vector3f GetVelocity() const ;


		/**
		*　速度ベクトルを設定します
		* @param const Vector3f& リスナーの速度ベクトル
		*/
		void SetVelocity(const Vector3f& velocity) ;


		/**
		* ドップラー係数を取得します
		* @return float ドップラー係数
		*/
		float GetDopplerFactor() const ;


		/**
		* ドップラー係数を設定します
		* @param float ドップラー係数
		*/
		void SetDopplerFactor(float dopplerFactor) ;


		/**
		* ロールオフ係数を取得します
		* @return ロールオフ係数
		*/
		float GetRolloffFactor() const ;


		/**
		* ロールオフ係数を設定します
		* @param float ロールオフ係数
		*/
		void SetRolloffFactor(float rolloffFactor) ;
	private:
		DirectSound3DListenerPtr listener_;
	};
}
#endif