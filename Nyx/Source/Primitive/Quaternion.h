/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_QUATERNION_H_
#define NYX_CORE_INCLUDED_QUATERNION_H_
#include "Primitive/EulerAngles.h"
#include "Primitive/Matrix44.h"
#include "Primitive/Vector3.h"
#include "Primitive/Vector4.h"

namespace Nyx {

	template<typename T=float>
	class Quaternion  {
		static_assert(std::is_floating_point<T>::value, "T required floating_point.");
	public:
		T w;///< w値
		T x;///< x値
		T y;///< y値
		T z;///< z値

		/** 
		* コンストラクタ
		*/
		Quaternion<T>()
			:w(0), x(0), y(0), z(0) {
		}


		/** コンストラクタ
		* @param Vector4f
		*/
		Quaternion<T>(const float w, const Vector3<T>& v) 
			:w(w), x(v.x), y(v.y), z(v.z) {
		}


		/** コンストラクタ
		* @param Vector4f
		*/
		Quaternion<T>(const Vector4<T>& v) 
			:w(v.w), x(v.x), y(v.y), z(v.z) {
		}


		/** コンストラクタ
		* @param T w
		* @param T x
		* @param T y
		* @param T z
		*/
		Quaternion<T> (const T w, const T x, const T y, const T z) {
			this->w = w;
			this->x = x;
			this->y = y;
			this->z = z;
		}
		

		/** クォータニオンの加算
		* @param const Quaternion<T> q
		* @return Quaternion<T>
		*/
		Quaternion<T> operator + (const Quaternion<T>& q) const {
			return Quaternion<T>(w + q.w, x + q.x, y + q.y, z + q.z);
		}


		/** クォータニオンの減算
		* @param const Quaternion<T> q
		* @return Quaternion<T> 
		*/
		Quaternion<T> operator - (const Quaternion<T>& q) const {
			return Quaternion<T>(w - q.w, x - q.x, y - q.y, z - q.z);
		}


		/** クォータニオンのスカラ乗算
		* @param const Quaternion<T> q
		* @return Quaternion<T> 
		*/
		Quaternion<T> operator * (const T s) const  {
			return Quaternion<T>(w * s, x * s, y * s, z * s);
		}


		/** クォータニオンのスカラ除算
		* @param const T s
		* @return Quaternion<T> 
		*/
		Quaternion<T> operator / (const T s) const  {
			if (s <= Math::Epsilon) {
				return std::move(Quaternion<T>(*this));
			}
			return Quaternion<T>(w / s, x / s, y / s, z / s);
		}
		

		/** 共役
		* @param const Quaternion<T> q
		* @return Quaternion<T> 
		*/
		Quaternion<T> operator ~ () const {
			return Quaternion<T>(w, -x, -y, -z);
		}


		/** クォータニオンの加算
		* @param const Quaternion<T> q
		* @return Quaternion<T> &
		*/
		Quaternion<T>& operator += (const Quaternion<T>& q) {
			this->w += q.w;
			this->x += q.x;
			this->y += q.y;
			this->z += q.z;

			return *this;
		}


		/** クォータニオンの減算
		* @param const Quaternion<T> q
		* @return Quaternion<T> &
		*/
		Quaternion<T>& operator -= (const Quaternion<T>& q) {
			this->w -= q.w;
			this->x -= q.x;
			this->y -= q.y;
			this->z -= q.z;

			return *this;
		}


		/** スカラ乗算
		* @param const T q
		* @return Quaternion<T> &
		*/
		Quaternion<T>& operator *= (const T s) {
			this->w *= s;
			this->x *= s;
			this->y *= s;
			this->z *= s;

			return *this;
		}


		/** スカラ除算
		* @param const T q
		* @return Quaternion<T> &
		*/
		Quaternion<T>& operator /= (const T s) {
			if (s <= Math::Epsilon) {
				return *this;
			}

			this->w /= s;
			this->x /= s;
			this->y /= s;
			this->z /= s;

			return *this;
		}


		/**
		* 恒等クォターニオン
		*/
		void SetupIdentity() {
			this->w = 1;
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}


		/** クォータニオンの長さ
		* @return float 長さ
		*/
		T Length() const {
			return Math::Sqrt(x*x + y*y + z*z + w*w);
		}


		/** クォータニオンの2乗の長さ
		* @return float 2乗の長さ
		*/
		T SquaredLength() const {
			return (x*x + y*y + z*z + w*w);
		}


