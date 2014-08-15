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
#ifndef NYX_CORE_INCLUDED_RECT2i_H_
#define NYX_CORE_INCLUDED_RECT2i_H_
#include "Primitive/Vector2.h"

namespace nyx
{
	template <typename T>
	class rectangle{
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic type.");
	public:
		union {
			struct {
				///
				T x;
				///
				T y;
				///
				T width;
				///
				T height;

			};
			T element[4];
		};


		static const rectangle<T> ZERO;
		
		static const rectangle<T> UNIT;


		/**
		* コンストラクタ
		*/
		rectangle<T>() {
			set(0, 0, 0, 0);
		}


		/**
		* コンストラクタ
		* @param T x
		* @param T y
		* @param T width
		* @param T height
		*/
		rectangle<T>(const T x, const T y, const T width, const T height) {
			set(x, y, width, height);
		}


		/**
		* コピーコンストラクタ
		*/
		rectangle<T>(const rectangle<T>& rect ) {
			set(rect.x, rect.y, rect.width, rect.height);
		}


		/**
		* 値のセット
		*/
		void set(const T x, const T y, const T width, const T height) {
			this->x      = x;
			this->y      = y;
			this->width  = width;
			this->height = height;
		}


		/**
		* 指定した点が矩形に包含されているか
		* @param const Point2<T> 点
		*/
		bool contain(const vector2<T>& point) const {
			const T right  = x + width;
			const T bottom = y + height;

			if ((x  <= point.x) && (point.x <= right) &&
				(y  <= point.y) && (point.y <= bottom)) {
					return true;
			}
			return false;
		}


		/**
		* 等価演算
		* @param const Rect<T>& rect
		*/
		bool operator ==(const rectangle<T>& rect) const {
			return (
				x      == rect.x     &&
				y      == rect.y     &&
				width  == rect.width &&
				height == rect.height);
		}


		/**
		* 等価演算
		* @param const Rect<T>& rect
		*/
		bool operator !=(const rectangle<T>& rect) const {
			return !(*this == rect);
		}
	};
	//--------------------------------------------------------------------------------------
	// 別名定義
	//--------------------------------------------------------------------------------------
	typedef rectangle<int>     rect2i;
	typedef rectangle<float>   rect2f;
	typedef rectangle<double>  rect2d;

	//--------------------------------------------------------------------------------------
	// 定数定義
	//--------------------------------------------------------------------------------------
	template <typename T>
	const rectangle<T> rectangle<T>::ZERO = rectangle<T>(0, 0, 0, 0);
	
	template <typename T>
	const rectangle<T> rectangle<T>::UNIT = rectangle<T>(1, 1, 1, 1);
} 
#endif