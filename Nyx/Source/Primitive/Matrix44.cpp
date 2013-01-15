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
#include "PCH/PCH.h"
#include "Primitive/Vector3.h"
#include "Primitive/Matrix44.h"
#include "Debug/Assert.h"

namespace Nyx {
	//--------------------------------------------------------------------------------------
	// �萔
	//--------------------------------------------------------------------------------------
	const Matrix44 Matrix44::Unit(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);

	const Matrix44 Matrix44::Zero(
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f);

	//--------------------------------------------------------------------------------------
	// �R���X�g���N�^�E�f�X�g���N�^
	//--------------------------------------------------------------------------------------
	/**�f�t�H���g�R���X�g���N�^
	* �s��̒l�����ׂă[���ɐݒ肷��
	*/
	Matrix44::Matrix44() {

	}

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
	Matrix44::Matrix44(
		float a11, float a12, float a13, float a14, 
		float a21, float a22, float a23, float a24,
		float a31, float a32, float a33, float a34,
		float a41, float a42, float a43, float a44
		)
		:
	_11(a11), _12(a12), _13(a13), _14(a14),
		_21(a21), _22(a22), _23(a23), _24(a24),
		_31(a31), _32(a32), _33(a33), _34(a34),
		_41(a41), _42(a42), _43(a43), _44(a44)
	{
	}
	/** 
	* �f�X�g���N�^
	*/
	Matrix44::~Matrix44() {

	}

	//--------------------------------------------------------------------------------------
	// �l�̐ݒ�
	//--------------------------------------------------------------------------------------
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
	void Matrix44::Set(float a11, float a12, float a13, float a14, 
		float a21, float a22, float a23, float a24,
		float a31, float a32, float a33, float a34,
		float a41, float a42, float a43, float a44) {

			Mat[0][0] = a11; Mat[0][1]=a12; Mat[0][2] =a13; Mat[0][3]=a14;
			Mat[1][0] = a21; Mat[1][1]=a22; Mat[1][2] =a23; Mat[1][3]=a24;
			Mat[2][0] = a31; Mat[2][1]=a32; Mat[2][2] =a33; Mat[2][3]=a34;
			Mat[3][0] = a41; Mat[3][1]=a42; Mat[3][2] =a43; Mat[3][3]=a44;
	}



	//--------------------------------------------------------------------------------------
	// ���Z
	//--------------------------------------------------------------------------------------
	/**
	* ���Z
	* @param �E�Ӓl
	* @return ���Z����
	*/
	Matrix44 Matrix44::operator +(const Matrix44& m) const {
		return Matrix44(
			Mat[0][0] + m.Mat[0][0], Mat[0][1] +m.Mat[0][1], Mat[0][2]+ m.Mat[0][2],Mat[0][3]+ m.Mat[0][3],
			Mat[1][0] + m.Mat[1][0], Mat[1][1] +m.Mat[1][1], Mat[1][2]+ m.Mat[1][2],Mat[1][3]+ m.Mat[1][3],
			Mat[2][0] + m.Mat[2][0], Mat[2][1] +m.Mat[2][1], Mat[2][2]+ m.Mat[2][2],Mat[2][3]+ m.Mat[2][3],
			Mat[3][0] + m.Mat[3][0], Mat[3][1] +m.Mat[3][1], Mat[3][2]+ m.Mat[3][2],Mat[3][3]+ m.Mat[3][3]);
	}

