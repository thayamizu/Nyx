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
#ifndef NYX_CORE_INCLUDED_CAMERA_H_
#define NYX_CORE_INCLUDED_CAMERA_H_
#include "Primitive/Vector3.h"
#include "Primitive/Matrix44.h"
namespace Nyx {

	///カメラ
	class Camera 
	{
	public:
		//--------------------------------------------------------------------------
		//構築・破壊
		//--------------------------------------------------------------------------
		/**
		* コンストラクタ
		*/
		Camera(
			float ex, float ey, float ez,
			float lx, float ly, float lz,
			float ux, float uy, float uz);

		/**
		* コンストラクタ
		*/
		Camera(Vector3f& eye, Vector3f& at, Vector3f&);

		/**
		* デストラクタ
		*/
		virtual ~Camera();

		//--------------------------------------------------------------------------
		//情報の取得・設定
		//--------------------------------------------------------------------------
		/**
		*
		*/
		virtual void GetEyePoint(Vector3f*);
		/**
		*
		*/
		virtual void SetEyePoint(Vector3f& eye);

		/**
		*
		*/
		virtual void GetLookAtPoint(Vector3f*);
		/**
		*
		*/
		virtual void SetLookAtPoint(Vector3f& lookAt);

		/**
		*
		*/
		virtual void GetUpPoint(Vector3f*);
		/**
		*
		*/
		virtual void SetUpPoint(Vector3f& up);

		//--------------------------------------------------------------------------
		//視野変換行列
		//--------------------------------------------------------------------------
		/**
		*
		*/
		void MatrixLookAtLH(Matrix44* out);
		/**
		*
		*/
		void MatrixLookAtRH(Matrix44* out);

		//--------------------------------------------------------------------------
		//射影変換行列
		//--------------------------------------------------------------------------
		/**
		*
		*/
		void MatrixOrthoLH(Matrix44* out, float w, float h, float zn, float zf);

		/**
		*
		*/
		void MatrixOrthoRH(Matrix44* out, float w, float h, float zn, float zf);
		/**
		*
		*/
		void MatrixPerspectiveFovLH(Matrix44* out, float fovy, float aspect, float zn, float zf);
		/**
		*
		*/
		void MatrixPerspectiveFovRH(Matrix44* out, float fovy, float aspect, float zn, float zf);

	private:
		Vector3f* eyePt;
		Vector3f* lookatPt;
		Vector3f* upPt;
	};
}
#endif