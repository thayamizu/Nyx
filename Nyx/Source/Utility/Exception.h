#ifndef NYX_CORE_INCLUDED_EXCEPTION_H_
#define NYX_CORE_INCLUDED_EXCEPTION_H_
#include <exception>
#include <stdexcept>
#include <Windows.h>

namespace nyx 
{
	///�t�H�[�}�b�g��O
	class format_exception : public std::domain_error
	{
	public:
		/**
		* �R���X�g���N�^
		* @param const char* ���b�Z�[�W
		*/
		format_exception(const char* message) 
			: std::domain_error(message) {}

		/**
		* ��O���b�Z�[�W���擾���܂�
		* @return const char* ���b�Z�[�W
		*/
		const char* get_message() {
			return what();
		}
	};

	///Win32��O
	class win32_exception : public std::domain_error 
	{
	public:
		/**
		* �R���X�g���N�^
		* @param const char* ���b�Z�[�W
		* @param LRESULT �X�e�[�^�X�R�[�h
		*/
		win32_exception(const char* message, LRESULT lr)
			:std::domain_error(message), lResult_(lr) {}

		/**
		* �X�e�[�^�X�R�[�h���擾���܂�
		* @return LRESULT �X�e�[�^�X�R�[�h
		*/
		LRESULT get_status() {
			return lResult_;
		}

		/**
		* ��O���b�Z�[�W���擾���܂�
		* @return const char* ���b�Z�[�W
		*/
		const char* get_message() {
			return what();
		}
	private:
		LRESULT lResult_;
	};

	///COM��O
	class com_exception : public std::domain_error
	{
	public:
		/**
		* �R���X�g���N�^
		* @param const char* ���b�Z�[�W
		* @param HRESULT �X�e�[�^�X�R�[�h
		*/
		com_exception(const char* message, HRESULT hr)
			:std::domain_error(message), hResult_(hr) {}

		/**
		* �X�e�[�^�X�R�[�h���擾���܂�
		* @return HRESULT �X�e�[�^�X�R�[�h
		*/
		HRESULT get_status() {
			return hResult_;
		}

		/**
		* ��O���b�Z�[�W���擾���܂�
		* @return const char* ���b�Z�[�W
		*/
		const char* get_message() {
			return what();
		}
	private:
		HRESULT hResult_;
	};
}
#endif