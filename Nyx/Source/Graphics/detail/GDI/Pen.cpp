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
#include "Graphics/detail/GDI/Pen.h"

namespace nyx {
	namespace gdi {
		//------------------------------------------------------------------------------
		//
		Pen::Pen()
			:hdc_(nullptr), pen_(nullptr)
		{

		}
		//------------------------------------------------------------------------------
		//
		Pen::Pen(PEN_STYLE style, int width, color3c color_){
			int type = static_cast<int>(style);
			pen_ = CreatePen(type, width, RGB(color_.r, color_.g, color_.b));
		}

		//------------------------------------------------------------------------------
		//
		Pen::~Pen() {
			::DeleteObject(pen_);

		} 

		//------------------------------------------------------------------------------
		//
		void  Pen::Set(PEN_STYLE style, int width, color3c color_) {
			int type = static_cast<int>(style);
			pen_ = CreatePen(type, width, RGB(color_.r, color_.g, color_.b));
		}
	
		//------------------------------------------------------------------------------
		//
		void Pen::Select(HWND hwnd) {
			hdc_ = GetDC(hwnd);	
		}


		//------------------------------------------------------------------------------
		//
		void  Pen::DrawLine(HDC hdc, int x, int y) {
			//�y����I�����Đ���`��
			SelectObject(hdc, pen_);
			LineTo(hdc, x, y); 
		}

		//------------------------------------------------------------------------------
		//
		void  Pen::DrawRect(HDC hdc, int x, int y, int width, int height) {
			//�y����I�����Ē����`��`��
			::SelectObject(hdc, pen_);
			::Rectangle(hdc, x, y, width, height);

		}

		//------------------------------------------------------------------------------
		//
		void  Pen::DrawEllipse(HDC hdc, int x, int y, int width, int height) {
			//�y����I�����đȉ~��`��
			SelectObject(hdc, pen_);
			::Rectangle(hdc, x, y, width, height);
		}

		//------------------------------------------------------------------------------
		//
		void  Pen::DrawPolygon(HDC hdc, point2i *point, int num) {
			//�y����I�����đ��p�`��`��
			::SelectObject(hdc, pen_);
			::Polygon(hdc, reinterpret_cast<POINT*>(point->elements), num);
		}

		//------------------------------------------------------------------------------
		//
		void  Pen::DrawBezier(HDC hdc, point2i* point, int num) {
			//�y����I�����ăx�W�F�Ȑ���`��
			SelectObject(hdc, pen_);
			::PolyBezier(hdc, reinterpret_cast<POINT*>(point->elements), num);
		}
	}
}