	/**
	* ���Z
	* @param �E�Ӓl
	* @return ���Z����
	*/
	Matrix44 Matrix44::operator -(const Matrix44& m) const {
		return Matrix44(
			Mat[0][0] - m.Mat[0][0], Mat[0][1] - m.Mat[0][1], Mat[0][2] - m.Mat[0][2], Mat[0][3] - m.Mat[0][3],
			Mat[1][0] - m.Mat[1][0], Mat[1][1] - m.Mat[1][1], Mat[1][2] - m.Mat[1][2], Mat[1][3] - m.Mat[1][3],
			Mat[2][0] - m.Mat[2][0], Mat[2][1] - m.Mat[2][1], Mat[2][2] - m.Mat[2][2], Mat[2][3] - m.Mat[2][3],
			Mat[3][0] - m.Mat[3][0], Mat[3][1] - m.Mat[3][1], Mat[3][2] - m.Mat[3][2], Mat[3][3] - m.Mat[3][3]);
	}
	/**
	* ��Z
	* @param �E�Ӓl
	* @return ��Z����
	*/
	Matrix44 Matrix44::operator *(const float s) const {
		return Matrix44(
			Mat[0][0] * s, Mat[0][1] * s, Mat[0][2] * s, Mat[0][3] * s,
			Mat[1][0] * s, Mat[1][1] * s, Mat[1][2] * s, Mat[1][3] * s,
			Mat[2][0] * s, Mat[2][1] * s, Mat[2][2] * s, Mat[2][3] * s,
			Mat[3][0] * s, Mat[3][1] * s, Mat[3][2] * s, Mat[3][3] * s
			);
	}
	/**
	* ��Z
	* @param �E�Ӓl 
	* @return ��Z����
	*/
	Matrix44 Matrix44::operator *(const Matrix44& mat) const {
		return Matrix44(

			Mat[0][0]*mat.Mat[0][0] + Mat[0][1]*mat.Mat[1][0] + Mat[0][2]*mat.Mat[2][0] + Mat[0][3] * mat.Mat[3][0],  
			Mat[0][0]*mat.Mat[0][1] + Mat[0][1]*mat.Mat[1][1] + Mat[0][2]*mat.Mat[2][1] + Mat[0][3] * mat.Mat[3][1], 
			Mat[0][0]*mat.Mat[0][2] + Mat[0][1]*mat.Mat[1][2] + Mat[0][2]*mat.Mat[2][2] + Mat[0][3] * mat.Mat[3][2], 
			Mat[0][0]*mat.Mat[0][3] + Mat[0][1]*mat.Mat[1][3] + Mat[0][2]*mat.Mat[2][3] + Mat[0][3] * mat.Mat[3][3], 

			Mat[1][0]*mat.Mat[0][0] + Mat[1][1]*mat.Mat[1][0] + Mat[1][2]*mat.Mat[2][0] + Mat[1][3] * mat.Mat[3][0],
			Mat[1][0]*mat.Mat[0][1] + Mat[1][1]*mat.Mat[1][1] + Mat[1][2]*mat.Mat[2][1] + Mat[1][3] * mat.Mat[3][1],
			Mat[1][0]*mat.Mat[0][2] + Mat[1][1]*mat.Mat[1][2] + Mat[1][2]*mat.Mat[2][2] + Mat[1][3] * mat.Mat[3][2], 
			Mat[1][0]*mat.Mat[0][3] + Mat[1][1]*mat.Mat[1][3] + Mat[1][2]*mat.Mat[2][3] + Mat[1][3] * mat.Mat[3][3], 

			Mat[2][0]*mat.Mat[0][0] + Mat[2][1]*mat.Mat[1][0] + Mat[2][2]*mat.Mat[2][0] + Mat[2][3] * mat.Mat[3][0], 
			Mat[2][0]*mat.Mat[0][1] + Mat[2][1]*mat.Mat[1][1] + Mat[2][2]*mat.Mat[2][1] + Mat[2][3] * mat.Mat[3][1], 
			Mat[2][0]*mat.Mat[0][2] + Mat[2][1]*mat.Mat[1][2] + Mat[2][2]*mat.Mat[2][2] + Mat[2][3] * mat.Mat[3][2], 
			Mat[2][0]*mat.Mat[0][3] + Mat[2][1]*mat.Mat[1][3] + Mat[2][2]*mat.Mat[2][3] + Mat[2][3] * mat.Mat[3][3], 

			Mat[3][0]*mat.Mat[0][0] + Mat[3][1]*mat.Mat[1][0] + Mat[3][2]*mat.Mat[3][0] + Mat[3][3] * mat.Mat[3][0], 
			Mat[3][0]*mat.Mat[0][1] + Mat[3][1]*mat.Mat[1][1] + Mat[3][2]*mat.Mat[3][1] + Mat[3][3] * mat.Mat[3][1], 
			Mat[3][0]*mat.Mat[0][2] + Mat[3][1]*mat.Mat[1][2] + Mat[3][2]*mat.Mat[3][2] + Mat[3][3] * mat.Mat[3][2], 
			Mat[3][0]*mat.Mat[0][3] + Mat[3][1]*mat.Mat[1][3] + Mat[3][2]*mat.Mat[3][3] + Mat[3][3] * mat.Mat[3][3]	
		);
	}



