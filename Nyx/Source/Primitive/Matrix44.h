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
#ifndef NYX_CORE_INCLUDED_MATRIX44_H_
#define NYX_CORE_INCLUDED_MATRIX44_H_
#include "Debug/Assert.h"
#include "Primitive/EulerAngles.h"
#include "Primitive/Quaternion.h"
#include "Primitive/Vector3.h"

namespace Nyx  {
	class Matrix44 {
	public:
		/// 4x4行列
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
		//--------------------------------------------------------------------------------------
		// コンストラクタ・デストラクタ
		//--------------------------------------------------------------------------------------
		/**デフォルトコンストラクタ
		* 行列の値をすべてゼロに設定する
		*/

		Matrix44::Matrix44() {

		}

		/**
		* コンストラクタ
		* 行列の各要素に任意の値を設定する
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

		//--------------------------------------------------------------------------------------
		// 値の設定
		//--------------------------------------------------------------------------------------
		/**
		* 行列の各要素に任意の値を設定する
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
		// 演算
		//--------------------------------------------------------------------------------------
		/**
		* 加算
		* @param 右辺値
		* @return 加算結果
		*/
		Matrix44 Matrix44::operator +(const Matrix44& m) const {
			return Matrix44(
				Mat[0][0] + m.Mat[0][0], Mat[0][1] +m.Mat[0][1], Mat[0][2]+ m.Mat[0][2],Mat[0][3]+ m.Mat[0][3],
				Mat[1][0] + m.Mat[1][0], Mat[1][1] +m.Mat[1][1], Mat[1][2]+ m.Mat[1][2],Mat[1][3]+ m.Mat[1][3],
				Mat[2][0] + m.Mat[2][0], Mat[2][1] +m.Mat[2][1], Mat[2][2]+ m.Mat[2][2],Mat[2][3]+ m.Mat[2][3],
				Mat[3][0] + m.Mat[3][0], Mat[3][1] +m.Mat[3][1], Mat[3][2]+ m.Mat[3][2],Mat[3][3]+ m.Mat[3][3]);
		}

		/**
		* 減算
		* @param 右辺値
		* @return 減算結果
		*/
		Matrix44 Matrix44::operator -(const Matrix44& m) const {
			return Matrix44(
				Mat[0][0] - m.Mat[0][0], Mat[0][1] - m.Mat[0][1], Mat[0][2] - m.Mat[0][2], Mat[0][3] - m.Mat[0][3],
				Mat[1][0] - m.Mat[1][0], Mat[1][1] - m.Mat[1][1], Mat[1][2] - m.Mat[1][2], Mat[1][3] - m.Mat[1][3],
				Mat[2][0] - m.Mat[2][0], Mat[2][1] - m.Mat[2][1], Mat[2][2] - m.Mat[2][2], Mat[2][3] - m.Mat[2][3],
				Mat[3][0] - m.Mat[3][0], Mat[3][1] - m.Mat[3][1], Mat[3][2] - m.Mat[3][2], Mat[3][3] - m.Mat[3][3]);
		}
		/**
		* 乗算
		* @param 右辺値
		* @return 乗算結果
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
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
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
		* 除算
		* @param 右辺値
		* @return 除算結果
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
		// 代入演算
		//--------------------------------------------------------------------------------------
		/**
		* 加算
		* @param 右辺値 
		* @return 加算結果 
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
		* 減算
		* @param 右辺値 
		* @return 減算結果
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
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
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
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
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
		* 除算
		* @param 右辺値 
		* @return 除算結果
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
		* 除算
		* @param 右辺値 
		* @return 除算結果
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
		// 論理演算
		//--------------------------------------------------------------------------------------
		/**
		* 誤差対策有り等価演算
		* @param 右辺値
		* @return 等しいならtrue
		*/
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


		/**
		* 誤差対策有り非等価演算
		* @param 右辺値
		* @return 等しくないならtrue
		*/
		bool Matrix44::NotEqual(const Matrix44& matrix) {
			return !Equal(matrix);
		}


		/**
		* 等価演算
		* @param 右辺値
		* @return 等しいならtrue
		*/
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


		/**
		* 非等価演算
		* @param 右辺値
		* @return 等しくないならtrue
		*/
		bool Matrix44::operator != (const Matrix44& matrix) {
			return !(*this == matrix);
		}


