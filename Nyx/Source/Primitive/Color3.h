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
			};

			T elements[3];
		} ;
		//--------------------------------------------------------------------------------------
		// 定数
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
		// コンストラクタ
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
		// 演算
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
		// 代入演算
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
		// 論理演算
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
	// 別名定義
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
	// 定数定義
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