	/**
	* ���Z
	* @param �E�Ӓl
	* @return ���Z����
	*/
	Matrix44 Matrix44::operator /(float s) const {
		if (s==0.f) {s=1;}
		return Matrix44(
			Mat[0][0] / s, Mat[0][1] / s, Mat[0][2] / s, Mat[0][3] / s,
			Mat[1][0] / s, Mat[1][1] / s, Mat[1][2] / s, Mat[1][3] / s,
			Mat[2][0] / s, Mat[2][1] / s, Mat[2][2] / s, Mat[2][3] / s,
			Mat[3][0] / s, Mat[3][1] / s, Mat[3][2] / s, Mat[3][3] / s
			);
	}

	//--------------------------------------------------------------------------------------
	// ������Z
	//--------------------------------------------------------------------------------------
	/**
	* ���Z
	* @param �E�Ӓl 
	* @return ���Z���� 
	*/
	Matrix44& Matrix44::operator +=(const Matrix44 & mat) {
		Mat[0][0] += mat.Mat[0][0];
		Mat[0][1] += mat.Mat[0][1];
		Mat[0][2] += mat.Mat[0][2];
		Mat[0][3] += mat.Mat[0][3];

		Mat[1][0] += mat.Mat[1][0];
		Mat[1][1] += mat.Mat[1][1];
		Mat[1][2] += mat.Mat[1][2];
		Mat[1][3] += mat.Mat[1][3];	

		Mat[2][0] += mat.Mat[2][0];
		Mat[2][1] += mat.Mat[2][1];
		Mat[2][2] += mat.Mat[2][2];
		Mat[2][3] += mat.Mat[2][3];

		Mat[3][0] += mat.Mat[3][0];
		Mat[3][1] += mat.Mat[3][1];
		Mat[3][2] += mat.Mat[3][2];
		Mat[3][3] += mat.Mat[3][3];
		return *this;
	}

	/**
	* ���Z
	* @param �E�Ӓl 
	* @return ���Z����
	*/
	Matrix44& Matrix44::operator -=(const Matrix44 & mat) {
		Mat[0][0] -= mat.Mat[0][0];
		Mat[0][1] -= mat.Mat[0][1];
		Mat[0][2] -= mat.Mat[0][2];
		Mat[0][3] -= mat.Mat[0][3];

		Mat[1][0] -= mat.Mat[1][0];
		Mat[1][1] -= mat.Mat[1][1];
		Mat[1][2] -= mat.Mat[1][2];
		Mat[1][3] -= mat.Mat[1][3];	

		Mat[2][0] -= mat.Mat[2][0];
		Mat[2][1] -= mat.Mat[2][1];
		Mat[2][2] -= mat.Mat[2][2];
		Mat[2][3] -= mat.Mat[2][3];

		Mat[3][0] -= mat.Mat[3][0];
		Mat[3][1] -= mat.Mat[3][1];
		Mat[3][2] -= mat.Mat[3][2];
		Mat[3][3] -= mat.Mat[3][3];
		return *this;
	}

	/**
	* ��Z
	* @param �E�Ӓl 
	* @return ��Z����
	*/
	Matrix44& Matrix44::operator *=(const float s) {
		Mat[0][0] *= s;
		Mat[0][1] *= s;
		Mat[0][2] *= s;
		Mat[0][3] *= s;
		Mat[1][0] *= s;
		Mat[1][1] *= s;
		Mat[1][2] *= s;
		Mat[1][3] *= s;	
		Mat[2][0] *= s;
		Mat[2][1] *= s;
		Mat[2][2] *= s;
		Mat[2][3] *= s;
		Mat[3][0] *= s;
		Mat[3][1] *= s;
		Mat[3][2] *= s;
		Mat[3][3] *= s;

		return *this;
	}

