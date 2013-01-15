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
#include "Primitive/Color4c.h"

namespace Nyx
{
	///
	const Color4c Color4c::White(255 , 255, 255, 255);

	///
	const Color4c Color4c::Gray(128, 128, 128, 255);

	///
	const Color4c Color4c::Black(0, 0, 0, 255);

	///
	const Color4c Color4c::Red(255, 0, 0, 255);

	///
	const Color4c Color4c::Green(0, 255, 0, 255);

	///
	const Color4c Color4c::Blue(0, 0, 255, 255);

	///
	const Color4c Color4c::Cyan(0, 255, 255, 255);

	///
	const Color4c Color4c::Magenta(255, 0, 255, 255);

	///
	const Color4c Color4c::Yellow(255, 255, 0, 255);

	//--------------------------------------------------------------------------------------
	Color4c::Color4c():r(0), g(0), b(0),a(0) {

	}
	
	//--------------------------------------------------------------------------------------
	Color4c::Color4c(uchar red, uchar green, uchar blue, uchar alpha) :
	r(red), g(green), b(blue), a(alpha)
	{
	}

	//--------------------------------------------------------------------------------------
	Color4c::Color4c(const Color4c& color) {
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}

	//--------------------------------------------------------------------------------------
	Color4c::~Color4c() {

	}

	//--------------------------------------------------------------------------------------
	Color4c Color4c::operator +(const Color4c& color) const {
		return Color4c(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	//--------------------------------------------------------------------------------------
	Color4c Color4c::operator -(const Color4c& color) const {
		return Color4c(r - color.r, g - color.g, b - color.b, a - color.a);

	}

	//--------------------------------------------------------------------------------------
	Color4c Color4c::operator *(float value) const {
		return Color4c(r * (uchar)value, g * (uchar)value, b * (uchar)value, a * (uchar)value);

	}

	//--------------------------------------------------------------------------------------
	Color4c Color4c::operator /(float value)  const {
		return Color4c(r / (uchar)value, g / (uchar)value, b / (uchar)value, a / (uchar)value);

	}


	//--------------------------------------------------------------------------------------
	Color4c& Color4c::operator +=(const Color4c& color) {
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	Color4c& Color4c::operator -=(const Color4c& color) {
		r -= color.r;
		g -= color.g;
		b -= color.b;
		a -= color.a;

		return *this;
	}

	//--------------------------------------------------------------------------------------
	Color4c& Color4c::operator *=(float value) {
		r *= (uchar)value;
		g *= (uchar)value;
		b *= (uchar)value;
		a *= (uchar)value;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	Color4c& Color4c::operator /=(float value) {
		r /= (uchar)value;
		g /= (uchar)value;
		b /= (uchar)value;
		a /= (uchar)value;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	bool Color4c::operator ==(const Color4c& color) {
		return (
			Math::Abs(r - color.r) <= Math::Epsilon &&
			Math::Abs(g - color.g) <= Math::Epsilon &&
			Math::Abs(b - color.b) <= Math::Epsilon &&
			Math::Abs(a - color.a) <= Math::Epsilon);

	}

	//--------------------------------------------------------------------------------------
	bool Color4c::operator !=(const Color4c& color) {
		return !(*this == color);
	}

}