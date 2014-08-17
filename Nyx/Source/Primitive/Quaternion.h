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

namespace nyx {

	template<typename T=float>
	class quaternion  {
		static_assert(std::is_floating_point<T>::value, "T required floating_point.");
	public:
		T w;///< w�l
		T x;///< x�l
		T y;///< y�l
		T z;///< z�l


		///�[���萔
		static const quaternion<T> ZERO;
		/** 
		* �R���X�g���N�^
		*/
		quaternion<T>()
			:w(0), x(0), y(0), z(0) {
		}


		/** �R���X�g���N�^
		* @param Vector4f
		*/
		quaternion<T>(const float w, const vector3<T>& v) 
			:w(w), x(v.x), y(v.y), z(v.z) {
		}


		/** �R���X�g���N�^
		* @param Vector4f
		*/
		quaternion<T>(const vector4<T>& v) 
			:w(v.w), x(v.x), y(v.y), z(v.z) {
		}


		/** �R���X�g���N�^
		* @param T w
		* @param T x
		* @param T y
		* @param T z
		*/
		quaternion<T> (const T w, const T x, const T y, const T z) {
			this->w = w;
			this->x = x;
			this->y = y;
			this->z = z;
		}
		

		/** �N�H�[�^�j�I���̉��Z
		* @param const Quaternion<T> q
		* @return Quaternion<T>
		*/
		quaternion<T> operator + (const quaternion<T>& q) const {
			return quaternion<T>(w + q.w, x + q.x, y + q.y, z + q.z);
		}


		/** �N�H�[�^�j�I���̌��Z
		* @param const Quaternion<T> q
		* @return Quaternion<T> 
		*/
		quaternion<T> operator - (const quaternion<T>& q) const {
			return quaternion<T>(w - q.w, x - q.x, y - q.y, z - q.z);
		}


		/** �N�H�[�^�j�I���̃X�J����Z
		* @param const Quaternion<T> q
		* @return Quaternion<T> 
		*/
		quaternion<T> operator * (const T s) const  {
			return quaternion<T>(w * s, x * s, y * s, z * s);
		}


		/** �N�H�[�^�j�I���̃X�J�����Z
		* @param const T s
		* @return Quaternion<T> 
		*/
		quaternion<T> operator / (const T s) const  {
			if (s <= math::EPSILON) {
				return *this;
			}
			return quaternion<T>(w / s, x / s, y / s, z / s);
		}
		

		/** ����
		* @param const Quaternion<T> q
		* @return Quaternion<T> 
		*/
		quaternion<T> operator ~ () const {
			return quaternion<T>(w, -x, -y, -z);
		}


