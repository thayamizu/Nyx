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


namespace Nyx
{
	template<typename T>
	class Vector2 {
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic type.");
	public:
		union {
			struct {
				T x; ///< X����
				T y; ///< Y����
			};

			T elements[2];
		};

		static const Vector2<T> Zero;  ///< �[���x�N�g��

		static const Vector2<T> UnitX; ///< X���P�ʃx�N�g��

		static const Vector2<T> UnitY; ///< Y���P�ʃx�N�g��

		static const Vector2<T> ScaleUnit; ///< �X�P�[���P�ʃx�N�g��


		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Vector2<T>() 
			: x(0), y(0) {
		}

		/**
		* �R���X�g���N�^
		* @param x
		* @param y
		*/
		Vector2<T>(T x, T y) {
			Set(x, y);
		}

		/**
		* �R�s�[�R���X�g���N�^
		* @param Vector2
		*/
		Vector2<T>(const Vector2 & u) 
			:x(u.x), y(u.y) {

		}

		/**
		* �l�̐ݒ�
		*/
		void Set(T x, T y) {
			this->x = x;
			this->y = y;
		}

		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Vector2<T> operator +(const Vector2<T>& u) const {
			return Vector2( x + u.x, y + u.y); 
		}

		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/ 
		Vector2<T> operator -(const Vector2<T>& u) const {
			return Vector2( x - u.x, y - u.y); 
		}

		/** 
		* �x�N�g����Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Vector2<T> operator *(const T u) const {
			return Vector2( x * u, y * u); 
		}

		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Vector2<T> operator /(const T u) const {
			return Vector2( x / u, y / u); 
		}

		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Vector2<T> & operator +=(const Vector2<T>& u) {
			x += u.x;
			y += u.y;

			return *this;
		}
		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/                                                                             
		Vector2<T> & operator -=(const Vector2<T>& u) {
			x -= u.x;
			y -= u.y;

			return *this;
		}

		/** 
		* �x�N�g����Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Vector2<T> &  operator *=(const T u) {
			x *= u;
			y *= u;

			return *this;
		}

		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Vector2<T> & operator /=(const T u) {
			x /= u;
			y /= u;

			return *this;
		}

		/** 
		* �x�N�g�����]
		* @param �E�Ӓl 
		* @return ���]���ꂽ�x�N�g��
		*/
		Vector2<T> operator ~() {
		}

		/** 
		* �x�N�g�����
		* @param �E�Ӓl 
		* @return ������ꂽ�x�N�g��
		*/
		Vector2<T>& operator =(const Vector2<T> &u) {
			x = u.x;
			y = u.y;

			return *this;
		}


		/**
		* �h�b�g�ρi���ρj
		* @param �E�Ӓl
		* @return ����
		*/
		T Dot(const Vector2& u) {
			return (x * u.x + y * u.y);

		}

		/**
		* �x�N�g���̒���
		* @return �x�N�g���̒����̕�����
		*/
		float Length() {
			return static_cast<float>(sqrt(x * x + y * y ));

		}

		/**
		* �x�N�g���̒����̕�����
		* @return �x�N�g���̒����̕�����
		*/
		float SquaredLength() {
			return static_cast<float>(x * x + y * y );
		}

		/**
		* �x�N�g���𐳋K��
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
		* �x�N�g���𔽓]
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
		* @return �[���x�N�g���Ȃ�true
		*/
		bool IsZero() const {
			return (
				Math::Abs(x) <= Math::Epsilon &&
				Math::Abs(y) <= Math::Epsilon);
		}


		/** 
		* @return �P�ʃx�N�g���Ȃ�true
		*/
		bool IsUnit() const {
			const float value = Math::Sqrt(x*x + y*y);
			return (Math::Abs(value - 1.f) <= Math::Epsilon);
		}


		/** 
		* �x�N�g���̓������Z
		* @param �E�Ӓl 
		* @return ��r���ʂ��������Ȃ��true
		*/
		bool operator ==(const Vector2<T>& v) const {
			return ( 
				Math::Abs(x - v.x ) < Math::Epsilon &&
				Math::Abs(y - v.y ) < Math::Epsilon);
		}


		/** 
		* �x�N�g���������Z
		* @param �E�Ӓl 
		* @return�@��r���ʂ��������Ȃ��Ȃ��true
		*/
		bool operator !=(const Vector2<T>& rhs) const {
			return !(*this == rhs);
		}
	};

	//--------------------------------------------------------------------------------------
	// �ʖ���`
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
	// �萔��`
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
