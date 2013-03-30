#pragma once
#include "Utility/Type.h"

//機能廃止宣言
#if defined(_MSC_VER)
#define DEPRECATED __declspec(deprecated) 
#elif defined(__GNUC__)
#define DEPRECATED 
#define DEPRECATED __attribute__((deprecated))
#else
#pragma message("DEPRECATEDはサポートされていません")
#endif

namespace Nyx {
	///----------------------------------------------------------------------------------
	/// 安全な解放処理
	///----------------------------------------------------------------------------------
	/**
	* ポインタの安全な削除
	* @param item 削除対象ポインタ
	*/
	template <typename T> 
	inline void SafeDelete(T*& item) {
		if (item != NULL) {
			delete item; 
		}
		item = NULL;
	}

	/**
	* 配列の安全な削除
	* @param item 削除対象ポインタ
	*/
	template <typename T>
	inline void SafeDeleteArray(T*& item) {
		delete[] item; 
		item = NULL;

	}

	/**
	* オブジェクトの安全な解放
	* @param item 削除対象ポインタ
	*/
	template <typename T>
	inline void SafeRelease(T*& item) {
		if ( item != NULL) {
			item->Release();
			item = NULL;
		}
	}

	///------------------------------------------------------
	///基本型の変換関数
	///-------------------------------------------------------
	/**
	* 数値型から文字列への変換
	* @param T 変換元の値
	* @return 文字列された数値
	*/
	template <typename T> 
	inline std::wstring ToString(T value) {
		std::wstringstream ss;
		ss<<value;

		return ss.str();
	}
	/**
	* char型への変換
	* @param T 変換元の値 
	* @return int 変換された値
	*/
	template <typename T> 
	inline char ToChar(T value) {
		char result;
		std::stringstream ss;

		ss << value;
		ss >> result;

		return result-'0';
	}

	/**
	* short型への変換
	* @param  T 変換元の値
	* @return short 変換された値
	*/  
	template <typename T> 
	inline short ToShort(T value) {
		short result;
		std::stringstream ss;

		ss << value;
		ss >> result;

		return result;
	}
	/**
	* int型への変換
	* @param  T 変換元の値
	* @return int 変換された値
	*/
	template <typename T> 
	inline int ToInt(T value) {
		int result;
		std::stringstream ss;

		ss << value;
		ss >> result;

		return result;
	}

	/**
	* float型への変換
	* @param  T 変換元の値
	* @return float 変換された値
	*/
	template <typename T> 
	inline float ToFloat(T value) {
		float result;
		std::stringstream ss;

		ss << value;
		ss >> result;

		return result;
	}
	/**
	* double型への変換
	* @param  T 変換元の値
	* @return double 変換された値
	*/ 
	template <typename T> 
	inline double ToDouble(T value) {
		double result;
		std::stringstream ss;

		ss << value;
		ss >> result;

		return result;
	}

};
