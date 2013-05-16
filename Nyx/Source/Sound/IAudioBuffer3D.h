#ifndef NYX_CORE_INCLUDED_IAUDIO_BUFFER_3D_H_
#define NYX_CORE_INCLUDED_IAUDIO_BUFFER_3D_H
namespace Nyx {
	///3Dオーディオバッファインタフェース
	class IAudioBuffer3D {
	public:
		virtual void GetPosition() = 0;
		virtual void SetPosition() = 0;
		virtual void GetVelocity() = 0;
		virtual void SetVelocity() = 0;

		/**
		* 音源からの最大距離を取得します
		* @return float 音源からの最大距離
		*/
		virtual float GetMaxDistance() const = 0;


		/**
		* 音源からの最大距離を設定します
		* @param float  最大距離
		*/
		virtual void SetMaxDistance(float maxDistance) = 0;
		

		/**
		* 音源からの最小距離を設定します
		* @param float  最小距離
		*/
		virtual float GetMinDistance() const = 0;


		/**
		* 音源からの最小距離を取得します
		* @return float 音源からの最小距離
		*/
		virtual void SetMinDistance(float minDistance) = 0;
	};
}
#endif