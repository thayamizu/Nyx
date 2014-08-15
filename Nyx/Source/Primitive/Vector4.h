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

namespace nyx
{
	template <typename T>
	class vector4 {
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

		static const vector4<T> ZERO;  ///< �[���x�N�g��

		static const vector4<T> UNIT_X; ///< X���P�ʃx�N�g��

		static const vector4<T> UNIT_Y; ///< Y���P�ʃx�N�g��

		static const vector4<T> UNIT_Z; ///< Z���P�ʃx�N�g��

		static const vector4<T> UNIT_W; ///< W���P�ʃx�N�g��

		static const vector4<T> SCALE_UNIT; ///< �X�P�[���P�ʃx�N�g�� 


		/**
		*�f�t�H���g�R���X�g���N�^
		*/
		vector4<T>()
			:x(0), y(0), z(0), w(0){
		}


		/**
		* �������R���X�g���N�^
		* @param x
		* @param y
		* @param z
		*/
		vector4<T>(T x_, T y_, T z_, T w_) 
			: x(x_), y(y_), z(z_), w(w_) {
		}


		/**
		* �R�s�[�R���X�g���N�^
		* @param Vector4<T>
		*/
		vector4<T>(const vector4<T> & u)
			: x(u.x), y(u.y), z(u.z) ,w(u.w){
		}


		/**
		* �l�̐ݒ�
		*/
		void set(T x_, T y_, T z_, T w_) {
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
		vector4<T> operator +(const vector4<T>& u) const {
			return vector4<T>( x + u.x, y + u.y, z + u.z, w + u.w); 
		}


		/**
		* ���Z
		* @param�@�E�Ӓl  
		* @return ���Z����
		*/
		vector4<T> operator -(const vector4<T>& u) const {
			return vector4<T>( x - u.x, y - u.y, z - u.z, w - u.w); 
		}


		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		vector4<T> operator *(const T u) const {
			return vector4<T>( x * u, y * u, z * u, w * u);
		}


		/**
		* ���Z
		* @param �E�Ӓl  
		* @return ���Z����
		*/
		vector4<T> operator /(const T u) const {
			return vector4<T>( x / u, y / u, z / u, w / u);

		}


		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		vector4<T>& operator +=(const vector4<T>& u) {
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
		vector4<T>& operator -=(const vector4<T>& u) {
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
		vector4<T>& operator *=(const T u) {
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
		vector4<T>& operator /=(const T u) {
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
		vector4<T>& operator =(vector4<T>& u) {
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
		vector4<T>& operator ~() {
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
		T dot(vector4<T>& u) {
			return (x * u.x + y * u.y + z * u.z + w*u.w);
		}


		/**
		* �x�N�g���̒���
		* @return  ����
		*/
		float norm() {
			return math::sqrt(x * x + y * y + z * z+ w * w);
		}


		/**
		* �x�N�g���̒����̓��l
		* @return  ����
		*/
		float squared_norm() {
			return static_cast<float>(x * x + y * y + z * z + w * w);

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
			w /= abs;

			if (math::abs(x) < math::EPSILON) {x = 0.f;}
			if (math::abs(y) < math::EPSILON) {y = 0.f;}
			if (math::abs(z) < math::EPSILON) {z = 0.f;}
			if (math::abs(w) < math::EPSILON) {w = 0.f;}
		}


		/**
		* �x�N�g���̔��]
		*/
		void inverse() {
			x = - x;
			y = - y;
			z = - z;
			w = - w;
		}

		/**
		* ���`���
		*/
		vector4<T> lerp(const vector4<T>& v1, const vector4<T>& v2, float s) {
			vector4<T> lerp;
			if (s > 1) s = 1;
			if (s < 0) s = 0;
			lerp.x = v1.x * (1 - s) + v2.x * s;
			lerp.y = v1.y * (1 - s) + v2.y * s;
			lerp.z = v1.z * (1 - s) + v2.z * s;
			lerp.w = v1.w * (1 - s) + v2.w * s;


			return std::move(lerp);	
		}
		
		
		/** 
		* @return �[���x�N�g���Ȃ�true
		*/
		bool is_zero() const {
			return (
				math::abs(x) <= math::EPSILON &&
				math::abs(y) <= math::EPSILON &&
				math::abs(z) <= math::EPSILON &&
				math::abs(w) <= math::EPSILON);
		}


		/** 
		* @return �P�ʃx�N�g���Ȃ�true
		*/
		bool is_unit() const {
			const float value = math::sqrt(x*x + y*y + z*z + w*w);
			return (math::abs(value - 1.f) <= math::EPSILON);
		}


		/** 
		* �x�N�g���̓������Z
		* @param �E�Ӓl 
		* @return ��r���ʂ��������Ȃ��true
		*/
		bool operator==(const vector4<T>& u) const {
			return (
				math::abs(x - u.x) <= math::EPSILON &&
				math::abs(y - u.y) <= math::EPSILON &&
				math::abs(z - u.z) <= math::EPSILON &&
				math::abs(w - u.w) <= math::EPSILON);
		}


		/** 
		* �x�N�g���������Z
		* @param �E�Ӓl 
		* @return�@��r���ʂ��������Ȃ��Ȃ��true
		*/
		bool operator !=(const vector4<T>& u) const {
			return !(*this == u);
		}
	};
	//--------------------------------------------------------------------------------------
	// �ʖ���`
	//--------------------------------------------------------------------------------------
	typedef vector4<int>     axis4i;
	typedef vector4<int>     point4i;
	typedef vector4<int>     vector4i;
	typedef vector4<int>     tex_choord4i;
	typedef vector4<float>   axis4f;
	typedef vector4<float>   point4f;
	typedef vector4<float>   vector4f;
	typedef vector4<float>   tex_choord_4f;
	typedef vector4<double>  axis4d;
	typedef vector4<double>  point4d;
	typedef vector4<double>  vector4d;
	typedef vector4<double>  tex_choord4d;

	//--------------------------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------------------------
	// �[���x�N�g��
	template<typename T>
	const vector4<T> vector4<T>::ZERO = vector4(0, 0, 0, 0);  

	// X���P�ʃx�N�g��
	template<typename T>
	const vector4<T> vector4<T>::UNIT_X = vector4(1, 0, 0, 0);

	// Y���P�ʃx�N�g��
	template<typename T>
	const vector4<T> vector4<T>::UNIT_Y = vector4(0, 1, 0, 0); 

	// Z���x�N�g��
	template<typename T>
	const vector4<T> vector4<T>::UNIT_Z = vector4(0, 0, 1, 0); 
	
	// W���x�N�g��
	template<typename T>
	const vector4<T> vector4<T>::UNIT_W = vector4(0, 0, 0, 1); 
	
	// �X�P�[���P�ʃx�N�g��
	template<typename T>
	const vector4<T> vector4<T>::SCALE_UNIT = vector4(1, 1, 1, 1);
}


#endif