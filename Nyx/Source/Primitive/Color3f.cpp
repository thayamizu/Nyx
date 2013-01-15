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