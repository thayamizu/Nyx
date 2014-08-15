#ifndef NYX_CORE_INCLUDED_EXCEPTION_H_
#define NYX_CORE_INCLUDED_EXCEPTION_H_
#include <exception>
#include <stdexcept>
#include <Windows.h>

namespace nyx 
{
	///フォーマット例外
	class format_exception : public std::domain_error
	{
	public:
		/**
		* コンストラクタ
		* @param const char* メッセージ
		*/
		format_exception(const char* message) 
			: std::domain_error(message) {}

		/**
		* 例外メッセージを取得します
		* @return const char* メッセージ
		*/
		const char* get_message() {
			return what();
		}
	};

	///Win32例外
	class win32_exception : public std::domain_error 
	{
	public:
		/**
		* コンストラクタ
		* @param const char* メッセージ
		* @param LRESULT ステータスコード
		*/
		win32_exception(const char* message, LRESULT lr)
			:std::domain_error(message), lResult_(lr) {}

		/**
		* ステータスコードを取得します
		* @return LRESULT ステータスコード
		*/
		LRESULT get_status() {
			return lResult_;
		}

		/**
		* 例外メッセージを取得します
		* @return const char* メッセージ
		*/
		const char* get_message() {
			return what();
		}
	private:
		LRESULT lResult_;
	};

	///COM例外
	class com_exception : public std::domain_error
	{
	public:
		/**
		* コンストラクタ
		* @param const char* メッセージ
		* @param HRESULT ステータスコード
		*/
		com_exception(const char* message, HRESULT hr)
			:std::domain_error(message), hResult_(hr) {}

		/**
		* ステータスコードを取得します
		* @return HRESULT ステータスコード
		*/
		HRESULT get_status() {
			return hResult_;
		}

		/**
		* 例外メッセージを取得します
		* @return const char* メッセージ
		*/
		const char* get_message() {
			return what();
		}
	private:
		HRESULT hResult_;
	};
}
#endif