		/**
		* 内積
		*/
		T Dot(const Quaternion<T>& q) const {
			return w * q.w + x * q.x + y * q.y + z * q.z;
		}
		
		
		/**
		* 外積
		*/
		Quaternion<T> Cross(const Quaternion<T>& q) const {
			Vector3<T> v1    = Vector3<T>(  x,   y,   z);
			Vector3<T> v2    = Vector3<T>(q.x, q.y, q.z);
			float dot        = v1.Dot(v2);
			Vector3<T> cross = v1.Cross(v2);
			return Quaternion(w * q.w - dot, cross + v2*w + v1*q.w);
		}

		/**
		* 逆数
		*/
		Quaternion<T> Inverse() const {
			const auto length = SquaredLength();
			if (length <= Math::Epsilon) {
				return Quaternion<T>(w, x, y, z);
			}

			Quaternion<T> q(w, x, y, z);
			q = ~q;
			return q / length;
		}

		/** 
		* 正規化
		*/
		void Normalize() {
			float length = Math::Sqrt(x * x + y * y + z * z + w * w);
			if (length <= Math::Epsilon) {
				length = 1;
			}

			x /= length;
			y /= length;
			z /= length;
			w /= length;
		}

		/**
		* Sphirical Lerp
		*/
		static Quaternion<T> Slerp(const Quaternion<T>& lhs, const Quaternion<T>& rhs, float t) {
			Quaternion<T> q1(lhs);
			Quaternion<T> q2(rhs);
			float cosOmega = q1.Dot(q2);
			if (cosOmega < 0.f) {
				q2 = ~q2;
				cosOmega = - cosOmega;
			} 

			float k0, k1;
			if (cosOmega > 0.9999f) {
				k0 = 1.0f - t;
				k1 = t;
			}
			else {
				const auto sinOmega = Math::Sqrt(1.f - cosOmega* cosOmega);
				const auto omega    = Math::Atan2(sinOmega, cosOmega);
				const auto inverse  = 1.f/sinOmega;

				k0 = Math::Sin((1.f - t) * omega) * inverse;
				k1 = Math::Sin(t * omega) * inverse;
			}


			return Quaternion<T>(q1.w * k0 + q2.w * k1, q1.x * k0+q2.x * k1, 
								 q1.y * k0 + q2.y * k1, q1.z * k0+q2.z * k1);
		}


		/**
		* クォターニオンからから回転角を取り出す
		*/
		static float GetRotationAngle(const Quaternion<T>& q) {
			float tmp =  Math::Clamp(w, -1.0, 1.0);
			float theta = Math::Asin(tmp);

			return theta;
		}
		

		/**
		* クォターニオンから回転軸を取り出す
		*/
		static Axis3f GetRotationAxis(){
			float sinTheta  = 1.f - w * w;

			if (Math::Abs(sinTheta) <= Math::Epsilon) {
				return Axis3f(1.f, 1.f, 1.f);
			}

			float oneOverSinTheta = 1.f / Math::Sqrt(sinTheta);

			return Axis3f(x * oneOverSinTheta,
						  y * oneOverSinTheta,
						  z * oneOverSinTheta);
		}

		/**
		* X軸周りの回転をセットアップします
		*/
		void SetupRotationAxisX(T theta) {
			T thetaOver2 = theta * 0.5f;
			w = Math::Cos(thetaOver2);
			x = Math::Sin(thetaOver2);
			y = 0;
			z = 0;
		}
		

		/**
		* Y軸周りの回転をセットアップする
		*/
		void SetupRotationAxisY(T theta) {
			T thetaOver2 = theta * 0.5f;
			w = Math::Cos(thetaOver2);
			x = 0;
			y = Math::Sin(thetaOver2);
			z = 0;
		}
		

		/**
		* Z軸周りの回転をセットアップする
		*/
		void SetupRotationAxisZ(T theta) {
			T thetaOver2 = theta * 0.5f;
			w = Math::Cos(thetaOver2);
			x = 0;
			y = 0;
			z = Math::Sin(thetaOver2);
		}

		/**
		* 任意軸周りの回転
		*/
		void SetupRotationAxis(const Vector3f& axis, T theta) {
			Assert(Math::Abs(axis.Length() - 1) <= Math::Epsilon);

			T radian   = theta * 0.5;
			T sinTheta = Math::Sin(radian);

			w = Math::Cos(radian);
			x = axis.x * sinTheta;
			y = axis.y * sinTheta;
			z = axis.z * sinTheta;
		}


		/**
		* 回転軸を追加します
		*/
		void AddRotationAxis(const Vector3f& axis, T radian) {
			Quaternion<T> quaternion;
			quaternion.SetRotationAxis(axis, radian);
			(*this) = quaternion.Cross(*this);
		}
	};
}
#endif