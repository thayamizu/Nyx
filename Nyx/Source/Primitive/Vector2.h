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
#ifndef NYX_CORE_INCLUDED_VECTOR2_H_
#define NYX_CORE_INCLUDED_VECTOR2_H_


namespace Nyx
{
	template<typename T>
	class Vector2 {
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic type.");
	public:
		union {
			struct {
				T x; ///< X成分
				T y; ///< Y成分
			};

			T elements[2];
		};

		static const Vector2<T> Zero;  ///< ゼロベクトル

		static const Vector2<T> UnitX; ///< X軸単位ベクトル

		static const Vector2<T> UnitY; ///< Y軸単位ベクトル

		static const Vector2<T> ScaleUnit; ///< スケール単位ベクトル


		/**
		* デフォルトコンストラクタ
		*/
		Vector2<T>() 
			: x(0), y(0) {
		}

		/**
		* コンストラクタ
		* @param x
		* @param y
		*/
		Vector2<T>(T x, T y) {
			Set(x, y);
		}

		/**
		* コピーコンストラクタ
		* @param Vector2
		*/
		Vector2<T>(const Vector2 & u) 
			:x(u.x), y(u.y) {

		}

		/**
		* 値の設定
		*/
		void Set(T x, T y) {
			this->x = x;
			this->y = y;
		}

		/** 
		* ベクトル加算
		* @param 右辺値 
		* @return 加算結果
		*/
		Vector2<T> operator +(const Vector2<T>& u) const {
			return Vector2( x + u.x, y + u.y); 
		}

		/** 
		* ベクトル減算
		* @param 右辺値 
		* @return 減算結果
		*/ 
		Vector2<T> operator -(const Vector2<T>& u) const {
			return Vector2( x - u.x, y - u.y); 
		}

		/** 
		* ベクトル乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Vector2<T> operator *(const T u) const {
			return Vector2( x * u, y * u); 
		}

		/** 
		* ベクトル除算
		* @param 右辺値 
		* @return 除算結果
		*/
		Vector2<T> operator /(const T u) const {
			return Vector2( x / u, y / u); 
		}

		/** 
		* ベクトル加算
		* @param 右辺値 
		* @return 加算結果
		*/
		Vector2<T> & operator +=(const Vector2<T>& u) {
			x += u.x;
			y += u.y;

			return *this;
		}
		/** 
		* ベクトル減算
		* @param 右辺値 
		* @return 減算結果
		*/                                                                             
		Vector2<T> & operator -=(const Vector2<T>& u) {
			x -= u.x;
			y -= u.y;

			return *this;
		}

		/** 
		* ベクトル乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Vector2<T> &  operator *=(const T u) {
			x *= u;
			y *= u;

			return *this;
		}

		/** 
		* ベクトル除算
		* @param 右辺値 
		* @return 除算結果
		*/
		Vector2<T> & operator /=(const T u) {
			x /= u;
			y /= u;

			return *this;
		}

		/** 
		* ベクトル反転
		* @param 右辺値 
		* @return 反転されたベクトル
		*/
		Vector2<T> operator ~() {
		}

		/** 
		* ベクトル代入
		* @param 右辺値 
		* @return 代入されたベクトル
		*/
		Vector2<T>& operator =(const Vector2<T> &u) {
			x = u.x;
			y = u.y;

			return *this;
		}


		/**
		* ドット積（内積）
		* @param 右辺値
		* @return 内積
		*/
		T Dot(const Vector2& u) {
			return (x * u.x + y * u.y);

		}

		/**
		* ベクトルの長さ
		* @return ベクトルの長さの平方根
		*/
		float Length() {
			return static_cast<float>(sqrt(x * x + y * y ));

		}

		/**
		* ベクトルの長さの平方根
		* @return ベクトルの長さの平方根
		*/
		float SquaredLength() {
			return static_cast<float>(x * x + y * y );
		}

		/**
		* ベクトルを正規化
		*/
		void Normalize() {
			float abs = Length();

			if (abs <= Math::Epsilon) { abs = 1.0;}

			x /= abs;
			y /= abs;

			if (Math::Abs(x) < Math::Epsilon) {x = 0.0f;}
			if (Math::Abs(y) < Math::Epsilon) {y = 0.0f;}
		}

		/**
		* ベクトルを反転
		*/
		void Inverse() {
			x = - x;
			y = - y;
		}

		/**
		*
		*/
		Vector2<T> Lerp(const Vector2<T>& v1, const Vector2<T>& v2, float s) {
			Vector2 lerp;
			if (s > 1) s = 1;
			if (s < 0) s = 0;
			lerp.x = v1.x * (1 - s) + v2.x * s;
			lerp.y = v1.y * (1 - s) + v2.y * s;

			return lerp;
		}


		/** 
		* @return ゼロベクトルならtrue
		*/
		bool IsZero() const {
			return (
				Math::Abs(x) <= Math::Epsilon &&
				Math::Abs(y) <= Math::Epsilon);
		}


		/** 
		* @return 単位ベクトルならtrue
		*/
		bool IsUnit() const {
			const float value = Math::Sqrt(x*x + y*y);
			return (Math::Abs(value - 1.f) <= Math::Epsilon);
		}


		/** 
		* ベクトルの等価演算
		* @param 右辺値 
		* @return 比較結果が等しいならばtrue
		*/
		bool operator ==(const Vector2<T>& v) const {
			return ( 
				Math::Abs(x - v.x ) < Math::Epsilon &&
				Math::Abs(y - v.y ) < Math::Epsilon);
		}


		/** 
		* ベクトル等価演算
		* @param 右辺値 
		* @return　比較結果が等しくないならばtrue
		*/
		bool operator !=(const Vector2<T>& rhs) const {
			return !(*this == rhs);
		}
	};

	//--------------------------------------------------------------------------------------
	// 別名定義
	//--------------------------------------------------------------------------------------
	typedef Vector2<int>     Axis2i;
	typedef Vector2<int>     Point2i;
	typedef Vector2<int>     Vector2i;
	typedef Vector2<int>     TexChoord2i;
	typedef Vector2<float>   Axis2f;
	typedef Vector2<float>   Point2f;
	typedef Vector2<float>   Vector2f;
	typedef Vector2<float>   TexChoord2f;
	typedef Vector2<double>  Axis2d;
	typedef Vector2<double>  Point2d;
	typedef Vector2<double>  Vector2d;
	typedef Vector2<double>  TexChoord2d;

	//--------------------------------------------------------------------------------------
	// 定数定義
	//-------------------------------------------------------------------------------------- 
	template<typename T>
	const Vector2<T> Vector2<T>::Zero = Vector2(0, 0);

	template<typename T>
	const Vector2<T> Vector2<T>::UnitX = Vector2(1, 0);

	template<typename T>
	const Vector2<T> Vector2<T>::UnitY = Vector2(0, 1);

	template<typename T>
	const Vector2<T> Vector2<T>::ScaleUnit = Vector2(1, 1);
}
#endif
//VECTOR_H
