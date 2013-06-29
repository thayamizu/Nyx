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
#ifndef NYX_CORE_INCLUDED_MATRIX44_H_
#define NYX_CORE_INCLUDED_MATRIX44_H_
#include "Primitive/Vector3.h"

namespace Nyx  {
	class Matrix44 {
	public:
		/// 4x4�s��
		union {	
			struct{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float Mat[4][4];
		};

		static const Matrix44 Unit;

		static const Matrix44 Zero;

		/**�f�t�H���g�R���X�g���N�^
		* �s��̒l�����ׂă[���ɐݒ肷��
		*/
		Matrix44();

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
		Matrix44(
			float a11, float a12, float a13, float a14, 
			float a21, float a22, float a23, float a24,
			float a31, float a32, float a33, float a34,
			float a41, float a42, float a43, float a44
			);

		/** 
		* �f�X�g���N�^
		*/
		~Matrix44();

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
		void Set(float a11, float a12, float a13, float a14, 
			float a21, float a22, float a23, float a24,
			float a31, float a32, float a33, float a34,
			float a41, float a42, float a43, float a44);

		/**
		* ���Z
		* @param �E�Ӓl
		* @return ���Z����
		*/
		Matrix44 operator +(const Matrix44& mat) const;

		/**
		* ���Z
		* @param �E�Ӓl
		* @return ���Z����
		*/
		Matrix44 operator -(const Matrix44& mat) const;

		/**
		* ��Z
		* @param �E�Ӓl
		* @return ��Z����
		*/
		Matrix44 operator *(const float s) const;

		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Matrix44 operator *(const Matrix44& mat) const;

		/**
		* ���Z
		* @param �E�Ӓl
		* @return ���Z����
		*/
		Matrix44 operator /(const float s) const;

		/**
		* ���Z
		* @param �E�Ӓl 
		* @return ���Z���� 
		*/
		Matrix44& operator +=(const Matrix44 & mat);

		/**
		* ���Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Matrix44& operator -=(const Matrix44 & mat);

		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Matrix44& operator *=(const float s);

		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Matrix44& operator *=(const Matrix44& s);

		/**
		* ���Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Matrix44& operator /=(const float s);

		/**
		*���
		*@param �E�Ӓl
		*@return �������
		*/
		Matrix44& operator = (const Matrix44& mat);

		bool Equal(const Matrix44 & m);
		bool operator == (const Matrix44 &m);
		bool operator != (const Matrix44 &m);

		/**
		* �s��
		* @return �s�񎮂̒l
		*/
		float Determinant();

		/**
		* �s��̓]�u
		* @return �]�u�s��
		*/
		Matrix44& Transpose();

		/**
		* �t�s��
		* @return �t�s��
		*/
		float Inverse();

		/*static Matrix44&& SetupTransform();
		static Matrix44&& SetupRotate();
		static Matrix44&& SetupScale();
		static Matrix44&& SetupTranslate();
		*/
		static Matrix44& Transform(
			Matrix44* out, 
			float sx, float sy, float sz, 
			float rx, float ry, float rz, 
			float tx, float ty, float tz);
		static Matrix44& Transform(Matrix44* out, Vector3f sv, Vector3f rv, Vector3f tv);

		static Matrix44& Translate(Matrix44* out, float tx, float ty, float tz);
		//static Matrix44& Translate(Matrix44* out, Vector3f tv);

		static Matrix44& Scale(Matrix44* out, float sx, float sy, float sz);
		//static Matrix44& Scale(Matrix44* out, Vector3f sv);

		static Matrix44& RotateX(Matrix44* out, float angle);
		static Matrix44& RotateY(Matrix44* out, float angle);
		static Matrix44& RotateZ(Matrix44* out, float angle);
		static Matrix44& RotateZXY(Matrix44* out, float roll, float pitch, float yaw);

		/**
		static EulerAngles ToQuaternion(); 
		static EulerAngles ToEulerAngles(); 
		*/
	};
};

//-----------------------------------------------------
#endif
//END OF NYX_ALL_H
//-----------------------------------------------------