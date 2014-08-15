#ifndef NYX_CORE_INCLUDED_LIMITS_H_
#define NYX_CORE_INCLUDED_LIMITS_H_

namespace nyx
{
	///----------------------------------------------------------------------------------
	///�^�̌��E�l��`
	///----------------------------------------------------------------------------------
	class limits {
	public:
		/**
		* char �^�̍ŏ��l�i�����t�j
		*/
		static const signed char CHAR_MINIMUM = (-128);
		
		/**
		* char �^�̍ő�l�i�����t�j
		*/
		static const signed char CHAR_MAXIMUM = (127);

		/**
		* char �^�̍ŏ��l�i�����Ȃ��j
		*/
		static const uint8_t UCHAR_MINIMUM = (0);

		/**
		* char �^�̍ő�l�i�����Ȃ��j
		*/
		static const uint8_t UCHAR_MAXIMUM = (0xff);


		/**
		* short �^�̍ŏ��l�i�����t�j
		*/
		static const short SHORT_MINIMUM = (-32768);

		/**
		* short �^�̍ő�l�i�����t�j
		*/
		static const short SHORT_MAXIMUM =   (32767);

		/**
		* short �^�̍ŏ��l�i�����Ȃ��j
		*/
		static const uint16_t USHORT_MINIMUM = (0);

		/**
		* short �^�̍ő�l�i�����Ȃ��j
		*/
		static const uint16_t USHORT_MAXIMUM = (0xffff);


		/**
		* int �^�̍ŏ��l�i�����t�j
		*/
		static const int INT_MINIMUM = (-2147483647 -1);

		/**
		* int �^�̍ő�l�i�����t�j
		*/
		static const int INT_MAXIMUM = (2147483647);

		/**
		* int �^�̍ŏ��l�i�����Ȃ��j
		*/
		static const uint32_t UINT_MINIMUM = (0);

		/**
		* int �^�̍ő�l�i�����Ȃ��j
		*/
		static const uint32_t UINT_MAXIMUM = (0xffffffff);

		/**
		* float  �^�̍ő�l
		*/
		static const float FLOAT_MINIMUM;

		/**
		* float �^�̍ő�l
		*/
		static const float FLOAT_MAXIMUM;

		/**
		* float �^�̍ő�l������
		*/
		static const float FLOAT_MAX_SQRT;

		/**
		* double �^�̍ő�l
		*/
		static const double DOUBLE_MINIMUM;

		/**
		* double �^�̍ő�l
		*/
		static const double DOUBLE_MAXIMUM;


		/**
		* char�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool is_char_range(T value) {
			return ((value >= CHAR_MINIMUM) && (value <= CHAR_MINIMUM));
		}

		/**
		* uchar�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool is_uchar_range(T value) {
			return ((value >= UCHAR_MINIMUM) && (value <= UCHAR_MAXIMUM));
		}

		/**
		* short�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool is_short_range(T value) {
			return ((value >= SHORT_MINIMUM) && (value <= SHORT_MAXIMUM));
		}

		/**
		* ushort�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool is_ushort_range(T value) {
			return ((value >= USHORT_MINIMUM) && (value <= USHORT_MAXIMUM));
		}

		/**
		* int�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool is_int_range(T value) {
			return ((value >= INT_MINIMUM) && (value <= INT_MAXIMUM));
		}

		/**
		* uint�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool is_uint_range(T value) {
			return ((value >= UINT_MINIMUM) && (value <= UINT_MAXIMUM));
		}

		/**
		* float�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool is_float_range(T value) {
			return ((value >= FLOAT_MINIMUM) && (value <= FLOAT_MAXIMUM));
		}

		/**
		* double�^�͈͓̔��ɂ��邩�`�F�b�N
		* @param value �`�F�b�N����l
		* @return bool �͈͓��Ȃ�true
		*/
		template<typename T>
		static bool is_double_range(T value) {
			return ((value >= DOUBLE_MINIMUM) && (value <= DOUBLE_MAXIMUM));
		}
	private:
		limits();//�����֎~
	};
}
#endif