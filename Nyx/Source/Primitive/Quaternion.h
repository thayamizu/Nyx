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

	template<typename T>
	class Quaternion  {
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic_type.");
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
		Quaternion<T>&& operator + (const Quaternion<T>& q) const {
			return std::move(Quaternion<T>(w + q.w, x + q.x, y + q.y, z + q.z));
		}


		/** クォータニオンの減算
		* @param const Quaternion<T> q
		* @return Quaternion<T> 
		*/
		Quaternion<T>&& operator - (const Quaternion<T>& q) const {
			return std::move(Quaternion<T>(w - q.w, x - q.x, y - q.y, z - q.z));
		}


		/** クォータニオンのスカラ乗算
		* @param const Quaternion<T> q
		* @return Quaternion<T> 
		*/
		Quaternion<T>&& operator * (const T s) const  {
			return std::move(Quaternion<T>(w * s, x * s, y * s, z * s));
		}


		/** クォータニオンのスカラ除算
		* @param const T s
		* @return Quaternion<T> 
		*/
		Quaternion<T>&& operator / (const T s) const  {
			if (s <= Math::Epsilon) {
				return std::move(Quaternion<T>(*this));
			}
			return std::move(Quaternion<T>(w / s, x / s, y / s, z / s));
		}
		

		/** 共役
		* @param const Quaternion<T> q
		* @return Quaternion<T> &
		*/
		Quaternion<T>&& operator ~ () const {
			return std::move(Quaternion<T>(w, -x, -y, -z));
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
		float Length() const {
			return Math::Sqrt(x*x + y*y + z*z + w*w);
		}


		/** クォータニオンの2乗の長さ
		* @return float 2乗の長さ
		*/
		float SquaredLength() const {
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
		static Quaternion<T> SLerp(const Quaternion<T>& rhs, const Quaternion<T>& q2, float t) {
			return Quaternion<T>();
		}

		/**
		* Sphirical and Quadrangle
		*/
		static Quaternion<T> Squad() {
			return Quaternion<T>();
		}

		/**
		*/
		static float getRotationAngle(const Quaternion<T>& q) {
			return 1.f;
		}
		/**
		*/
		static EulerAngles getEulerAngle(const Quaternion<T>& q) {
			return 1.f;
		}


		/**
		* 回転行列に変換します
		*/
		static Matrix44 ToRotaionMatrix44() {
			return Matrix44::Unit;
		}
	};
}
#endif