	/**
	* ��Z
	* @param �E�Ӓl 
	* @return ��Z����
	*/
	Matrix44& Matrix44::operator *=(const Matrix44& mat) {
		Set(
			Mat[0][0]*mat.Mat[0][0] + Mat[0][1]*mat.Mat[1][0] + Mat[0][2]*mat.Mat[2][0] + Mat[0][3] * mat.Mat[3][0],  
			Mat[0][0]*mat.Mat[0][1] + Mat[0][1]*mat.Mat[1][1] + Mat[0][2]*mat.Mat[2][1] + Mat[0][3] * mat.Mat[3][1],
			Mat[0][0]*mat.Mat[0][2] + Mat[0][1]*mat.Mat[1][2] + Mat[0][2]*mat.Mat[2][2] + Mat[0][3] * mat.Mat[3][2], 
			Mat[0][0]*mat.Mat[0][3] + Mat[0][1]*mat.Mat[1][3] + Mat[0][2]*mat.Mat[2][3] + Mat[0][3] * mat.Mat[3][3], 

			Mat[1][0]*mat.Mat[0][0] + Mat[1][1]*mat.Mat[1][0] + Mat[1][2]*mat.Mat[2][0] + Mat[1][3] * mat.Mat[3][0],
			Mat[1][0]*mat.Mat[0][1] + Mat[1][1]*mat.Mat[1][1] + Mat[1][2]*mat.Mat[2][1] + Mat[1][3] * mat.Mat[3][1],
			Mat[1][0]*mat.Mat[0][2] + Mat[1][1]*mat.Mat[1][2] + Mat[1][2]*mat.Mat[2][2] + Mat[1][3] * mat.Mat[3][2], 
			Mat[1][0]*mat.Mat[0][3] + Mat[1][1]*mat.Mat[1][3] + Mat[1][2]*mat.Mat[2][3] + Mat[1][3] * mat.Mat[3][3], 

			Mat[2][0]*mat.Mat[0][0] + Mat[2][1]*mat.Mat[1][0] + Mat[2][2]*mat.Mat[2][0] + Mat[2][3] * mat.Mat[3][0], 
			Mat[2][0]*mat.Mat[0][1] + Mat[2][1]*mat.Mat[1][1] + Mat[2][2]*mat.Mat[2][1] + Mat[2][3] * mat.Mat[3][1], 
			Mat[2][0]*mat.Mat[0][2] + Mat[2][1]*mat.Mat[1][2] + Mat[2][2]*mat.Mat[2][2] + Mat[2][3] * mat.Mat[3][2], 
			Mat[2][0]*mat.Mat[0][3] + Mat[2][1]*mat.Mat[1][3] + Mat[2][2]*mat.Mat[2][3] + Mat[2][3] * mat.Mat[3][3], 

			Mat[3][0]*mat.Mat[0][0] + Mat[3][1]*mat.Mat[1][0] + Mat[3][2]*mat.Mat[2][0] + Mat[3][3] * mat.Mat[3][0], 
			Mat[3][0]*mat.Mat[0][1] + Mat[3][1]*mat.Mat[1][1] + Mat[3][2]*mat.Mat[2][1] + Mat[3][3] * mat.Mat[3][1], 
			Mat[3][0]*mat.Mat[0][2] + Mat[3][1]*mat.Mat[1][2] + Mat[3][2]*mat.Mat[2][2] + Mat[3][3] * mat.Mat[3][2], 
			Mat[3][0]*mat.Mat[0][3] + Mat[3][1]*mat.Mat[1][3] + Mat[3][2]*mat.Mat[2][3] + Mat[3][3] * mat.Mat[3][3]); 

		return *this;
	}

	/**
	* ���Z
	* @param �E�Ӓl 
	* @return ���Z����
	*/
	Matrix44& Matrix44::operator /=(const float s) {
		Mat[0][0] /= s;
		Mat[0][1] /= s;
		Mat[0][2] /= s;
		Mat[0][3] /= s;
		Mat[1][0] /= s;
		Mat[1][1] /= s;
		Mat[1][2] /= s;
		Mat[1][3] /= s;	
		Mat[2][0] /= s;
		Mat[2][1] /= s;
		Mat[2][2] /= s;
		Mat[2][3] /= s;
		Mat[3][0] /= s;
		Mat[3][1] /= s;
		Mat[3][2] /= s;
		Mat[3][3] /= s;

		return *this;

	}


	/**
	* ���Z
	* @param �E�Ӓl 
	* @return ���Z����
	*/
	Matrix44& Matrix44::operator =(const Matrix44& mat) {
		Mat[0][0] = mat.Mat[0][0];
		Mat[0][1] = mat.Mat[0][1];
		Mat[0][2] = mat.Mat[0][2];
		Mat[0][3] = mat.Mat[0][3];

		Mat[1][0] = mat.Mat[1][0];
		Mat[1][1] = mat.Mat[1][1];
		Mat[1][2] = mat.Mat[1][2];
		Mat[1][3] = mat.Mat[1][3];	

		Mat[2][0] = mat.Mat[2][0];
		Mat[2][1] = mat.Mat[2][1];
		Mat[2][2] = mat.Mat[2][2];
		Mat[2][3] = mat.Mat[2][3];

		Mat[3][0] = mat.Mat[3][0];
		Mat[3][1] = mat.Mat[3][1];
		Mat[3][2] = mat.Mat[3][2];
		Mat[3][3] = mat.Mat[3][3];

		return *this;

	}

