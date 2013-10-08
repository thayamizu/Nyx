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
//DirectX9���g��
#define USE_DIRECTX9 1
#ifdef USE_DIRECTX9
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#elif USE_DIRECTX10
//DirectX10�ȍ~�̋@�\�𗘗p����
//�Œ�@�\�p�C�v���C�����p�~���ꂽ���߁A�X�v���C�g��`�悷�邲�ƂɃV�F�[�_���K�v�Ŏ������ʓ|�ł���
//�܂��A2D�`���Direct2D(DirectDraw����)��WindowsVista�ȍ~�����g���Ȃ��B�䂦�ɁA���΂炭��DX9
//d2d
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
//d3d
#include <d3d10.h>
#include <d3dx10.h>
#pragma comment( lib, "d3d10.lib")
#pragma comment( lib, "d3dx10.lib") 
#endif

//dx error
#include <dxerr.h>
#pragma comment( lib, "dxerr.lib")

//dx guid
#pragma comment( lib, "dxguid.lib")






//�^��`
//--------------------------------------------------------------
//Direct 3D
#ifdef USE_DIRECTX9
typedef LPDIRECT3D9                   Direct3D;
typedef LPDIRECT3DDEVICE9             Direct3DDevice;
typedef	D3DMATERIAL9                  D3DMaterial;
typedef D3DLIGHT9	                  D3DLight;
typedef D3DVIEWPORT9                  D3DViewPort;
typedef	LPD3DXMESH                    D3DMesh;
typedef	LPDIRECT3DTEXTURE9            D3DTexture;
typedef LPD3DXFRAME                   D3DXFrame;
typedef LPD3DXMESHCONTAINER           D3DXMeshContainer;
typedef	LPD3DXANIMATIONCONTROLLER     D3DXAnimationController;


#elif USE_DIRECTX10
//�C���^�t�F�[�X
//�\����
#elif USE_DIRECTX11
//�C���^�t�F�[�X
//�\����
#endif


