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
#ifndef NYX_CORE_INCLUDED_VECTOR4_H_
#define NYX_CORE_INCLUDED_VECTOR4_H_

namespace Nyx
{
	template <typename T>
	class Vector4 {
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic type.");
	public:
		union {
			struct {
				/// x値
				T  x;
				/// y値
				T  y;
				/// z値
				T z;
				/// w
				T w;
			};
			/// 配列
			T elements[4];
		};

		static const Vector4<T> Zero;  ///< ゼロベクトル

		static const Vector4<T> UnitX; ///< X軸単位ベクトル

		static const Vector4<T> UnitY; ///< Y軸単位ベクトル

		static const Vector4<T> UnitZ; ///< Z軸単位ベクトル

		static const Vector4<T> UnitW; ///< W軸単位ベクトル

		static const Vector4<T> ScaleUnit; ///< スケール単位ベクトル 


		/**
		*デフォルトコンストラクタ
		*/
		Vector4<T>()
			:x(0), y(0), z(0), w(0){
		}


		/**
		* 引数つきコンストラクタ
		* @param x
		* @param y
		* @param z
		*/
		Vector4<T>(T x_, T y_, T z_, T w_) 
			: x(x_), y(y_), z(z_), w(w_) {
		}


		/**
		* コピーコンストラクタ
		* @param Vector4<T>
		*/
		Vector4<T>(const Vector4<T> & u)
			: x(u.x), y(u.y), z(u.z) ,w(u.w){
		}


		/**
		* 値の設定
		*/
		void Set(T x_, T y_, T z_, T w_) {
			x = x_;
			y = y_;
			z = z_;
			w = w_;
		}


		/**
		* 加算
		* @param 右辺値  
		* @return　加算結果 
		*/
		Vector4<T> operator +(const Vector4<T>& u) const {
			return Vector4<T>( x + u.x, y + u.y, z + u.z, w + u.w); 
		}


		/**
		* 減算
		* @param　右辺値  
		* @return 減算結果
		*/
		Vector4<T> operator -(const Vector4<T>& u) const {
			return Vector4<T>( x - u.x, y - u.y, z - u.z, w - u.w); 
		}


		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Vector4<T> operator *(const T u) const {
			return Vector4<T>( x * u, y * u, z * u, w * u);
		}


		/**
		* 除算
		* @param 右辺値  
		* @return 除算結果
		*/
		Vector4<T> operator /(const T u) const {
			return Vector4<T>( x / u, y / u, z / u, w / u);

		}


		/**
		* 加算代入
		* @param  右辺値
		* @return 加算結果
		*/
		Vector4<T>& operator +=(const Vector4<T>& u) {
			x += u.x;
			y += u.y;
			z += u.z;
			w += u.w;
			return *this;
		}


		/**
		* 減算代入
		* @param  右辺値
		* @return 減算結果
		*/
		Vector4<T>& operator -=(const Vector4<T>& u) {
			x -= u.x;
			y -= u.y;
			z -= u.z;
			w -= u.w;

			return *this;
		}


		/**
		* 乗算代入
		* @param  右辺値
		* @return 乗算結果
		*/
		Vector4<T>& operator *=(const T u) {
			x *= u;
			y *= u;
			z *= u;
			w *= u;

			return *this;
		}


		/**
		* 除算代入
		* @param  右辺値
		* @return 除算結果
		*/
		Vector4<T>& operator /=(const T u) {
			x /= u;
			y /= u;
			z /= u;
			w /= u;
			return *this;
		}


		/**
		* 代入
		* @param 右辺値
		* @return 代入結果
		*/
		Vector4<T>& operator =(Vector4<T>& u) {
			x = u.x;
			y = u.y;
			z = u.z;
			w = u.w;
			return *this;
		}


		/**
		* 反転 
		* @param 反転結果
		*/
		Vector4<T>& operator ~() {
			x = - x;
			y = - y;
			z = - z;
			w = - w;
			return *this;
		}


		/**
		* ドット積
		* @param 右辺値
		* @return 内積
		*/
		T Dot(Vector4<T>& u) {
			return (x * u.x + y * u.y + z * u.z + w*u.w);
		}


		/**
		* ベクトルの長さ
		* @return  長さ
		*/
		float Length() {
			return Math::Sqrt(x * x + y * y + z * z+ w * w);
		}


