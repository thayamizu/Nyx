#ifndef NYX_CORE_INCLUDED_LIMITS_H_
#define NYX_CORE_INCLUDED_LIMITS_H_

namespace nyx
{
	///----------------------------------------------------------------------------------
	///型の限界値定義
	///----------------------------------------------------------------------------------
	class limits {
	public:
		/**
		* char 型の最小値（符号付）
		*/
		static const signed char CHAR_MINIMUM = (-128);
		
		/**
		* char 型の最大値（符号付）
		*/
		static const signed char CHAR_MAXIMUM = (127);

		/**
		* char 型の最小値（符号なし）
		*/
		static const uint8_t UCHAR_MINIMUM = (0);

		/**
		* char 型の最大値（符号なし）
		*/
		static const uint8_t UCHAR_MAXIMUM = (0xff);


		/**
		* short 型の最小値（符号付）
		*/
		static const short SHORT_MINIMUM = (-32768);

		/**
		* short 型の最大値（符号付）
		*/
		static const short SHORT_MAXIMUM =   (32767);

		/**
		* short 型の最小値（符号なし）
		*/
		static const uint16_t USHORT_MINIMUM = (0);

		/**
		* short 型の最大値（符号なし）
		*/
		static const uint16_t USHORT_MAXIMUM = (0xffff);


		/**
		* int 型の最小値（符号付）
		*/
		static const int INT_MINIMUM = (-2147483647 -1);

		/**
		* int 型の最大値（符号付）
		*/
		static const int INT_MAXIMUM = (2147483647);

		/**
		* int 型の最小値（符号なし）
		*/
		static const uint32_t UINT_MINIMUM = (0);

		/**
		* int 型の最大値（符号なし）
		*/
		static const uint32_t UINT_MAXIMUM = (0xffffffff);

		/**
		* float  型の最大値
		*/
		static const float FLOAT_MINIMUM;

		/**
		* float 型の最大値
		*/
		static const float FLOAT_MAXIMUM;

		/**
		* float 型の最大値平方根
		*/
		static const float FLOAT_MAX_SQRT;

		/**
		* double 型の最大値
		*/
		static const double DOUBLE_MINIMUM;

		/**
		* double 型の最大値
		*/
		static const double DOUBLE_MAXIMUM;


		/**
		* char型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool is_char_range(T value) {
			return ((value >= CHAR_MINIMUM) && (value <= CHAR_MINIMUM));
		}

		/**
		* uchar型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool is_uchar_range(T value) {
			return ((value >= UCHAR_MINIMUM) && (value <= UCHAR_MAXIMUM));
		}

		/**
		* short型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool is_short_range(T value) {
			return ((value >= SHORT_MINIMUM) && (value <= SHORT_MAXIMUM));
		}

		/**
		* ushort型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool is_ushort_range(T value) {
			return ((value >= USHORT_MINIMUM) && (value <= USHORT_MAXIMUM));
		}

		/**
		* int型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool is_int_range(T value) {
			return ((value >= INT_MINIMUM) && (value <= INT_MAXIMUM));
		}

		/**
		* uint型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool is_uint_range(T value) {
			return ((value >= UINT_MINIMUM) && (value <= UINT_MAXIMUM));
		}

		/**
		* float型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool is_float_range(T value) {
			return ((value >= FLOAT_MINIMUM) && (value <= FLOAT_MAXIMUM));
		}

		/**
		* double型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool is_double_range(T value) {
			return ((value >= DOUBLE_MINIMUM) && (value <= DOUBLE_MAXIMUM));
		}
	private:
		limits();//生成禁止
	};
}
#endif