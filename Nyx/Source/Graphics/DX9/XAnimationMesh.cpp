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
		//���b�V���R���e�i�[���쐬����
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

			// ���Y���b�V�����@���������Ȃ��ꍇ�͖@����ǉ�����
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
		//�t���[����j������
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
		//���b�V���R���e�i�[��j������
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
		const float XAnimationMesh::defaultAnimationSpeed=0.0125f;//60FPS�̏ꍇ�BDirectX�ł́A4800�t���[�����P�b�Ƃ��Ĉ����̂�60/4800��0.0125�ł���

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

			/*�e�N���XXMesh�̐��������Ă���
			* XMesh�ł̓��b�V�����ʂ̏���(�}�e���A���̎擾�E�ݒ�Ƃ�)���L�q���Ă��邪�A
			* XAnimationMesh�N���X�ł�ID3DXMESHCONTAINER�𗘗p���Ă��邽�߁AXMesh���s�v�Ȃ̂��B�䂦�ɁA�l��0
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
			//�t���[���K�w�����
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