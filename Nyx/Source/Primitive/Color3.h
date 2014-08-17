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
#ifndef NYX_CORE_INCLUDED_COLOR3_H_
#define NYX_CORE_INCLUDED_COLOR3_H_
#include "Utility/Math.h"

namespace nyx
{
	template <typename T>
	class color3{
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic type.");
	public:
		//--------------------------------------------------------------------------------------
		// �ϐ�
		//--------------------------------------------------------------------------------------
		union {
			struct {
				///
				T r;
				///
				T g;
				///
				T b;
			};

			T elements[3];
		} ;
		//--------------------------------------------------------------------------------------
		// �萔
		//--------------------------------------------------------------------------------------
		///
		static const color3<T> White;

		///
		static const color3<T> Gray;

		///
		static const color3<T> Black;

		///
		static const color3<T> Red;

		///
		static const color3<T> Green;

		///
		static const color3<T> Blue;

		///
		static const color3<T> Cyan;

		///
		static const color3<T> Magenta;

		///
		static const color3<T> Yellow;

		//--------------------------------------------------------------------------------------
		// �R���X�g���N�^
		//--------------------------------------------------------------------------------------
		color3<T>() {
			Set(0, 0, 0);
		}
		color3<T>(T r, T g, T b) {
			Set(r, g, b);
		}
		color3<T>(const color3<T>& other) {
			Set(other.r, other.g, other.b);
		}

		void Set(T r, T g, T b) {
			this->r = r;
			this->g = g;
			this->b = b;
			Clamp();

		}
		void Clamp() {
			r = math::clamp<T>(r, 0, 255); 
			g = math::clamp<T>(g, 0, 255); 
			b = math::clamp<T>(b, 0, 255); 
		}

		

		//--------------------------------------------------------------------------------------
		// ���Z
		//--------------------------------------------------------------------------------------
		color3<T> operator +(const color3<T>&  color) const {
			return color3<T>(r + color.r, g + color.g, b + color.b);

		}
		color3<T> operator -(const color3<T>&  color) const {
			return color3<T>(r - color.r, g - color.g, b - color.b);

		}
		color3<T> operator *(const T value) const {
			return color3<T>(r * value, g * value, b * value);

		}
		color3<T> operator /(const T value) const {
			return color3<T>(r / value, g / value, b / value);

		}

		//--------------------------------------------------------------------------------------
		// ������Z
		//--------------------------------------------------------------------------------------
		color3<T>& operator +=(const color3<T>&  color) {
			Set(r + color.r, g + color.g, b + color.b);
			return *this;
		}
		color3<T>& operator -=(const color3<T>& color) {
			Set(r - color.r, g - color.g, b - color.b);
			return *this;
		}
		color3<T>& operator *=(T value) {
			Set(r * value, g * value, b * value);
			return *this;
		}
		color3<T>& operator /=(T value) {
			Set(r / value, g / value, b / value);
			return *this;
		}

		//--------------------------------------------------------------------------------------
		// �_�����Z
		//--------------------------------------------------------------------------------------
		bool operator ==(const color3<T>& color) const {
			return (
				math::abs(r - color.r) <= math::EPSILON &&
				math::abs(g - color.g) <= math::EPSILON &&
				math::abs(b - color.b) <= math::EPSILON);
		}
		bool operator !=(const color3<T>& color) const {
			return !( *this == color);
		}
	};


	//--------------------------------------------------------------------------------------
	// �ʖ���`
	//--------------------------------------------------------------------------------------
	typedef color3<uint8_t> color3c;
	typedef color3<float> color3f;

	template<>
	void color3f::Clamp() {
		r = math::clamp<float>(r, 0.f, 1.f); 
		g = math::clamp<float>(g, 0.f, 1.f); 
		b = math::clamp<float>(b, 0.f, 1.f); 
	}


	//--------------------------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------------------------
	template <typename T>
	const color3<T> color3<T>::White(255 , 255, 255);

	///
	template <typename T>
	const color3<T> color3<T>::Gray(128, 128, 128);

	///
	template <typename T>
	const color3<T> color3<T>::Black(0, 0, 0);

	///
	template <typename T>
	const color3<T> color3<T>::Red(255, 0, 0);

	///
	template <typename T>
	const color3<T> color3<T>::Green(0, 255, 0);

	///
	template <typename T>
	const color3<T> color3<T>::Blue(0, 0, 255);

	///
	template <typename T>
	const color3<T> color3<T>::Cyan(0, 255, 255);

	///
	template <typename T>
	const color3<T> color3<T>::Magenta(255, 0, 255);

	///
	template <typename T>
	const color3<T> color3<T>::Yellow(255, 255, 0);

	///
	const color3f color3f::White(1.f , 1.f, 1.f);

	///
	const color3f  color3f::Gray(0.5f, 0.5f, 0.5f);

	///
	const color3f  color3f::Black(0.f, 0.f, 0.f);

	///
	const color3f  color3f::Red(1.f, 0.f, 0.f);

	///
	const color3f  color3f::Green(0, 1.f, 0);

	///
	const color3f  color3f::Blue(0, 0, 1.f);

	///
	const color3f  color3f::Cyan(0, 1.f, 1.f);

	///
	const color3f color3f::Magenta(1.f, 0, 1.f);

	///
	const color3f  color3f::Yellow(1.f, 1.f, 0);
}
#endif