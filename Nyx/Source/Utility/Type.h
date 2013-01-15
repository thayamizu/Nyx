#ifndef NYX_CORE_INCLUDED_TYPE_H_
#define NYX_CORE_INCLUDED_TYPE_H_
#include <string>
#include <sstream>

namespace Nyx
{
	///----------------------------------------------------------------------------------
	///型の別名定義
	///----------------------------------------------------------------------------------
	/**
	* unsigned charの別名定義
	*/
	typedef unsigned char uchar;

	/**
	* unsigned shortの別名定義
	*/
	typedef unsigned short ushort;

	/**
	* unsigned intの別名定義
	*/
	typedef unsigned int uint;

	/**
	* unsigned longの別名定義
	*/
	typedef unsigned long ulong;
	
	/**
	* std::basic_string<TCHAR>の別名定義
	*/
	typedef std::basic_string<TCHAR> tstring;

	/**
	* std::basic_stringstream<TCHAR>の別名定義
	*/
	typedef std::basic_stringstream<TCHAR> tstringstream;
}

#endif