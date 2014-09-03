#pragma once
#include "Utility/Type.h"

//�@�\�p�~�錾
#if defined(_MSC_VER)
#define NYX_DEPRECATED __declspec(deprecated) 
#elif defined(__GNUC__)
#define NYX_DEPRECATED 
#define NYX_DEPRECATED __attribute__((deprecated))
#else
#pragma message("DEPRECATED�̓T�|�[�g����Ă��܂���")
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
	/// ���S�ȉ������
	///----------------------------------------------------------------------------------
	/**
	* �|�C���^�̈��S�ȍ폜
	* @param item �폜�Ώۃ|�C���^
	*/
	template <typename T> 
	inline void SafeDelete(T*& item) {
		if (item != NULL) {
			delete item; 
		}
		item = NULL;
	}

	/**
	* �z��̈��S�ȍ폜
	* @param item �폜�Ώۃ|�C���^
	*/
	template <typename T>
	inline void SafeDeleteArray(T*& item) {
		delete[] item; 
		item = NULL;

	}

	/**
	* �I�u�W�F�N�g�̈��S�ȉ��
	* @param item �폜�Ώۃ|�C���^
	*/
	template <typename T>
	inline void SafeRelease(T*& item) {
		if ( item != NULL) {
			item->Release();
			item = NULL;
		}
	}

	///------------------------------------------------------
	///��{�^�̕ϊ��֐�
	///-------------------------------------------------------
	/**
	* ���l�^���當����ւ̕ϊ�
	* @param T �ϊ����̒l
	* @return �����񂳂ꂽ���l
	*/
	template <typename T> 
	std::wstring to_string(T value) {
		std::wstringstream ss;
		ss<<value;

		return ss.str();
	}
	/**
	* char�^�ւ̕ϊ�
	* @param T �ϊ����̒l 
	* @return int �ϊ����ꂽ�l
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
	* short�^�ւ̕ϊ�
	* @param  T �ϊ����̒l
	* @return short �ϊ����ꂽ�l
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
	* int�^�ւ̕ϊ�
	* @param  T �ϊ����̒l
	* @return int �ϊ����ꂽ�l
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
	* float�^�ւ̕ϊ�
	* @param  T �ϊ����̒l
	* @return float �ϊ����ꂽ�l
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
	* double�^�ւ̕ϊ�
	* @param  T �ϊ����̒l
	* @return double �ϊ����ꂽ�l
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
