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
				/// x�l
				T  x;
				/// y�l
				T  y;
				/// z�l
				T z;
			};
			/// �z��
			T elements[3];
		};

		static const Vector3<T> Zero;  ///< �[���x�N�g��

		static const Vector3<T> UnitX; ///< X���P�ʃx�N�g��

		static const Vector3<T> UnitY; ///< Y���P�ʃx�N�g��

		static const Vector3<T> UnitZ; ///< Z���P�ʃx�N�g��

		static const Vector3<T> ScaleUnit; ///< �X�P�[���P�ʃx�N�g�� 

		/**
		*�f�t�H���g�R���X�g���N�^
		*/
		Vector3<T>() {
			Set(0, 0, 0);
		}

		/**
		* �������R���X�g���N�^
		* @param x
		* @param y
		* @param z
		*/
		Vector3<T>(T x, T y, T z) {
			Set(x, y, z);
		}

		/**
		* �R�s�[�R���X�g���N�^
		* @param Vector3<T>
		*/
		Vector3<T>(const Vector3<T> & u) {
			Set(u.x, u.y, u.z);
		}

		/**
		* �l�̐ݒ�
		*/
		void Set(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
		* ���Z
		* @param �E�Ӓl  
		* @return�@���Z���� 
		*/
		Vector3<T> operator +(const Vector3<T>& u) const {
			return Vector3<T>( x + u.x, y + u.y, z + u.z); 

		}

		/**
		* ���Z
		* @param�@�E�Ӓl  
		* @return ���Z����
		*/
		Vector3<T> operator -(const Vector3<T>& u) const {
			return Vector3<T>( x - u.x, y - u.y, z - u.z); 

		}

		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Vector3<T> operator *(const T u) const {
			return Vector3<T>( x * u, y * u, z * u);

		}

		/**
		* ���Z
		* @param �E�Ӓl  
		* @return ���Z����
		*/
		Vector3<T> operator /(const T u) const {
			return Vector3<T>( x / u, y / u, z / u);
		}

		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		Vector3<T>& operator +=(const Vector3<T>& u) {
			x += u.x;
			y += u.y;
			z += u.z;
			return *this;
		}

		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		Vector3<T>& operator -=(const Vector3<T>& u) {
			x -= u.x;
			y -= u.y;
			z -= u.z;
			return *this;
		}

		/**
		* ��Z���
		* @param  �E�Ӓl
		* @return ��Z����
		*/
		Vector3<T>& operator *=(const T u) {
			x *= u;
			y *= u;
			z *= u;
			return *this;
		}

		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		Vector3<T>& operator /=(const T u) {
			Assert(u != 0);
			x /= u;
			y /= u;
			z /= u;
			return *this;
		}

		/**
		* ���
		* @param �E�Ӓl
		* @return �������
		*/
		Vector3<T>& operator =(Vector3<T>& u) {
			using std::swap;
			swap(*this, u);
			return u;
		}

		/**
		* ���] 
		* @param ���]����
		*/
		Vector3<T>& operator ~() {
			Inverse();
			return *this;
		}

		/**
		* �h�b�g��
		* @param �E�Ӓl
		* @return T ����
		*/
		T Dot(Vector3<T>& u) {
			return (x * u.x + y * u.y + z * u.z);
		}

		/**
		* �N���X��
		* @param   �E�Ӓl
		* @return�@Vector3<T> �N���X�� 
		*/
		Vector3<T> Cross(Vector3<T>& u) {
			return Vector3<T>(
				(y * u.z - z * u.y ),
				(x * u.z - z * u.x ),
				(x * u.y - y * u.x ));
		}

		/**
		* �x�N�g���̒���
		* @return  T ����
		*/
		T Length() {
			return static_cast<T>(sqrt(x * x + y * y + z * z));

		}

		/**
		* �x�N�g���̒����̓��l
		* @return  T ����
		*/
		T SquaredLength() {
			return static_cast<T>(x * x + y * y + z * z);

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

			if (Math::Abs(x) < Math::Epsilon) {x = 0.f;}
			if (Math::Abs(y) < Math::Epsilon) {y = 0.f;}
			if (Math::Abs(z) < Math::Epsilon) {z = 0.f;}
		}

		/**
		* �x�N�g���̔��]
		*/
		void Inverse() {
			x = - x;
			y = - y;
			z = - z;
		}

		/**
		* ���`���
		* @param const Vector3<T>& �n�_�x�N�g��
		* @param const Vector3<T>& �I�_�x�N�g��
		* @param T ��ԌW��
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
		* @return �[���x�N�g���Ȃ�true
		*/
		bool IsZero() const {
			return (
				Math::Abs(x) <= Math::Epsilon &&
				Math::Abs(y) <= Math::Epsilon &&
				Math::Abs(z) <= Math::Epsilon);
		}

		/** 
		* @return �P�ʃx�N�g���Ȃ�true
		*/
		bool IsUnit() const {
			return (
				Math::Abs(x - 1.f) <= Math::Epsilon &&
				Math::Abs(y - 1.f) <= Math::Epsilon &&
				Math::Abs(z - 1.f) <= Math::Epsilon);
		}

		/** 
		* �x�N�g���̓������Z
		* @param �E�Ӓl 
		* @return ��r���ʂ��������Ȃ��true
		*/
		bool operator ==(const Vector3<T>& u) const {	
			return (
			Math::Abs(x - u.x) <= Math::Epsilon &&
			Math::Abs(y - u.y) <= Math::Epsilon &&
			Math::Abs(z - u.z) <= Math::Epsilon);
		}

		/** 
		* �x�N�g���������Z
		* @param �E�Ӓl 
		* @return�@��r���ʂ��������Ȃ��Ȃ��true
		*/
		bool operator !=(const Vector3<T>& u) const {
			return !(*this == u);
		}
	};
	//--------------------------------------------------------------------------------------
	// �萔��`
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
	// �萔��`
	//--------------------------------------------------------------------------------------
	// �[���x�N�g��   
	template<typename T>
	const Vector3<T> Vector3<T>::Zero = Vector3<T>(0, 0, 0);  

	// X���P�ʃx�N�g��
	template<typename T>
	const Vector3<T> Vector3<T>::UnitX = Vector3<T>(1, 0, 0);

	// Y���P�ʃx�N�g��
	template<typename T>
	const Vector3<T> Vector3<T>::UnitY = Vector3<T>(0, 1, 0); 

	// Z���x�N�g��
	template<typename T>
	const Vector3<T> Vector3<T>::UnitZ = Vector3<T>(0, 0, 1); 

	// �X�P�[���P�ʃx�N�g��
	template<typename T>
	const Vector3<T> Vector3<T>::ScaleUnit = Vector3<T>(1, 1, 1);

}


#endif