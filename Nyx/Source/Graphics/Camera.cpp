f/********************************************************************************
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
