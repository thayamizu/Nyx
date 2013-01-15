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
#ifndef NYX_CORE_INCLUDED_POINT3I_H_
#define NYX_CORE_INCLUDED_POINT3I_H_

namespace Nyx 
{
	class Point3i {
	public:
		//--------------------------------------------------------------------------------------
		// �����o�ϐ�
		//--------------------------------------------------------------------------------------
		/// �����o�ϐ�
		union {
			struct {
				/// x�l
				int x;
				/// y�l
				int y;
				/// z�l
				int z;
			};
			/// �z��
			int elements[3];
		};

		//--------------------------------------------------------------------------------------
		// �萔
		//--------------------------------------------------------------------------------------
		/// �[���ʒu
		static const Point3i Zero;

		/// �P�ʈʒu
		static const Point3i Unit;

		//--------------------------------------------------------------------------------------
		// �R���X�g���N�^�E�f�X�g���N�^
		//--------------------------------------------------------------------------------------
		/**
		*
		*/
		Point3i():x(0), y(0), z(0){}
		/**
		*
		*/
		Point3i(int a, int b, int c):x(a), y(b), z(c) {

		}
		/**
		*
		*/
		Point3i(int array[3]):x(array[0]), y(array[1]),z(array[2]) {

		}
		/**
		*
		*/
		Point3i(const Point3i& p):x(p.x),y(p.y),z(p.z) {

		}

		/**
		*
		*/
		~Point3i() {}


		//--------------------------------------------------------------------------------------
		// ���Z
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param p ���Z����Point3i
		* @return ���Z���ꂽ
		*/
		Point3i operator +(const Point3i& p) const {
			return Point3i(x + p.x, y + p.y, z + p.z);
		}
		/**
		*
		*/
		Point3i operator -(const Point3i& p) const {
			return Point3i(x - p.x, y - p.y, z - p.z);
		} 
		/**
		*
		*/
		Point3i operator *(float value) const {
			return Point3i(x * (int)value, y * (int)value, z * (int)value);
		}
		/**
		*
		*/
		Point3i operator /(float value) const {
			return Point3i(x / (int)value, y / (int)value, z / (int)value);
		}//--------------------------------------------------------------------------------------
		// ������Z
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param
		* @return
		*/
		Point3i& operator +=(const Point3i & p) {
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
		Point3i& operator -=(const Point3i & p) {
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
		Point3i& operator *=(float value) {
			x *= (int)value;
			y *= (int)value;
			z *= (int)value;

			return *this;
		}

		/**
		*
		* @param
		* @return
		*/
		Point3i& operator /=(float value) {
			x /= (int)value;
			y /= (int)value;
			z /= (int)value;

			return *this;
		}//--------------------------------------------------------------------------------------
		// �_�����Z
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param
		* @return
		*/
		bool operator ==(const Point3i & p) const {
			return ((x == p.x) && (y == p.y) && (z == p.z));
		}

		/**
		*
		* @param
		* @return
		*/
		bool operator !=(const Point3i & p) const {
			return !(*this == p);
		}
	};
}

#endif