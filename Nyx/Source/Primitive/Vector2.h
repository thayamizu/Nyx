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
#ifndef NYX_CORE_INCLUDED_VECTOR2_H_
#define NYX_CORE_INCLUDED_VECTOR2_H_


namespace nyx
{
	template<typename T>
	class vector2 {
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic type.");
	public:
		union {
			struct {
				T x; ///< X����
				T y; ///< Y����
			};

			T elements[2];
		};

		static const vector2<T> ZERO;  ///< �[���x�N�g��

		static const vector2<T> UNIT_X; ///< X���P�ʃx�N�g��

		static const vector2<T> UNIT_Y; ///< Y���P�ʃx�N�g��

		static const vector2<T> SCALE_UNIT; ///< �X�P�[���P�ʃx�N�g��


		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		vector2<T>() 
			: x(0), y(0) {
		}


		/**
		* �R���X�g���N�^
		* @param x
		* @param y
		*/
		vector2<T>(T x, T y) {
			set(x, y);
		}


		/**
		* �R�s�[�R���X�g���N�^
		* @param Vector2
		*/
		vector2<T>(const vector2 & u) 
			:x(u.x), y(u.y) {

		}


		/**
		* �l�̐ݒ�
		*/
		void set(T x, T y) {
			this->x = x;
			this->y = y;
		}


		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		vector2<T> operator +(const vector2<T>& u) const {
			return vector2( x + u.x, y + u.y); 
		}


		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/ 
		vector2<T> operator -(const vector2<T>& u) const {
			return vector2( x - u.x, y - u.y); 
		}


		/** 
		* �x�N�g����Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		vector2<T> operator *(const T u) const {
			return vector2( x * u, y * u); 
		}


		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		vector2<T> operator /(const T u) const {
			return vector2( x / u, y / u); 
		}


		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		vector2<T> & operator +=(const vector2<T>& u) {
			x += u.x;
			y += u.y;

			return *this;
		}


		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/                                                                             
		vector2<T> & operator -=(const vector2<T>& u) {
			x -= u.x;
			y -= u.y;

			return *this;
		}


		/** 
		* �x�N�g����Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		vector2<T> &  operator *=(const T u) {
			x *= u;
			y *= u;

			return *this;
		}


		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		vector2<T> & operator /=(const T u) {
			x /= u;
			y /= u;

			return *this;
		}


		/** 
		* �x�N�g�����]
		* @param �E�Ӓl 
		* @return ���]���ꂽ�x�N�g��
		*/
		vector2<T> operator ~() {
		}


		/** 
		* �x�N�g�����
		* @param �E�Ӓl 
		* @return ������ꂽ�x�N�g��
		*/
		vector2<T>& operator =(const vector2<T> &u) {
			x = u.x;
			y = u.y;

			return *this;
		}


		/**
		* �h�b�g�ρi���ρj
		* @param �E�Ӓl
		* @return ����
		*/
		T dot(const vector2& u) {
			return (x * u.x + y * u.y);

		}

		/**
		* �x�N�g���̒���
		* @return �x�N�g���̒����̕�����
		*/
		float norm() {
			return static_cast<float>(sqrt(x * x + y * y ));

		}

		/**
		* �x�N�g���̒����̕�����
		* @return �x�N�g���̒����̕�����
		*/
		float squared_norm() {
			return static_cast<float>(x * x + y * y );
		}

		/**
		* �x�N�g���𐳋K��
		*/
		void normalize() {
			float abs = norm();

			if (abs <= math::EPSILON) { abs = 1.0;}

			x /= abs;
			y /= abs;

			if (math::abs(x) < math::EPSILON) {x = 0.0f;}
			if (math::abs(y) < math::EPSILON) {y = 0.0f;}
		}


		/**
		* �x�N�g���𔽓]
		*/
		void inverse() {
			x = - x;
			y = - y;
		}


		/**
		*
		*/
		vector2<T> lerp(const vector2<T>& v1, const vector2<T>& v2, float s) {
			vector2 lerp;
			if (s > 1) s = 1;
			if (s < 0) s = 0;
			lerp.x = v1.x * (1 - s) + v2.x * s;
			lerp.y = v1.y * (1 - s) + v2.y * s;

			return lerp;
		}


		/** 
		* @return �[���x�N�g���Ȃ�true
		*/
		bool is_zero() const {
			return (
				math::abs(x) <= math::EPSILON &&
				math::abs(y) <= math::EPSILON);
		}


		/** 
		* @return �P�ʃx�N�g���Ȃ�true
		*/
		bool is_unit() const {
			const float value = math::sqrt(x*x + y*y);
			return (math::abs(value - 1.f) <= math::EPSILON);
		}


		/** 
		* �x�N�g���̓������Z
		* @param �E�Ӓl 
		* @return ��r���ʂ��������Ȃ��true
		*/
		bool operator ==(const vector2<T>& v) const {
			return ( 
				math::abs(x - v.x ) < math::EPSILON &&
				math::abs(y - v.y ) < math::EPSILON);
		}


		/** 
		* �x�N�g���������Z
		* @param �E�Ӓl 
		* @return�@��r���ʂ��������Ȃ��Ȃ��true
		*/
		bool operator !=(const vector2<T>& rhs) const {
			return !(*this == rhs);
		}
	};

	//--------------------------------------------------------------------------------------
	// �ʖ���`
	//--------------------------------------------------------------------------------------
	typedef vector2<int>     axis2i;
	typedef vector2<int>     point2i;
	typedef vector2<int>     vector2i;
	typedef vector2<int>     tex_choord2i;
	typedef vector2<float>   axis2f;
	typedef vector2<float>   point2f;
	typedef vector2<float>   vector2f;
	typedef vector2<float>   tex_choord2f;
	typedef vector2<double>  axis2d;
	typedef vector2<double>  point2d;
	typedef vector2<double>  vector2d;
	typedef vector2<double>  tex_choord2d;

	//--------------------------------------------------------------------------------------
	// �萔��`
	//-------------------------------------------------------------------------------------- 
	template<typename T>
	const vector2<T> vector2<T>::ZERO = vector2(0, 0);

	template<typename T>
	const vector2<T> vector2<T>::UNIT_X = vector2(1, 0);

	template<typename T>
	const vector2<T> vector2<T>::UNIT_Y = vector2(0, 1);

	template<typename T>
	const vector2<T> vector2<T>::SCALE_UNIT = vector2(1, 1);
}
#endif
//VECTOR_H
