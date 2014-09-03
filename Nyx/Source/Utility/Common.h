#pragma once
#include "Utility/Type.h"

//機能廃止宣言
#if defined(_MSC_VER)
#define NYX_DEPRECATED __declspec(deprecated) 
#elif defined(__GNUC__)
#define NYX_DEPRECATED 
#define NYX_DEPRECATED __attribute__((deprecated))
#else
#pragma message("DEPRECATEDはサポートされていません")
#endif

///----------------------------------------------------------------------------------
/// boost::intrusive_ptr
///----------------------------------------------------------------------------------
inline void intrusive_ptr_add_ref( IUnknown* ptr ) {
	if (ptr != nullptr) {
		ptr->AddRef();
	}
}


inline void intrusive_ptr_release( IUnknown* ptr ) {
	if (ptr != nullptr) {
		ptr->Release();
	}
}

namespace nyx {


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
	std::wstring to_string(T value) {
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
	char to_char(T value) {
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
	short to_short(T value) {
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
	int to_int(T value) {
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
	float to_float(T value) {
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
	double to_double(T value) {
		double result;
		std::stringstream ss;

		ss << value;
		ss >> result;

		return result;
	}

};
