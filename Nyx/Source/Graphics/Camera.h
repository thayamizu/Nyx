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
#ifndef NYX_CORE_INCLUDED_CAMERA_H_
#define NYX_CORE_INCLUDED_CAMERA_H_
#include "Primitive/Vector3.h"
#include "Primitive/Matrix44.h"
namespace Nyx {

	///�J����
	class Camera 
	{
	public:
		//--------------------------------------------------------------------------
		//�\�z�E�j��
		//--------------------------------------------------------------------------
		/**
		* �R���X�g���N�^
		*/
		Camera(
			float ex, float ey, float ez,
			float lx, float ly, float lz,
			float ux, float uy, float uz);

		/**
		* �R���X�g���N�^
		*/
		Camera(Vector3& eye, Vector3& at, Vector3&);

		/**
		* �f�X�g���N�^
		*/
		virtual ~Camera();

		//--------------------------------------------------------------------------
		//���̎擾�E�ݒ�
		//--------------------------------------------------------------------------
		/**
		*
		*/
		virtual void GetEyePoint(Vector3*);
		/**
		*
		*/
		virtual void SetEyePoint(Vector3& eye);

		/**
		*
		*/
		virtual void GetLookAtPoint(Vector3*);
		/**
		*
		*/
		virtual void SetLookAtPoint(Vector3& lookAt);

		/**
		*
		*/
		virtual void GetUpPoint(Vector3*);
		/**
		*
		*/
		virtual void SetUpPoint(Vector3& up);

		//--------------------------------------------------------------------------
		//����ϊ��s��
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
		//�ˉe�ϊ��s��
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
		Vector3* eyePt;
		Vector3* lookatPt;
		Vector3* upPt;
	};
}
#endif