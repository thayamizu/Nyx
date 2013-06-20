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
				/// x�l
				T  x;
				/// y�l
				T  y;
				/// z�l
				T z;
				/// w
				T w;
			};
			/// �z��
			T elements[4];
		};

		static const Vector4<T> Zero;  ///< �[���x�N�g��

		static const Vector4<T> UnitX; ///< X���P�ʃx�N�g��

		static const Vector4<T> UnitY; ///< Y���P�ʃx�N�g��

		static const Vector4<T> UnitZ; ///< Z���P�ʃx�N�g��

		static const Vector4<T> UnitW; ///< W���P�ʃx�N�g��

		static const Vector4<T> ScaleUnit; ///< �X�P�[���P�ʃx�N�g�� 


		/**
		*�f�t�H���g�R���X�g���N�^
		*/
		Vector4<T>()
			:x(0), y(0), z(0), w(0){
		}


		/**
		* �������R���X�g���N�^
		* @param x
		* @param y
		* @param z
		*/
		Vector4<T>(T x_, T y_, T z_, T w_) 
			: x(x_), y(y_), z(z_), w(w_) {
		}


		/**
		* �R�s�[�R���X�g���N�^
		* @param Vector4<T>
		*/
		Vector4<T>(const Vector4<T> & u)
			: x(u.x), y(u.y), z(u.z) ,w(u.w){
		}


		/**
		* �l�̐ݒ�
		*/
		void Set(T x_, T y_, T z_, T w_) {
			x = x_;
			y = y_;
			z = z_;
			w = w_;
		}


		/**
		* ���Z
		* @param �E�Ӓl  
		* @return�@���Z���� 
		*/
		Vector4<T> operator +(const Vector4<T>& u) const {
			return Vector4<T>( x + u.x, y + u.y, z + u.z, w + u.w); 
		}


		/**
		* ���Z
		* @param�@�E�Ӓl  
		* @return ���Z����
		*/
		Vector4<T> operator -(const Vector4<T>& u) const {
			return Vector4<T>( x - u.x, y - u.y, z - u.z, w - u.w); 
		}


		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Vector4<T> operator *(const T u) const {
			return Vector4<T>( x * u, y * u, z * u, w * u);
		}


		/**
		* ���Z
		* @param �E�Ӓl  
		* @return ���Z����
		*/
		Vector4<T> operator /(const T u) const {
			return Vector4<T>( x / u, y / u, z / u, w / u);

		}


		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		Vector4<T>& operator +=(const Vector4<T>& u) {
			x += u.x;
			y += u.y;
			z += u.z;
			w += u.w;
			return *this;
		}


		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		Vector4<T>& operator -=(const Vector4<T>& u) {
			x -= u.x;
			y -= u.y;
			z -= u.z;
			w -= u.w;

			return *this;
		}


		/**
		* ��Z���
		* @param  �E�Ӓl
		* @return ��Z����
		*/
		Vector4<T>& operator *=(const T u) {
			x *= u;
			y *= u;
			z *= u;
			w *= u;

			return *this;
		}


		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		Vector4<T>& operator /=(const T u) {
			x /= u;
			y /= u;
			z /= u;
			w /= u;
			return *this;
		}


		/**
		* ���
		* @param �E�Ӓl
		* @return �������
		*/
		Vector4<T>& operator =(Vector4<T>& u) {
			x = u.x;
			y = u.y;
			z = u.z;
			w = u.w;
			return *this;
		}


		/**
		* ���] 
		* @param ���]����
		*/
		Vector4<T>& operator ~() {
			x = - x;
			y = - y;
			z = - z;
			w = - w;
			return *this;
		}


		/**
		* �h�b�g��
		* @param �E�Ӓl
		* @return ����
		*/
		T Dot(Vector4<T>& u) {
			return (x * u.x + y * u.y + z * u.z + w*u.w);
		}


		/**
		* �x�N�g���̒���
		* @return  ����
		*/
		float Length() {
			return Math::Sqrt(x * x + y * y + z * z+ w * w);
		}


		/**
		* �x�N�g���̒����̓��l
		* @return  ����
		*/
		float SquaredLength() {
			return static_cast<float>(x * x + y * y + z * z + w * w);

		}


		/**
		* �x�N�g���̐��K��
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
		* �x�N�g���̔��]
		*/
		void Inverse() {
			x = - x;
			y = - y;
			z = - z;
			w = - w;
		}

		/**
		* ���`���
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
		* @return �[���x�N�g���Ȃ�true
		*/
		bool IsZero() const {
			return (
				Math::Abs(x) <= Math::Epsilon &&
				Math::Abs(y) <= Math::Epsilon &&
				Math::Abs(z) <= Math::Epsilon &&
				Math::Abs(w) <= Math::Epsilon);
		}


		/** 
		* @return �P�ʃx�N�g���Ȃ�true
		*/
		bool IsUnit() const {
			const float value = Math::Sqrt(x*x + y*y + z*z + w*w);
			return (Math::Abs(value - 1.f) <= Math::Epsilon);
		}


		/** 
		* �x�N�g���̓������Z
		* @param �E�Ӓl 
		* @return ��r���ʂ��������Ȃ��true
		*/
		bool operator==(const Vector4<T>& u) const {
			return (
				Math::Abs(x - u.x) <= Math::Epsilon &&
				Math::Abs(y - u.y) <= Math::Epsilon &&
				Math::Abs(z - u.z) <= Math::Epsilon &&
				Math::Abs(w - u.w) <= Math::Epsilon);
		}


		/** 
		* �x�N�g���������Z
		* @param �E�Ӓl 
		* @return�@��r���ʂ��������Ȃ��Ȃ��true
		*/
		bool operator !=(const Vector4<T>& u) const {
			return !(*this == u);
		}
	};
	//--------------------------------------------------------------------------------------
	// �ʖ���`
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
	// �萔��`
	//--------------------------------------------------------------------------------------
	// �[���x�N�g��
	template<typename T>
	const Vector4<T> Vector4<T>::Zero = Vector4(0, 0, 0, 0);  

	// X���P�ʃx�N�g��
	template<typename T>
	const Vector4<T> Vector4<T>::UnitX = Vector4(1, 0, 0, 0);

	// Y���P�ʃx�N�g��
	template<typename T>
	const Vector4<T> Vector4<T>::UnitY = Vector4(0, 1, 0, 0); 

	// Z���x�N�g��
	template<typename T>
	const Vector4<T> Vector4<T>::UnitZ = Vector4(0, 0, 1, 0); 
	
	// W���x�N�g��
	template<typename T>
	const Vector4<T> Vector4<T>::UnitW = Vector4(0, 0, 0, 1); 
	
	// �X�P�[���P�ʃx�N�g��
	template<typename T>
	const Vector4<T> Vector4<T>::ScaleUnit = Vector4(1, 1, 1, 1);
}


#endif