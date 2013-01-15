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
#ifndef NYX_CORE_INCLUDED_DIRECT_GRAPHICS_SPRITE_MANAGER_H_
#define NYX_CORE_INCLUDED_DIRECT_GRAPHICS_SPRITE_MANAGER_H_

#include "Graphics/DX9/DXSprite.h"
namespace Nyx {
	namespace DX9 {

		//�O���錾
		class Nyx::DX9::DXSprite;
		class Nyx::DX9::DirectGraphicsDevice;

		///�X�v���C�g�̊Ǘ��N���X
		class DXSpriteManager {
			typedef std::vector<DXSprite*> DXSpriteContainer;
		public:
			static const int defaultCapacity;
			/**
			*
			*/

			DXSpriteManager();
			/**
			*
			*/
			DXSpriteManager(int capacity);
			/**
			*
			*/
			~DXSpriteManager() ;
			/**
			*
			*/
			bool Load(DirectGraphicsDevice& device, tstring fileName, int width, int height, int cw=0, int ch=0);
			/**
			*
			*/
			int Add(DXSprite* sprite);
			/**
			*
			*/
			void Release();
			/**
			*@note
			* ���̃��\�b�h���g���ƁA�������ɃL���b�V�����ꂽ�f�[�^�����ɁA�e�N�X�`�����Đ����邱�Ƃ��ł���B<br/>
			* �������ADXSprite�N���X�́A�������X�g���[�W�N���X��D3DPOOL_MANAGED���g�p���Ă��邽�߁A�����I�Ƀ��X�g�A����K�v
			* �͂Ȃ�<br/>
			* �f�o�C�X���X�g�����ꍇ�ɂ́ADirectGraphicsDevice��OnLostDevice���\�b�h��Direct3DDevice�����Z�b�g����Ƃ���
			* ���̂悤�ɂ���΂悢<br/>
			* spriteManager->OnLostDevice();<br/>
			* if (device->OnLosteDevice()) {<br/>
			*    sprite->OnReset();<br/>
			*}<br/>
			*���̃��\�b�h���g���ꍇ�ɂ́A���̂悤�ɂ���Ƃ悢<br/>
			* spriteManager->Release();<br/>
			* if (device->OnLostDevice()) {<br/>
			* spriteManager->Restore();<br/>
			*}<br/>
			* �������A�ǂ���̕��@���}���`���j�^�ɂ͑Ή����Ă��Ȃ��B�}���`���j�^�̏ꍇ�A�܂�Ɏ��s���邱�Ƃ�����
			*/
			void Restore(DirectGraphicsDevice& device);
			/**
			*
			*/
			void Clear();
			/**
			*
			*/
			bool OnResetDevice();
			/**
			*
			*/
			bool OnLostDevice();
			DXSprite* GetSprite(size_t index);
		private:
			bool LoadFromFile(DirectGraphicsDevice& device, tstring fileName, int w, int h, int cw, int ch);
			bool LoadFromPackedFile(DirectGraphicsDevice& device, tstring fileName, int w, int h, int cw, int ch);

		private:
			DXSpriteContainer spriteContainer;
		};
	}
}
#endif