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

			//�e�N�X�`���E�}�e���A���ǂݍ��݂̉�����
			D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
			//�e�N���XXMesh�̐���
			Create(numMaterials);

			for (ulong i=0; i < numMaterials; i++ ) { 
				//�}�e���A���̓ǂݍ���
				SetMaterial(d3dxMaterials[i].MatD3D, i);

				//�e�N�X�`���̓ǂݍ���		
				if( (d3dxMaterials[i].pTextureFilename != NULL) && 
					(strlen(d3dxMaterials[i].pTextureFilename) > 0) ){
						D3DTexture texture;
						hr = D3DXCreateTextureFromFileA( d3dDevice,  d3dxMaterials[i].pTextureFilename,  &texture); 
						SetTexture(&texture, i);
						Assert(hr == S_OK);
				}
				else {//�e�N�X�`�����Ȃ���
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
				//�}�e���A���̎擾
				D3DMaterial material;
				D3DTexture texture;
				GetMaterial(&material, i);
				GetTexture(&texture, i);

				//�}�e���A����ݒ�

				d3ddevice->SetMaterial(&material);
				//	if (texture != NULL)
				d3ddevice->SetTexture(0, texture);

				//�`��
				mesh->DrawSubset(i);
			}

		}
	}
}