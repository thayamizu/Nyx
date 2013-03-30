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
#ifndef NYX_CORE_INCLUDED_XMESH_ANIMATION_H_
#define NYX_CORE_INCLUDED_XMESH_ANIMATION_H_
#include "Graphics/DX9/DirectGraphicsDevice.h"
#include "Graphics/DX9/XAnimationController.h"
#include "Graphics/DX9/XMesh.h"
#include "Primitive/Vector3.h"
#include "Primitive/Matrix44.h"

namespace Nyx {
	namespace DX9{

		//--------------------------------------------------------------------------------------
		///派生フレーム構造体 
		struct XFrame: public D3DXFRAME {
			D3DXMATRIX CombinedTransformationMatrix;///< それぞれのメッシュ用の最終ワールド行列
		};

		//---------------------------------------------------------------------------------------
		///Xファイルメッシュコンテナー構造体
		struct XMeshContainer : public D3DXMESHCONTAINER {
			uint weight;///<重みの個数（重みとは頂点への影響。）
			uint boneNum;///<ボーンの数
			D3DTexture*  ppTextures;///< テクスチャへのポインタ
			LPD3DXBUFFER boneBuffer;///<ボーン・テーブル
			D3DXMATRIX** boneMatrix;///<全てのボーンのワールド行列の先頭ポインター
			D3DXMATRIX* boneOffsetMatrices;///<フレームとしてのボーンのワールド行列のポインター
		};


		//---------------------------------------------------------------------------------------
		///Xメッシュ階層構造
		class XMeshHierarchy: public ID3DXAllocateHierarchy
		{
		public:
			XMeshHierarchy(){}
			virtual ~XMeshHierarchy() {}
			STDMETHOD(CreateFrame)(THIS_ LPCSTR , LPD3DXFRAME *);
			STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR ,CONST D3DXMESHDATA* ,CONST D3DXMATERIAL* , 
				CONST D3DXEFFECTINSTANCE* , DWORD , CONST DWORD *, LPD3DXSKININFO , LPD3DXMESHCONTAINER *);
			STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME );
			STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER );
		};


		//---------------------------------------------------------------------------------------
		/// アニメーションメッシュ
		class XAnimationMesh : public XMesh {
		public:
			//---------------------------------------------------------------------------
			//構築・破壊
			//---------------------------------------------------------------------------
			XAnimationMesh(std::wstring fileName, DirectGraphicsDevice& device);
			~XAnimationMesh();
			//---------------------------------------------------------------------------
			//アニメーション
			//---------------------------------------------------------------------------
			bool SetLoopTime( uint animID, float time );
			bool ChangeTrack(uint track);
			bool SetShiftTime(uint track, float time); 

			float GetAnimationSpeed();
			void SetAnimationSpeed(float speed);

			float GetAnimationTime();
			int GetNumAnimationSet();
			//---------------------------------------------------------------------------
			//描画
			//---------------------------------------------------------------------------
			void Render(Matrix44& world);
			Vector3 position;
			Matrix44 rotation;
			Matrix44 world;
		public:
			static const float defaultAnimationSpeed;

		private:
			void LoadFromX(std::wstring fileName, Direct3DDevice d3dDevice);
			void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
			void RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
			void DrawFrame(LPD3DXFRAME pFrame);
			void FreeFrameHierarchy(LPD3DXFRAME pFrame);

			float animationSpeed;
			D3DXFrame frameRoot;
			XAnimationController* animationController;
			XMeshHierarchy hierarchy;
		};


	}
}
#endif