		//--------------------------------------------------------------------------------------
		// 行列演算
		//--------------------------------------------------------------------------------------
		/**
		* 行列式
		* @return 行列式の値
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
		* 行列の転置
		* @return 転置行列
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
		* 逆行列にします
		* @return 逆行列
		*/
		float Matrix44::Invert() {
			Matrix44 invertMatrix;
			// 行列式を出す
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

			// 各要素の算出
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
			// 行列式の逆数を掛ける
			float invDeterm = 1.f / determ;
			invertMatrix *= invDeterm;
			(*this) = invertMatrix;
			return determ;
		}

		//--------------------------------------------------------------------------------------
		// 変換行列
		//--------------------------------------------------------------------------------------
		/**
		* 変換行列を作成します
		* @param Matrix44* 出力行列
		* @param float scaleX
		* @param float scaleY
		* @param float scaleZ
		* @param float rotateX
		* @param float rotateY
		* @param float rotateZ
		* @param float translateX
		* @param float translateY
		* @param float translateZ
		*/
		static Matrix44& Matrix44::SetTransform(
			Matrix44* out, 
			float sx, float sy, float sz, 
			float rx, float ry, float rz, 
			float tx, float ty, float tz) {
				Matrix44 scaling = Unit;
				Matrix44 rotation = Unit;
				Matrix44 translation = Unit;


				SetScale(&scaling, sx,sy, sz);
				SetRotateZXY(&rotation, rz,rx, ry);
				SetTranslate(&translation, tx,ty, tz);

				*out = scaling * rotation* translation; 

				return *out;
		}


		/**
		* 変換行列を作成します
		* @param Matrix44* 出力行列
		* @param float スケーリングベクトル
		* @param float 回転ベクトル
		* @param float 平行移動ベクトル
		*/
		static Matrix44& Matrix44::SetTransform(Matrix44* matrix, Vector3f sv, Vector3f rv, Vector3f tv) 
		{
			SetTransform(matrix, sv.x, sv.y, sv.z, rv.x, rv.y, rv.z, tv.x, tv.y, tv.z);
			return *matrix;
		}

		/**
		* 変換行列を追加します
		* @param Matrix44* 出力行列
		* @param float scaleX
		* @param float scaleY
		* @param float scaleZ
		* @param float rotateX
		* @param float rotateY
		* @param float rotateZ
		* @param float translateX
		* @param float translateY
		* @param float translateZ
		*/
		static Matrix44& Matrix44::AddTransform(
			Matrix44* matrix, 
			float sx, float sy, float sz, 
			float rx, float ry, float rz, 
			float tx, float ty, float tz) 
		{
			Matrix44 mat = Unit;
			SetTransform(&mat, sx, sy, sz, rx, ry, rz, tx, ty, tz);

			*matrix = mat * (*matrix);

			return *matrix;
		}


		/**
		* 変換行列を追加します
		* @param Matrix44* 出力行列
		* @param float スケーリングベクトル
		* @param float 回転ベクトル
		* @param float 平行移動ベクトル
		*/
		static Matrix44& Matrix44::AddTransform(Matrix44* matrix, Vector3f sv, Vector3f rv, Vector3f tv) 
		{
			Matrix44 mat = Unit;
			mat.SetTransform(&mat, sv, rv, tv);
			*matrix = mat * (*matrix); 

			return *matrix;
		}

		//--------------------------------------------------------------------------------------
		// 平行移動
		//--------------------------------------------------------------------------------------
		/**
		* 平行移動行列を生成します
		* @param Matrix44* 出力行列
		* @param float translateX
		* @param float translateY
		* @param float translateZ
		*/
		static Matrix44& Matrix44::SetTranslate(Matrix44* matrix, float tx, float ty, float tz) {
			matrix->Set(1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				tx,  ty,  tz,  1.f);
			return  *matrix;
		}


		/**
		* 平行移動行列を生成します
		* @param Matrix44* 出力行列
		* @param const Vector3f& スケーリングベクトル
		*/
		static Matrix44& Matrix44::SetTranslate(Matrix44* matrix, const Vector3f& tv) {
			return SetTranslate(matrix, tv.x, tv.y, tv.z);
		}


		/**
		* 平行移動行列を追加します
		* @param Matrix44* 出力行列
		* @param float translateX
		* @param float translateY
		* @param float translateZ
		*/
		static Matrix44& Matrix44::AddTranslate(Matrix44* matrix, float tx, float ty, float tz) {
			Matrix44 translate;
			translate.SetTranslate(&translate, tx, ty, tz);
			*matrix = translate * (*matrix);
			return *matrix;
		}


