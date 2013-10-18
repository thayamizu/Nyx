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
#ifndef NYX_CORE_INCLUDED_DIRECT_GRAPHICS_9_DEFINITION_H_
#define NYX_CORE_INCLUDED_DIRECT_GRAPHICS_9_DEFINITION_H_
#include <memory>
//boost/intrusive_ptr
#include <boost/intrusive_ptr.hpp>

//D3D9
#include <D3D9.h>
#include <D3DX9.h>

//dx error
#include <DXErr.h>



//型定義
//--------------------------------------------------------------
//Direct 3D
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


#endif