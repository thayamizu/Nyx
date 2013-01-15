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
#ifndef NYX_CORE_INCLUDED_ISPRITE_H_
#define NYX_CORE_INCLUDED_ISPRITE_H_
#include "Graphics/ITexture.h"
namespace Nyx {
	class ITexture;
	///�X�v���C�g
	class ISprite : public ITexture {
	public:
		/**
		*
		*/
		ISprite() 
			:ITexture(), width(0), height(0), chipX(0),chipY(0), chipWidth(0), chipHeight(0)
		{

		} 
		/**
		*
		*/
		ISprite(int w, int h, int cx, int cy, int cw, int ch)
			:ITexture(), width(w), height(h), chipX(cx), chipY(cy), chipWidth(cw), chipHeight(ch)
		{

		}

		/**
		*
		*/
		virtual ~ISprite() {}
		/**
		*
		*/
		virtual void SetWidth(int w);

		/**
		*
		*/
		virtual int GetWidth();
		/**
		*
		*/
		virtual void SetHeight(int h);
		/**
		*
		*/
		virtual int GetHeight();
		/**
		*
		*/
		virtual void SetChipSize(int w, int h);
		/**
		*
		*/
		virtual void GetChipSize(int& w, int & h);
		/**
		*
		*/
		virtual void SetChipX(int x);
		/**
		*
		*/
		virtual int GetChipX();
		/**
		*
		*/
		virtual void SetChipY(int y);
		/**
		*
		*/
		virtual int GetChipY();
	private:
		int width;
		int height;
		int chipX, chipY;
		int chipWidth, chipHeight;

	};
}
#endif