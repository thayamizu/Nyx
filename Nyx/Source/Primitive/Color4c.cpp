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