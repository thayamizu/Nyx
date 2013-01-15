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
#ifndef NYX_CORE_INCLUDED_POINT2F_H_
#define NYX_CORE_INCLUDED_POINT2F_H_

namespace Nyx 
{

	class Point2f {
	public:
		//--------------------------------------------------------------------------------------
		// �����o�ϐ�
		//--------------------------------------------------------------------------------------
		/// �����o�ϐ�
		union {
			struct {
				/// x�l
				float  x;
				/// y�l
				float  y;
			};
			/// �z��
			float elements[2];
		};

		//--------------------------------------------------------------------------------------
		// �萔
		//--------------------------------------------------------------------------------------
		/// �[���ʒu
		static const Point2f Zero;

		/// �P�ʈʒu
		static const Point2f Unit;

		//--------------------------------------------------------------------------------------
		// �R���X�g���N�^�E�f�X�g���N�^
		//--------------------------------------------------------------------------------------

		Point2f():x(0), y(0){}

		Point2f(float a, float b):x(a), y(b) {

		}

		Point2f(float array[2]):x(array[0]), y(array[1]) {

		}

		Point2f(const Point2f& p):x(p.x),y(p.y) {

		}


		~Point2f() {}


		//--------------------------------------------------------------------------------------
		// ���Z
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param p ���Z����Point2f
		* @return ���Z���ꂽ
		*/
		Point2f operator +(const Point2f& p) const {
			return Point2f(x + p.x, y + p.y);
		}

		Point2f operator -(const Point2f& p) const {
			return Point2f(x - p.x, y - p.y);
		} 

		Point2f operator *(float value) const {
			return Point2f(x * value, y * value);
		}

		Point2f operator /(float value) const {
			return Point2f(x / value, y / value);
		}



		//--------------------------------------------------------------------------------------
		// ������Z
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param
		* @return
		*/
		Point2f& operator +=(const Point2f & p) {
			x += p.x;
			y += p.y;

			return *this;
		}
		/**
		*
		* @param
		* @return
		*/
		Point2f& operator -=(const Point2f & p) {
			x -= p.x;
			y -= p.y;

			return *this;
		}
		/**
		*
		* @param
		* @return
		*/
		Point2f& operator *=(const Point2f & p){
			x *= p.x;
			y *= p.y;

			return *this;
		}
		/**
		*
		* @param
		* @return
		*/
		Point2f& operator *=(float value) {
			x *= value;
			y *= value;

			return *this;
		}

		/**
		*
		* @param
		* @return
		*/
		Point2f& operator /=(float value) {
			x /= value;
			y /= value;

			return *this;
		}//--------------------------------------------------------------------------------------
		// �_�����Z
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param
		* @return
		*/
		bool operator ==(const Point2f & p) const {
			return ((x == p.x) && (y == p.y));
		}

		/**
		*
		* @param
		* @return
		*/
		bool operator !=(const Point2f & p) const {
			return ((x != p.x) || (y != p.y));
		}


	};

}

#endif