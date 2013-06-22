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
#ifndef NYX_CORE_INCLUDED_COLOR4_H_
#define NYX_CORE_INCLUDED_COLOR4_H_

namespace Nyx
{
	template <typename T>
	class Color4 {
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic type");
	public:
		//--------------------------------------------------------------------------------------
		// 変数
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
		// 定数
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
	// 別名定義
	//--------------------------------------------------------------------------------------
	typedef Color4<uchar> Color4c;
	typedef Color4<float> Color4f;

	//--------------------------------------------------------------------------------------
	// 特殊化
	//--------------------------------------------------------------------------------------
	template<>
	void Color4f::Clamp() {
		r = Math::Clamp<float>(r, 0.f, 1.f); 
		g = Math::Clamp<float>(g, 0.f, 1.f); 
		b = Math::Clamp<float>(b, 0.f, 1.f); 
		a = Math::Clamp<float>(a, 0.f, 1.f); 
	}


	//--------------------------------------------------------------------------------------
	// 定数定義
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