	//--------------------------------------------------------------------------------------
	// �_�����Z
	//--------------------------------------------------------------------------------------
	bool Matrix44::Equal(const Matrix44 & m) {

		return (
			Math::Abs(Mat[0][0] - m.Mat[0][0]) <= Math::Epsilon &&
			Math::Abs(Mat[0][1] - m.Mat[0][1]) <= Math::Epsilon &&
			Math::Abs(Mat[0][2] - m.Mat[0][2]) <= Math::Epsilon &&
			Math::Abs(Mat[0][3] - m.Mat[0][3]) <= Math::Epsilon &&

			Math::Abs(Mat[1][0] - m.Mat[1][0]) <= Math::Epsilon &&
			Math::Abs(Mat[1][1] - m.Mat[1][1]) <= Math::Epsilon &&
			Math::Abs(Mat[1][2] - m.Mat[1][2]) <= Math::Epsilon &&
			Math::Abs(Mat[1][3] - m.Mat[1][3]) <= Math::Epsilon &&

			Math::Abs(Mat[2][0] - m.Mat[2][0]) <= Math::Epsilon &&
			Math::Abs(Mat[2][1] - m.Mat[2][1]) <= Math::Epsilon &&
			Math::Abs(Mat[2][2] - m.Mat[2][2]) <= Math::Epsilon &&
			Math::Abs(Mat[2][3] - m.Mat[2][3]) <= Math::Epsilon &&

			Math::Abs(Mat[3][0] - m.Mat[3][0]) <= Math::Epsilon &&
			Math::Abs(Mat[3][1] - m.Mat[3][1]) <= Math::Epsilon &&
			Math::Abs(Mat[3][2] - m.Mat[3][2]) <= Math::Epsilon &&
			Math::Abs(Mat[3][3] - m.Mat[3][3]) <= Math::Epsilon
			);
	}

	bool Matrix44::operator == (const Matrix44 &m) {
		return (
			Mat[0][0] == m.Mat[0][0] && 
			Mat[0][1] == m.Mat[0][1] && 
			Mat[0][2] == m.Mat[0][2] && 
			Mat[0][3] == m.Mat[0][3] && 

			Mat[1][0] == m.Mat[1][0] && 
			Mat[1][1] == m.Mat[1][1] && 
			Mat[1][2] == m.Mat[1][2] && 
			Mat[1][3] == m.Mat[1][3] && 

			Mat[2][0] == m.Mat[2][0] && 
			Mat[2][1] == m.Mat[2][1] && 
			Mat[2][2] == m.Mat[2][2] && 
			Mat[2][3] == m.Mat[2][3] && 

			Mat[3][0] == m.Mat[3][0] && 
			Mat[3][1] == m.Mat[3][1] && 
			Mat[3][2] == m.Mat[3][2] && 
			Mat[3][3] == m.Mat[3][3] 
		);
	}

	bool Matrix44::operator != (const Matrix44 &m) {

		return (
			Mat[0][0] != m.Mat[0][0] || 
			Mat[0][1] != m.Mat[0][1] || 
			Mat[0][2] != m.Mat[0][2] || 
			Mat[0][3] != m.Mat[0][3] || 

			Mat[1][0] != m.Mat[1][0] || 
			Mat[1][1] != m.Mat[1][1] || 
			Mat[1][2] != m.Mat[1][2] || 
			Mat[1][3] != m.Mat[1][3] || 

			Mat[2][0] != m.Mat[2][0] || 
			Mat[2][1] != m.Mat[2][1] || 
			Mat[2][2] != m.Mat[2][2] || 
			Mat[2][3] != m.Mat[2][3] || 

			Mat[3][0] != m.Mat[3][0] || 
			Mat[3][1] != m.Mat[3][1] || 
			Mat[3][2] != m.Mat[3][2] || 
			Mat[3][3] != m.Mat[3][3] 
		);

	}

