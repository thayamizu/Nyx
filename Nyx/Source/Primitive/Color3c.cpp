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