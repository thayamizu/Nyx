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
#include "Primitive/Color4f.h"

namespace Nyx
{

	const Color4f Color4f::White(1.f , 1.f, 1.f, 1.f);

	///
	const Color4f Color4f::Gray(0.5f, 0.5f, 0.5f, 1.f);

	///
	const Color4f Color4f::Black(0, 0, 0, 1.f);

	///
	const Color4f Color4f::Red(1.f, 0, 0, 1.f);

	///
	const Color4f Color4f::Green(0, 1.f, 0, 1.f);

	///
	const Color4f Color4f::Blue(0, 0, 1.f, 1.f);

	///
	const Color4f Color4f::Cyan(0, 1.f, 1.f, 1.f);

	///
	const Color4f Color4f::Magenta(1.f, 0, 1.f, 1.f);

	///
	const Color4f Color4f::Yellow(1.f, 1.f, 0, 1.f);

	//--------------------------------------------------------------------------------------
	//
	//
	Color4f::Color4f()
		:r(0), g(0), b(0),a(0)
	{
	}
	//--------------------------------------------------------------------------------------
	//
	//
	Color4f::Color4f(float red, float green, float blue, float alpha)
		: r(red),g(green),b(blue),a(alpha) 
	{
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color4f::Color4f(const Color4f& color) {
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	Color4f::~Color4f() {

	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color4f Color4f::operator +(const Color4f& color) const {
		return Color4f(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color4f Color4f::operator -(const Color4f& color) const {
		return Color4f(r - color.r, g - color.g, b - color.b, a - color.a);

	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color4f Color4f::operator *(const float value) const {
		return Color4f(r * value, g * value, b * value, a * value);

	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color4f Color4f::operator /(const float value)  const {
		return Color4f(r / value, g / value, b / value, a / value);

	}


	//--------------------------------------------------------------------------------------
	//
	//
	Color4f& Color4f::operator +=(const Color4f& color) {
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color4f& Color4f::operator -=(const Color4f& color) {
		r -= color.r;
		g -= color.g;
		b -= color.b;
		a -= color.a;

		return *this;
	}

	//--------------------------------------------------------------------------------------
	//
	//
	Color4f& Color4f::operator *=(const float value) {
		r *= value;
		g *= value;
		b *= value;
		a *= value;
		return *this;
	}
	//--------------------------------------------------------------------------------------
	//
	//
	Color4f& Color4f::operator /=(const float value) {
		r /= value;
		g /= value;
		b /= value;
		a /= value;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	//
	//
	bool Color4f::operator ==(const Color4f& color) {
		return (
			Math::Abs(r - color.r) <= Math::Epsilon &&
			Math::Abs(g - color.g) <= Math::Epsilon &&
			Math::Abs(b - color.b) <= Math::Epsilon &&
			Math::Abs(a - color.a) <= Math::Epsilon);

	}

	//--------------------------------------------------------------------------------------
	//
	//
	bool Color4f::operator !=(const Color4f& color) {
		return ! (*this == color);
	}

}