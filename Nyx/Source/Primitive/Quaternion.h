/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
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
		T w;///< w�l
		T x;///< x�l
		T y;///< y�l
		T z;///< z�l

		/** 
		* �R���X�g���N�^
		*/
		Quaternion<T>()
			:w(0), x(0), y(0), z(0) {
		}


		/** �R���X�g���N�^
		* @param Vector4f
		*/
		Quaternion<T>(const float w, const Vector3<T>& v) 
			:w(w), x(v.x), y(v.y), z(v.z) {
		}


		/** �R���X�g���N�^
		* @param Vector4f
		*/
		Quaternion<T>(const Vector4<T>& v) 
			:w(v.w), x(v.x), y(v.y), z(v.z) {
		}


		/** �R���X�g���N�^
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
		

		/** �N�H�[�^�j�I���̉��Z
		* @param const Quaternion<T> q
		* @return Quaternion<T>
		*/
		Quaternion<T>&& operator + (const Quaternion<T>& q) const {
			return std::move(Quaternion<T>(w + q.w, x + q.x, y + q.y, z + q.z));
		}


		/** �N�H�[�^�j�I���̌��Z
		* @param const Quaternion<T> q
		* @return Quaternion<T> 
		*/
		Quaternion<T>&& operator - (const Quaternion<T>& q) const {
			return std::move(Quaternion<T>(w - q.w, x - q.x, y - q.y, z - q.z));
		}


		/** �N�H�[�^�j�I���̃X�J����Z
		* @param const Quaternion<T> q
		* @return Quaternion<T> 
		*/
		Quaternion<T>&& operator * (const T s) const  {
			return std::move(Quaternion<T>(w * s, x * s, y * s, z * s));
		}


		/** �N�H�[�^�j�I���̃X�J�����Z
		* @param const T s
		* @return Quaternion<T> 
		*/
		Quaternion<T>&& operator / (const T s) const  {
			if (s <= Math::Epsilon) {
				return std::move(Quaternion<T>(*this));
			}
			return std::move(Quaternion<T>(w / s, x / s, y / s, z / s));
		}
		

		/** ����
		* @param const Quaternion<T> q
		* @return Quaternion<T> &
		*/
		Quaternion<T>&& operator ~ () const {
			return std::move(Quaternion<T>(w, -x, -y, -z));
		}


		/** �N�H�[�^�j�I���̉��Z
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


		/** �N�H�[�^�j�I���̌��Z
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


		/** �X�J����Z
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


		/** �X�J�����Z
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
		* �P���N�H�^�[�j�I��
		*/
		void SetupIdentity() {
			this->w = 1;
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}


		/** �N�H�[�^�j�I���̒���
		* @return float ����
		*/
		float Length() const {
			return Math::Sqrt(x*x + y*y + z*z + w*w);
		}


		/** �N�H�[�^�j�I����2��̒���
		* @return float 2��̒���
		*/
		float SquaredLength() const {
			return (x*x + y*y + z*z + w*w);
		}


		/**
		* ����
		*/
		T Dot(const Quaternion<T>& q) const {
			return w * q.w + x * q.x + y * q.y + z * q.z;
		}
		
		
		/**
		* �O��
		*/
		Quaternion<T> Cross(const Quaternion<T>& q) const {
			Vector3<T> v1    = Vector3<T>(  x,   y,   z);
			Vector3<T> v2    = Vector3<T>(q.x, q.y, q.z);
			float dot        = v1.Dot(v2);
			Vector3<T> cross = v1.Cross(v2);
			return Quaternion(w * q.w - dot, cross + v2*w + v1*q.w);
		}


		/** 
		* ���K��
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
		* ��]�s��ɕϊ����܂�
		*/
		static Matrix44 ToRotaionMatrix44() {
			return Matrix44::Unit;
		}
	};
}
#endif