		/**
		* 平行移動行列を追加します
		* @param Matrix44* 出力行列
		* @param const Vector3f& 平行移動ベクトル
		*/
		static Matrix44& Matrix44::AddTranslate(Matrix44* matrix,  const Vector3f& tv) {
			return AddTranslate(matrix, tv.x, tv.y, tv.z);
		}

		//--------------------------------------------------------------------------------------
		// 拡大・縮小
		//--------------------------------------------------------------------------------------
		/**
		* 拡大縮小行列を生成します
		* @param Matrix44* 出力行列
		* @param float scaleX
		* @param float scaleY
		* @param float scaleZ
		*/
		static Matrix44& Matrix44::SetScale(Matrix44* matrix, float sx, float sy, float sz) {
			matrix->Set(sx, 0.f, 0.f, 0.f,
				0.f, sy , 0.f, 0.f,
				0.f, 0.f, sz , 0.f,
				0.f, 0.f, 0.f, 1.f);
			return  *matrix;
		}


		/**
		* 拡大縮小行列を生成します
		* @param Matrix44* 出力行列
		* @param const Vector3f& スケーリングベクトル
		*/
		static Matrix44& Matrix44::SetScale(Matrix44* matrix, const Vector3f& sv) {
			return SetScale(matrix, sv.x, sv.y, sv.z);
		}

		/**
		* 拡大縮小を追加します
		* @param Matrix44* 出力行列
		* @param float scaleX
		* @param float scaleY
		* @param float scaleZ
		*/
		static Matrix44& Matrix44::AddScale(Matrix44* matrix, float sx, float sy, float sz) {
			Matrix44 scale;
			scale.SetScale(&scale, sx, sy, sz);
			*matrix = scale * (*matrix);
			return  *matrix;
		}


		/**
		* 拡大縮小行列を追加します
		* @param Matrix44* 出力行列
		* @param const Vector3f& スケーリングベクトル
		*/
		static Matrix44& Matrix44::AddScale(Matrix44* matrix, const Vector3f& sv) {
			return AddScale(matrix, sv.x, sv.y, sv.z);
		}

		//--------------------------------------------------------------------------------------
		// 回転
		//--------------------------------------------------------------------------------------
		/**
		* X軸回転行列を生成します
		* @param Matrix44* 出力行列
		* @param float 回転角
		*/
		static Matrix44& Matrix44::SetRotateX(Matrix44* matrix, float angle) {
			float c = Math::Cos(angle);
			float s = Math::Sin(angle);

			matrix->Set(1.f, 0.f, 0.f, 0.f,
				0.f,   c,   s, 0.f,
				0.f,  -s,   c, 0.f,
				0.f, 0.f, 0.f, 1.f);
			return  *matrix;
		}


		/**
		* X軸回転行列を追加します
		* @param Matrix44* 出力行列
		* @param float 回転角
		*/
		static Matrix44& Matrix44::AddRotateX(Matrix44* matrix, float angle) {
			Matrix44 rotation = Unit;
			rotation.SetRotateX(&rotation, angle);
			*matrix = rotation * (*matrix);
			return *matrix;
		}


		/**
		* Y軸回転行列を追加します
		* @param Matrix44* 出力行列
		* @param float 回転角
		*/
		static Matrix44& Matrix44::SetRotateY(Matrix44* matrix, float angle) {
			float c = Math::Cos(angle);
			float s = Math::Sin(angle);

			matrix->Set(c  , 0.f,  -s, 0.f,
				0.f, 1.f, 0.f, 0.f,
				s  , 0.f,   c, 0.f,
				0.f, 0.f, 0.f, 1.f);
			return  *matrix;

		}

		/**
		* Y軸回転行列を追加します
		* @param Matrix44* 出力行列
		* @param float 回転角
		*/
		static Matrix44& Matrix44::AddRotateY(Matrix44* matrix, float angle) {
			Matrix44 rotation = Unit;
			rotation.SetRotateY(&rotation, angle);
			*matrix = rotation * (*matrix);
			return *matrix;
		}


		/**
		* Z軸回転行列を生成します
		* @param Matrix44* 出力行列
		* @param float 回転角
		*/
		static Matrix44& Matrix44::SetRotateZ(Matrix44* matrix, float angle) {
			float c = Math::Cos(angle);
			float s = Math::Sin(angle);

			matrix->Set( c,   s, 0.f, 0.f,
				-s,   c, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f);
			return  *matrix;

		}


