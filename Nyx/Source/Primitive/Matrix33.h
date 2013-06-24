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
#ifndef NYX_CORE_INCLUDED_MATRIX33_H_
#define NYX_CORE_INCLUDED_MATRIX33_H_
#include "Primitive/Vector3.h"
#include "Primitive/EulerAngles.h"
#include "Primitive/Quaternion.h"

namespace Nyx {

	class Matrix33 {
	public:
		/// 3x3行列
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
		* デフォルトコンストラクタ
		* 行列の値をすべてゼロに設定する
		*/
		Matrix33();

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
		Matrix33(float a11, float a12, float a13, 
			float a21, float a22, float a23,
			float a31, float a32, float a33);
		
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
		void Set(float a11, float a12, float a13,
			float a21, float a22, float a23,
			float a31, float a32, float a33);


		/**
		* 加算
		* @param 右辺値
		* @return 加算結果
		*/
		Matrix33 operator +(const Matrix33& mat) const;


		/**
		* 減算
		* @param 右辺値
		* @return 減算結果
		*/
		Matrix33 operator -(const Matrix33& mat) const;


		/**
		* 乗算
		* @param 右辺値
		* @return 乗算結果
		*/
		Matrix33 operator *(const float s) const;


		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Matrix33 operator *(const Matrix33& mat) const;


		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Vector3f operator *(const Vector3f& v) const;


		/**
		* 除算
		* @param 右辺値
		* @return 除算結果
		*/
		Matrix33 operator /(const float s) const;


		/**
		* 加算
		* @param 右辺値 
		* @return 加算結果 
		*/
		Matrix33& operator +=(const Matrix33 & mat);


		/**
		* 減算
		* @param 右辺値 
		* @return 減算結果
		*/
		Matrix33& operator -=(const Matrix33 & mat);


		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Matrix33& operator *=(const float s);


		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Matrix33& operator *=(const Matrix33& s);


		/**
		* 除算
		* @param 右辺値 
		* @return 除算結果
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
		* 行列式
		* @return 行列式の値
		*/
		float Determinant();


		/**
		* 行列の転置
		* @return 転置行列
		*/
		Matrix33 Transpose();


		/**
		* 逆行列
		* @return 逆行列
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