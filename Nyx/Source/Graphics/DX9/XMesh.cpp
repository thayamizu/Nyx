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
#include "Primitive/Color4f.h"
#include "Graphics/DX9/XMesh.h"

namespace Nyx {
	namespace DX9 {
		//-----------------------------------------------------------------------------------------
		//
		XMesh::~XMesh() {
			SafeDelete(materials);
			SafeDelete(textures);
		}

		//-----------------------------------------------------------------------------------------
		//
		void XMesh::Create(int numMaterials) {
			numMaterial = numMaterials;

			materials = new D3DMaterial[numMaterial];
			Assert(materials != NULL);

			textures = new D3DTexture[numMaterial];
			Assert(textures != NULL);
		}

		//-----------------------------------------------------------------------------------------
		//
		void XMesh::GetAmbient(Color4f* ambient, int index) {
			if (index < 0 || index >= numMaterial) {return ;}
			ambient->r = materials[index].Ambient.r;
			ambient->g = materials[index].Ambient.g;
			ambient->b = materials[index].Ambient.b;
			ambient->a = materials[index].Ambient.a;

		}

		//-----------------------------------------------------------------------------------------
		//
		void XMesh::SetAmbient(Color4f& ambient, int index) {
			if (index < 0 || index >= numMaterial) {return ;}
			materials[index].Ambient.r = ambient.r;
			materials[index].Ambient.g = ambient.g;
			materials[index].Ambient.b = ambient.b;
			materials[index].Ambient.a = ambient.a;
		}
		//-----------------------------------------------------------------------------------------
		//	
		void XMesh::GetSpecular(Color4f* specular, int index) {
			if (index < 0 || index >= numMaterial) {return ;}
			specular->r = materials[index].Specular.r;
			specular->g = materials[index].Specular.g;
			specular->b = materials[index].Specular.b;
			specular->a = materials[index].Specular.a;
		}

		//-----------------------------------------------------------------------------------------
		//
		void XMesh::SetSpecular(Color4f& specular, int index) {
			if (index < 0 || index >= numMaterial) {return ;}
			materials[index].Specular.r = specular.r;
			materials[index].Specular.g = specular.g;
			materials[index].Specular.b = specular.b;
			materials[index].Specular.a = specular.a;
		}

		//-----------------------------------------------------------------------------------------
		//
		void XMesh::GetDiffuse(Color4f* diffuse, int index) {
			if (index < 0 || index >= numMaterial) {return ;}
			diffuse->r = materials[index].Diffuse.r;
			diffuse->g = materials[index].Diffuse.g;
			diffuse->b = materials[index].Diffuse.b;
			diffuse->a = materials[index].Diffuse.a;
		}

		//-----------------------------------------------------------------------------------------
		//
		void XMesh::SetDiffuse(Color4f& diffuse, int index) {
			if (index < 0 || index >= numMaterial) {return ;}
			materials[index].Diffuse.r = diffuse.r;
			materials[index].Diffuse.g = diffuse.g;
			materials[index].Diffuse.b = diffuse.b;
			materials[index].Diffuse.a = diffuse.a;
		}


		//-----------------------------------------------------------------------------------------
		//
		float XMesh::GetPower(int index) {
			if (index<0 || index >= numMaterial) {return -1.f;}
			return materials[index].Power;
		}

		//-----------------------------------------------------------------------------------------
		//
		void  XMesh::SetPower(float power, int index) {
			if (index<0 || index >= numMaterial) {return ;}
			materials[index].Power = power;
		}

		//-----------------------------------------------------------------------------------------
		//
		void XMesh::GetMaterial(D3DMaterial* material, int index) {
			if (index<0 || index >= numMaterial) {return ;}
			*material = materials[index];
		}

		//-----------------------------------------------------------------------------------------
		//
		void XMesh::SetMaterial(D3DMaterial& material, int index) {
			if (index<0 || index >= numMaterial) {return ;}

			materials[index] = material;
		}

		//-----------------------------------------------------------------------------------------
		//
		void XMesh::GetTexture(D3DTexture* texture, int index) {
			if (index<0 || index >= numMaterial) {return ;}

			*texture = textures[index];
		}

		//-----------------------------------------------------------------------------------------
		//
		void XMesh::SetTexture(D3DTexture* texture,int index) {
			if (index<0 || index >= numMaterial) {return ;}
			if (texture == NULL) {
				textures[index] = NULL; return;
			}
			textures[index] = *texture;

		}

		//-----------------------------------------------------------------------------------------
		//
		int XMesh::GetNumMaterial() {
			return numMaterial;
		}
	}
}