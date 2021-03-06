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
#include "Graphics/detail/GDI/Pen.h"

namespace nyx {
	namespace gdi {
		//------------------------------------------------------------------------------
		//
		pen::pen()
			:hdc_(nullptr), pen_(nullptr)
		{

		}
		//------------------------------------------------------------------------------
		//
		pen::pen(PEN_STYLE style, int width, color3c color_){
			int type = static_cast<int>(style);
			pen_ = CreatePen(type, width, RGB(color_.r, color_.g, color_.b));
		}

		//------------------------------------------------------------------------------
		//
		pen::~pen() {
			::DeleteObject(pen_);

		} 

		//------------------------------------------------------------------------------
		//
		void  pen::set(PEN_STYLE style, int width, color3c color_) {
			int type = static_cast<int>(style);
			pen_ = CreatePen(type, width, RGB(color_.r, color_.g, color_.b));
		}
	
		//------------------------------------------------------------------------------
		//
		void pen::select(HWND hwnd) {
			hdc_ = GetDC(hwnd);	
		}


		//------------------------------------------------------------------------------
		//
		void  pen::draw_line(HDC hdc, int x, int y) {
			//ペンを選択して線を描画
			SelectObject(hdc, pen_);
			LineTo(hdc, x, y); 
		}

		//------------------------------------------------------------------------------
		//
		void  pen::draw_rect(HDC hdc, int x, int y, int width, int height) {
			//ペンを選択して長方形を描画
			::SelectObject(hdc, pen_);
			::Rectangle(hdc, x, y, width, height);

		}

		//------------------------------------------------------------------------------
		//
		void  pen::draw_ellipse(HDC hdc, int x, int y, int width, int height) {
			//ペンを選択して楕円を描画
			SelectObject(hdc, pen_);
			::Rectangle(hdc, x, y, width, height);
		}

		//------------------------------------------------------------------------------
		//
		void  pen::draw_polygon(HDC hdc, point2i *point, int num) {
			//ペンを選択して多角形を描画
			::SelectObject(hdc, pen_);
			::Polygon(hdc, reinterpret_cast<POINT*>(point->elements), num);
		}

		//------------------------------------------------------------------------------
		//
		void  pen::draw_bezier(HDC hdc, point2i* point, int num) {
			//ペンを選択してベジェ曲線を描画
			SelectObject(hdc, pen_);
			::PolyBezier(hdc, reinterpret_cast<POINT*>(point->elements), num);
		}
	}
}