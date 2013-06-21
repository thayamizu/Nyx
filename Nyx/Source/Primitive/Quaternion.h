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
/*@file
*@brief 演算
*テスト実装なので、できれば使わないでください。
*Todo：単体テストの実施
*@author t.hayamizu
*/
#ifndef NYX_CORE_INCLUDED_QUATERNION_H_
#define NYX_CORE_INCLUDED_QUATERNION_H_
#include "Primitive/EulerAngles.h"
#include "Primitive/Matrix44.h"
#include "Primitive/Vector3.h"
#include "Primitive/Vector4.h"

namespace Nyx {
	class Quaternion  {
	public:
		float w;///< w値
		float x;///< x値
		float y;///< y値
		float z;///< z値

		/** 
		* コンストラクタ
		*/
		Quaternion()
			:w(0), x(0), y(0), z(0) {
		}


		/** コンストラクタ
		* @param Vector4f
		*/
		Quaternion(const Vector4f& v) 
			:w(v.w), x(v.x), y(v.y), z(v.z) {
		}


		/** コンストラクタ
		* @param float w
		* @param float x
		* @param float y
		* @param float z
		*/
		Quaternion (const float w, const float x, const float y, const float z) {
			this->w = w;
			this->x = x;
			this->y = y;
			this->z = z;
		}
		

		/** クォータニオンの加算
		* @param const Quaternion q
		* @return Quaternion
		*/
		Quaternion&& operator + (const Quaternion& q) const {
			return std::move(Quaternion(w + q.w, x + q.x, y + q.y, z + q.z));
		}


		/** クォータニオンの減算
		* @param const Quaternion q
		* @return Quaternion 
		*/
		Quaternion&& operator - (const Quaternion& q) const {
			return std::move(Quaternion(w - q.w, x - q.x, y - q.y, z - q.z));
		}


		/** クォータニオンのスカラ乗算
		* @param const Quaternion q
		* @return Quaternion 
		*/
		Quaternion&& operator * (const float s) const  {
			return std::move(Quaternion(w * s, x * s, y * s, z * s));
		}


		/** クォータニオンのスカラ除算
		* @param const float s
		* @return Quaternion 
		*/
		Quaternion&& operator / (const float s) const  {
			if (s <= Math::Epsilon) {
				return std::move(Quaternion(*this));
			}
			return std::move(Quaternion(w / s, x / s, y / s, z / s));
		}
		

		/** 共役
		* @param const Quaternion q
		* @return Quaternion &
		*/
		Quaternion&& operator ~ () const {
			return std::move(Quaternion(-w, -x, -y, -z));
		}


		/** クォータニオンの加算
		* @param const Quaternion q
		* @return Quaternion &
		*/
		Quaternion& operator += (const Quaternion& q) {
			this->w += q.w;
			this->x += q.x;
			this->y += q.y;
			this->z += q.z;

			return *this;
		}


		/** クォータニオンの減算
		* @param const Quaternion q
		* @return Quaternion &
		*/
		Quaternion& operator -= (const Quaternion& q) {
			this->w -= q.w;
			this->x -= q.x;
			this->y -= q.y;
			this->z -= q.z;

			return *this;
		}


		/** スカラ乗算
		* @param const float q
		* @return Quaternion &
		*/
		Quaternion& operator *= (const float s) {
			this->w *= s;
			this->x *= s;
			this->y *= s;
			this->z *= s;

			return *this;
		}


		/** スカラ除算
		* @param const float q
		* @return Quaternion &
		*/
		Quaternion& operator /= (const float s) {
			if (s <= Math::Epsilon) {
				return *this;
			}

			this->w *= s;
			this->x *= s;
			this->y *= s;
			this->z *= s;

			return *this;
		}


		/**
		* 恒等クォターニオン
		*/
		void SetupIdentity() {
			this->w = 1;
			this->x = 1;
			this->y = 1;
			this->z = 1;
		}


		/** クォータニオンの長さ
		* @return float 長さ
		*/
		float Length() {
			return Math::Sqrt(x*x + y*y + z*z + w*w);
		}


		/** クォータニオンの2乗の長さ
		* @return float 2乗の長さ
		*/
		float SquaredLength() {
			return (x*x + y*y + z*z + w*w);
		}


		/**
		* 乗算
		*/
		Quaternion Product(const Quaternion& q) {
			return q;
		}


		/** 
		* 逆元
		* @return Quaternion&
		*/
		Quaternion& Inverse() {
			const float abs2 = Math::Pow2(Math::Abs(x * x + y * y + z * z + w * w));
			if (abs2 <= Math::Epsilon) {
				return *this;
			}

			*this = ~(*this)/abs2;
			return *this;
		}


		/** 
		* 正規化
		*/
		void Normalize() {
			float length = Math::Sqrt(x * x + y * y + z * z + w * w);
			if (length <= Math::Epsilon) {
				length = 1;
			}
			const float inverse = 1/length;

			x *= inverse;
			y *= inverse;
			z *= inverse;
			w *= inverse;
		}


		/**
		* SLerp
		*/
		Quaternion SLerp() {
			return Quaternion();
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