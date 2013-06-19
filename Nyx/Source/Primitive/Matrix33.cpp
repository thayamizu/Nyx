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