	//--------------------------------------------------------------------------------------
	// �s�񉉎Z
	//--------------------------------------------------------------------------------------
	/**
	* �s��
	* @return �s�񎮂̒l
	*/
	float Matrix44::Determinant() {

		return Mat[0][0] * (
			Mat[1][1] * (Mat[2][2] * Mat[3][3] - Mat[3][2] * Mat[2][3]) -
			Mat[1][2] * (Mat[2][1] * Mat[3][3] - Mat[3][1] * Mat[2][3]) +
			Mat[1][3] * (Mat[2][1] * Mat[3][2] - Mat[3][1] * Mat[2][2])
			) -
			Mat[0][1] * (
			Mat[1][0] * (Mat[2][2] * Mat[3][3] - Mat[3][2] * Mat[2][3]) -
			Mat[1][2] * (Mat[2][0] * Mat[3][3] - Mat[3][0] * Mat[2][3]) +
			Mat[1][3] * (Mat[2][0] * Mat[3][2] - Mat[3][0] * Mat[2][2])
			) +
			Mat[0][2] * (
			Mat[1][0] * (Mat[2][1] * Mat[3][3] - Mat[3][1] * Mat[2][3]) -
			Mat[1][1] * (Mat[2][0] * Mat[3][3] - Mat[3][0] * Mat[2][3]) +
			Mat[1][3] * (Mat[2][0] * Mat[3][1] - Mat[3][0] * Mat[2][1])
			) -
			Mat[0][3] * (
			Mat[1][0] * (Mat[2][1] * Mat[3][2] - Mat[3][1] * Mat[2][2]) -
			Mat[1][1] * (Mat[2][0] * Mat[3][2] - Mat[3][0] * Mat[2][2]) +
			Mat[1][2] * (Mat[2][0] * Mat[3][1] - Mat[3][0] * Mat[2][1])
			);


	}

	/**
	* �s��̓]�u
	* @return �]�u�s��
	*/
	Matrix44& Matrix44::Transpose() {

		Set(
			Mat[0][0], Mat[1][0], Mat[2][0], Mat[3][0],
			Mat[0][1], Mat[1][1], Mat[2][1], Mat[3][1],
			Mat[0][2], Mat[1][2], Mat[2][2], Mat[3][2],
			Mat[0][3], Mat[1][3], Mat[2][3], Mat[3][3]);

		return *this;
	}

