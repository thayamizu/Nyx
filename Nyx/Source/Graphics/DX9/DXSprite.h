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
#ifndef NYX_CORE_DIRECT_GRAPHICS_SPRITE_H_
#define NYX_CORE_DIRECT_GRAPHICS_SPRITE_H_

#include "Graphics/ISprite.h"
#include "Primitive/Rect2i.h"
#include "Primitive/Color4c.h"

namespace Nyx {
	namespace DX9 {


		///�X�v���C�g��DirectX�ɂ�����
		/**
		����Ȋ����ŕ`��ł���Ƃ��ꂵ��
		//�R���X�g���N�^���Ȃ���ŏ�����
		ctor {
		Sprite * sprite = new Sprite("image", int w, int h);
		}

		�Ȃ�炩�̕`��^�X�N�ŕ`�悷��Ƃ��ɕϊ��s����쐬���ĕ`�悷��
		void Task::Render() {
		Matrix44 world = Matrix44::Unit;
		Matrix44::Tranform(&world, sx, sy, sz, rx, ry, rz, tx, ty, tz);
		�����
		Matrix44::Tranform(&world, Vector3(sx, sy, sz), Vector3(rx, ry, rz), Vector3(tx, ty, tz));
		�Ƃ��Ă����܂�Ȃ����낤
		sprite->Render(world);	
		}

		�ϊ��s������̂����߂�ǂ��Łi�����āA�኱�x���i�s��I�ȈӖ��ł��j�j���邪�A����͒v��������܂��B����ȊO�́A���Ȃ�y����̂͂��ł���B
		�`�b�v�Ƃ��Ďg��������΁A�R���X�g���N�^�ł̂悤�ɁA�������Ƃ������̃`�b�v�ԍ�����ѕ��E�������w�肷��΂悢�B
		ctor {
		Sprite * sprite = new Sprite("image", int w, int h, int cx, int cy, int cw, int ch);
		}

		void Task::Render(camera) {
		cx = counter%2 //�܂��A���Ԃ�J�E���^�g���ă`�b�v�ԍ����߂���=>�A�j���[�V�����p�^�[���̎擾�͓����I�ɏ����Ă������������
		cy = counter%2 // 
		//�K�v������΃`�b�v�T�C�Y��ύX���邱�Ƃ��ł���
		sprite->SetChipSize(64, 64);
		Matrix44 world = Matrix44::Unit;
		Matrix44::TranformMatrix(&world, sx, sy, sz, rx, ry, rz, tx, ty, tz);
		sprite->Render(world, cx, cy);	
		}

		*/


		///�X�v���C�g
		class DXSprite :public ISprite {
		public:
			//----------------------------------------------------------------------------------------------
			//�\�z�E�j��
			//----------------------------------------------------------------------------------------------
			/**
			* �R���X�g���N�^
			*/
			DXSprite(DirectGraphicsDevice& device, int w, int h);
			/**
			*
			*/
			DXSprite(DirectGraphicsDevice& device, tstring fileName, int w, int h, int cw=0, int ch=0);
			/**
			*
			*/
			DXSprite(DirectGraphicsDevice& device, std::shared_ptr<char> data, uint size,  
				int w, int h, int cw=0, int ch=0);
			/**
			*
			*/
			~DXSprite();
			/**
			*
			*/

			void Restore();
			/**
			*
			*/
			void Release();

			/**
			*
			*/
			void Fill(Rect2i rect,Color4c color);
			/**
			*
			*/
			void Render(Matrix44& world, Color4c color);

			/**
			*
			*/
			void Render(Matrix44& world, int cx, int cy, Color4c color);

			/**
			*
			*/
			void Render(Matrix44& world, Rect2i rect, Color4c color);

			/**
			*
			*/
			HRESULT OnLostDevice();

			/**
			*
			*/
			HRESULT OnResetDevice();
			/**
			*
			*/
			HRESULT CreateSprite(DirectGraphicsDevice& device);

		private:
			D3DTexture texture;///<
			ID3DXSprite * sprite;///<
		};
	}
}
#endif