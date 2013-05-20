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
#include "Graphics/DX9/XAnimationController.h"
#include "Graphics/DX9/XAnimationMesh.h"

namespace Nyx {
	namespace DX9{

		//---------------------------------------------------------------------------------------
		//
		HRESULT XMeshHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame) {

			*ppNewFrame = NULL;
			XFrame *pFrame =new XFrame();
			Assert(pFrame != NULL);
			if (pFrame == NULL) {
				return E_OUTOFMEMORY;    
			}

			pFrame->Name=new char[lstrlenA(Name) + 1];
			Assert(pFrame->Name != NULL);
			if (!pFrame->Name) {
				return E_FAIL;
			}
			strcpy(pFrame->Name,Name);

			D3DXMatrixIdentity(&pFrame->TransformationMatrix);
			D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
			pFrame->pMeshContainer	 = NULL;
			pFrame->pFrameSibling	 = NULL;
			pFrame->pFrameFirstChild = NULL;

			*ppNewFrame = pFrame;
			//DestroyFrame(pFrame);
			return S_OK;
		}

		//---------------------------------------------------------------------------------------
		//
		//HRESULT XMeshHierarchy::CreateMeshContainer
		//メッシュコンテナーを作成する
		HRESULT XMeshHierarchy::CreateMeshContainer(
			LPCSTR Name, CONST D3DXMESHDATA* pMeshData,
			CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE* pEffectInstances,
			DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, 
			LPD3DXMESHCONTAINER *ppMeshContainer) 
		{

			HRESULT hr;
			XMeshContainer *pMeshContainer = NULL;
			int iFacesAmount;
			size_t iMaterial;
			LPDIRECT3DDEVICE9 pDevice = NULL;
			LPD3DXMESH pMesh = NULL;
			*ppMeshContainer = NULL;

			pMesh = pMeshData->pMesh;
			pMeshContainer = new XMeshContainer;
			if (pMeshContainer == NULL)
			{
				return E_OUTOFMEMORY;
			}
			ZeroMemory(pMeshContainer, sizeof(XMeshContainer));

			pMeshContainer->Name=new char[lstrlenA(Name) + 1];	
			if (!pMeshContainer->Name)
			{
				return E_FAIL;
			}
			strcpy(pMeshContainer->Name,Name);
			pMesh->GetDevice(&pDevice);
			iFacesAmount = pMesh->GetNumFaces();

			// 当該メッシュが法線を持たない場合は法線を追加する
			if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
			{
				pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
				hr = pMesh->CloneMeshFVF( pMesh->GetOptions(), 
					pMesh->GetFVF() | D3DFVF_NORMAL, 
					pDevice, &pMeshContainer->MeshData.pMesh );
				if (FAILED(hr))
				{
					return E_FAIL;
				}

				pMesh = pMeshContainer->MeshData.pMesh;
				D3DXComputeNormals( pMesh, NULL );
			}
			else 
			{
				pMeshContainer->MeshData.pMesh = pMesh;
				pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
				pMesh->AddRef();
			}
			pMeshContainer->NumMaterials = max(1, NumMaterials);
			pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
			pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
			pMeshContainer->pAdjacency = new DWORD[iFacesAmount*3];
			if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
			{
				return E_OUTOFMEMORY;
			}

			memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * iFacesAmount*3);
			memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

			if (NumMaterials > 0)            
			{
				memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

				for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
				{
					if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
					{
						char strTexturePath[MAX_PATH];
						strcpy( strTexturePath,  pMeshContainer->pMaterials[iMaterial].pTextureFilename );
						if( FAILED( D3DXCreateTextureFromFileA( pDevice, strTexturePath, 
							&pMeshContainer->ppTextures[iMaterial] ) ) )
							pMeshContainer->ppTextures[iMaterial] = NULL;
						pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
					}
				}
			}
			else
			{
				pMeshContainer->pMaterials[0].pTextureFilename = NULL;
				memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
				pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
				pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
				pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
				pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
			}   
			*ppMeshContainer = pMeshContainer;
			pMeshContainer = NULL;

			if (pMeshContainer != NULL)
			{
				DestroyMeshContainer(pMeshContainer);
			}

