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
/*@file
*@brief ���Z
*�e�X�g�����Ȃ̂ŁA�ł���Ύg��Ȃ��ł��������B
*Todo�F�P�̃e�X�g�̎��{
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
		float w;///< w�l
		float x;///< x�l
		float y;///< y�l
		float z;///< z�l

		/** 
		* �R���X�g���N�^
		*/
		Quaternion()
			:w(0), x(0), y(0), z(0) {
		}


		/** �R���X�g���N�^
		* @param Vector4f
		*/
		Quaternion(const Vector4f& v) 
			:w(v.w), x(v.x), y(v.y), z(v.z) {
		}


		/** �R���X�g���N�^
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
		

		/** �N�H�[�^�j�I���̉��Z
		* @param const Quaternion q
		* @return Quaternion
		*/
		Quaternion&& operator + (const Quaternion& q) const {
			return std::move(Quaternion(w + q.w, x + q.x, y + q.y, z + q.z));
		}


		/** �N�H�[�^�j�I���̌��Z
		* @param const Quaternion q
		* @return Quaternion 
		*/
		Quaternion&& operator - (const Quaternion& q) const {
			return std::move(Quaternion(w - q.w, x - q.x, y - q.y, z - q.z));
		}


		/** �N�H�[�^�j�I���̃X�J����Z
		* @param const Quaternion q
		* @return Quaternion 
		*/
		Quaternion&& operator * (const float s) const  {
			return std::move(Quaternion(w * s, x * s, y * s, z * s));
		}


		/** �N�H�[�^�j�I���̃X�J�����Z
		* @param const float s
		* @return Quaternion 
		*/
		Quaternion&& operator / (const float s) const  {
			if (s <= Math::Epsilon) {
				return std::move(Quaternion(*this));
			}
			return std::move(Quaternion(w / s, x / s, y / s, z / s));
		}
		

		/** ����
		* @param const Quaternion q
		* @return Quaternion &
		*/
		Quaternion&& operator ~ () const {
			return std::move(Quaternion(-w, -x, -y, -z));
		}


		/** �N�H�[�^�j�I���̉��Z
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


		/** �N�H�[�^�j�I���̌��Z
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


		/** �X�J����Z
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


		/** �X�J�����Z
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
		* �P���N�H�^�[�j�I��
		*/
		void SetupIdentity() {
			this->w = 1;
			this->x = 1;
			this->y = 1;
			this->z = 1;
		}


		/** �N�H�[�^�j�I���̒���
		* @return float ����
		*/
		float Length() {
			return Math::Sqrt(x*x + y*y + z*z + w*w);
		}


		/** �N�H�[�^�j�I����2��̒���
		* @return float 2��̒���
		*/
		float SquaredLength() {
			return (x*x + y*y + z*z + w*w);
		}


		/**
		* ��Z
		*/
		Quaternion Product(const Quaternion& q) {
			return q;
		}


		/** 
		* �t��
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
		* ���K��
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
		* ��]�s��ɕϊ����܂�
		*/
		static Matrix44 ToRotaionMatrix44() {
			return Matrix44::Unit;
		}
	};
}
#endif