		/**
		* ベクトルの長さの二乗値
		* @return  長さ
		*/
		float SquaredLength() {
			return static_cast<float>(x * x + y * y + z * z + w * w);

		}


		/**
		* ベクトルの正規化
		*/
		void Normalize() {
			T abs = Length(); 

			if (abs <= Math::Epsilon) { abs = 1.f;}

			x /= abs;
			y /= abs;
			z /= abs;
			w /= abs;

			if (Math::Abs(x) < Math::Epsilon) {x = 0.f;}
			if (Math::Abs(y) < Math::Epsilon) {y = 0.f;}
			if (Math::Abs(z) < Math::Epsilon) {z = 0.f;}
			if (Math::Abs(w) < Math::Epsilon) {w = 0.f;}
		}


		/**
		* ベクトルの反転
		*/
		void Inverse() {
			x = - x;
			y = - y;
			z = - z;
			w = - w;
		}

		/**
		* 線形補間
		*/
		Vector4<T> Lerp(const Vector4<T>& v1, const Vector4<T>& v2, T s) {
			Vector4<T> lerp;
			if (s > 1) s = 1;
			if (s < 0) s = 0;
			lerp.x = v1.x * (1 - s) + v2.x * s;
			lerp.y = v1.y * (1 - s) + v2.y * s;
			lerp.z = v1.z * (1 - s) + v2.z * s;
			lerp.w = v1.w * (1 - s) + v2.w * s;


			return lerp;	
		}
		
		
		/** 
		* @return ゼロベクトルならtrue
		*/
		bool IsZero() const {
			return (
				Math::Abs(x) <= Math::Epsilon &&
				Math::Abs(y) <= Math::Epsilon &&
				Math::Abs(z) <= Math::Epsilon &&
				Math::Abs(w) <= Math::Epsilon);
		}


		/** 
		* @return 単位ベクトルならtrue
		*/
		bool IsUnit() const {
			const float value = Math::Sqrt(x*x + y*y + z*z + w*w);
			return (Math::Abs(value - 1.f) <= Math::Epsilon);
		}


		/** 
		* ベクトルの等価演算
		* @param 右辺値 
		* @return 比較結果が等しいならばtrue
		*/
		bool operator==(const Vector4<T>& u) const {
			return (
				Math::Abs(x - u.x) <= Math::Epsilon &&
				Math::Abs(y - u.y) <= Math::Epsilon &&
				Math::Abs(z - u.z) <= Math::Epsilon &&
				Math::Abs(w - u.w) <= Math::Epsilon);
		}


		/** 
		* ベクトル等価演算
		* @param 右辺値 
		* @return　比較結果が等しくないならばtrue
		*/
		bool operator !=(const Vector4<T>& u) const {
			return !(*this == u);
		}
	};
	//--------------------------------------------------------------------------------------
	// 別名定義
	//--------------------------------------------------------------------------------------
	typedef Vector4<int>     Axis4i;
	typedef Vector4<int>     Point4i;
	typedef Vector4<int>     Vector4i;
	typedef Vector4<int>     TexChoord4i;
	typedef Vector4<float>   Axis4f;
	typedef Vector4<float>   Point4f;
	typedef Vector4<float>   Vector4f;
	typedef Vector4<float>   TexChoord4f;
	typedef Vector4<double>  Axis4d;
	typedef Vector4<double>  Point4d;
	typedef Vector4<double>  Vector4d;
	typedef Vector4<double>  TexChoord4d;

	//--------------------------------------------------------------------------------------
	// 定数定義
	//--------------------------------------------------------------------------------------
	// ゼロベクトル
	template<typename T>
	const Vector4<T> Vector4<T>::Zero = Vector4(0, 0, 0, 0);  

	// X軸単位ベクトル
	template<typename T>
	const Vector4<T> Vector4<T>::UnitX = Vector4(1, 0, 0, 0);

	// Y軸単位ベクトル
	template<typename T>
	const Vector4<T> Vector4<T>::UnitY = Vector4(0, 1, 0, 0); 

	// Z軸ベクトル
	template<typename T>
	const Vector4<T> Vector4<T>::UnitZ = Vector4(0, 0, 1, 0); 
	
	// W軸ベクトル
	template<typename T>
	const Vector4<T> Vector4<T>::UnitW = Vector4(0, 0, 0, 1); 
	
	// スケール単位ベクトル
	template<typename T>
	const Vector4<T> Vector4<T>::ScaleUnit = Vector4(1, 1, 1, 1);
}


#endif