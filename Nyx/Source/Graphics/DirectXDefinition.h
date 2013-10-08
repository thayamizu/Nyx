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
//DirectX9を使う
#define USE_DIRECTX9 1
#ifdef USE_DIRECTX9
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#elif USE_DIRECTX10
//DirectX10以降の機能を利用する
//固定機能パイプラインが廃止されたため、スプライト一つ描画するごとにシェーダが必要で実装が面倒である
//また、2D描画のDirect2D(DirectDraw相当)はWindowsVista以降しか使えない。ゆえに、しばらくはDX9
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






//型定義
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
//インタフェース
//構造体
#elif USE_DIRECTX11
//インタフェース
//構造体
#endif