		/**
		* Z軸回転行列を追加します
		* @param Matrix44* 出力行列
		* @param float 回転角
		*/
		static Matrix44& Matrix44::AddRotateZ(Matrix44* matrix, float angle) {
			Matrix44 rotation = Unit;
			rotation.SetRotateZ(&rotation, angle);
			*matrix = rotation * (*matrix);
			return *matrix;
		}


		/**
		* ３軸回転行列を生成します
		* @param Matrix44* 出力行列
		* @param float ロール角
		* @param float ピッチ角
		* @param float ヨー角
		*/
		static Matrix44& Matrix44::SetRotateZXY(Matrix44* matrix, float roll, float pitch, float yaw) {
			Matrix44 tmp = Unit;
			*matrix = Unit;
			*matrix *= SetRotateZ(&tmp,roll);
			*matrix *= SetRotateX(&tmp,pitch);
			*matrix *= SetRotateY(&tmp,yaw);

			return  *matrix;
		}


		/**
		* ３軸回転行列を生成します
		* @param Matrix44* 出力行列
		* @param const Vector3f& 回転ベクトル
		*/
		static Matrix44& Matrix44::SetRotateZXY(Matrix44* matrix, const Vector3f& rv) {
			return SetRotateZXY(matrix, rv.x, rv.y, rv.z);
		}


		/**
		* 任意軸回転行列を生成します
		* @param Matrix44* 出力行列
		* @param const Axis3f scaleX
		* @param float 回転角
		*/
		static Matrix44& Matrix44::SetRotateAxis(Matrix44* matrix, const Axis3f& axis, float angle) {
			float c = Math::Cos(angle);
			float s = Math::Sin(angle);
			float xx = axis.x * axis.x;
			float yy = axis.y * axis.y;
			float zz = axis.z * axis.z;
			float xy = axis.x * axis.y;
			float xz = axis.x * axis.z;
			float yz = axis.y * axis.z;

			matrix->Set(
				xx * (1 - c) + c         , xy * (1 - c) + axis.z * s, xz * (1 - c) - axis.y * s, 0,
				xy * (1 - c) - axis.z * c, yy * (1 - c) + c         , xz * (1 - c) - axis.x * s, 0,
				xz * (1 - c) + axis.y * s, yz * (1 - c) - axis.x * s, zz * (1 - c) + c         , 0,
				0                        , 0                        , 0                        , 1);
			return *matrix;
		}


		/**
		* 任意軸回転行列を追加します
		* @param Matrix44* 出力行列
		* @param constAxis3f 軸
		* @param float 回転角
		*/
		static Matrix44& Matrix44::AddRotateAxis(Matrix44* matrix, const Axis3f& axis, float angle) {
			Matrix44 rotation = Unit;
			rotation.SetRotateAxis(&rotation, axis, angle);
			*matrix = rotation * (*matrix);
			return *matrix;
		}


		/**
		* 四元数から回転行列を生成します
		* @param Matrix44* 出力行列
		* @param const Quaternion<float>& quoternion
		*/		
		static Matrix44& Matrix44::SetRotationQuaternion(Matrix44* matrix, const Quaternion<float>& quaternion) {
			float x2 = quaternion.x + quaternion.x;
			float y2 = quaternion.y + quaternion.y;
			float z2 = quaternion.z + quaternion.z;
			float xx2 = quaternion.x * x2;
			float xy2 = quaternion.x * y2;
			float xz2 = quaternion.x * z2;
			float yy2 = quaternion.y * y2;
			float yz2 = quaternion.y * z2;
			float zz2 = quaternion.z * z2;
			float wx2 = quaternion.w * x2;
			float wy2 = quaternion.w * y2;
			float wz2 = quaternion.w * z2;


			matrix->Set(1 - (yy2 + zz2), xy2 - wz2      , xz2 + wy2      , 0,
				xy2 + wz2      , 1 - (xx2 + zz2), yz2 - wx2      , 0,
				xy2 - wy2      , yz2 + wx2      , 1 - (xx2 + yy2), 0,
				0              , 0              , 0,              1);
			return *matrix;
		}


		/**
		* 四元数から回転行列を追加します
		* @param Matrix44* 出力行列
		* @param const Quaternion<float>& quoternion
		*/
		static Matrix44& Matrix44::AddRotationQuaternion(Matrix44* matrix, const Quaternion<float>& quoternion) {
			Matrix44 rotation;
			rotation.SetRotationQuaternion(&rotation, quoternion);
			*matrix = rotation * (*matrix);

			return *matrix;
		}
	};


}
//-----------------------------------------------------
#endif
//END OF NYX_ALL_H
//-----------------------------------------------------