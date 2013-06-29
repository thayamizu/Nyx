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
#ifndef NYX_CORE_INCLUDED_XMESH_H_
#define NYX_CORE_INCLUDED_XMESH_H_
#include "Graphics/IMesh.h"
#include "Primitive/Color4.h"
namespace Nyx {
	namespace DX9 {

		///XFileメッシュ
		class XMesh : public IMesh {
		public:
			/**
			*
			*/
			virtual ~XMesh();
			/**
			*
			*/
			virtual void Create(int numMaterials);

			/**
			*
			*/
			virtual void GetAmbient(Color4f* ambient, int index);

			/**
			*
			*/
			virtual void SetAmbient(Color4f& ambient, int index);

			/**
			*
			*/
			virtual void GetSpecular(Color4f* specular, int index);
			/**
			*
			*/
			virtual void SetSpecular(Color4f& specular, int index);

			/**
			*
			*/
			virtual void GetDiffuse(Color4f* diffuse, int index);
			/**
			*
			*/
			virtual void SetDiffuse(Color4f& diffuse, int index);

			/**
			*
			*/
			virtual float GetPower(int index);
			/**
			*
			*/
			virtual void  SetPower(float power, int index);

			/**
			*
			*/
			virtual void GetMaterial(D3DMaterial* material, int index);
			/**
			*
			*/
			virtual void SetMaterial(D3DMaterial& material, int index);

			/**
			*
			*/
			virtual void GetTexture(D3DTexture* texture, int index);
			/**
			*
			*/
			virtual void SetTexture(D3DTexture* texture,int index);

			/**
			*
			*/
			virtual int GetNumMaterial();
		private:
			int numMaterial;
			D3DMaterial* materials;
			D3DTexture* textures;
		};
	}
}
#endif