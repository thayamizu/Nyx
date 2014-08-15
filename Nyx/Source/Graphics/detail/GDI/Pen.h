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
#ifndef NYX_CORE_INCLUDED_PEN_H_
#define NYX_CORE_INCLUDED_PEN_H_

#include "Primitive/Color3.h"
#include "Primitive/Vector2.h"

namespace nyx {
	namespace gdi
	{  
		/// �y���X�^�C�� 
		enum class PEN_STYLE {
			PEN_STYLE_SOLID      = 0x00,
			PEN_STYLE_DASH       = 0x01,       
			PEN_STYLE_DOT        = 0x02,       
			PEN_STYLE_DASH_DOT    = 0x03,       
			PENSTYLE_DASH_DOT_DOT = 0x04, 
			PEN_STYLE_NULL		  = 0x05,
			PEN_STYLE_NUM,
		};


		///�y��
		class Pen {
		public:
			//---------------------------------------------------------------
			//�\�z�E�j��
			//---------------------------------------------------------------
			/**
			*
			*/
			Pen();
			
			/**
			*
			*/
			Pen(PEN_STYLE style, int width, color3c color);

			/**
			*
			*/
			~Pen();

			//---------------------------------------------------------------
			//�Z�b�g
			//---------------------------------------------------------------
			/**
			*
			*/
			void Set(PEN_STYLE style, int width, color3c color);

			/**
			*
			*/
			void Select(HWND hwnd);
			//---------------------------------------------------------------
			//�`��
			//--------------------------------------------------------------- 
			/**
			*
			*/
			void DrawLine(HDC hdc, int x, int y);
			/**
			*
			*/
			void DrawRect(HDC hdc, int x, int y, int width, int height);
			/**
			*
			*/
			void DrawEllipse(HDC hdc, int x, int y, int width, int height);

			/**
			*
			*/
			void DrawPolygon(HDC hdc, point2i* p, int num);

			/**
			*
			*/
			void DrawBezier(HDC hdc, point2i* p, int num);
		private:
			HDC hdc_;
			HPEN pen_;
		};
	}
}
#endif

