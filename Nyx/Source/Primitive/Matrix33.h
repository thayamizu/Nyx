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
#ifndef NYX_CORE_INCLUDED_MATRIX33_H_
#define NYX_CORE_INCLUDED_MATRIX33_H_
#include "Primitive/Vector3.h"
#include "Primitive/EulerAngles.h"
#include "Primitive/Quaternion.h"

namespace Nyx {

	class Matrix33 {
	public:
		/// 3x3�s��
		union {	
			struct{
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			float Mat[3][3];
		};
		static const Matrix33 Unit;

		static const Matrix33 Zero;

		/**
		* �f�t�H���g�R���X�g���N�^
		* �s��̒l�����ׂă[���ɐݒ肷��
		*/
		Matrix33();

		/**
		* �R���X�g���N�^
		* �s��̊e�v�f�ɔC�ӂ̒l��ݒ肷��
		* @param a11 
		* @param a12
		* @param a13
		* @param a21
		* @param a22
		* @param a23
		* @param a31
		* @param a32
		* @param a33
		*/
		Matrix33(float a11, float a12, float a13, 
			float a21, float a22, float a23,
			float a31, float a32, float a33);
		
		/**
		* �s��̊e�v�f�ɔC�ӂ̒l��ݒ肷��
		* @param a11 
		* @param a12
		* @param a13
		* @param a21
		* @param a22
		* @param a23
		* @param a31
		* @param a32
		* @param a33
		*/
		void Set(float a11, float a12, float a13,
			float a21, float a22, float a23,
			float a31, float a32, float a33);


		/**
		* ���Z
		* @param �E�Ӓl
		* @return ���Z����
		*/
		Matrix33 operator +(const Matrix33& mat) const;


		/**
		* ���Z
		* @param �E�Ӓl
		* @return ���Z����
		*/
		Matrix33 operator -(const Matrix33& mat) const;


		/**
		* ��Z
		* @param �E�Ӓl
		* @return ��Z����
		*/
		Matrix33 operator *(const float s) const;


		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Matrix33 operator *(const Matrix33& mat) const;


		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Vector3f operator *(const Vector3f& v) const;


		/**
		* ���Z
		* @param �E�Ӓl
		* @return ���Z����
		*/
		Matrix33 operator /(const float s) const;


		/**
		* ���Z
		* @param �E�Ӓl 
		* @return ���Z���� 
		*/
		Matrix33& operator +=(const Matrix33 & mat);


		/**
		* ���Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Matrix33& operator -=(const Matrix33 & mat);


		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Matrix33& operator *=(const float s);


		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Matrix33& operator *=(const Matrix33& s);


		/**
		* ���Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Matrix33& operator /=(const float s);

		bool operator==(const Matrix33& mat) const {
			return (
			Mat[0][0] == mat.Mat[0][0] && 
			Mat[0][1] == mat.Mat[0][1] &&
			Mat[0][2] == mat.Mat[0][2] &&
			
			Mat[1][0] == mat.Mat[1][0] &&
			Mat[1][1] == mat.Mat[1][1] &&
			Mat[1][2] == mat.Mat[1][2] &&
			
			Mat[2][0] == mat.Mat[2][0] && 
			Mat[2][1] == mat.Mat[2][1] &&
			Mat[2][2] == mat.Mat[2][2]);
		}


		bool operator != (const Matrix33& mat) const {
			return !(*this == mat);
		}


		void SetupIdentity();


		/**
		* �s��
		* @return �s�񎮂̒l
		*/
		float Determinant();


		/**
		* �s��̓]�u
		* @return �]�u�s��
		*/
		Matrix33 Transpose();


		/**
		* �t�s��
		* @return �t�s��
		*/
		Matrix33 Inverse();

		void SetupRotate(const EulerAngles& orientation);

		void FromObjectToInertial(const Quaternion<float> & q);
		void FromObjectToInertial(const Vector3<float> & v);
		void FromInertialToObject(const Quaternion<float> &q);
		void FromInertialToObject(const Vector3<float>& v);
	};
}
//-----------------------------------------------------
#endif
//END OF NYX_MATRIX33_H
//-----------------------------------------------------