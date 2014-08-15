#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_AUDIO_LISTENER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_AUDIO_LISTENER_H_
#include "IAudioListener.h"
#include "DirectSoundDefinition.h"

namespace nyx {
	class dsound_audio_listener : public iaudio_listener{
	public:
		dsound_audio_listener(dsound_ptr dsound);
		virtual ~dsound_audio_listener();
		/**
		* リスナーの位置を取得します
		* @return Vecto3f リスナーの位置ベクトル
		*/
		vector3f get_position() const ;


		/**
		*　リスナーの位置を設定します
		* @param const Vector3f&　リスナーの位置ベクトル
		*/
		void set_position(const vector3f& pos) ;


		/**
		* 速度ベクトルを取得します
		* @return Vector3f　リスナーの速度ベクトル
		*/
		vector3f get_velocity() const ;


		/**
		*　速度ベクトルを設定します
		* @param const Vector3f& リスナーの速度ベクトル
		*/
		void set_velocity(const vector3f& velocity) ;


		/**
		* ドップラー係数を取得します
		* @return float ドップラー係数
		*/
		float get_doppler_factor() const ;


		/**
		* ドップラー係数を設定します
		* @param float ドップラー係数
		*/
		void set_doppler_factor(float dopplerFactor) ;


		/**
		* ロールオフ係数を取得します
		* @return ロールオフ係数
		*/
		float get_rolloff_factor() const ;


		/**
		* ロールオフ係数を設定します
		* @param float ロールオフ係数
		*/
		void set_rolloff_factor(float rolloffFactor) ;
	private:
		dsound_3d_listener_ptr listener_;
	};
}
#endif