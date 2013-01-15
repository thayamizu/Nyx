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
#include "Primitive/Color3f.h"

namespace Nyx
{
	///
	const Color3f Color3f::White(1.f , 1.f, 1.f);

	///
	const Color3f  Color3f::Gray(0.5f, 0.5f, 0.5f);

	///
	const Color3f  Color3f::Black(0.f, 0.f, 0.f);

	///
	const Color3f  Color3f::Red(1.f, 0.f, 0.f);

	///
	const Color3f  Color3f::Green(0, 1.f, 0);

	///
	const Color3f  Color3f::Blue(0, 0, 1.f);

	///
	const Color3f  Color3f::Cyan(0, 1.f, 1.f);

	///
	const Color3f Color3f::Magenta(1.f, 0, 1.f);

	///
	const Color3f  Color3f::Yellow(1.f, 1.f, 0);

	//--------------------------------------------------------------------------------------
	//
	//
	Color3f::Color3f()
		:r(0.f), g(0.f), b(0.f)
	{

	}
	//--------------------------------------------------------------------------------------
	//
	//
	Color3f::Color3f(float red,float green, float blue)
		: r(red),g(green),b(blue)
	{

	}
	//--------------------------------------------------------------------------------------
	//
	//
	Color3f::Color3f(const Color3f& color) 
		:r(color.r), g(color.g), b(color.b)
	{

	}
	Color3f::~Color3f() {

	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3f Color3f::operator +(const Color3f& color) const {
		return Color3f(r + color.r, g + color.g, b + color.b);
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3f Color3f::operator -(const Color3f& color) const {
		return Color3f(r - color.r, g - color.g, b - color.b);
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3f Color3f::operator *(float value) const {
		return Color3f(r * value, g * value, b * value);
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3f Color3f::operator /(float value)  const {
		return Color3f(r / value, g / value, b / value);
	}


	//--------------------------------------------------------------------------------------
	//
	//
	Color3f& Color3f::operator +=(const Color3f& color) {
		r += color.r;
		g += color.g;
		b += color.b;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3f& Color3f::operator -=(const Color3f& color) {
		r -= color.r;
		g -= color.g;
		b -= color.b;

		return *this;
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color3f& Color3f::operator *=(float value) {
		r *= value;
		g *= value;
		b *= value;
		return *this;
	}
	//--------------------------------------------------------------------------------------
	//
	//
	Color3f& Color3f::operator /=(float value) {
		r /= value;
		g /= value;
		b /= value;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	//
	//
	bool Color3f::operator ==(const Color3f& color) {
		return (
			Math::Abs(r - color.r) <= Math::Epsilon &&
			Math::Abs(g - color.g) <= Math::Epsilon &&
			Math::Abs(b - color.b) <= Math::Epsilon);

	}

	//--------------------------------------------------------------------------------------
	//
	//
	bool Color3f::operator !=(const Color3f& color) {
		return (
			Math::Abs(r - color.r) > Math::Epsilon ||
			Math::Abs(g - color.g) > Math::Epsilon ||
			Math::Abs(b - color.b) > Math::Epsilon);
	}
}