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
#include "Primitive/Matrix33.h"
#include "Primitive/Vector3.h"
namespace Nyx {
	const Matrix33 Matrix33::Unit(1, 0, 0,
		0, 1, 0,
		0, 0, 1);

	const Matrix33 Matrix33::Zero(0, 0, 0,
		0, 0, 0,
		0, 0, 0);

	Matrix33::Matrix33() {
	}
	Matrix33::Matrix33(
		float a11, float a12, float a13, 
		float a21, float a22, float a23,
		float a31, float a32, float a33):_11(a11), _12(a12), _13(a13),_21(a21), _22(a22), _23(a23),_31(a31), _32(a32), _33(a33) {

	}

	Matrix33 Matrix33::operator +(const Matrix33& mat) const {
		return Matrix33(Mat[0][0] + mat.Mat[0][0], Mat[0][1] + mat.Mat[0][1], Mat[0][2] + mat.Mat[0][2],
			Mat[1][0] + mat.Mat[1][0], Mat[1][1] + mat.Mat[1][1], Mat[1][2] + mat.Mat[1][2],
			Mat[2][0] + mat.Mat[2][0], Mat[2][1] + mat.Mat[2][1], Mat[2][2] + mat.Mat[2][2]);
	}

	Matrix33 Matrix33::operator-(const Matrix33& mat) const {
		return Matrix33(Mat[0][0] - mat.Mat[0][0], Mat[0][1] - mat.Mat[0][1], Mat[0][2] - mat.Mat[0][2],
			Mat[1][0] - mat.Mat[1][0], Mat[1][1] - mat.Mat[1][1], Mat[1][2] - mat.Mat[1][2],
			Mat[2][0] - mat.Mat[2][0], Mat[2][1] - mat.Mat[2][1], Mat[2][2] - mat.Mat[2][2]);
	}

	Matrix33 Matrix33::operator*(const Matrix33& mat) const {
		return Matrix33(
			Mat[0][0]*mat.Mat[0][0] + Mat[0][1]*mat.Mat[1][0] + Mat[0][2]*mat.Mat[2][0], 
			Mat[0][0]*mat.Mat[0][1] + Mat[0][1]*mat.Mat[1][1] + Mat[0][2]*mat.Mat[2][1], 
			Mat[0][0]*mat.Mat[0][2] + Mat[0][1]*mat.Mat[1][2] + Mat[0][2]*mat.Mat[2][2], 

			Mat[1][0]*mat.Mat[0][0] + Mat[1][1]*mat.Mat[1][0] + Mat[1][2]*mat.Mat[2][0], 
			Mat[1][0]*mat.Mat[0][1] + Mat[1][1]*mat.Mat[1][1] + Mat[1][2]*mat.Mat[2][1], 
			Mat[1][0]*mat.Mat[0][2] + Mat[1][1]*mat.Mat[1][2] + Mat[1][2]*mat.Mat[2][2], 

			Mat[2][0]*mat.Mat[0][0] + Mat[2][1]*mat.Mat[1][0] + Mat[2][2]*mat.Mat[2][0], 
			Mat[2][0]*mat.Mat[0][1] + Mat[2][1]*mat.Mat[1][1] + Mat[2][2]*mat.Mat[2][1], 
			Mat[2][0]*mat.Mat[0][2] + Mat[2][1]*mat.Mat[1][2] + Mat[2][2]*mat.Mat[2][2]);



	}

	Matrix33 Matrix33::operator*(const float s) const {
		return Matrix33(Mat[0][0] * s, Mat[0][1] * s, Mat[0][2] * s,
			Mat[1][0] * s, Mat[1][1] * s, Mat[1][2] * s,
			Mat[2][0] * s, Mat[2][1] * s, Mat[2][2] * s);
	}



	Matrix33& Matrix33::operator+=(const Matrix33 & mat) {
		Mat[0][0] += mat.Mat[0][0];
		Mat[0][1] += mat.Mat[0][1];
		Mat[0][2] += mat.Mat[0][2];
		Mat[1][0] += mat.Mat[1][0];
		Mat[1][1] += mat.Mat[1][1];
		Mat[1][2] += mat.Mat[1][2];
		Mat[2][0] += mat.Mat[2][0];
		Mat[2][1] += mat.Mat[2][1];
		Mat[2][2] += mat.Mat[2][2];

		return *this;
	}

	Matrix33& Matrix33::operator-=(const Matrix33 & mat) {
		Mat[0][0] -= mat.Mat[0][0];
		Mat[0][1] -= mat.Mat[0][1];
		Mat[0][2] -= mat.Mat[0][2];
		Mat[1][0] -= mat.Mat[1][0];
		Mat[1][1] -= mat.Mat[1][1];
		Mat[1][2] -= mat.Mat[1][2];
		Mat[2][0] -= mat.Mat[2][0];
		Mat[2][1] -= mat.Mat[2][1];
		Mat[2][2] -= mat.Mat[2][2];

		return *this;
	}

	Matrix33& Matrix33::operator*=(const float s) {
		Mat[0][0] *= s;
		Mat[0][1] *= s;
		Mat[0][2] *= s;
		Mat[1][0] *= s;
		Mat[1][1] *= s;
		Mat[1][2] *= s;
		Mat[2][0] *= s;
		Mat[2][1] *= s;
		Mat[2][2] *= s;

		return *this;
	}


	float Matrix33::Determinant() {
		return (
			Mat[0][0] * (Mat[1][1] * Mat[2][2] - Mat[1][2] * Mat[2][1]) -
			Mat[0][1] * (Mat[1][0] * Mat[2][2] - Mat[1][2] * Mat[2][0]) +
			Mat[0][2] * (Mat[1][0] * Mat[2][1] - Mat[1][1] * Mat[2][0]));
	}

	Matrix33 Matrix33::Transpose() {
		return Matrix33(Mat[0][0], Mat[1][0], Mat[2][0],
			Mat[0][1], Mat[1][1], Mat[2][1],
			Mat[0][2], Mat[1][2], Mat[2][2]);
	}

	Matrix33 Matrix33::Inverse() {
		float d = this->Determinant();
		if (d == 0) {exit(-1);}

		return Matrix33((Mat[1][1]*Mat[2][2] - Mat[1][2]*Mat[2][1])/d, 
			-(Mat[0][1]*Mat[2][2] - Mat[0][2]*Mat[2][1])/d, 
			(Mat[0][1]*Mat[1][2] - Mat[0][2]*Mat[1][1])/d,
			-(Mat[1][0]*Mat[2][2] - Mat[1][2]*Mat[2][0])/d, 
			(Mat[0][0]*Mat[2][2] - Mat[0][2]*Mat[2][0])/d, 
			-(Mat[0][0]*Mat[1][2] - Mat[0][2]*Mat[1][0])/d,
			(Mat[1][0]*Mat[2][1] - Mat[1][1]*Mat[2][0])/d, 
			-(Mat[0][0]*Mat[2][1] - Mat[0][1]*Mat[2][0])/d, 
			(Mat[0][0]*Mat[1][1] - Mat[0][1]*Mat[1][0])/d);
	}
}