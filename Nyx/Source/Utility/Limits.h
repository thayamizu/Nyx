#ifndef NYX_CORE_INCLUDED_LIMITS_H_
#define NYX_CORE_INCLUDED_LIMITS_H_

namespace Nyx
{
	///----------------------------------------------------------------------------------
	///型の限界値定義
	///----------------------------------------------------------------------------------
	class Limits {
	public:
		/**
		* char 型の最小値（符号付）
		*/
		static const char CharMin = (-128);
		
		/**
		* char 型の最大値（符号付）
		*/
		static const char CharMax = (127);

		/**
		* char 型の最小値（符号なし）
		*/
		static const uchar UCharMin = (0);

		/**
		* char 型の最大値（符号なし）
		*/
		static const uchar UCharMax = (0xff);


		/**
		* short 型の最小値（符号付）
		*/
		static const short ShortMin = (-32768);

		/**
		* short 型の最大値（符号付）
		*/
		static const short ShortMax =   (32767);

		/**
		* short 型の最小値（符号なし）
		*/
		static const ushort UShortMin = (0);

		/**
		* short 型の最大値（符号なし）
		*/
		static const ushort UShortMax = (0xffff);


		/**
		* int 型の最小値（符号付）
		*/
		static const int IntMin = (-2147483647 -1);

		/**
		* int 型の最大値（符号付）
		*/
		static const int IntMax = (2147483647);

		/**
		* int 型の最小値（符号なし）
		*/
		static const uint UIntMin = (0);

		/**
		* int 型の最大値（符号なし）
		*/
		static const uint UIntMax = (0xffffffff);

		/**
		* float  型の最大値
		*/
		static const float FloatMin;

		/**
		* float 型の最大値
		*/
		static const float FloatMax;

		/**
		* float 型の最大値平方根
		*/
		static const float FloatMaxSqrt;

		/**
		* double 型の最大値
		*/
		static const double DoubleMin;

		/**
		* double 型の最大値
		*/
		static const double DoubleMax;


		/**
		* char型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool IsCharRange(T value) {
			return ((value >= CharMin) && (value <= CharMax));
		}

		/**
		* uchar型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool IsUCharRange(T value) {
			return ((value >= UCharMin) && (value <= UCharMax));
		}

		/**
		* short型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool IsShortRange(T value) {
			return ((value >= ShortMin) && (value <= ShortMax));
		}

		/**
		* ushort型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool IsUShortRange(T value) {
			return ((value >= UShortMin) && (value <= UShortMax));
		}

		/**
		* int型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool IsIntRange(T value) {
			return ((value >= IntMin) && (value <= IntMax));
		}

		/**
		* uint型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool IsUIntRange(T value) {
			return ((value >= UIntMin) && (value <= UIntMax));
		}

		/**
		* float型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool IsFloatRange(T value) {
			return ((value >= FloatMin) && (value <= FloatMax));
		}

		/**
		* double型の範囲内にあるかチェック
		* @param value チェックする値
		* @return bool 範囲内ならtrue
		*/
		template<typename T>
		static bool IsDoubleRange(T value) {
			return ((value >= DoubleMin) && (value <= DoubleMax));
		}
	private:
		Limits();//生成禁止
	};
}
#endif