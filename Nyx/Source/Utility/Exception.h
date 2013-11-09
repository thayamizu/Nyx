#ifndef NYX_CORE_INCLUDED_EXCEPTION_H_
#define NYX_CORE_INCLUDED_EXCEPTION_H_
#include <exception>
#include <stdexcept>
#include <Windows.h>

namespace Nyx 
{
	///�t�H�[�}�b�g��O
	class FormatException : public std::domain_error
	{
	public:
		/**
		* �R���X�g���N�^
		* @param const char* ���b�Z�[�W
		*/
		FormatException(const char* message) 
			: std::domain_error(message) {}

		/**
		* ��O���b�Z�[�W���擾���܂�
		* @return const char* ���b�Z�[�W
		*/
		const char* GetMessage() {
			return what();
		}
	};

	///Win32��O
	class Win32Exception : public std::domain_error 
	{
	public:
		/**
		* �R���X�g���N�^
		* @param const char* ���b�Z�[�W
		* @param LRESULT �X�e�[�^�X�R�[�h
		*/
		Win32Exception(const char* message, LRESULT lr)
			:std::domain_error(message), lResult_(lr) {}

		/**
		* �X�e�[�^�X�R�[�h���擾���܂�
		* @return LRESULT �X�e�[�^�X�R�[�h
		*/
		LRESULT GetStatus() {
			return lResult_;
		}

		/**
		* ��O���b�Z�[�W���擾���܂�
		* @return const char* ���b�Z�[�W
		*/
		const char* GetMessage() {
			return what();
		}
	private:
		LRESULT lResult_;
	};

	///COM��O
	class COMException : public std::domain_error
	{
	public:
		/**
		* �R���X�g���N�^
		* @param const char* ���b�Z�[�W
		* @param HRESULT �X�e�[�^�X�R�[�h
		*/
		COMException(const char* message, HRESULT hr)
			:std::domain_error(message), hResult_(hr) {}

		/**
		* �X�e�[�^�X�R�[�h���擾���܂�
		* @return HRESULT �X�e�[�^�X�R�[�h
		*/
		HRESULT GetStatus() {
			return hResult_;
		}

		/**
		* ��O���b�Z�[�W���擾���܂�
		* @return const char* ���b�Z�[�W
		*/
		const char* GetMessage() {
			return what();
		}
	private:
		HRESULT hResult_;
	};
}
#endif