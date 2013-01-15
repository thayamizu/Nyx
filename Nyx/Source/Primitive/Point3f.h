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
#ifndef NYX_CORE_INCLUDED_POINT3F_H_
#define NYX_CORE_INCLUDED_POINT3F_H_

namespace Nyx 
{
	class Point3f {
	public:
		//--------------------------------------------------------------------------------------
		// �����o�ϐ�
		//--------------------------------------------------------------------------------------
		/// �����o�ϐ�
		union {
			struct {
				/// x�l
				float x;
				/// y�l
				float y;
				/// z�l
				float z;
			};
			/// �z��
			float elements[3];
		};

		//--------------------------------------------------------------------------------------
		// �萔
		//--------------------------------------------------------------------------------------
		/// �[���ʒu
		static const Point3f Zero;

		/// �P�ʈʒu
		static const Point3f Unit;

		//--------------------------------------------------------------------------------------
		// �R���X�g���N�^�E�f�X�g���N�^
		//--------------------------------------------------------------------------------------
		/**
		*
		*/
		Point3f()
			:x(0.f), y(0.f), z(0.f) {
		}
		/**
		*
		*/
		Point3f(float a, float b, float c)
			:x(a), y(b), z(c) {
		}
		/**
		*
		*/
		Point3f(float array[3]):x(array[0]), y(array[1]),z(array[2]) {

		}
		/**
		*
		*/
		Point3f(const Point3f& p):x(p.x),y(p.y),z(p.z) {

		}
		/**
		*
		*/
		~Point3f() {}


		//--------------------------------------------------------------------------------------
		// ���Z
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param p ���Z����Point3f
		* @return ���Z���ꂽ
		*/
		Point3f operator +(const Point3f& p) const {
			return Point3f(x + p.x, y + p.y, z + p.z);
		}
		/**
		*
		*/
		Point3f operator -(const Point3f& p) const {
			return Point3f(x - p.x, y - p.y, z - p.z);
		} 
		/**
		*
		*/
		Point3f operator *(float value) const {
			return Point3f(x * value, y *value, z * value);
		}

		/**
		*
		*/
		Point3f operator /(float value) const {
			return Point3f(x / value, y / value, z / value);
		}

		//--------------------------------------------------------------------------------------
		// ������Z
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param
		* @return
		*/
		Point3f& operator +=(const Point3f & p) {
			x += p.x;
			y += p.y;
			z += p.z;

			return *this;
		}
		/**
		*
		* @param
		* @return
		*/
		Point3f& operator -=(const Point3f & p) {
			x -= p.x;
			y -= p.y;
			z -= p.z;

			return *this;
		}
		/**
		*
		* @param
		* @return
		*/
		Point3f& operator *=(const Point3f & p){
			x *= p.x;
			y *= p.y;
			z *= p.z;

			return *this;
		}
		/**
		*
		* @param
		* @return
		*/
		Point3f& operator *=(float value) {
			x *= value;
			y *= value;
			z *= value;

			return *this;
		}

		/**
		*
		* @param
		* @return
		*/
		Point3f& operator /=(float value) {
			x /= value;
			y /= value;
			z /= value;

			return *this;
		}
		//--------------------------------------------------------------------------------------
		// �_�����Z
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param
		* @return
		*/
		bool operator ==(const Point3f & p) const {
			return ((x == p.x) && (y == p.y) && (z == p.z));
		}

		/**
		*
		* @param
		* @return
		*/
		bool operator !=(const Point3f & p) const {
			return ((x != p.x) || (y != p.y) || (z != p.z));
		}


	};

}

#endif