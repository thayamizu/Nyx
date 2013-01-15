#ifndef NYX_CORE_INCLUDED_MATH_H_
#define NYX_CORE_INCLUDED_MATH_H_
#include <cmath>

namespace Nyx
{
	class Math  {
	public:
		//--------------------------------------------------------------------------------------
		//数学定数定義
		//--------------------------------------------------------------------------------------
		/**
		* パイ
		*/
		static const float PI;       

		/**
		* ネイピア数
		*/
		static const float E;

		/**
		* パイ/2
		*/
		static const float HalfPI;

		/**
		* パイ/4
		*/
		static const float QuadraplePI;

		/**
		* パイ * 2
		*/
		static const float DoublePI;

		/**
		* パイ * 4
		*/
		static const float QuadrantPI;

		/**
		* イプシロン
		*/
		static const float Epsilon;



		//--------------------------------------------------------------------------------------
		// 単位変換関数
		//--------------------------------------------------------------------------------------
		/**
		* 弧度法へ変換
		* @param deg 度数法の角度
		* @return  float 度数法を弧度法に変換した値
		*/
		static float ToRadian(float deg) {
			return deg * PI / 180.0F ; 
		}

		/**
		* 度数法へ変換
		* @param rad 弧度法
		* @return  float 弧度法を度数法に変換した値
		*/
		static float ToDegree(float rad) {
			return rad * 180.0F / PI;
		}

		//--------------------------------------------------------------------------------------
		// 絶対値
		//--------------------------------------------------------------------------------------
		/**
		* 絶対値を計算する
		* @param  x    絶対値にしたい数字
		* @return 絶対値
		*/
		static int Abs(int x) {
			return ::abs(x);

		}

		/**
		* 絶対値を計算する
		* @param  x　絶対値にしたい数字
		* @return 絶対値
		*/
		static float Abs(float x) {
			return ::fabs(x);
		}

		//--------------------------------------------------------------------------------------
		// 最大値・最小値
		//--------------------------------------------------------------------------------------
		/**
		* 最大値
		* @param x 右辺値
		* @param y 左辺値
		* @return 大きい方を返す
		*/
		static int Max(int x, int y) {
			return (x > y) ? x : y;
		}

		/**
		* 最大値
		* @param x 右辺値
		* @param y 左辺値
		* @return 大きい方を返す
		*/
		static float Max(float x, float y) {
			return (x > y) ? x : y;
		}

		/**
		* 最小値
		* @param x 右辺値
		* @param y 左辺値
		* @return　小さい方を返す
		*/
		static int Min(int x, int y) {
			return  (x > y) ? y : x;
		}

		/**
		* 最小値
		* @param x 右辺値
		* @param y 左辺値
		* @return　小さい方を返す
		*/
		static float Min(float x, float y) {
			return (x > y) ? y : x;
		}

		//--------------------------------------------------------------------------------------
		// 切り上げ・切り捨て
		//--------------------------------------------------------------------------------------
		/**
		* 切り捨て
		* @param x 切り捨てたい数
		* @return 切り捨てた値
		*/
		static float Floor(float x) {
			return ::floorf(x);
		}

		/**
		* 切り上げ
		* @param x 切り上げたい値
		* @return 切り上げた値
		*/  
		static float Ceil(float x) {
			return ::ceilf(x);
		}

		//--------------------------------------------------------------------------------------
		//指数・対数関数
		//--------------------------------------------------------------------------------------
		/**
		* 平方根を計算する
		* @param
		* @return 
		*/
		static float Sqrt(float x) {
			return ::sqrtf(x);
		}

		/**
		* べき乗
		* @param x 底
		* @param y 指数
		* @return xのy乗
		*/
		static float Pow(float x, float y) {
			return ::powf(x, y);
		}
		/**
		* 2のべき乗
		* @param x 指数
		* @return 2のx乗
		*/
		static float Pow2(float x) {
			return ::powf(2.0f, x);
		}

		/**
		* 指数
		* @param x 乗数
		* @return 自然対数の底のx乗
		*/
		static float Exp(float x) {
			return ::expf(x);
		}

		/**
		* 自然対数
		* @param x 自然対数を取る対象値
		* @return 自然対数
		*/ 
		static float Log(float x) {
			return ::logf(x);
		}

		/**
		* 常用対数
		* @param x 常用対数を取る対象値
		* @return 常用対数
		*/ 
		static float Log10(float x) {
			return ::log10f(x);
		}

		/**
		* 2のべき乗かをチェック
		* @param x 
		* @return 2の累乗ならtrue
		*/
		static bool IsPow2(int x) {
			return (x & (x-1)) == 0;
		}


		//--------------------------------------------------------------------------------------
		//三角関数
		//--------------------------------------------------------------------------------------
		/**
		* 正弦
		* @param x 正弦を計算する値
		* @return xの正弦
		*/
		static float Sin(float x) {
			return ::sinf(x);
		}

		/**
		* 余弦
		* @param x 余弦を計算する値
		* @return xの余弦
		*/
		static float Cos(float x) {
			return ::cosf(x);
		}

		/**
		* 正接
		* @param x 正接を計算する値
		* @return xの正接
		*/
		static float Tan(float x) {
			return ::tanf(x);
		}

		/**
		* 双曲正弦
		* @param x 双曲正弦を計算する値
		* @return xの双曲正弦
		*/
		static float Sinh(float x) {
			return ::sinhf(x);  
		}

		/**
		* 双曲余弦
		* @param x 双曲余弦を計算する値
		* @return xの双曲余弦
		*/
		static float Cosh(float x) {
			return ::coshf(x);
		}
		/**
		* 双曲正接
		* @param x 双曲正接を計算する値
		* @return xの双曲正接
		*/
		static float Tanh(float x) {
			return ::tanhf(x);
		}

		/**
		* 逆正弦
		* @param x 逆正弦を計算する値  -1 ～ 1
		* @return xの逆正弦   -π/2～π/2
		*/
		static float Asin(float x) {
			return ::asinf(x);
		}

		/**
		* 逆余弦
		* @param x 逆余弦を計算する値 -1 ～ 1
		* @return xの逆余弦-π/2～π/2
		*/
		static float Acos(float x) {
			return ::acosf(x);
		}

		/**
		* 逆正接
		* @param x 逆正接を計算する値
		* @return xの逆正接  -π/2～π/2
		*/
		static float Atan(float x) {
			return ::atanf(x);
		}

		/**
		* 逆正接
		* @param y 逆正接を計算するy値
		* @param x 逆正接を計算するx値     
		* @return (x,y)の逆正接 -π～π
		*/                         
		static float Atan2(float y, float x) {
			return ::atan2f(y, x);
		}
	};
}
#endif