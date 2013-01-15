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
#include "Primitive/Color3c.h"

namespace Nyx
{
	///
	const Color3c Color3c::White(255 , 255, 255);

	///
	const Color3c Color3c::Gray(128, 128, 128);

	///
	const Color3c Color3c::Black(0, 0, 0);

	///
	const Color3c Color3c::Red(255, 0, 0);

	///
	const Color3c Color3c::Green(0, 255, 0);

	///
	const Color3c Color3c::Blue(0, 0, 255);

	///
	const Color3c Color3c::Cyan(0, 255, 255);

	///
	const Color3c Color3c::Magenta(255, 0, 255);

	///
	const Color3c Color3c::Yellow(255, 255, 0);

	//--------------------------------------------------------------------------------------
	//
	//
	Color3c::Color3c():r(0), g(0), b(0) {

	}
	//--------------------------------------------------------------------------------------
	//
	//
	Color3c::Color3c(const uchar _r, const uchar _g, const uchar _b): r(_r),g(_g),b(_b) {

	}
	//--------------------------------------------------------------------------------------
	//
	//
	Color3c::Color3c(const Color3c& color) {
		r = color.r;
		g = color.g;
		b = color.b;

	}
	Color3c::~Color3c() {

	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3c Color3c::operator +(const Color3c& color) const {
		return Color3c(r + color.r, g + color.g, b + color.b);
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3c Color3c::operator -(const Color3c& color) const {
		return Color3c(r - color.r, g - color.g, b - color.b);
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3c Color3c::operator *(const float value) const {
		return Color3c(r * (uchar)value, g * (uchar)value, b * (uchar)value);
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3c Color3c::operator /(const float value)  const {
		return Color3c(r / (uchar)value, g / (uchar)value, b / (uchar)value);
	}


	//--------------------------------------------------------------------------------------
	//
	//
	Color3c& Color3c::operator +=(const Color3c& color) {
		r += color.r;
		g += color.g;
		b += color.b;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3c& Color3c::operator -=(const Color3c& color) {
		r -= color.r;
		g -= color.g;
		b -= color.b;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3c& Color3c::operator *=(float value) {
		r *= (uchar)value;
		g *= (uchar)value;
		b *= (uchar)value;
		return *this;
	}
	//--------------------------------------------------------------------------------------
	//
	//
	Color3c& Color3c::operator /=(const float value) {
		r /= (uchar)value;
		g /= (uchar)value;
		b /= (uchar)value;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	//
	//
	bool Color3c::operator ==(const Color3c& color) {
		return (
			Math::Abs(r - color.r) <= Math::Epsilon &&
			Math::Abs(g - color.g) <= Math::Epsilon &&
			Math::Abs(b - color.b) <= Math::Epsilon);

	}

	//--------------------------------------------------------------------------------------
	//
	//       
	bool Color3c::operator !=(const Color3c& color) {
		return !( *this == color);
	}
}