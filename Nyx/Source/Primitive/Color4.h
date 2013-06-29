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
#ifndef NYX_CORE_INCLUDED_COLOR4_H_
#define NYX_CORE_INCLUDED_COLOR4_H_

namespace Nyx
{
	template <typename T>
	class Color4 {
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic type");
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
				///
				T a;
			};

			T elements[4];
		} ;
		//--------------------------------------------------------------------------------------
		// �萔
		//--------------------------------------------------------------------------------------
		///
		static const Color4<T> White;

		///
		static const Color4<T> Gray;

		///
		static const Color4<T> Black;

		///
		static const Color4<T> Red;

		///
		static const Color4<T> Green;

		///
		static const Color4<T> Blue;

		///
		static const Color4<T> Cyan;

		///
		static const Color4<T> Magenta;

		///
		static const Color4<T> Yellow;

		/**
		*
		*/
		Color4<T>() {
			Set(0, 0, 0, 0);
		}


		/**
		*
		*/
		Color4<T>(const T red, const T green, const T blue, const T alpha) {
			Set(red, green, blue, alpha);
		}


		/**
		*
		*/
		Color4<T>(const Color4<T>& color) {
			Set(color.r, color.g, color.b, color.a);
		}


		/**
		*
		*/
		void Set(const T red, const T green, const T blue, const T alpha) {
			this->r = red;
			this->g = green;
			this->b = blue;
			this->a = alpha;
			Clamp();
		}


		/**
		*
		*/
		void Clamp() {
			r = Math::Clamp<T>(r, 0, 255);
			g = Math::Clamp<T>(g, 0, 255);
			b = Math::Clamp<T>(b, 0, 255);
			a = Math::Clamp<T>(a, 0, 255);
		}


		/**
		*
		*/
		Color4<T> operator +(const Color4<T>& color) const {
			return Color4<T>(r + color.r, g + color.g, b + color.b, a + color.a);
		}


		/**
		*
		*/
		Color4<T> operator -(const Color4<T>& color) const {
			return Color4<T>(r - color.r, g - color.g, b - color.b, a - color.a);
		}


		/**
		*
		*/
		Color4<T> operator *(T value) const {
			return Color4<T>(r * value, g * value, b * value, a * value);
		}


		/**
		*
		*/
		Color4<T> operator /(T value) const {
			return Color4<T>(r / value, g / value, b / value, a / value);
		}


		/**
		*
		*/
		Color4<T>& operator +=(const Color4<T>& color) {
			Set(r + color.r, g + color.g, b + color.b, a + color.a);
			return *this;
		}


		/**
		*
		*/
		Color4<T>& operator -=(const Color4<T>& color) {
			Set(r - color.r, g - color.g, b - color.b, a - color.a);
			return *this;
		}


		/**
		*
		*/
		Color4<T>& operator *=(T value) {
			Set(r * value, g * value, b * value, a * value);
			return *this;
		}


		/**
		*
		*/
		Color4<T>& operator /=(T value) {
			Set(r / value, g / value, b / value, a / value);
			return *this;
		}


		/**
		*
		*/
		bool operator ==(const Color4<T>& color) {
			return (
				Math::Abs(r - color.r) <= Math::Epsilon &&
				Math::Abs(g - color.g) <= Math::Epsilon &&
				Math::Abs(b - color.b) <= Math::Epsilon &&
				Math::Abs(a - color.a) <= Math::Epsilon);
		}


		/**
		*
		*/
		bool operator !=(const Color4<T>& color) {
			return !(*this == color);
		}
	};

	//--------------------------------------------------------------------------------------
	// �ʖ���`
	//--------------------------------------------------------------------------------------
	typedef Color4<uchar> Color4c;
	typedef Color4<float> Color4f;

	//--------------------------------------------------------------------------------------
	// ���ꉻ
	//--------------------------------------------------------------------------------------
	template<>
	void Color4f::Clamp() {
		r = Math::Clamp<float>(r, 0.f, 1.f); 
		g = Math::Clamp<float>(g, 0.f, 1.f); 
		b = Math::Clamp<float>(b, 0.f, 1.f); 
		a = Math::Clamp<float>(a, 0.f, 1.f); 
	}


	//--------------------------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------------------------
	template <typename T>
	const Color4<T> Color4<T>::White(255 , 255, 255, 255);

	///
	template <typename T>
	const Color4<T> Color4<T>::Gray(128, 128, 128, 255);

	///
	template <typename T>
	const Color4<T> Color4<T>::Black(0, 0, 0, 255);

	///
	template <typename T>
	const Color4<T> Color4<T>::Red(255, 0, 0, 255);

	///
	template <typename T>
	const Color4<T> Color4<T>::Green(0, 255, 0, 255);

	///
	template <typename T>
	const Color4<T> Color4<T>::Blue(0, 0, 255, 255);

	///
	template <typename T>
	const Color4<T> Color4<T>::Cyan(0, 255, 255, 255);

	///
	template <typename T>
	const Color4<T> Color4<T>::Magenta(255, 0, 255, 255);

	///
	template <typename T>
	const Color4<T> Color4<T>::Yellow(255, 255, 0, 255);

	///
	const Color4f Color4f::White(1.f, 1.f, 1.f, 1.f);

	///
	const Color4f  Color4f::Gray(0.5f, 0.5f, 0.5f, 1.f);

	///
	const Color4f  Color4f::Black(0.f, 0.f, 0.f, 1.f);

	///
	const Color4f  Color4f::Red(1.f, 0.f, 0.f, 1.f);

	///
	const Color4f  Color4f::Green(0, 1.f, 0, 1.f);

	///
	const Color4f  Color4f::Blue(0, 0, 1.f, 1.f);

	///
	const Color4f  Color4f::Cyan(0, 1.f, 1.f, 1.f);

	///
	const Color4f Color4f::Magenta(1.f, 0, 1.f, 1.f);

	///
	const Color4f  Color4f::Yellow(1.f, 1.f, 0, 1.f);
}
#endif