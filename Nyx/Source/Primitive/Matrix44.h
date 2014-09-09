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

namespace nyx  {

	class matrix {
	public:
		/// 4x4行列
		union {	
			struct{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float mat_[4][4];
			float array_[16];
		};

		//static const Matrix Unit;

		//static const Matrix Zero;
		//--------------------------------------------------------------------------------------
		// コンストラクタ・デストラクタ
		//--------------------------------------------------------------------------------------
		/**デフォルトコンストラクタ
		* 行列の値をすべてゼロに設定する
		*/

		matrix() {
			memset(array_, 0, sizeof(array_)); 
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
		matrix(
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
		void set(float a11, float a12, float a13, float a14, 
			float a21, float a22, float a23, float a24,
			float a31, float a32, float a33, float a34,
			float a41, float a42, float a43, float a44) {

				mat_[0][0] = a11; mat_[0][1]=a12; mat_[0][2] =a13; mat_[0][3]=a14;
				mat_[1][0] = a21; mat_[1][1]=a22; mat_[1][2] =a23; mat_[1][3]=a24;
				mat_[2][0] = a31; mat_[2][1]=a32; mat_[2][2] =a33; mat_[2][3]=a34;
				mat_[3][0] = a41; mat_[3][1]=a42; mat_[3][2] =a43; mat_[3][3]=a44;
		}

		void identity() {
			set(1, 0, 0, 0, 
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		//--------------------------------------------------------------------------------------
		// 演算
		//--------------------------------------------------------------------------------------
		/**
		* 加算
		* @param 右辺値
		* @return 加算結果
		*/
		matrix operator +(const matrix& m) const {
			return matrix(
				mat_[0][0] + m.mat_[0][0], mat_[0][1] +m.mat_[0][1], mat_[0][2]+ m.mat_[0][2],mat_[0][3]+ m.mat_[0][3],
				mat_[1][0] + m.mat_[1][0], mat_[1][1] +m.mat_[1][1], mat_[1][2]+ m.mat_[1][2],mat_[1][3]+ m.mat_[1][3],
				mat_[2][0] + m.mat_[2][0], mat_[2][1] +m.mat_[2][1], mat_[2][2]+ m.mat_[2][2],mat_[2][3]+ m.mat_[2][3],
				mat_[3][0] + m.mat_[3][0], mat_[3][1] +m.mat_[3][1], mat_[3][2]+ m.mat_[3][2],mat_[3][3]+ m.mat_[3][3]);
		}

		/**
		* 減算
		* @param 右辺値
		* @return 減算結果
		*/
		matrix operator -(const matrix& m) const {
			return matrix(
				mat_[0][0] - m.mat_[0][0], mat_[0][1] - m.mat_[0][1], mat_[0][2] - m.mat_[0][2], mat_[0][3] - m.mat_[0][3],
				mat_[1][0] - m.mat_[1][0], mat_[1][1] - m.mat_[1][1], mat_[1][2] - m.mat_[1][2], mat_[1][3] - m.mat_[1][3],
				mat_[2][0] - m.mat_[2][0], mat_[2][1] - m.mat_[2][1], mat_[2][2] - m.mat_[2][2], mat_[2][3] - m.mat_[2][3],
				mat_[3][0] - m.mat_[3][0], mat_[3][1] - m.mat_[3][1], mat_[3][2] - m.mat_[3][2], mat_[3][3] - m.mat_[3][3]);
		}
		/**
		* 乗算
		* @param 右辺値
		* @return 乗算結果
		*/
		matrix operator *(const float s) const {
			return matrix(
				mat_[0][0] * s, mat_[0][1] * s, mat_[0][2] * s, mat_[0][3] * s,
				mat_[1][0] * s, mat_[1][1] * s, mat_[1][2] * s, mat_[1][3] * s,
				mat_[2][0] * s, mat_[2][1] * s, mat_[2][2] * s, mat_[2][3] * s,
				mat_[3][0] * s, mat_[3][1] * s, mat_[3][2] * s, mat_[3][3] * s
				);
		}
		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		matrix operator *(const matrix& mat) const {
			return matrix(
				mat_[0][0] * mat.mat_[0][0] + mat_[0][1] * mat.mat_[1][0] + mat_[0][2] * mat.mat_[2][0] + mat_[0][3] * mat.mat_[3][0],
				mat_[0][0] * mat.mat_[0][1] + mat_[0][1] * mat.mat_[1][1] + mat_[0][2] * mat.mat_[2][1] + mat_[0][3] * mat.mat_[3][1],
				mat_[0][0] * mat.mat_[0][2] + mat_[0][1] * mat.mat_[1][2] + mat_[0][2] * mat.mat_[2][2] + mat_[0][3] * mat.mat_[3][2],
				mat_[0][0] * mat.mat_[0][3] + mat_[0][1] * mat.mat_[1][3] + mat_[0][2] * mat.mat_[2][3] + mat_[0][3] * mat.mat_[3][3],

				mat_[1][0] * mat.mat_[0][0] + mat_[1][1] * mat.mat_[1][0] + mat_[1][2] * mat.mat_[2][0] + mat_[1][3] * mat.mat_[3][0],
				mat_[1][0] * mat.mat_[0][1] + mat_[1][1] * mat.mat_[1][1] + mat_[1][2] * mat.mat_[2][1] + mat_[1][3] * mat.mat_[3][1],
				mat_[1][0] * mat.mat_[0][2] + mat_[1][1] * mat.mat_[1][2] + mat_[1][2] * mat.mat_[2][2] + mat_[1][3] * mat.mat_[3][2],
				mat_[1][0] * mat.mat_[0][3] + mat_[1][1] * mat.mat_[1][3] + mat_[1][2] * mat.mat_[2][3] + mat_[1][3] * mat.mat_[3][3],

				mat_[2][0] * mat.mat_[0][0] + mat_[2][1] * mat.mat_[1][0] + mat_[2][2] * mat.mat_[2][0] + mat_[2][3] * mat.mat_[3][0],
				mat_[2][0] * mat.mat_[0][1] + mat_[2][1] * mat.mat_[1][1] + mat_[2][2] * mat.mat_[2][1] + mat_[2][3] * mat.mat_[3][1],
				mat_[2][0] * mat.mat_[0][2] + mat_[2][1] * mat.mat_[1][2] + mat_[2][2] * mat.mat_[2][2] + mat_[2][3] * mat.mat_[3][2],
				mat_[2][0] * mat.mat_[0][3] + mat_[2][1] * mat.mat_[1][3] + mat_[2][2] * mat.mat_[2][3] + mat_[2][3] * mat.mat_[3][3],

				mat_[3][0] * mat.mat_[0][0] + mat_[3][1] * mat.mat_[1][0] + mat_[3][2] * mat.mat_[2][0] + mat_[3][3] * mat.mat_[3][0],
				mat_[3][0] * mat.mat_[0][1] + mat_[3][1] * mat.mat_[1][1] + mat_[3][2] * mat.mat_[2][1] + mat_[3][3] * mat.mat_[3][1],
				mat_[3][0] * mat.mat_[0][2] + mat_[3][1] * mat.mat_[1][2] + mat_[3][2] * mat.mat_[2][2] + mat_[3][3] * mat.mat_[3][2],
				mat_[3][0] * mat.mat_[0][3] + mat_[3][1] * mat.mat_[1][3] + mat_[3][2] * mat.mat_[2][3] + mat_[3][3] * mat.mat_[3][3]
			);
		}



		/**
		* 除算
		* @param 右辺値
		* @return 除算結果
		*/
		matrix operator /(float s) const {
			if (s==0.f) {s=1;}
			return matrix(
				mat_[0][0] / s, mat_[0][1] / s, mat_[0][2] / s, mat_[0][3] / s,
				mat_[1][0] / s, mat_[1][1] / s, mat_[1][2] / s, mat_[1][3] / s,
				mat_[2][0] / s, mat_[2][1] / s, mat_[2][2] / s, mat_[2][3] / s,
				mat_[3][0] / s, mat_[3][1] / s, mat_[3][2] / s, mat_[3][3] / s
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
		matrix& operator +=(const matrix & mat) {
			mat_[0][0] += mat.mat_[0][0];
			mat_[0][1] += mat.mat_[0][1];
			mat_[0][2] += mat.mat_[0][2];
			mat_[0][3] += mat.mat_[0][3];

			mat_[1][0] += mat.mat_[1][0];
			mat_[1][1] += mat.mat_[1][1];
			mat_[1][2] += mat.mat_[1][2];
			mat_[1][3] += mat.mat_[1][3];	

			mat_[2][0] += mat.mat_[2][0];
			mat_[2][1] += mat.mat_[2][1];
			mat_[2][2] += mat.mat_[2][2];
			mat_[2][3] += mat.mat_[2][3];

			mat_[3][0] += mat.mat_[3][0];
			mat_[3][1] += mat.mat_[3][1];
			mat_[3][2] += mat.mat_[3][2];
			mat_[3][3] += mat.mat_[3][3];
			return *this;
		}

		/**
		* 減算
		* @param 右辺値 
		* @return 減算結果
		*/
		matrix& operator -=(const matrix & mat) {
			mat_[0][0] -= mat.mat_[0][0];
			mat_[0][1] -= mat.mat_[0][1];
			mat_[0][2] -= mat.mat_[0][2];
			mat_[0][3] -= mat.mat_[0][3];

			mat_[1][0] -= mat.mat_[1][0];
			mat_[1][1] -= mat.mat_[1][1];
			mat_[1][2] -= mat.mat_[1][2];
			mat_[1][3] -= mat.mat_[1][3];	

			mat_[2][0] -= mat.mat_[2][0];
			mat_[2][1] -= mat.mat_[2][1];
			mat_[2][2] -= mat.mat_[2][2];
			mat_[2][3] -= mat.mat_[2][3];

			mat_[3][0] -= mat.mat_[3][0];
			mat_[3][1] -= mat.mat_[3][1];
			mat_[3][2] -= mat.mat_[3][2];
			mat_[3][3] -= mat.mat_[3][3];
			return *this;
		}

		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		matrix& operator *=(const float s) {
			mat_[0][0] *= s;
			mat_[0][1] *= s;
			mat_[0][2] *= s;
			mat_[0][3] *= s;
			mat_[1][0] *= s;
			mat_[1][1] *= s;
			mat_[1][2] *= s;
			mat_[1][3] *= s;	
			mat_[2][0] *= s;
			mat_[2][1] *= s;
			mat_[2][2] *= s;
			mat_[2][3] *= s;
			mat_[3][0] *= s;
			mat_[3][1] *= s;
			mat_[3][2] *= s;
			mat_[3][3] *= s;

			return *this;
		}

		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		matrix& operator *=(const matrix& mat) {
			set(
				mat_[0][0]*mat.mat_[0][0] + mat_[0][1]*mat.mat_[1][0] + mat_[0][2]*mat.mat_[2][0] + mat_[0][3] * mat.mat_[3][0],  
				mat_[0][0]*mat.mat_[0][1] + mat_[0][1]*mat.mat_[1][1] + mat_[0][2]*mat.mat_[2][1] + mat_[0][3] * mat.mat_[3][1],
				mat_[0][0]*mat.mat_[0][2] + mat_[0][1]*mat.mat_[1][2] + mat_[0][2]*mat.mat_[2][2] + mat_[0][3] * mat.mat_[3][2], 
				mat_[0][0]*mat.mat_[0][3] + mat_[0][1]*mat.mat_[1][3] + mat_[0][2]*mat.mat_[2][3] + mat_[0][3] * mat.mat_[3][3], 

				mat_[1][0]*mat.mat_[0][0] + mat_[1][1]*mat.mat_[1][0] + mat_[1][2]*mat.mat_[2][0] + mat_[1][3] * mat.mat_[3][0],
				mat_[1][0]*mat.mat_[0][1] + mat_[1][1]*mat.mat_[1][1] + mat_[1][2]*mat.mat_[2][1] + mat_[1][3] * mat.mat_[3][1],
				mat_[1][0]*mat.mat_[0][2] + mat_[1][1]*mat.mat_[1][2] + mat_[1][2]*mat.mat_[2][2] + mat_[1][3] * mat.mat_[3][2], 
				mat_[1][0]*mat.mat_[0][3] + mat_[1][1]*mat.mat_[1][3] + mat_[1][2]*mat.mat_[2][3] + mat_[1][3] * mat.mat_[3][3], 

				mat_[2][0]*mat.mat_[0][0] + mat_[2][1]*mat.mat_[1][0] + mat_[2][2]*mat.mat_[2][0] + mat_[2][3] * mat.mat_[3][0], 
				mat_[2][0]*mat.mat_[0][1] + mat_[2][1]*mat.mat_[1][1] + mat_[2][2]*mat.mat_[2][1] + mat_[2][3] * mat.mat_[3][1], 
				mat_[2][0]*mat.mat_[0][2] + mat_[2][1]*mat.mat_[1][2] + mat_[2][2]*mat.mat_[2][2] + mat_[2][3] * mat.mat_[3][2], 
				mat_[2][0]*mat.mat_[0][3] + mat_[2][1]*mat.mat_[1][3] + mat_[2][2]*mat.mat_[2][3] + mat_[2][3] * mat.mat_[3][3], 

				mat_[3][0]*mat.mat_[0][0] + mat_[3][1]*mat.mat_[1][0] + mat_[3][2]*mat.mat_[2][0] + mat_[3][3] * mat.mat_[3][0], 
				mat_[3][0]*mat.mat_[0][1] + mat_[3][1]*mat.mat_[1][1] + mat_[3][2]*mat.mat_[2][1] + mat_[3][3] * mat.mat_[3][1], 
				mat_[3][0]*mat.mat_[0][2] + mat_[3][1]*mat.mat_[1][2] + mat_[3][2]*mat.mat_[2][2] + mat_[3][3] * mat.mat_[3][2], 
				mat_[3][0]*mat.mat_[0][3] + mat_[3][1]*mat.mat_[1][3] + mat_[3][2]*mat.mat_[2][3] + mat_[3][3] * mat.mat_[3][3]); 

			return *this;
		}

		/**
		* 除算
		* @param 右辺値 
		* @return 除算結果
		*/
		matrix& operator /=(const float s) {
			mat_[0][0] /= s;
			mat_[0][1] /= s;
			mat_[0][2] /= s;
			mat_[0][3] /= s;
			mat_[1][0] /= s;
			mat_[1][1] /= s;
			mat_[1][2] /= s;
			mat_[1][3] /= s;	
			mat_[2][0] /= s;
			mat_[2][1] /= s;
			mat_[2][2] /= s;
			mat_[2][3] /= s;
			mat_[3][0] /= s;
			mat_[3][1] /= s;
			mat_[3][2] /= s;
			mat_[3][3] /= s;

			return *this;

		}


		/**
		* 除算
		* @param 右辺値 
		* @return 除算結果
		*/
		matrix& operator =(const matrix& mat) {
			mat_[0][0] = mat.mat_[0][0];
			mat_[0][1] = mat.mat_[0][1];
			mat_[0][2] = mat.mat_[0][2];
			mat_[0][3] = mat.mat_[0][3];

			mat_[1][0] = mat.mat_[1][0];
			mat_[1][1] = mat.mat_[1][1];
			mat_[1][2] = mat.mat_[1][2];
			mat_[1][3] = mat.mat_[1][3];	

			mat_[2][0] = mat.mat_[2][0];
			mat_[2][1] = mat.mat_[2][1];
			mat_[2][2] = mat.mat_[2][2];
			mat_[2][3] = mat.mat_[2][3];

			mat_[3][0] = mat.mat_[3][0];
			mat_[3][1] = mat.mat_[3][1];
			mat_[3][2] = mat.mat_[3][2];
			mat_[3][3] = mat.mat_[3][3];

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
		bool Equal(const matrix & m) {

			return (
				math::abs(mat_[0][0] - m.mat_[0][0]) <= math::EPSILON &&
				math::abs(mat_[0][1] - m.mat_[0][1]) <= math::EPSILON &&
				math::abs(mat_[0][2] - m.mat_[0][2]) <= math::EPSILON &&
				math::abs(mat_[0][3] - m.mat_[0][3]) <= math::EPSILON &&

				math::abs(mat_[1][0] - m.mat_[1][0]) <= math::EPSILON &&
				math::abs(mat_[1][1] - m.mat_[1][1]) <= math::EPSILON &&
				math::abs(mat_[1][2] - m.mat_[1][2]) <= math::EPSILON &&
				math::abs(mat_[1][3] - m.mat_[1][3]) <= math::EPSILON &&

				math::abs(mat_[2][0] - m.mat_[2][0]) <= math::EPSILON &&
				math::abs(mat_[2][1] - m.mat_[2][1]) <= math::EPSILON &&
				math::abs(mat_[2][2] - m.mat_[2][2]) <= math::EPSILON &&
				math::abs(mat_[2][3] - m.mat_[2][3]) <= math::EPSILON &&

				math::abs(mat_[3][0] - m.mat_[3][0]) <= math::EPSILON &&
				math::abs(mat_[3][1] - m.mat_[3][1]) <= math::EPSILON &&
				math::abs(mat_[3][2] - m.mat_[3][2]) <= math::EPSILON &&
				math::abs(mat_[3][3] - m.mat_[3][3]) <= math::EPSILON
				);
		}


		/**
		* 誤差対策有り非等価演算
		* @param 右辺値
		* @return 等しくないならtrue
		*/
		bool NotEqual(const matrix& matrix) {
			return !Equal(matrix);
		}


		/**
		* 等価演算
		* @param 右辺値
		* @return 等しいならtrue
		*/
		bool operator == (const matrix &m) {
			return (
				mat_[0][0] == m.mat_[0][0] && 
				mat_[0][1] == m.mat_[0][1] && 
				mat_[0][2] == m.mat_[0][2] && 
				mat_[0][3] == m.mat_[0][3] && 

				mat_[1][0] == m.mat_[1][0] && 
				mat_[1][1] == m.mat_[1][1] && 
				mat_[1][2] == m.mat_[1][2] && 
				mat_[1][3] == m.mat_[1][3] && 

				mat_[2][0] == m.mat_[2][0] && 
				mat_[2][1] == m.mat_[2][1] && 
				mat_[2][2] == m.mat_[2][2] && 
				mat_[2][3] == m.mat_[2][3] && 

				mat_[3][0] == m.mat_[3][0] && 
				mat_[3][1] == m.mat_[3][1] && 
				mat_[3][2] == m.mat_[3][2] && 
				mat_[3][3] == m.mat_[3][3] 
			);
		}


		/**
		* 非等価演算
		* @param 右辺値
		* @return 等しくないならtrue
		*/
		bool operator != (const matrix& matrix) {
			return !(*this == matrix);
		}


		//--------------------------------------------------------------------------------------
		// 行列演算
		//--------------------------------------------------------------------------------------
		/**
		* 行列式
		* @return 行列式の値
		*/
		float determinant() {

			return mat_[0][0] * (
				mat_[1][1] * (mat_[2][2] * mat_[3][3] - mat_[3][2] * mat_[2][3]) -
				mat_[1][2] * (mat_[2][1] * mat_[3][3] - mat_[3][1] * mat_[2][3]) +
				mat_[1][3] * (mat_[2][1] * mat_[3][2] - mat_[3][1] * mat_[2][2])
				) -
				mat_[0][1] * (
				mat_[1][0] * (mat_[2][2] * mat_[3][3] - mat_[3][2] * mat_[2][3]) -
				mat_[1][2] * (mat_[2][0] * mat_[3][3] - mat_[3][0] * mat_[2][3]) +
				mat_[1][3] * (mat_[2][0] * mat_[3][2] - mat_[3][0] * mat_[2][2])
				) +
				mat_[0][2] * (
				mat_[1][0] * (mat_[2][1] * mat_[3][3] - mat_[3][1] * mat_[2][3]) -
				mat_[1][1] * (mat_[2][0] * mat_[3][3] - mat_[3][0] * mat_[2][3]) +
				mat_[1][3] * (mat_[2][0] * mat_[3][1] - mat_[3][0] * mat_[2][1])
				) -
				mat_[0][3] * (
				mat_[1][0] * (mat_[2][1] * mat_[3][2] - mat_[3][1] * mat_[2][2]) -
				mat_[1][1] * (mat_[2][0] * mat_[3][2] - mat_[3][0] * mat_[2][2]) +
				mat_[1][2] * (mat_[2][0] * mat_[3][1] - mat_[3][0] * mat_[2][1])
				);


		}


		/**
		* 行列の転置
		* @return 転置行列
		*/
		matrix& transpose() {

			set(
				mat_[0][0], mat_[1][0], mat_[2][0], mat_[3][0],
				mat_[0][1], mat_[1][1], mat_[2][1], mat_[3][1],
				mat_[0][2], mat_[1][2], mat_[2][2], mat_[3][2],
				mat_[0][3], mat_[1][3], mat_[2][3], mat_[3][3]);

			return *this;
		}


		/**
		* 逆行列にします
		* @return 逆行列
		*/
		float invert() {
			matrix invertMatrix;
			// 行列式を出す
			invertMatrix.mat_[0][0] = (
				mat_[1][1] * (mat_[2][2] * mat_[3][3] - mat_[3][2] * mat_[2][3]) -
				mat_[1][2] * (mat_[2][1] * mat_[3][3] - mat_[3][1] * mat_[2][3]) +
				mat_[1][3] * (mat_[2][1] * mat_[3][2] - mat_[3][1] * mat_[2][2]));
			invertMatrix.mat_[1][0] = -(
				mat_[1][0] * (mat_[2][2] * mat_[3][3] - mat_[3][2] * mat_[2][3]) -
				mat_[1][2] * (mat_[2][0] * mat_[3][3] - mat_[3][0] * mat_[2][3]) +
				mat_[1][3] * (mat_[2][0] * mat_[3][2] - mat_[3][0] * mat_[2][2]));
			invertMatrix.mat_[2][0] = (
				mat_[1][0] * (mat_[2][1] * mat_[3][3] - mat_[3][1] * mat_[2][3]) -
				mat_[1][1] * (mat_[2][0] * mat_[3][3] - mat_[3][0] * mat_[2][3]) +
				mat_[1][3] * (mat_[2][0] * mat_[3][1] - mat_[3][0] * mat_[2][1]));
			invertMatrix.mat_[3][0] = -(
				mat_[1][0] * (mat_[2][1] * mat_[3][2] - mat_[3][1] * mat_[2][2]) -
				mat_[1][1] * (mat_[2][0] * mat_[3][2] - mat_[3][0] * mat_[2][2]) +
				mat_[1][2] * (mat_[2][0] * mat_[3][1] - mat_[3][0] * mat_[2][1]));
			float determ =
				mat_[0][0] * invertMatrix.mat_[0][0] +
				mat_[0][1] * invertMatrix.mat_[1][0] +
				mat_[0][2] * invertMatrix.mat_[2][0] +
				mat_[0][3] * invertMatrix.mat_[3][0];

			NYX_ASSERT(determ !=0);

			// 各要素の算出
			invertMatrix.mat_[0][1] = -(
				mat_[0][1] * (mat_[2][2] * mat_[3][3] - mat_[3][2] * mat_[2][3]) -
				mat_[0][2] * (mat_[2][1] * mat_[3][3] - mat_[3][1] * mat_[2][3]) +
				mat_[0][3] * (mat_[2][1] * mat_[3][2] - mat_[3][1] * mat_[2][2]));
			invertMatrix.mat_[0][2] = (
				mat_[0][1] * (mat_[1][2] * mat_[3][3] - mat_[3][2] * mat_[1][3]) -
				mat_[0][2] * (mat_[1][1] * mat_[3][3] - mat_[3][1] * mat_[1][3]) +
				mat_[0][3] * (mat_[1][1] * mat_[3][2] - mat_[3][1] * mat_[1][2]));
			invertMatrix.mat_[0][3] = -(
				mat_[0][1] * (mat_[1][2] * mat_[2][3] - mat_[2][2] * mat_[1][3]) -
				mat_[0][2] * (mat_[1][1] * mat_[2][3] - mat_[2][1] * mat_[1][3]) +
				mat_[0][3] * (mat_[1][1] * mat_[2][2] - mat_[2][1] * mat_[1][2]));
			invertMatrix.mat_[1][1] = (
				mat_[0][0] * (mat_[2][2] * mat_[3][3] - mat_[3][2] * mat_[2][3]) -
				mat_[0][2] * (mat_[2][0] * mat_[3][3] - mat_[3][0] * mat_[2][3]) +
				mat_[0][3] * (mat_[2][0] * mat_[3][2] - mat_[3][0] * mat_[2][2]));
			invertMatrix.mat_[1][2] = -(
				mat_[0][0] * (mat_[1][2] * mat_[3][3] - mat_[3][2] * mat_[1][3]) -
				mat_[0][2] * (mat_[1][0] * mat_[3][3] - mat_[3][0] * mat_[1][3]) +
				mat_[0][3] * (mat_[1][0] * mat_[3][2] - mat_[3][0] * mat_[1][2]));
			invertMatrix.mat_[1][3] = (
				mat_[0][0] * (mat_[1][2] * mat_[2][3] - mat_[2][2] * mat_[1][3]) -
				mat_[0][2] * (mat_[1][0] * mat_[2][3] - mat_[2][0] * mat_[1][3]) +
				mat_[0][3] * (mat_[1][0] * mat_[2][2] - mat_[2][0] * mat_[1][2]));
			invertMatrix.mat_[2][1] = -(
				mat_[0][0] * (mat_[2][1] * mat_[3][3] - mat_[3][1] * mat_[2][3]) -
				mat_[0][1] * (mat_[2][0] * mat_[3][3] - mat_[3][0] * mat_[2][3]) +
				mat_[0][3] * (mat_[2][0] * mat_[3][1] - mat_[3][0] * mat_[2][1]));
			invertMatrix.mat_[2][2] = (
				mat_[0][0] * (mat_[1][1] * mat_[3][3] - mat_[3][1] * mat_[1][3]) -
				mat_[0][1] * (mat_[1][0] * mat_[3][3] - mat_[3][0] * mat_[1][3]) +
				mat_[0][3] * (mat_[1][0] * mat_[3][1] - mat_[3][0] * mat_[1][1]));
			invertMatrix.mat_[2][3] = -(
				mat_[0][0] * (mat_[1][1] * mat_[2][3] - mat_[2][1] * mat_[1][3]) -
				mat_[0][1] * (mat_[1][0] * mat_[2][3] - mat_[2][0] * mat_[1][3]) +
				mat_[0][3] * (mat_[1][0] * mat_[2][1] - mat_[2][0] * mat_[1][1]));
			invertMatrix.mat_[3][1] = (
				mat_[0][0] * (mat_[2][1] * mat_[3][2] - mat_[3][1] * mat_[2][2]) -
				mat_[0][1] * (mat_[2][0] * mat_[3][2] - mat_[3][0] * mat_[2][2]) +
				mat_[0][2] * (mat_[2][0] * mat_[3][1] - mat_[3][0] * mat_[2][1]));
			invertMatrix.mat_[3][2] = -(
				mat_[0][0] * (mat_[1][1] * mat_[3][2] - mat_[3][1] * mat_[1][2]) -
				mat_[0][1] * (mat_[1][0] * mat_[3][2] - mat_[3][0] * mat_[1][2]) +
				mat_[0][2] * (mat_[1][0] * mat_[3][1] - mat_[3][0] * mat_[1][1]));
			invertMatrix.mat_[3][3] = (
				mat_[0][0] * (mat_[1][1] * mat_[2][2] - mat_[2][1] * mat_[1][2]) -
				mat_[0][1] * (mat_[1][0] * mat_[2][2] - mat_[2][0] * mat_[1][2]) +
				mat_[0][2] * (mat_[1][0] * mat_[2][1] - mat_[2][0] * mat_[1][1]));
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
		* @param Matrix* 出力行列
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
		static matrix& set_transform(
			matrix* out, 
			float sx, float sy, float sz, 
			float rx, float ry, float rz, 
			float tx, float ty, float tz) {
				matrix scaling ;
				matrix rotation ;
				matrix translation ;


				set_scale(&scaling, sx,sy, sz);
				set_rotate_zxy(&rotation, rz,rx, ry);
				set_translate(&translation, tx,ty, tz);

				*out = scaling * rotation* translation; 

				return *out;
		}


		/**
		* 変換行列を作成します
		* @param Matrix* 出力行列
		* @param float スケーリングベクトル
		* @param float 回転ベクトル
		* @param float 平行移動ベクトル
		*/
		static matrix& set_transform(matrix* matrix, vector3f sv, vector3f rv, vector3f tv) 
		{
			set_transform(matrix, sv.x, sv.y, sv.z, rv.x, rv.y, rv.z, tv.x, tv.y, tv.z);
			return *matrix;
		}

		/**
		* 変換行列を追加します
		* @param Matrix* 出力行列
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
		static matrix& add_transform(
			matrix* m, 
			float sx, float sy, float sz, 
			float rx, float ry, float rz, 
			float tx, float ty, float tz) 
		{
			matrix mat;
			set_transform(&mat, sx, sy, sz, rx, ry, rz, tx, ty, tz);

			*m = mat * (*m);

			return *m;
		}


		/**
		* 変換行列を追加します
		* @param Matrix* 出力行列
		* @param float スケーリングベクトル
		* @param float 回転ベクトル
		* @param float 平行移動ベクトル
		*/
		static matrix& add_transform(matrix* m, vector3f sv, vector3f rv, vector3f tv)
		{
			matrix mat;
			mat.set_transform(&mat, sv, rv, tv);
			*m = mat * (*m);

			return *m;
		}

		//--------------------------------------------------------------------------------------
		// 平行移動
		//--------------------------------------------------------------------------------------
		/**
		* 平行移動行列を生成します
		* @param Matrix* 出力行列
		* @param float translateX
		* @param float translateY
		* @param float translateZ
		*/
		static matrix& set_translate(matrix* m, float tx, float ty, float tz) {
			m->set(1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				tx,  ty,  tz,  1.f);
			return  *m;
		}


		/**
		* 平行移動行列を生成します
		* @param Matrix* 出力行列
		* @param const Vector3f& スケーリングベクトル
		*/
		static matrix& matrix::set_translate(matrix* m, const vector3f& tv) {
			return set_translate(m, tv.x, tv.y, tv.z);
		}


		/**
		* 平行移動行列を追加します
		* @param Matrix* 出力行列
		* @param float translateX
		* @param float translateY
		* @param float translateZ
		*/
		static matrix& matrix::add_translate(matrix* m, float tx, float ty, float tz) {
			matrix translate;
			translate.set_translate(&translate, tx, ty, tz);
			*m = translate * (*m);
			return *m;
		}


		/**
		* 平行移動行列を追加します
		* @param Matrix* 出力行列
		* @param const Vector3f& 平行移動ベクトル
		*/
		static matrix& matrix::add_translate(matrix* m, const vector3f& tv) {
			return add_translate(m, tv.x, tv.y, tv.z);
		}

		//--------------------------------------------------------------------------------------
		// 拡大・縮小
		//--------------------------------------------------------------------------------------
		/**
		* 拡大縮小行列を生成します
		* @param Matrix* 出力行列
		* @param float scaleX
		* @param float scaleY
		* @param float scaleZ
		*/
		static matrix& matrix::set_scale(matrix* m, float sx, float sy, float sz) {
			m->set(sx, 0.f, 0.f, 0.f,
				0.f, sy , 0.f, 0.f,
				0.f, 0.f, sz , 0.f,
				0.f, 0.f, 0.f, 1.f);
			return  *m;
		}


		/**
		* 拡大縮小行列を生成します
		* @param Matrix* 出力行列
		* @param const Vector3f& スケーリングベクトル
		*/
		static matrix& matrix::set_scale(matrix* m, const vector3f& sv) {
			return set_scale(m, sv.x, sv.y, sv.z);
		}

		/**
		* 拡大縮小を追加します
		* @param Matrix* 出力行列
		* @param float scaleX
		* @param float scaleY
		* @param float scaleZ
		*/
		static matrix& matrix::add_scale(matrix* m, float sx, float sy, float sz) {
			matrix scale;
			scale.set_scale(&scale, sx, sy, sz);
			*m = scale * (*m);
			return  *m;
		}


		/**
		* 拡大縮小行列を追加します
		* @param Matrix* 出力行列
		* @param const Vector3f& スケーリングベクトル
		*/
		static matrix& matrix::add_scale(matrix* m, const vector3f& sv) {
			return add_scale(m, sv.x, sv.y, sv.z);
		}

		//--------------------------------------------------------------------------------------
		// 回転
		//--------------------------------------------------------------------------------------
		/**
		* X軸回転行列を生成します
		* @param Matrix* 出力行列
		* @param float 回転角
		*/
		static matrix& matrix::set_rotate_x(matrix* m, float angle) {
			float c = math::cos(angle);
			float s = math::sin(angle);

			m->set(1.f, 0.f, 0.f, 0.f,
				0.f,   c,   s, 0.f,
				0.f,  -s,   c, 0.f,
				0.f, 0.f, 0.f, 1.f);
			return  *m;
		}


		/**
		* X軸回転行列を追加します
		* @param Matrix* 出力行列
		* @param float 回転角
		*/
		static matrix& matrix::add_rotate_x(matrix* m, float angle) {
			matrix rotation;
			rotation.set_rotate_x(&rotation, angle);
			*m = rotation * (*m);
			return *m;
		}


		/**
		* Y軸回転行列を追加します
		* @param Matrix* 出力行列
		* @param float 回転角
		*/
		static matrix& matrix::set_rotate_y(matrix* m, float angle) {
			float c = math::cos(angle);
			float s = math::sin(angle);

			m->set(c, 0.f, -s, 0.f,
				0.f, 1.f, 0.f, 0.f,
				s  , 0.f,   c, 0.f,
				0.f, 0.f, 0.f, 1.f);
			return  *m;

		}

		/**
		* Y軸回転行列を追加します
		* @param Matrix* 出力行列
		* @param float 回転角
		*/
		static matrix& matrix::add_rotate_y(matrix* m, float angle) {
			matrix rotation ;
			rotation.set_rotate_y(&rotation, angle);
			*m = rotation * (*m);
			return *m;
		}


		/**
		* Z軸回転行列を生成します
		* @param Matrix* 出力行列
		* @param float 回転角
		*/
		static matrix& matrix::set_rotate_z(matrix* m, float angle) {
			float c = math::cos(angle);
			float s = math::sin(angle);

			m->set(c, s, 0.f, 0.f,
				-s,   c, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f);
			return  *m;

		}


		/**
		* Z軸回転行列を追加します
		* @param Matrix* 出力行列
		* @param float 回転角
		*/
		static matrix& matrix::add_rotate_z(matrix* m, float angle) {
			matrix rotation ;
			rotation.set_rotate_z(&rotation, angle);
			*m = rotation * (*m);
			return *m;
		}


		/**
		* ３軸回転行列を生成します
		* @param Matrix* 出力行列
		* @param float ロール角
		* @param float ピッチ角
		* @param float ヨー角
		*/
		static matrix& matrix::set_rotate_zxy(matrix* m, float roll, float pitch, float yaw) {
			matrix tmp ;
			*m *= set_rotate_z(&tmp, roll);
			*m *= set_rotate_x(&tmp, pitch);
			*m *= set_rotate_y(&tmp, yaw);

			return  *m;
		}


		/**
		* ３軸回転行列を生成します
		* @param Matrix* 出力行列
		* @param const Vector3f& 回転ベクトル
		*/
		static matrix& matrix::set_rotate_zxy(matrix* m, const vector3f& rv) {
			return set_rotate_zxy(m, rv.x, rv.y, rv.z);
		}


		/**
		* 任意軸回転行列を生成します
		* @param Matrix* 出力行列
		* @param const Axis3f scaleX
		* @param float 回転角
		*/
		static matrix& matrix::set_rotate_axis(matrix* m, const axis3f& axis, float angle) {
			float c = math::cos(angle);
			float s = math::sin(angle);
			float xx = axis.x * axis.x;
			float yy = axis.y * axis.y;
			float zz = axis.z * axis.z;
			float xy = axis.x * axis.y;
			float xz = axis.x * axis.z;
			float yz = axis.y * axis.z;

			m->set(
				xx * (1 - c) + c         , xy * (1 - c) + axis.z * s, xz * (1 - c) - axis.y * s, 0,
				xy * (1 - c) - axis.z * c, yy * (1 - c) + c         , xz * (1 - c) - axis.x * s, 0,
				xz * (1 - c) + axis.y * s, yz * (1 - c) - axis.x * s, zz * (1 - c) + c         , 0,
				0                        , 0                        , 0                        , 1);
			return *m;
		}


		/**
		* 任意軸回転行列を追加します
		* @param Matrix* 出力行列
		* @param constAxis3f 軸
		* @param float 回転角
		*/
		static matrix& matrix::add_rotate_axis(matrix* m, const axis3f& axis, float angle) {
			matrix rotation;
			rotation.set_rotate_axis(&rotation, axis, angle);
			*m = rotation * (*m);
			return *m;
		}


		/**
		* 四元数から回転行列を生成します
		* @param Matrix* 出力行列
		* @param const Quaternion<float>& quoternion
		*/		
		static matrix& matrix::set_rotate_from_quaternion(matrix* m, const quaternion<float>& quaternion) {
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


			m->set(1 - (yy2 + zz2), xy2 - wz2, xz2 + wy2, 0,
				xy2 + wz2      , 1 - (xx2 + zz2), yz2 - wx2      , 0,
				xy2 - wy2      , yz2 + wx2      , 1 - (xx2 + yy2), 0,
				0              , 0              , 0,              1);
			return *m;
		}


		/**
		* 四元数から回転行列を追加します
		* @param Matrix* 出力行列
		* @param const Quaternion<float>& quoternion
		*/
		static matrix& matrix::add_rotate_from_quaternion(matrix* m, const quaternion<float>& quoternion) {
			matrix rotation;
			rotation.set_rotate_from_quaternion(&rotation, quoternion);
			*m = rotation * (*m);

			return *m;
		}
	};
}
//-----------------------------------------------------
#endif
//END OF NYX_ALL_H
//-----------------------------------------------------