		/** �N�H�[�^�j�I���̉��Z
		* @param const Quaternion<T> q
		* @return Quaternion<T> &
		*/
		quaternion<T>& operator += (const quaternion<T>& q) {
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
		quaternion<T>& operator -= (const quaternion<T>& q) {
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
		quaternion<T>& operator *= (const T s) {
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
		quaternion<T>& operator /= (const T s) {
			if (s <= math::EPSILON) {
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
		void set_identity() {
			this->w = 1;
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}


		/** �N�H�[�^�j�I���̒���
		* @return float ����
		*/
		T norm() const {
			return math::sqrt(x*x + y*y + z*z + w*w);
		}


		/** �N�H�[�^�j�I����2��̒���
		* @return float 2��̒���
		*/
		T squared_norm() const {
			return (x*x + y*y + z*z + w*w);
		}


		/**
		* ����
		*/
		T dot(const quaternion<T>& q) const {
			return w * q.w + x * q.x + y * q.y + z * q.z;
		}
		
		
		/**
		* �O��
		*/
		quaternion<T> cross(const quaternion<T>& q) const {
			vector3<T> v1    = vector3<T>(  x,   y,   z);
			vector3<T> v2    = vector3<T>(q.x, q.y, q.z);
			float dot        = v1.dot(v2);
			vector3<T> cross = v1.cross(v2);
			return quaternion(w * q.w - dot, cross + v2*w + v1*q.w);
		}

		/**
		* �t��
		*/
		quaternion<T> inverse() const {
			const auto length = squared_norm();
			if (length <= math::EPSILON) {
				return quaternion<T>(w, x, y, z);
			}

			quaternion<T> q(w, x, y, z);
			q = ~q;
			return q / length;
		}

		/** 
		* ���K��
		*/
		void normalize() {
			float length = math::sqrt(x * x + y * y + z * z + w * w);
			if (length <= math::EPSILON) {
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
		static quaternion<T> slerp(const quaternion<T>& lhs, const quaternion<T>& rhs, float t) {
			quaternion<T> q1(lhs);
			quaternion<T> q2(rhs);
			float cosOmega = q1.dot(q2);
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
				const auto sinOmega = math::sqrt(1.f - cosOmega* cosOmega);
				const auto omega    = math::atan2(sinOmega, cosOmega);
				const auto inverse  = 1.f/sinOmega;

				k0 = math::sin((1.f - t) * omega) * inverse;
				k1 = math::sin(t * omega) * inverse;
			}


			return quaternion<T>(q1.w * k0 + q2.w * k1, q1.x * k0+q2.x * k1, 
								 q1.y * k0 + q2.y * k1, q1.z * k0+q2.z * k1);
		}


		/**
		* �N�H�^�[�j�I�����炩���]�p�����o��
		*/
		static float get_rotation_angle(const quaternion<T>& q) {
			float tmp =  math::clamp(w, -1.0, 1.0);
			float theta = math::asin(tmp);

			return theta;
		}
		

		/**
		* �N�H�^�[�j�I�������]�������o��
		*/
		static axis3f get_rotation_axis(){
			float sinTheta  = 1.f - w * w;

			if (math::abs(sinTheta) <= math::EPSILON) {
				return axis3f(1.f, 1.f, 1.f);
			}

			float oneOverSinTheta = 1.f / math::sqrt(sinTheta);

			return axis3f(x * oneOverSinTheta,
						  y * oneOverSinTheta,
						  z * oneOverSinTheta);
		}

		/**
		* X������̉�]���Z�b�g�A�b�v���܂�
		*/
		void set_rotation_axis_x(T theta) {
			T thetaOver2 = theta * 0.5f;
			w = math::cos(thetaOver2);
			x = math::sin(thetaOver2);
			y = 0;
			z = 0;
		}
		

		/**
		* Y������̉�]���Z�b�g�A�b�v����
		*/
		void set_rotation_axis_y(T theta) {
			T thetaOver2 = theta * 0.5f;
			w = math::cos(thetaOver2);
			x = 0;
			y = math::sin(thetaOver2);
			z = 0;
		}
		

		/**
		* Z������̉�]���Z�b�g�A�b�v����
		*/
		void set_rotation_axis_z(T theta) {
			T thetaOver2 = theta * 0.5f;
			w = math::cos(thetaOver2);
			x = 0;
			y = 0;
			z = math::sin(thetaOver2);
		}

		/**
		* �C�ӎ�����̉�]
		*/
		void set_rotation_axis(const vector3f& axis, T theta) {
			NYX_ASSERT(math::abs(axis.Length() - 1) <= math::EPSILON);

			T radian   = theta * 0.5;
			T sinTheta = math::sin(radian);

			w = math::cos(radian);
			x = axis.x * sinTheta;
			y = axis.y * sinTheta;
			z = axis.z * sinTheta;
		}


		/**
		* ��]����ǉ����܂�
		*/
		void add_rotation_axis(const vector3f& axis, T radian) {
			quaternion<T> quaternion;
			quaternion.set_rotation_axis(axis, radian);
			(*this) = quaternion.cross(*this);
		}
	};


	//--------------------------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------------------------
	// �[���l����
	template<typename T>
	const quaternion<T>  quaternion<T>::ZERO(0, 0, 0, 0);
}
#endif