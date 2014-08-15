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

namespace nyx
{
	template <typename T>
	class color4 {
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
	// 別名定義
	//--------------------------------------------------------------------------------------
	typedef color4<uint8_t> color4c;
	typedef color4<float>   color4f;

	//--------------------------------------------------------------------------------------
	// 特殊化
	//--------------------------------------------------------------------------------------
	template<>
	void color4f::clamp() {
		r = math::clamp<float>(r, 0.f, 1.f); 
		g = math::clamp<float>(g, 0.f, 1.f); 
		b = math::clamp<float>(b, 0.f, 1.f); 
		a = math::clamp<float>(a, 0.f, 1.f); 
	}


	//--------------------------------------------------------------------------------------
	// 定数定義
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