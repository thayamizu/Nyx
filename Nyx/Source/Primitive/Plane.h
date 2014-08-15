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
#ifndef NYX_CORE_INCLUDED_PLANE_H_
#define NYX_CORE_INCLUDED_PLANE_H_

namespace nyx {

	template <typename T>
	class plane{
		static_assert(std::is_arithmetic<T>::value,"T required arithmetic type.");
	public:
		union {
			struct {
				///
				T  a;
				///
				T  b;
				///
				T  c;
				///
				T  d;
			};
			///
			T  element[4];
		};


		/**
		*
		*/
		plane() 
			: a(0), b(0), c(0), d(0) {

		} 


		/**
		*
		*/
		plane(T a, T b, T c, T d) {
				set(a, b, c, d);
		}


		/**
		*
		*/
		void set(T a, T b, T c, T d) {
			this->a = a;
			this->b = b;
			this->c = c;
			this->d = d;
		}


		/**
		*
		*/
		void normalize(){
			float distance = math::abs(math::sqrt(a*a + b*b + c*c));
			NYX_ASSERT(distance != 0);

			a /= distance;
			b /= distance;
			c /= distance;

			if (math::abs(a) <= math::EPSILON) {
				a = 0.f;
			}
			if (math::abs(b) <= math::EPSILON) {
				b = 0.f;
			}
			if (math::abs(c) <= math::EPSILON) {
				c = 0.f;
			}
		}
		
		
		/**
		*
		*/
		float get_signed_distance(const vector3<T>& point) {
			return math::sqrt(a * point.x + b * point.y + c * point.z + d);
		}
		

		/**
		*
		*/
		float get_unsigned_distance(const vector3<T>& point) {
			return math::abs(get_signed_distance(point));
		}
	};
}
#endif
//PLANE_H_
