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
#ifndef NYX_CORE_DIRECT_GRAPHICS_DEVICE_H_
#define NYX_CORE_DIRECT_GRAPHICS_DEVICE_H_

#include "Primitive/Color3.h"
#include "Primitive/Vector3.h"
#include "Primitive/Matrix44.h"
#include "DirectXDefinition.h"

namespace Nyx {
	namespace DX9 {

		///DirectGraphics�f�o�C�X
		class DirectGraphicsDevice 
		{
		public:
			/**
			* �R���X�g���N�^
			* @param HWND �E�C���h�E�n���h���C���X�^���X
			* @param int �E�C���h�E�̕�(�E�C���h�E�̕��E�������o�b�N�o�b�t�@�̕��E�����ƂȂ�܂�)
			* @param int �E�C���h�E�̍���
			* @param bool �E�C���h�E���[�h
			*/
			DirectGraphicsDevice(HWND hwnd, int w, int h, bool mode=true);

			/**
			* �f�X�g���N�^
			*/
			~DirectGraphicsDevice();

			/**
			* �f�o�C�X���X�g���̏���
			* @return bool �f�o�C�X���Z�b�g�ɐ��������true��Ԃ��܂�
			*/
			bool OnLostDevice();

			/**
			* Direct3D�f�o�C�X��Ԃ��܂��B
			* @return Direct3DDevice  
			*/
			D3dDevice9Ptr GetDevice();

			/**
			*�@�J�[�\���̕\���E��\����؂�ւ��܂�
			* @param bool true�ł���΃J�[�\���\��
			*/
			void ShowCursor(bool);

			/**
			* �f�B�X�v���C�\���x��؂�ւ��܂��B
			* @return bool �E�C���h�E���[�h�ł����true��Ԃ��܂�
			*/
			bool ChangeDisplayMode();

			/**
			* �E�C���h�E���[�h���ǂ����𔻒�
			* @return bool �E�C���h�E���[�h�ł���Ȃ��true
			*/
			bool IsWindowed();

			/**
			* �t���X�N���[�����[�h���ǂ����𔻒�
			* @return bool �t���X�N���[�����[�h�ł���Ȃ��true
			*/
			bool IsFullScreen();
			
			
			
			//---------------------------------------------------------------------------
			//�T���v���[�X�e�[�g
			//---------------------------------------------------------------------------
			/**
			*�@���݂̃T���v���[�X�e�[�g�̎擾
			* @param DWORD �T���v���[�X�e�[�g�C���f�b�N�X
			* @param D3DSAMPLERSTATETYPE �T���v���[�X�e�[�g�̎��
			* @param DWORD �擾����T�A���v���[�X�e�[�g�̒l
			*/
			void GetSamplerState(DWORD sampler,D3DSAMPLERSTATETYPE type, DWORD* value);


			/**
			* �T���v���[�X�e�[�g�̐ݒ�
			* @param DWORD �T���v���[�X�e�[�g�C���f�b�N�X
			* @param D3DSAMPLERSTATETYPE �T���v���[�X�e�[�g�̎��
			* @param DWORD �ݒ肷��X�e�[�g�l
			*/
			void SetSamplerState(DWORD sampler,D3DSAMPLERSTATETYPE type, DWORD value);
			
			
			//---------------------------------------------------------------------------
			//���C�g
			//---------------------------------------------------------------------------
			/**
			*���C�g���擾
			*/
			void GetLight(D3DLIGHT9 *);

			/**
			* ���C�g��ݒ�
			* @param Vector3f ���C�g�ʒu
			* @param Vector3f �����x�N�g��
			* @param Color3f �g�U���ˌ��̒l(RGB)
			* @param Color3f ���ʔ��ˌ��̒l(RGB)
			* @param float ���C�g�͈̔�
			* @param D3DLIGHTTYPE ���C�g�̎��(�|�C���g���C�g�f�B���N�V���i�����C�g�Ȃ�)
			*/
			void SetLight(Vector3f pos, Vector3f dir, Color3f diffuse, Color3f specular, float range, D3DLIGHTTYPE type);

			//---------------------------------------------------------------------------
			//�g�����X�t�H�[��
			//---------------------------------------------------------------------------
			/**
			* �f�o�C�X�̃g�����X�t�H�[���֘A�X�e�[�g��ݒ肷��
			* @param D3DTRANSFORMSTATETYPE �g�����X�t�H�[���X�e�[�g�̒l
			* @param const Matrix44�g�����X�t�H�[���s��
			*/
			void SetTransform(D3DTRANSFORMSTATETYPE state, const Matrix44 * matrix);


			/**
			*�f�o�C�X�̃g�����X�t�H�[���֘A�X�e�[�g���擾����
			* @param D3DTRANSFORMSTATETYPE �g�����X�t�H�[���X�e�[�g�̒l
			* @param Matrix44�g�����X�t�H�[���s��
			*/
			void GetTransform(D3DTRANSFORMSTATETYPE state, Matrix44 * matrix);

			//---------------------------------------------------------------------------
			//�r���[�|�[�g
			//---------------------------------------------------------------------------
			/**
			* �r���[�|�[�g���擾
			* @param D3DVeiwPort �r���[�|�[�g
			*/
			void GetViewPort(D3DVIEWPORT9* viewport);

			/**
			*�@�r���[�|�[�g�̐ݒ�
			* @param int x�l
			* @param int y�l
			* @param int�@��
			* @param int�@����
			* @param float z-near
			* @param float z-far
			*/
			void SetViewPort(int x, int y, int width, int height, float near, float far);

			//---------------------------------------------------------------------------
			//�`��
			//---------------------------------------------------------------------------
			/**
			* ��ʂ��N���A
			*/
			void Clear();
			/**
			* �V�[���̊J�n
			* @return bool �V�[���̊J�n�Ɏ��s�����ꍇ�ɂ�false���Ԃ�܂�
			*/
			bool BeginScene();

			/**
			* �V�[���̏I��
			*/
			void EndScene();

			void RenderPrimitive();

			//---------------------------------------------------------------------------
			//�X�e�[�g�u���b�N
			//---------------------------------------------------------------------------
			void BeginStateBlock();
			void EndStateBlock();


			//---------------------------------------------------------------------------
			//���_�L�q
			//---------------------------------------------------------------------------
			void CreateVertexDeclaration();
			
			//---------------------------------------------------------------------------
			//���_�o�b�t�@�̐���
			//---------------------------------------------------------------------------
			void CreateVertexBuffer();
			
			//---------------------------------------------------------------------------
			//�t�H�O
			//---------------------------------------------------------------------------
			void SetFog();

			//---------------------------------------------------------------------------
			//Z�e�X�g
			//---------------------------------------------------------------------------
			void SetZTest();

			//---------------------------------------------------------------------------
			//�C��
			//---------------------------------------------------------------------------
			/**
			* �f�o�C�X�̃��Z�b�g
			* @param�@D3DPRESETN_PARAMETERS �f�o�C�X�p�����[�^
			* @return �f�o�C�X���Z�b�g�ɐ��������true
			*/
			bool ResetDevice(D3DPRESENT_PARAMETERS& d3dpp);
		private:
			RECT windowSize;
			int backBufferWidth;
			int backBufferHeight;

			bool isWindowed;
			bool isLostDevice;
			bool isShowCursor;

			HWND hwnd;
			D3d9Ptr d3d_;
			HMENU hMenu;
			D3dDevice9Ptr d3dDevice_;
			D3DPRESENT_PARAMETERS presentParameter;
		};
	}
}

#endif