	/**
	* �t�s��
	* @return �t�s��
	*/
	float Matrix44::Inverse() {
		Matrix44 invertMatrix;
		// �s�񎮂��o��
		invertMatrix.Mat[0][0] = (
			Mat[1][1] * (Mat[2][2] * Mat[3][3] - Mat[3][2] * Mat[2][3]) -
			Mat[1][2] * (Mat[2][1] * Mat[3][3] - Mat[3][1] * Mat[2][3]) +
			Mat[1][3] * (Mat[2][1] * Mat[3][2] - Mat[3][1] * Mat[2][2]));
		invertMatrix.Mat[1][0] = -(
			Mat[1][0] * (Mat[2][2] * Mat[3][3] - Mat[3][2] * Mat[2][3]) -
			Mat[1][2] * (Mat[2][0] * Mat[3][3] - Mat[3][0] * Mat[2][3]) +
			Mat[1][3] * (Mat[2][0] * Mat[3][2] - Mat[3][0] * Mat[2][2]));
		invertMatrix.Mat[2][0] = (
			Mat[1][0] * (Mat[2][1] * Mat[3][3] - Mat[3][1] * Mat[2][3]) -
			Mat[1][1] * (Mat[2][0] * Mat[3][3] - Mat[3][0] * Mat[2][3]) +
			Mat[1][3] * (Mat[2][0] * Mat[3][1] - Mat[3][0] * Mat[2][1]));
		invertMatrix.Mat[3][0] = -(
			Mat[1][0] * (Mat[2][1] * Mat[3][2] - Mat[3][1] * Mat[2][2]) -
			Mat[1][1] * (Mat[2][0] * Mat[3][2] - Mat[3][0] * Mat[2][2]) +
			Mat[1][2] * (Mat[2][0] * Mat[3][1] - Mat[3][0] * Mat[2][1]));
		float determ =
			Mat[0][0] * invertMatrix.Mat[0][0] +
			Mat[0][1] * invertMatrix.Mat[1][0] +
			Mat[0][2] * invertMatrix.Mat[2][0] +
			Mat[0][3] * invertMatrix.Mat[3][0];

		Assert(determ !=0);

		// �e�v�f�̎Z�o
		invertMatrix.Mat[0][1] = -(
			Mat[0][1] * (Mat[2][2] * Mat[3][3] - Mat[3][2] * Mat[2][3]) -
			Mat[0][2] * (Mat[2][1] * Mat[3][3] - Mat[3][1] * Mat[2][3]) +
			Mat[0][3] * (Mat[2][1] * Mat[3][2] - Mat[3][1] * Mat[2][2]));
		invertMatrix.Mat[0][2] = (
			Mat[0][1] * (Mat[1][2] * Mat[3][3] - Mat[3][2] * Mat[1][3]) -
			Mat[0][2] * (Mat[1][1] * Mat[3][3] - Mat[3][1] * Mat[1][3]) +
			Mat[0][3] * (Mat[1][1] * Mat[3][2] - Mat[3][1] * Mat[1][2]));
		invertMatrix.Mat[0][3] = -(
			Mat[0][1] * (Mat[1][2] * Mat[2][3] - Mat[2][2] * Mat[1][3]) -
			Mat[0][2] * (Mat[1][1] * Mat[2][3] - Mat[2][1] * Mat[1][3]) +
			Mat[0][3] * (Mat[1][1] * Mat[2][2] - Mat[2][1] * Mat[1][2]));
		invertMatrix.Mat[1][1] = (
			Mat[0][0] * (Mat[2][2] * Mat[3][3] - Mat[3][2] * Mat[2][3]) -
			Mat[0][2] * (Mat[2][0] * Mat[3][3] - Mat[3][0] * Mat[2][3]) +
			Mat[0][3] * (Mat[2][0] * Mat[3][2] - Mat[3][0] * Mat[2][2]));
		invertMatrix.Mat[1][2] = -(
			Mat[0][0] * (Mat[1][2] * Mat[3][3] - Mat[3][2] * Mat[1][3]) -
			Mat[0][2] * (Mat[1][0] * Mat[3][3] - Mat[3][0] * Mat[1][3]) +
			Mat[0][3] * (Mat[1][0] * Mat[3][2] - Mat[3][0] * Mat[1][2]));
		invertMatrix.Mat[1][3] = (
			Mat[0][0] * (Mat[1][2] * Mat[2][3] - Mat[2][2] * Mat[1][3]) -
			Mat[0][2] * (Mat[1][0] * Mat[2][3] - Mat[2][0] * Mat[1][3]) +
			Mat[0][3] * (Mat[1][0] * Mat[2][2] - Mat[2][0] * Mat[1][2]));
		invertMatrix.Mat[2][1] = -(
			Mat[0][0] * (Mat[2][1] * Mat[3][3] - Mat[3][1] * Mat[2][3]) -
			Mat[0][1] * (Mat[2][0] * Mat[3][3] - Mat[3][0] * Mat[2][3]) +
			Mat[0][3] * (Mat[2][0] * Mat[3][1] - Mat[3][0] * Mat[2][1]));
		invertMatrix.Mat[2][2] = (
			Mat[0][0] * (Mat[1][1] * Mat[3][3] - Mat[3][1] * Mat[1][3]) -
			Mat[0][1] * (Mat[1][0] * Mat[3][3] - Mat[3][0] * Mat[1][3]) +
			Mat[0][3] * (Mat[1][0] * Mat[3][1] - Mat[3][0] * Mat[1][1]));
		invertMatrix.Mat[2][3] = -(
			Mat[0][0] * (Mat[1][1] * Mat[2][3] - Mat[2][1] * Mat[1][3]) -
			Mat[0][1] * (Mat[1][0] * Mat[2][3] - Mat[2][0] * Mat[1][3]) +
			Mat[0][3] * (Mat[1][0] * Mat[2][1] - Mat[2][0] * Mat[1][1]));
		invertMatrix.Mat[3][1] = (
			Mat[0][0] * (Mat[2][1] * Mat[3][2] - Mat[3][1] * Mat[2][2]) -
			Mat[0][1] * (Mat[2][0] * Mat[3][2] - Mat[3][0] * Mat[2][2]) +
			Mat[0][2] * (Mat[2][0] * Mat[3][1] - Mat[3][0] * Mat[2][1]));
		invertMatrix.Mat[3][2] = -(
			Mat[0][0] * (Mat[1][1] * Mat[3][2] - Mat[3][1] * Mat[1][2]) -
			Mat[0][1] * (Mat[1][0] * Mat[3][2] - Mat[3][0] * Mat[1][2]) +
			Mat[0][2] * (Mat[1][0] * Mat[3][1] - Mat[3][0] * Mat[1][1]));
		invertMatrix.Mat[3][3] = (
			Mat[0][0] * (Mat[1][1] * Mat[2][2] - Mat[2][1] * Mat[1][2]) -
			Mat[0][1] * (Mat[1][0] * Mat[2][2] - Mat[2][0] * Mat[1][2]) +
			Mat[0][2] * (Mat[1][0] * Mat[2][1] - Mat[2][0] * Mat[1][1]));
		// �s�񎮂̋t�����|����
		float invDeterm = 1.f / determ;
		invertMatrix *= invDeterm;
		(*this) = invertMatrix;
		return determ;
	}

