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

namespace nyx
{
	template<typename T>
	class vector3 {
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

		static const vector3<T> ZERO;  ///< �[���x�N�g��

		static const vector3<T> UNIT_X; ///< X���P�ʃx�N�g��

		static const vector3<T> UNIT_Y; ///< Y���P�ʃx�N�g��

		static const vector3<T> UNIT_Z; ///< Z���P�ʃx�N�g��

		static const vector3<T> SCALE_UNIT; ///< �X�P�[���P�ʃx�N�g�� 
	

		/**
		*�f�t�H���g�R���X�g���N�^
		*/
		vector3<T>() {
			set(0, 0, 0);
		}


		/**
		* �������R���X�g���N�^
		* @param x
		* @param y
		* @param z
		*/
		vector3<T>(T x, T y, T z) {
			set(x, y, z);
		}


		/**
		* �R�s�[�R���X�g���N�^
		* @param Vector3<T>
		*/
		vector3<T>(const vector3<T> & u) {
			set(u.x, u.y, u.z);
		}


		/**
		* �l�̐ݒ�
		*/
		void set(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}


		/**
		* ���Z
		* @param �E�Ӓl  
		* @return�@���Z���� 
		*/
		vector3<T> operator +(const vector3<T>& u) const {
			return vector3<T>( x + u.x, y + u.y, z + u.z); 

		}


		/**
		* ���Z
		* @param�@�E�Ӓl  
		* @return ���Z����
		*/
		vector3<T> operator -(const vector3<T>& u) const {
			return vector3<T>( x - u.x, y - u.y, z - u.z); 

		}


		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		vector3<T> operator *(const T u) const {
			return vector3<T>( x * u, y * u, z * u);

		}


		/**
		* ���Z
		* @param �E�Ӓl  
		* @return ���Z����
		*/
		vector3<T> operator /(const T u) const {
			if (u <= math::EPSILON) {
				return *this;
			}
			return vector3<T>( x / u, y / u, z / u);
		}


		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		vector3<T>& operator +=(const vector3<T>& u) {
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
		vector3<T>& operator -=(const vector3<T>& u) {
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
		vector3<T>& operator *=(const T u) {
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
		vector3<T>& operator /=(const T u) {
			NYX_ASSERT(u != 0);
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
		vector3<T>& operator =(vector3<T>& u) {
			using std::swap;
			swap(*this, u);
			return u;
		}


		/**
		* ���] 
		* @param ���]����
		*/
		vector3<T>& operator ~() {
			Inverse();
			return *this;
		}


		/**
		* �h�b�g��
		* @param �E�Ӓl
		* @return T ����
		*/
		T dot(vector3<T>& u) {
			return (x * u.x + y * u.y + z * u.z);
		}


		/**
		* �N���X��
		* @param   �E�Ӓl
		* @return�@Vector3<T> �N���X�� 
		*/
		vector3<T> cross(vector3<T>& u) {
			return vector3<T>(
				(y * u.z - z * u.y ),
				(x * u.z - z * u.x ),
				(x * u.y - y * u.x ));
		}


		/**
		* �x�N�g���̒���
		* @return  T ����
		*/
		float norm() {
			return static_cast<float>(sqrt(x * x + y * y + z * z));

		}


		/**
		* �x�N�g���̒����̓��l
		* @return  T ����
		*/
		float squared_norm() {
			return static_cast<float>(x * x + y * y + z * z);

		}


		/**
		* �x�N�g���̐��K��
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
		* �x�N�g���̔��]
		*/
		void inverse() {
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
		* @return �[���x�N�g���Ȃ�true
		*/
		bool is_zero() const {
			return (
				math::abs(x) <= math::EPSILON &&
				math::abs(y) <= math::EPSILON &&
				math::abs(z) <= math::EPSILON);
		}


		/** 
		* @return �P�ʃx�N�g���Ȃ�true
		*/
		bool is_unit() const {
			const auto value = math::sqrt(x*x + y*y +z*z);
			return (math::abs(value - 1.f) <= math::EPSILON);
		}


		/** 
		* �x�N�g���̓������Z
		* @param �E�Ӓl 
		* @return ��r���ʂ��������Ȃ��true
		*/
		bool operator ==(const vector3<T>& u) const {	
			return (
			math::abs(x - u.x) <= math::EPSILON &&
			math::abs(y - u.y) <= math::EPSILON &&
			math::abs(z - u.z) <= math::EPSILON);
		}


		/** 
		* �x�N�g���������Z
		* @param �E�Ӓl 
		* @return�@��r���ʂ��������Ȃ��Ȃ��true
		*/
		bool operator !=(const vector3<T>& u) const {
			return !(*this == u);
		}
	};
	//--------------------------------------------------------------------------------------
	// �萔��`
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
	// �萔��`
	//--------------------------------------------------------------------------------------
	// �[���x�N�g��   
	template<typename T>
	const vector3<T> vector3<T>::ZERO = vector3<T>(0, 0, 0);  

	// X���P�ʃx�N�g��
	template<typename T>
	const vector3<T> vector3<T>::UNIT_X = vector3<T>(1, 0, 0);

	// Y���P�ʃx�N�g��
	template<typename T>
	const vector3<T> vector3<T>::UNIT_Y = vector3<T>(0, 1, 0); 

	// Z���x�N�g��
	template<typename T>
	const vector3<T> vector3<T>::UNIT_Z = vector3<T>(0, 0, 1); 

	// �X�P�[���P�ʃx�N�g��
	template<typename T>
	const vector3<T> vector3<T>::SCALE_UNIT = vector3<T>(1, 1, 1);

}


#endif