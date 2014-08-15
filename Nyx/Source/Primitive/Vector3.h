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

namespace nyx
{
	template<typename T>
	class vector3 {
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

		static const vector3<T> ZERO;  ///< ゼロベクトル

		static const vector3<T> UNIT_X; ///< X軸単位ベクトル

		static const vector3<T> UNIT_Y; ///< Y軸単位ベクトル

		static const vector3<T> UNIT_Z; ///< Z軸単位ベクトル

		static const vector3<T> SCALE_UNIT; ///< スケール単位ベクトル 
	

		/**
		*デフォルトコンストラクタ
		*/
		vector3<T>() {
			set(0, 0, 0);
		}


		/**
		* 引数つきコンストラクタ
		* @param x
		* @param y
		* @param z
		*/
		vector3<T>(T x, T y, T z) {
			set(x, y, z);
		}


		/**
		* コピーコンストラクタ
		* @param Vector3<T>
		*/
		vector3<T>(const vector3<T> & u) {
			set(u.x, u.y, u.z);
		}


		/**
		* 値の設定
		*/
		void set(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}


		/**
		* 加算
		* @param 右辺値  
		* @return　加算結果 
		*/
		vector3<T> operator +(const vector3<T>& u) const {
			return vector3<T>( x + u.x, y + u.y, z + u.z); 

		}


		/**
		* 減算
		* @param　右辺値  
		* @return 減算結果
		*/
		vector3<T> operator -(const vector3<T>& u) const {
			return vector3<T>( x - u.x, y - u.y, z - u.z); 

		}


		/**
		* 乗算
		* @param 右辺値 
		* @return 乗算結果
		*/
		vector3<T> operator *(const T u) const {
			return vector3<T>( x * u, y * u, z * u);

		}


		/**
		* 除算
		* @param 右辺値  
		* @return 除算結果
		*/
		vector3<T> operator /(const T u) const {
			if (u <= math::EPSILON) {
				return *this;
			}
			return vector3<T>( x / u, y / u, z / u);
		}


		/**
		* 加算代入
		* @param  右辺値
		* @return 加算結果
		*/
		vector3<T>& operator +=(const vector3<T>& u) {
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
		vector3<T>& operator -=(const vector3<T>& u) {
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
		vector3<T>& operator *=(const T u) {
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
		vector3<T>& operator /=(const T u) {
			NYX_ASSERT(u != 0);
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
		vector3<T>& operator =(vector3<T>& u) {
			using std::swap;
			swap(*this, u);
			return u;
		}


		/**
		* 反転 
		* @param 反転結果
		*/
		vector3<T>& operator ~() {
			Inverse();
			return *this;
		}


		/**
		* ドット積
		* @param 右辺値
		* @return T 内積
		*/
		T dot(vector3<T>& u) {
			return (x * u.x + y * u.y + z * u.z);
		}


		/**
		* クロス積
		* @param   右辺値
		* @return　Vector3<T> クロス積 
		*/
		vector3<T> cross(vector3<T>& u) {
			return vector3<T>(
				(y * u.z - z * u.y ),
				(x * u.z - z * u.x ),
				(x * u.y - y * u.x ));
		}


		/**
		* ベクトルの長さ
		* @return  T 長さ
		*/
		float norm() {
			return static_cast<float>(sqrt(x * x + y * y + z * z));

		}


		/**
		* ベクトルの長さの二乗値
		* @return  T 長さ
		*/
		float squared_norm() {
			return static_cast<float>(x * x + y * y + z * z);

		}


		/**
		* ベクトルの正規化
		*/
		void normalize() {
			T abs = norm(); 

			if (abs <= math::EPSILON) { abs = 1.f;}

			x /= abs;
			y /= abs;
			z /= abs;

			if (math::abs(x) < math::EPSILON) {x = 0.f;}
			if (math::abs(y) < math::EPSILON) {y = 0.f;}
			if (math::abs(z) < math::EPSILON) {z = 0.f;}
		}


		/**
		* ベクトルの反転
		*/
		void inverse() {
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
		vector3<T> lerp(const vector3<T>& v1, const vector3<T>& v2, float s) {
			vector3<T> lerp;
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
		bool is_zero() const {
			return (
				math::abs(x) <= math::EPSILON &&
				math::abs(y) <= math::EPSILON &&
				math::abs(z) <= math::EPSILON);
		}


		/** 
		* @return 単位ベクトルならtrue
		*/
		bool is_unit() const {
			const auto value = math::sqrt(x*x + y*y +z*z);
			return (math::abs(value - 1.f) <= math::EPSILON);
		}


		/** 
		* ベクトルの等価演算
		* @param 右辺値 
		* @return 比較結果が等しいならばtrue
		*/
		bool operator ==(const vector3<T>& u) const {	
			return (
			math::abs(x - u.x) <= math::EPSILON &&
			math::abs(y - u.y) <= math::EPSILON &&
			math::abs(z - u.z) <= math::EPSILON);
		}


		/** 
		* ベクトル等価演算
		* @param 右辺値 
		* @return　比較結果が等しくないならばtrue
		*/
		bool operator !=(const vector3<T>& u) const {
			return !(*this == u);
		}
	};
	//--------------------------------------------------------------------------------------
	// 定数定義
	//--------------------------------------------------------------------------------------
	typedef vector3<int>     axis3i;
	typedef vector3<float>   axis3f;
	typedef vector3<double>  axis3d;
	typedef vector3<int>     point3i;
	typedef vector3<float>   point3f;
	typedef vector3<double>  point3d;
	typedef vector3<int>     vector3i;
	typedef vector3<float>   vector3f;
	typedef vector3<double>  vector3d;
	typedef vector3<int>     tex_choord3i;
	typedef vector3<float>   tex_choord3f;
	typedef vector3<double>  tex_choord3d;


	//--------------------------------------------------------------------------------------
	// 定数定義
	//--------------------------------------------------------------------------------------
	// ゼロベクトル   
	template<typename T>
	const vector3<T> vector3<T>::ZERO = vector3<T>(0, 0, 0);  

	// X軸単位ベクトル
	template<typename T>
	const vector3<T> vector3<T>::UNIT_X = vector3<T>(1, 0, 0);

	// Y軸単位ベクトル
	template<typename T>
	const vector3<T> vector3<T>::UNIT_Y = vector3<T>(0, 1, 0); 

	// Z軸ベクトル
	template<typename T>
	const vector3<T> vector3<T>::UNIT_Z = vector3<T>(0, 0, 1); 

	// スケール単位ベクトル
	template<typename T>
	const vector3<T> vector3<T>::SCALE_UNIT = vector3<T>(1, 1, 1);

}


#endif