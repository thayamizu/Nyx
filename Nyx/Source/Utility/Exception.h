#ifndef NYX_CORE_INCLUDED_EXCEPTION_H_
#define NYX_CORE_INCLUDED_EXCEPTION_H_
#include <exception>
#include <stdexcept>
#include <Windows.h>

namespace Nyx 
{
	///フォーマット例外
	class FormatException : public std::domain_error
	{
	public:
		/**
		* コンストラクタ
		* @param const char* メッセージ
		*/
		FormatException(const char* message) 
			: std::domain_error(message) {}

		/**
		* 例外メッセージを取得します
		* @return const char* メッセージ
		*/
		const char* GetMessage() {
			return what();
		}
	};

	///Win32例外
	class Win32Exception : public std::domain_error 
	{
	public:
		/**
		* コンストラクタ
		* @param const char* メッセージ
		* @param LRESULT ステータスコード
		*/
		Win32Exception(const char* message, LRESULT lr)
			:std::domain_error(message), lResult_(lr) {}

		/**
		* ステータスコードを取得します
		* @return LRESULT ステータスコード
		*/
		LRESULT GetStatus() {
			return lResult_;
		}

		/**
		* 例外メッセージを取得します
		* @return const char* メッセージ
		*/
		const char* GetMessage() {
			return what();
		}
	private:
		LRESULT lResult_;
	};

	///COM例外
	class COMException : public std::domain_error
	{
	public:
		/**
		* コンストラクタ
		* @param const char* メッセージ
		* @param HRESULT ステータスコード
		*/
		COMException(const char* message, HRESULT hr)
			:std::domain_error(message), hResult_(hr) {}

		/**
		* ステータスコードを取得します
		* @return HRESULT ステータスコード
		*/
		HRESULT GetStatus() {
			return hResult_;
		}

		/**
		* 例外メッセージを取得します
		* @return const char* メッセージ
		*/
		const char* GetMessage() {
			return what();
		}
	private:
		HRESULT hResult_;
	};
}
#endif