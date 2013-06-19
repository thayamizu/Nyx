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
#ifndef NYX_CORE_INCLUDED_VECTOR3_H_
#define NYX_CORE_INCLUDED_VECTOR3_H_

namespace Nyx
{
	template<typename T>
	class Vector3 {
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
			};
			/// 配列
			T elements[3];
		};

		static const Vector3<T> Zero;  ///< ゼロベクトル

		static const Vector3<T> UnitX; ///< X軸単位ベクトル

		static const Vector3<T> UnitY; ///< Y軸単位ベクトル

		static const Vector3<T> UnitZ; ///< Z軸単位ベクトル

		static const Vector3<T> ScaleUnit; ///< スケール単位ベクトル 

		/**
		*デフォルトコンストラクタ
		*/
		Vector3<T>() {
			Set(0, 0, 0);
		}

		/**
		* 引数つきコンストラクタ
		* @param x
		* @param y
		* @param z
		*/
		Vector3<T>(T x, T y, T z) {
			Set(x, y, z);
		}

		/**
		* コピーコンストラクタ
		* @param Vector3<T>
		*/
		Vector3<T>(const Vector3<T> & u) {
			Set(u.x, u.y, u.z);
		}

		/**
		* 値の設定
		*/
		void Set(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
		* 加算
		* @param 右辺値  
		* @return　加算結果 
		*/
		Vector3<T> operator +(const Vector3<T>& u) const {
			return Vector3<T>( x + u.x, y + u.y, z + u.z); 

		}

		/**
		* 減算
		* @param　右辺値  
		* @return 減算結果
		*/
		Vector3<T> operator -(const Vector3<T>& u) const {
			return Vector3<T>( x - u.x, y - u.y, z - u.z); 

		}

		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		Vector3<T> operator *(const T u) const {
			return Vector3<T>( x * u, y * u, z * u);

		}

		/**
		* 除算
		* @param 右辺値  
		* @return 除算結果
		*/
		Vector3<T> operator /(const T u) const {
			return Vector3<T>( x / u, y / u, z / u);
		}

		/**
		* 加算代入
		* @param  右辺値
		* @return 加算結果
		*/
		Vector3<T>& operator +=(const Vector3<T>& u) {
			x += u.x;
			y += u.y;
			z += u.z;
			return *this;
		}

		/**
		* 減算代入
		* @param  右辺値
		* @return 減算結果
		*/
		Vector3<T>& operator -=(const Vector3<T>& u) {
			x -= u.x;
			y -= u.y;
			z -= u.z;
			return *this;
		}

		/**
		* 乗算代入
		* @param  右辺値
		* @return 乗算結果
		*/
		Vector3<T>& operator *=(const T u) {
			x *= u;
			y *= u;
			z *= u;
			return *this;
		}

		/**
		* 除算代入
		* @param  右辺値
		* @return 除算結果
		*/
		Vector3<T>& operator /=(const T u) {
			Assert(u != 0);
			x /= u;
			y /= u;
			z /= u;
			return *this;
		}

		/**
		* 代入
		* @param 右辺値
		* @return 代入結果
		*/
		Vector3<T>& operator =(Vector3<T>& u) {
			using std::swap;
			swap(*this, u);
			return u;
		}

		/**
		* 反転 
		* @param 反転結果
		*/
		Vector3<T>& operator ~() {
			Inverse();
			return *this;
		}

		/**
		* ドット積
		* @param 右辺値
		* @return T 内積
		*/
		T Dot(Vector3<T>& u) {
			return (x * u.x + y * u.y + z * u.z);
		}

		/**
		* クロス積
		* @param   右辺値
		* @return　Vector3<T> クロス積 
		*/
		Vector3<T> Cross(Vector3<T>& u) {
			return Vector3<T>(
				(y * u.z - z * u.y ),
				(x * u.z - z * u.x ),
				(x * u.y - y * u.x ));
		}

		/**
		* ベクトルの長さ
		* @return  T 長さ
		*/
		T Length() {
			return static_cast<T>(sqrt(x * x + y * y + z * z));

		}

		/**
		* ベクトルの長さの二乗値
		* @return  T 長さ
		*/
		T SquaredLength() {
			return static_cast<T>(x * x + y * y + z * z);

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

			if (Math::Abs(x) < Math::Epsilon) {x = 0.f;}
			if (Math::Abs(y) < Math::Epsilon) {y = 0.f;}
			if (Math::Abs(z) < Math::Epsilon) {z = 0.f;}
		}

		/**
		* ベクトルの反転
		*/
		void Inverse() {
			x = - x;
			y = - y;
			z = - z;
		}

		/**
		* 線形補間
		* @param const Vector3<T>& 始点ベクトル
		* @param const Vector3<T>& 終点ベクトル
		* @param T 補間係数
		*/
		Vector3<T> Lerp(const Vector3<T>& v1, const Vector3<T>& v2, T s) {
			Vector3<T> lerp;
			if (s > 1) s = 1;
			if (s < 0) s = 0;
			lerp.x = v1.x * (1 - s) + v2.x * s;
			lerp.y = v1.y * (1 - s) + v2.y * s;
			lerp.z = v1.z * (1 - s) + v2.z * s;

			return lerp;	
		}

		/** 
		* @return ゼロベクトルならtrue
		*/
		bool IsZero() const {
			return (
				Math::Abs(x) <= Math::Epsilon &&
				Math::Abs(y) <= Math::Epsilon &&
				Math::Abs(z) <= Math::Epsilon);
		}

		/** 
		* @return 単位ベクトルならtrue
		*/
		bool IsUnit() const {
			return (
				Math::Abs(x - 1.f) <= Math::Epsilon &&
				Math::Abs(y - 1.f) <= Math::Epsilon &&
				Math::Abs(z - 1.f) <= Math::Epsilon);
		}

		/** 
		* ベクトルの等価演算
		* @param 右辺値 
		* @return 比較結果が等しいならばtrue
		*/
		bool operator ==(const Vector3<T>& u) const {	
			return (
			Math::Abs(x - u.x) <= Math::Epsilon &&
			Math::Abs(y - u.y) <= Math::Epsilon &&
			Math::Abs(z - u.z) <= Math::Epsilon);
		}

		/** 
		* ベクトル等価演算
		* @param 右辺値 
		* @return　比較結果が等しくないならばtrue
		*/
		bool operator !=(const Vector3<T>& u) const {
			return !(*this == u);
		}
	};
	//--------------------------------------------------------------------------------------
	// 定数定義
	//--------------------------------------------------------------------------------------
	typedef Vector3<int>     Axis3i;
	typedef Vector3<float>   Axis3f;
	typedef Vector3<double>  Axis3d;
	typedef Vector3<int>     Point3i;
	typedef Vector3<float>   Point3f;
	typedef Vector3<double>  Point3d;
	typedef Vector3<int>     Vector3i;
	typedef Vector3<float>   Vector3f;
	typedef Vector3<double>  Vector3d;
	typedef Vector3<int>     TexChoord3i;
	typedef Vector3<float>   TexChoord3f;
	typedef Vector3<double>  TexChoord3d;

	//--------------------------------------------------------------------------------------
	// 定数定義
	//--------------------------------------------------------------------------------------
	// ゼロベクトル   
	template<typename T>
	const Vector3<T> Vector3<T>::Zero = Vector3<T>(0, 0, 0);  

	// X軸単位ベクトル
	template<typename T>
	const Vector3<T> Vector3<T>::UnitX = Vector3<T>(1, 0, 0);

	// Y軸単位ベクトル
	template<typename T>
	const Vector3<T> Vector3<T>::UnitY = Vector3<T>(0, 1, 0); 

	// Z軸ベクトル
	template<typename T>
	const Vector3<T> Vector3<T>::UnitZ = Vector3<T>(0, 0, 1); 

	// スケール単位ベクトル
	template<typename T>
	const Vector3<T> Vector3<T>::ScaleUnit = Vector3<T>(1, 1, 1);

}


#endif