	//--------------------------------------------------------------------------------------
	// �ϊ��s��
	//--------------------------------------------------------------------------------------
	Matrix44& Matrix44::Transform(
		Matrix44* out, 
		float sx, float sy, float sz, 
		float rx, float ry, float rz, 
		float tx, float ty, float tz) 
	{
		Matrix44 scaling = Unit;
		Matrix44 rotation = Unit;
		Matrix44 translation = Unit;


		Scaling(&scaling, sx,sy, sz);
		RotationZXY(&rotation, rz,rx, ry);
		Translation(&translation, tx,ty, tz);

		*out = scaling * rotation* translation; 

		return *out;
	}

	Matrix44& Matrix44::Transform(Matrix44* out, Vector3 sv, Vector3 rv, Vector3 tv) 
	{
		Matrix44 scaling  = Unit;
		Matrix44 rotation =Unit;
		Matrix44 translation=Unit;

		Scaling(&scaling, sv.x,sv.y, sv.z);
		RotationZXY(&rotation, rv.z,rv.x, rv.y);
		Translation(&translation, tv.x,tv.y, tv.z);

		*out = scaling * rotation* translation; 

		return *out;
	}
	//--------------------------------------------------------------------------------------
	// ���s�ړ�
	//--------------------------------------------------------------------------------------
	Matrix44& Matrix44::Translation(Matrix44* out, float tx, float ty, float tz) {
		out->Set(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			tx,  ty,  tz, 1.f
			);
		return  *out;
	}

	//--------------------------------------------------------------------------------------
	// �g��E�k��
	//--------------------------------------------------------------------------------------
	Matrix44& Matrix44::Scaling(Matrix44* out, float sx, float sy, float sz) {
		out->Set(
			sx, 0.f, 0.f, 0.f,
			0.f,  sy, 0.f, 0.f,
			0.f, 0.f,  sz, 0.f,
			0.f, 0.f, 0.f, 1.f

			);
		return  *out;
	}

	//--------------------------------------------------------------------------------------
	// ��]
	//--------------------------------------------------------------------------------------
	Matrix44& Matrix44::RotationX(Matrix44* out, float angle) {
		float c = Math::Cos(angle);
		float s = Math::Sin(angle);

		out->Set(
			1.f, 0.f, 0.f, 0.f,
			0.f,   c,   s, 0.f,
			0.f,  -s,   c, 0.f,
			0.f, 0.f, 0.f, 1.f

			);
		return  *out;

	}
	Matrix44& Matrix44::RotationY(Matrix44* out, float angle) {
		float c = Math::Cos(angle);
		float s = Math::Sin(angle);

		out->Set(
			c, 0.f,  -s, 0.f,
			0.f, 1.f, 0.f, 0.f,
			s, 0.f,   c, 0.f,
			0.f, 0.f, 0.f, 1.f

			);
		return  *out;

	}
	Matrix44& Matrix44::RotationZ(Matrix44* out, float angle) {
		float c = Math::Cos(angle);
		float s = Math::Sin(angle);

		out->Set(
			c,   s, 0.f, 0.f,
			-s,   c, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f

			);
		return  *out;

	}
	Matrix44& Matrix44::RotationZXY(Matrix44* out, float roll, float pitch, float yaw) {
		Matrix44 tmp;
		*out = Unit;
		*out *= RotationZ(&tmp,roll);
		*out *= RotationX(&tmp,pitch);
		*out *= RotationY(&tmp,yaw);

		return  *out;

	}
}
