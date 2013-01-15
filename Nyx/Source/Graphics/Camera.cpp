f/********************************************************************************
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
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Graphics/Camera.h"
 namespace Nyx {
	 //-----------------------------------------------------------------------------------------
	 //
	 Camera::Camera(
		 float  ex, float ey, float ez,
		 float  lx, float ly, float lz,
		 float  ux, float uy, float uz)
	 {
		 eyePt	= new Vector3(ex, ey, ez);
		 lookatPt	= new Vector3(lx, ly, lz);
		 upPt	= new Vector3(ux, uy, uz);

	 }

	 //-----------------------------------------------------------------------------------------
	 //
	 Camera::Camera(Vector3& eye, Vector3& at, Vector3& up)
	 {
		 eyePt	= new Vector3(eye);
		 lookatPt	= new Vector3(at);
		 upPt	= new Vector3(up);

	 }
	 //-----------------------------------------------------------------------------------------
	 //
	 Camera::~Camera()
	 {
		 SafeDelete(eyePt);
		 SafeDelete(lookatPt);
		 SafeDelete(upPt);
	 }

	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::GetEyePoint(Vector3* eye)
	 {
		 Assert(eyePt);
		 *eye	= *eyePt;
	 }

	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::SetEyePoint(Vector3& eye)
	 {
		 Assert(eyePt);
		 *eyePt	= eye;
	 }

	 //-----------------------------------------------------------------------------------------
	 //	
	 void Camera::GetLookAtPoint(Vector3* lookat) 
	 {
		 Assert(lookatPt);
		 *lookat	= *lookatPt; 
	 }

	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::SetLookAtPoint(Vector3& lookat)
	 {
		 Assert(lookatPt);
		 *lookatPt = lookat;
	 }

	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::GetUpPoint(Vector3* up)
	 {
		 Assert(upPt);
		 *up	= *upPt;

	 }

	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::SetUpPoint(Vector3& up)
	 {
		 Assert(upPt);
		 *upPt	= up;
	 }

	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::MatrixLookAtLH(Matrix44* out)
	 {
		 Assert(eyePt);
		 Assert(lookatPt);
		 Assert(upPt);

		 ::D3DXMatrixLookAtLH(
			 reinterpret_cast<D3DXMATRIX*>(out->Mat), 
			 reinterpret_cast<D3DXVECTOR3*>(eyePt), 
			 reinterpret_cast<D3DXVECTOR3*>(lookatPt), 
			 reinterpret_cast<D3DXVECTOR3*>(upPt));

	 }

	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::MatrixLookAtRH(Matrix44* out)
	 {
		 ::D3DXMatrixLookAtRH(
			 reinterpret_cast<D3DXMATRIX*>(out), 
			 reinterpret_cast<D3DXVECTOR3*>(eyePt), 
			 reinterpret_cast<D3DXVECTOR3*>(lookatPt), 
			 reinterpret_cast<D3DXVECTOR3*>(upPt));

	 }


	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::MatrixOrthoLH(Matrix44* out,		float w, float h, float zn, float zf)
	 {
		 ::D3DXMatrixOrthoLH(reinterpret_cast<D3DXMATRIX*>(out), w, h, zn, zf);
	 }


	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::MatrixOrthoRH(Matrix44* out,		float w, float h, float zn, float zf)
	 {
		 ::D3DXMatrixOrthoRH(reinterpret_cast<D3DXMATRIX*>(out), w, h, zn, zf);

	 }

	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::MatrixPerspectiveFovLH(Matrix44* out,	float fovy, float aspect, float zn, float zf)
	 {
		 ::D3DXMatrixPerspectiveFovLH(reinterpret_cast<D3DXMATRIX*>(out), fovy, aspect, zn, zf);
	 }

	 //-----------------------------------------------------------------------------------------
	 //
	 void Camera::MatrixPerspectiveFovRH(Matrix44* out,	float fovy, float aspect, float zn, float zf)
	 {
		 ::D3DXMatrixPerspectiveFovRH(reinterpret_cast<D3DXMATRIX*>(out), fovy, aspect, zn, zf);

	 }
}