			SafeRelease( pDevice );
			return S_OK;
		}

		//---------------------------------------------------------------------------------------
		//フレームを破棄する
		HRESULT XMeshHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree) 
		{
			if(pFrameToFree->pFrameFirstChild) {    
				DestroyFrame(pFrameToFree->pFrameFirstChild);
			}

			if(pFrameToFree->pFrameSibling) {
				DestroyFrame(pFrameToFree->pFrameSibling);
			}

			SafeDeleteArray( pFrameToFree->Name );
			SafeDelete( pFrameToFree );

			return S_OK; 
		}

		//HRESULT XMeshHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
		//メッシュコンテナーを破棄する
		HRESULT XMeshHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase) {
			XMeshContainer *pMeshContainer = (XMeshContainer*)pMeshContainerBase;

			SafeRelease(pMeshContainer->pSkinInfo);
			SafeDeleteArray( pMeshContainer->Name );
			SafeDeleteArray( pMeshContainer->pAdjacency );
			SafeDeleteArray( pMeshContainer->pMaterials );

			if (pMeshContainer->ppTextures != NULL) {
				for (uint i = 0; i < pMeshContainer->NumMaterials; ++i) {
					SafeRelease( pMeshContainer->ppTextures[i] );
				}
				SafeDeleteArray(pMeshContainer->ppTextures);
			}

			SafeRelease( pMeshContainer->MeshData.pMesh);
			SafeDelete( pMeshContainer );

			return S_OK;
		}

		//---------------------------------------------------------------------------------------
		//
		const float XAnimationMesh::defaultAnimationSpeed=0.0125f;//60FPSの場合。DirectXでは、4800フレームを１秒として扱うので60/4800≒0.0125である

		//---------------------------------------------------------------------------------------
		//
		XAnimationMesh::XAnimationMesh(std::wstring fileName, DirectGraphicsDevice& device) {
			/*position = pos;
			rotation = Matrix44::Unit;
			world = Matrix44::Unit;*/
			animationSpeed = defaultAnimationSpeed;
			frameRoot = NULL;

			animationController= new XAnimationController();
			LoadFromX(fileName, device.GetDevice());

			/*親クラスXMeshの生成をしておく
			* XMeshではメッシュ共通の処理(マテリアルの取得・設定とか)を記述してあるが、
			* XAnimationMeshクラスではID3DXMESHCONTAINERを利用しているため、XMeshが不要なのだ。ゆえに、値は0
			*/
			Create(0);
		}

		//---------------------------------------------------------------------------------------
		//
		void XAnimationMesh::LoadFromX(std::wstring fileName, Direct3DDevice d3dDevice) {
			D3DXAnimationController animationController = NULL;
			HRESULT hr = D3DXLoadMeshHierarchyFromX(
				fileName.c_str(), D3DXMESH_MANAGED, d3dDevice, &hierarchy, 
				NULL, &frameRoot, &animationController);

			this->animationController->SetAnimationController(animationController);
			Assert(hr == S_OK);
		}

		//---------------------------------------------------------------------------------------
		//
		XAnimationMesh::~XAnimationMesh() {
			FreeFrameHierarchy(frameRoot);
			//フレーム階層を解放
			hierarchy.DestroyFrame(frameRoot);
			SafeDelete(animationController);
		}
		//---------------------------------------------------------------------------------------
		//
		void XAnimationMesh::FreeFrameHierarchy(D3DXFrame pFrame) {
			if(pFrame->pMeshContainer != NULL){	
				hierarchy.DestroyMeshContainer(pFrame->pMeshContainer);
			}	

			if (pFrame->pFrameSibling != NULL){
				FreeFrameHierarchy(pFrame->pFrameSibling);
			}

			if (pFrame->pFrameFirstChild != NULL) {
				FreeFrameHierarchy(pFrame->pFrameFirstChild);
			}
		}

		//---------------------------------------------------------------------------------------
		//
		void XAnimationMesh::RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase) {
			XMeshContainer *container = (XMeshContainer*)pMeshContainerBase;
			XFrame *frame = (XFrame*)pFrameBase;

			Direct3DDevice d3dDevice;
			container->MeshData.pMesh->GetDevice(&d3dDevice);
			d3dDevice->SetTransform(D3DTS_WORLD, &frame->CombinedTransformationMatrix);

			for (uint i = 0; i < container->NumMaterials; ++i) {
				d3dDevice->SetMaterial( &container->pMaterials[i].MatD3D );
				d3dDevice->SetTexture( 0, container->ppTextures[i] );
				container->MeshData.pMesh->DrawSubset(i);
			}
		}
		//
		//---------------------------------------------------------------------------------------
		//
		void XAnimationMesh::DrawFrame(D3DXFrame pFrame) 
		{

			D3DXMeshContainer meshContainer;
			meshContainer = pFrame->pMeshContainer;
			while (meshContainer != NULL) {
				RenderMeshContainer(meshContainer, pFrame);
				meshContainer = meshContainer->pNextMeshContainer;
			}

			if (pFrame->pFrameSibling != NULL) {
				DrawFrame(pFrame->pFrameSibling);
			}

			if (pFrame->pFrameFirstChild != NULL) {
				DrawFrame(pFrame->pFrameFirstChild);
			}

		}
		//---------------------------------------------------------------------------------------

		void XAnimationMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
		{
			XFrame *pFrame = (XFrame*)pFrameBase;	

			if (pParentMatrix != NULL) {
				D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
			}
			else {
				pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
			}

			if (pFrame->pFrameSibling != NULL) {
				UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
			}

			if (pFrame->pFrameFirstChild != NULL) {
				UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
			}
		}

		//------------------------------------------------------------------------------------------------
		//
		void XAnimationMesh::Render(Matrix44& world) {
			UpdateFrameMatrices(frameRoot, reinterpret_cast<D3DXMATRIX*>(&world.Mat));
			DrawFrame(frameRoot);		
			animationController->AdvanceTime(animationSpeed);	
		}
		//------------------------------------------------------------------------------------------------
		//
		bool XAnimationMesh::SetLoopTime( uint animID, float time ) {
			return animationController->SetLoopTime(animID, time);
		}

		//------------------------------------------------------------------------------------------------
		//
		bool XAnimationMesh::SetShiftTime(uint track, float time) {
			return animationController->SetShiftTime(track, time);
		}

		//------------------------------------------------------------------------------------------------
		//
		bool XAnimationMesh::ChangeTrack(uint track) {
			return animationController->ChangeAnimation(track);
		}

		//------------------------------------------------------------------------------------------------
		//
		float XAnimationMesh::GetAnimationSpeed() {
			return animationSpeed;
		}

		//------------------------------------------------------------------------------------------------
		//
		void XAnimationMesh::SetAnimationSpeed(float speed) {
			animationSpeed = speed;
		}

		//------------------------------------------------------------------------------------------------
		//
		int XAnimationMesh::GetNumAnimationSet() {
			return animationController->GetNumAnimationSet();//animationController->GetNumAnimationSets();
		}
	}
}