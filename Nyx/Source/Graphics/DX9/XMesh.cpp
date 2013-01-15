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