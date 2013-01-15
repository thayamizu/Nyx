#ifndef NYX_CORE_INCLUDED_LIMITS_H_
#define NYX_CORE_INCLUDED_LIMITS_H_

namespace Nyx
{
	///----------------------------------------------------------------------------------
	///�^�̌��E�l��`
	///----------------------------------------------------------------------------------
	class Limits {
	public:
		/**
		* char �^�̍ŏ��l�i�����t�j
		*/
		static const char CharMin = (-128);
		
		/**
		* char �^�̍ő�l�i�����t�j
		*/
		static const char CharMax = (127);

		/**
		* char �^�̍ŏ��l�i�����Ȃ��j
		*/
		static const uchar UCharMin = (0);

		/**
		* char �^�̍ő�l�i�����Ȃ��j
		*/
		static const uchar UCharMax = (0xff);


		/**
		* short �^�̍ŏ��l�i�����t�j
		*/
		static const short ShortMin = (-32768);

		/**
		* short �^�̍ő�l�i�����t�j
		*/
		static const short ShortMax =   (32767);

		/**
		* short �^�̍ŏ��l�i�����Ȃ��j
		*/
		static const ushort UShortMin = (0);

		/**
		* short �^�̍ő�l�i�����Ȃ��j
		*/
		static const ushort UShortMax = (0xffff);


		/**
		* int �^�̍ŏ��l�i�����t�j
		*/
		static const int IntMin = (-2147483647 -1);

		/**
		* int �^�̍ő�l�i�����t�j
		*/
		static const int IntMax = (2147483647);

		/**
		* int �^�̍ŏ��l�i�����Ȃ��j
		*/
		static const uint UIntMin = (0);

		/**
		* int �^�̍ő�l�i�����Ȃ��j
		*/
		static const uint UIntMax = (0xffffffff);

		/**
		* float  �^�̍ő�l
		*/
		static const float FloatMin;

		/**
		* float �^�̍ő�l
		*/
		static const float FloatMax;

		/**
		* float �^�̍ő�l������
		*/
		static const float FloatMaxSqrt;

		/**
		* double �^�̍ő�l
		*/
		static const double DoubleMin;

		/**
		* double �^�̍ő�l
		*/
		static const double DoubleMax;


		/**
		* char�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool IsCharRange(T value) {
			return ((value >= CharMin) && (value <= CharMax));
		}

		/**
		* uchar�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool IsUCharRange(T value) {
			return ((value >= UCharMin) && (value <= UCharMax));
		}

		/**
		* short�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool IsShortRange(T value) {
			return ((value >= ShortMin) && (value <= ShortMax));
		}

		/**
		* ushort�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool IsUShortRange(T value) {
			return ((value >= UShortMin) && (value <= UShortMax));
		}

		/**
		* int�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool IsIntRange(T value) {
			return ((value >= IntMin) && (value <= IntMax));
		}

		/**
		* uint�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool IsUIntRange(T value) {
			return ((value >= UIntMin) && (value <= UIntMax));
		}

		/**
		* float�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool IsFloatRange(T value) {
			return ((value >= FloatMin) && (value <= FloatMax));
		}

		/**
		* double�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool IsDoubleRange(T value) {
			return ((value >= DoubleMin) && (value <= DoubleMax));
		}
	private:
		Limits();//�����֎~
	};
}
#endif