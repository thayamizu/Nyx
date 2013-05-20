#ifndef NYX_CORE_INCLUDED_IAUDIO_BUFFER_3D_H_
#define NYX_CORE_INCLUDED_IAUDIO_BUFFER_3D_H
#include "Primitive/Vector3.h"
namespace Nyx {
	///3Dサウンドの機能を持つオーディオバッファインタフェース
	class I3DAudioBuffer{
	public:
		virtual Vector3f GetPosition() const = 0;
		virtual void SetPosition(const Vector3f& velocity) = 0;
		virtual Vector3f GetVelocity() const = 0;
		virtual void SetVelocity(const Vector3f& velocity) = 0;

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