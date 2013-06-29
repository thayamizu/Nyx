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

		/**デフォルトコンストラクタ
		* 行列の値をすべてゼロに設定する
		*/
		Matrix44();

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
		Matrix44(
			float a11, float a12, float a13, float a14, 
			float a21, float a22, float a23, float a24,
			float a31, float a32, float a33, float a34,
			float a41, float a42, float a43, float a44
			);

		/** 
		* デストラクタ
		*/
		~Matrix44();

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
		void Set(float a11, float a12, float a13, float a14, 
			float a21, float a22, float a23, float a24,
			float a31, float a32, float a33, float a34,
			float a41, float a42, float a43, float a44);

		/**
		* 加算
		* @param 右辺値
		* @return 加算結果
		*/
		Matrix44 operator +(const Matrix44& mat) const;

		/**
		* 減算
		* @param 右辺値
		* @return 減算結果
		*/
		Matrix44 operator -(const Matrix44& mat) const;

		/**
		* 乗算
		* @param 右辺値
		* @return 乗算結果
		*/
		Matrix44 operator *(const float s) const;

		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Matrix44 operator *(const Matrix44& mat) const;

		/**
		* 除算
		* @param 右辺値
		* @return 除算結果
		*/
		Matrix44 operator /(const float s) const;

		/**
		* 加算
		* @param 右辺値 
		* @return 加算結果 
		*/
		Matrix44& operator +=(const Matrix44 & mat);

		/**
		* 減算
		* @param 右辺値 
		* @return 減算結果
		*/
		Matrix44& operator -=(const Matrix44 & mat);

		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Matrix44& operator *=(const float s);

		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Matrix44& operator *=(const Matrix44& s);

		/**
		* 除算
		* @param 右辺値 
		* @return 除算結果
		*/
		Matrix44& operator /=(const float s);

		/**
		*代入
		*@param 右辺値
		*@return 代入結果
		*/
		Matrix44& operator = (const Matrix44& mat);

		bool Equal(const Matrix44 & m);
		bool operator == (const Matrix44 &m);
		bool operator != (const Matrix44 &m);

		/**
		* 行列式
		* @return 行列式の値
		*/
		float Determinant();

		/**
		* 行列の転置
		* @return 転置行列
		*/
		Matrix44& Transpose();

		/**
		* 逆行列
		* @return 逆行列
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