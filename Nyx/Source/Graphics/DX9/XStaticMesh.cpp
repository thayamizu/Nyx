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
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Graphics/DX9/DirectGraphicsDevice.h"
#include "Graphics/DX9/XMesh.h"
#include "Graphics/DX9/XStaticMesh.h"

namespace Nyx {
	namespace DX9 {
		//-----------------------------------------------------------------------------------------
		//
		XStaticMesh::XStaticMesh(tstring fileName, DirectGraphicsDevice* device) {
			LoadFromX(fileName, device);
		}

		//-----------------------------------------------------------------------------------------
		//
		XStaticMesh::~XStaticMesh() {
			SafeRelease(mesh);
		}

		//-----------------------------------------------------------------------------------------
		//
		int XStaticMesh::GetVertexNum() {
			return mesh->GetNumVertices();
		}

		//-----------------------------------------------------------------------------------------
		//
		int XStaticMesh::GetFaceNum() {
			return mesh->GetNumFaces();
		}

		//-----------------------------------------------------------------------------------------
		//
		void XStaticMesh::LoadFromX(tstring fileName, DirectGraphicsDevice* device) {
			LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
			ulong numMaterials;

			Direct3DDevice d3dDevice = device->GetDevice();

			HRESULT hr = D3DXLoadMeshFromX(
				fileName.c_str(), D3DXMESH_MANAGED, 
				d3dDevice, NULL, &pD3DXMtrlBuffer, NULL,
				&numMaterials, &mesh );
			Assert(hr == S_OK);

			//テクスチャ・マテリアル読み込みの下準備
			D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
			//親クラスXMeshの生成
			Create(numMaterials);

			for (ulong i=0; i < numMaterials; i++ ) { 
				//マテリアルの読み込み
				SetMaterial(d3dxMaterials[i].MatD3D, i);

				//テクスチャの読み込み		
				if( (d3dxMaterials[i].pTextureFilename != NULL) && 
					(strlen(d3dxMaterials[i].pTextureFilename) > 0) ){
						D3DTexture texture;
						hr = D3DXCreateTextureFromFileA( d3dDevice,  d3dxMaterials[i].pTextureFilename,  &texture); 
						SetTexture(&texture, i);
						Assert(hr == S_OK);
				}
				else {//テクスチャがないぞ
					SetTexture(NULL, i);
				}
			}
		}

		//-----------------------------------------------------------------------------------------
		//
		void XStaticMesh::Render(DirectGraphicsDevice *device, Matrix44* world) {


			Direct3DDevice d3ddevice=device->GetDevice();
			d3ddevice->SetTransform(D3DTS_WORLD, reinterpret_cast<D3DXMATRIX*>(world));
			int n = GetNumMaterial();
			for (int i=0; i < n; i++) {
				//マテリアルの取得
				D3DMaterial material;
				D3DTexture texture;
				GetMaterial(&material, i);
				GetTexture(&texture, i);

				//マテリアルを設定

				d3ddevice->SetMaterial(&material);
				//	if (texture != NULL)
				d3ddevice->SetTexture(0, texture);

				//描画
				mesh->DrawSubset(i);
			}

		}
	}
}