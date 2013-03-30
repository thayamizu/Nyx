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
		///�h���t���[���\���� 
		struct XFrame: public D3DXFRAME {
			D3DXMATRIX CombinedTransformationMatrix;///< ���ꂼ��̃��b�V���p�̍ŏI���[���h�s��
		};

		//---------------------------------------------------------------------------------------
		///X�t�@�C�����b�V���R���e�i�[�\����
		struct XMeshContainer : public D3DXMESHCONTAINER {
			uint weight;///<�d�݂̌��i�d�݂Ƃ͒��_�ւ̉e���B�j
			uint boneNum;///<�{�[���̐�
			D3DTexture*  ppTextures;///< �e�N�X�`���ւ̃|�C���^
			LPD3DXBUFFER boneBuffer;///<�{�[���E�e�[�u��
			D3DXMATRIX** boneMatrix;///<�S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
			D3DXMATRIX* boneOffsetMatrices;///<�t���[���Ƃ��Ẵ{�[���̃��[���h�s��̃|�C���^�[
		};


		//---------------------------------------------------------------------------------------
		///X���b�V���K�w�\��
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
		/// �A�j���[�V�������b�V��
		class XAnimationMesh : public XMesh {
		public:
			//---------------------------------------------------------------------------
			//�\�z�E�j��
			//---------------------------------------------------------------------------
			XAnimationMesh(std::wstring fileName, DirectGraphicsDevice& device);
			~XAnimationMesh();
			//---------------------------------------------------------------------------
			//�A�j���[�V����
			//---------------------------------------------------------------------------
			bool SetLoopTime( uint animID, float time );
			bool ChangeTrack(uint track);
			bool SetShiftTime(uint track, float time); 

			float GetAnimationSpeed();
			void SetAnimationSpeed(float speed);

			float GetAnimationTime();
			int GetNumAnimationSet();
			//---------------------------------------------------------------------------
			//�`��
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