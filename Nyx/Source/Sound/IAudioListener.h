#ifndef NYX_CORE_INCLUDED_IAUDIO_LISTENER_
#define NYX_CORE_INCLUDED_IAUDIO_LISTENER_

namespace Nyx {
	
	class Vector3f;
	///オーディオリスナー
	class IAudioListener {
	public:
		~IAudioListener() {}
	
		/**
		* リスナーの位置を取得します
		* @return Vecto3f リスナーの位置ベクトル
		*/
		virtual Vector3f GetPosition() const = 0;
	

		/**
		*　リスナーの位置を設定します
		* @param const Vector3f&　リスナーの位置ベクトル
		*/
		virtual void SetPosition(const Vector3f& pos) = 0;
		
		
		/**
		* 速度ベクトルを取得します
		* @return Vector3f　リスナーの速度ベクトル
		*/
		virtual Vector3f GetVelocity() const = 0;
		
		
		/**
		*　速度ベクトルを設定します
		* @param const Vector3f& リスナーの速度ベクトル
		*/
		virtual void SetVelocity(const Vector3f& velocity) = 0;


		/**
		* ドップラー係数を取得します
		* @return float ドップラー係数
		*/
		virtual float GetDopplerFactor() const = 0;
		

		/**
		* ドップラー係数を設定します
		* @param float ドップラー係数
		*/
		virtual void SetDopplerFactor(float dopplerFactor) = 0;
		

		/**
		* ロールオフ係数を取得します
		* @return ロールオフ係数
		*/
		virtual float GetRolloffFactor() const = 0;
		
		
		/**
		* ロールオフ係数を設定します
		* @param float ロールオフ係数
		*/
		virtual void SetRolloffFactor(float rolloffFactor) = 0;
	};
}
#endif