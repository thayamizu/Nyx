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

namespace nyx
{
	template <typename T>
	class color4 {
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
		static const color4<T> WHITE;

		///
		static const color4<T> GRAY;

		///
		static const color4<T> BLACK;

		///
		static const color4<T> RED;

		///
		static const color4<T> GREEN;

		///
		static const color4<T> BLUE;

		///
		static const color4<T> CYAN;

		///
		static const color4<T> MAGENTA;

		///
		static const color4<T> YELLOW;

		/**
		*
		*/
		color4<T>() {
			set(0, 0, 0, 0);
		}


		/**
		*
		*/
		color4<T>(const T red, const T green, const T blue, const T alpha) {
			set(red, green, blue, alpha);
		}


		/**
		*
		*/
		color4<T>(const color4<T>& color) {
			set(color.r, color.g, color.b, color.a);
		}


		/**
		*
		*/
		void set(const T red, const T green, const T blue, const T alpha) {
			this->r = red;
			this->g = green;
			this->b = blue;
			this->a = alpha;
			clamp();
		}


		/**
		*
		*/
		void clamp() {
			r = math::clamp<T>(r, 0, 255);
			g = math::clamp<T>(g, 0, 255);
			b = math::clamp<T>(b, 0, 255);
			a = math::clamp<T>(a, 0, 255);
		}


		/**
		*
		*/
		color4<T> operator +(const color4<T>& color) const {
			return color4<T>(r + color.r, g + color.g, b + color.b, a + color.a);
		}


		/**
		*
		*/
		color4<T> operator -(const color4<T>& color) const {
			return color4<T>(r - color.r, g - color.g, b - color.b, a - color.a);
		}


		/**
		*
		*/
		color4<T> operator *(T value) const {
			return color4<T>(r * value, g * value, b * value, a * value);
		}


		/**
		*
		*/
		color4<T> operator /(T value) const {
			return color4<T>(r / value, g / value, b / value, a / value);
		}


		/**
		*
		*/
		color4<T>& operator +=(const color4<T>& color) {
			set(r + color.r, g + color.g, b + color.b, a + color.a);
			return *this;
		}


		/**
		*
		*/
		color4<T>& operator -=(const color4<T>& color) {
			set(r - color.r, g - color.g, b - color.b, a - color.a);
			return *this;
		}


		/**
		*
		*/
		color4<T>& operator *=(T value) {
			set(r * value, g * value, b * value, a * value);
			return *this;
		}


		/**
		*
		*/
		color4<T>& operator /=(T value) {
			set(r / value, g / value, b / value, a / value);
			return *this;
		}


		/**
		*
		*/
		bool operator ==(const color4<T>& color) {
			return (
				math::abs(r - color.r) <= math::EPSILON &&
				math::abs(g - color.g) <= math::EPSILON &&
				math::abs(b - color.b) <= math::EPSILON &&
				math::abs(a - color.a) <= math::EPSILON);
		}


		/**
		*
		*/
		bool operator !=(const color4<T>& color) {
			return !(*this == color);
		}
	};

	//--------------------------------------------------------------------------------------
	// �ʖ���`
	//--------------------------------------------------------------------------------------
	typedef color4<uint8_t> color4c;
	typedef color4<float>   color4f;

	//--------------------------------------------------------------------------------------
	// ���ꉻ
	//--------------------------------------------------------------------------------------
	template<>
	void color4f::clamp() {
		r = math::clamp<float>(r, 0.f, 1.f); 
		g = math::clamp<float>(g, 0.f, 1.f); 
		b = math::clamp<float>(b, 0.f, 1.f); 
		a = math::clamp<float>(a, 0.f, 1.f); 
	}


	//--------------------------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------------------------
	template <typename T>
	const color4<T> color4<T>::WHITE(255 , 255, 255, 255);

	///
	template <typename T>
	const color4<T> color4<T>::GRAY(128, 128, 128, 255);

	///
	template <typename T>
	const color4<T> color4<T>::BLACK(0, 0, 0, 255);

	///
	template <typename T>
	const color4<T> color4<T>::RED(255, 0, 0, 255);

	///
	template <typename T>
	const color4<T> color4<T>::GREEN(0, 255, 0, 255);

	///
	template <typename T>
	const color4<T> color4<T>::BLUE(0, 0, 255, 255);

	///
	template <typename T>
	const color4<T> color4<T>::CYAN(0, 255, 255, 255);

	///
	template <typename T>
	const color4<T> color4<T>::MAGENTA(255, 0, 255, 255);

	///
	template <typename T>
	const color4<T> color4<T>::YELLOW(255, 255, 0, 255);

	///
	const color4f color4f::WHITE(1.f, 1.f, 1.f, 1.f);

	///
	const color4f  color4f::GRAY(0.5f, 0.5f, 0.5f, 1.f);

	///
	const color4f  color4f::BLACK(0.f, 0.f, 0.f, 1.f);

	///
	const color4f  color4f::RED(1.f, 0.f, 0.f, 1.f);

	///
	const color4f  color4f::GREEN(0, 1.f, 0, 1.f);

	///
	const color4f  color4f::BLUE(0, 0, 1.f, 1.f);

	///
	const color4f  color4f::CYAN(0, 1.f, 1.f, 1.f);

	///
	const color4f color4f::MAGENTA(1.f, 0, 1.f, 1.f);

	///
	const color4f  color4f::YELLOW(1.f, 1.f, 0, 1.f);
}
#endif