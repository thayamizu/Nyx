#ifndef NYX_CORE_INCLUDED_TYPE_H_
#define NYX_CORE_INCLUDED_TYPE_H_
#include <string>
#include <sstream>

namespace Nyx
{
	///----------------------------------------------------------------------------------
	///�^�̕ʖ���`
	///----------------------------------------------------------------------------------
	/**
	* unsigned char�̕ʖ���`
	*/
	typedef unsigned char uchar;

	/**
	* unsigned short�̕ʖ���`
	*/
	typedef unsigned short ushort;

	/**
	* unsigned int�̕ʖ���`
	*/
	typedef unsigned int uint;

	/**
	* unsigned long�̕ʖ���`
	*/
	typedef unsigned long ulong;
	
	/**
	* std::basic_string<TCHAR>�̕ʖ���`
	*/
	typedef std::basic_string<TCHAR> tstring;

	/**
	* std::basic_stringstream<TCHAR>�̕ʖ���`
	*/
	typedef std::basic_stringstream<TCHAR> tstringstream;
}

#endif