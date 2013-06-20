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
#ifndef NYX_CORE_INCLUDED_RECT2i_H_
#define NYX_CORE_INCLUDED_RECT2i_H_
#include "Primitive/Vector2.h"

namespace Nyx
{
	template <typename T>
	class Rect{
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic type.");
	public:
		union {
			struct {
				///
				T x;
				///
				T y;
				///
				T width;
				///
				T height;

			};
			T element[4];
		};
		static const Rect<T> Zero;
		static const Rect<T> Unit;

		/**
		* �R���X�g���N�^
		*/
		Rect<T>() {
			Set(0, 0, 0, 0);
		}


		/**
		* �R���X�g���N�^
		* @param T x
		* @param T y
		* @param T width
		* @param T height
		*/
		Rect<T>(const T x, const T y, const T width, const T height) {
			Set(x, y, width, height);
		}


		/**
		* �R�s�[�R���X�g���N�^
		*/
		Rect<T>(const Rect<T>& rect ) {
			Set(rect.x, rect.y, rect.width, rect.height);
		}


		/**
		* �l�̃Z�b�g
		*/
		void Set(const T x, const T y, const T width, const T height) {
			this->x      = x;
			this->y      = y;
			this->width  = width;
			this->height = height;
		}


		/**
		* �w�肵���_����`�ɕ�܂���Ă��邩
		* @param const Point2<T> �_
		*/
		bool Contain(const Vector2<T>& point) const {
			const T right  = x + width;
			const T bottom = y + height;

			if ((x  <= point.x) && (point.x <= right) &&
				(y  <= point.y) && (point.y <= bottom)) {
					return true;
			}
			return false;
		}

		/**
		* �������Z
		* @param const Rect<T>& rect
		*/
		bool operator ==(const Rect<T>& rect) const {
			return (
				x      == rect.x     &&
				y      == rect.y     &&
				width  == rect.width &&
				height == rect.height);
		}


		/**
		* �������Z
		* @param const Rect<T>& rect
		*/
		bool operator !=(const Rect<T>& rect) const {
			return !(*this == rect);
		}
	};
	//--------------------------------------------------------------------------------------
	// �ʖ���`
	//--------------------------------------------------------------------------------------
	typedef Rect<int>     Rect2i;
	typedef Rect<float>   Rect2f;
	typedef Rect<double>  Rect2d;

	//--------------------------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------------------------
	template <typename T>
	const Rect<T> Rect<T>::Zero = Rect<T>(0, 0, 0, 0);
	
	template <typename T>
	const Rect<T> Rect<T>::Unit = Rect<T>(1, 1, 1, 1);
} 
#endif