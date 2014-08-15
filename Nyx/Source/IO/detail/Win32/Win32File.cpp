/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#include "PCH/PCH.h"
#include "Win32File.h"
namespace nyx {

	//-----------------------------------------------------------------------------------
	win32_file::win32_file() 
		:handle(INVALID_HANDLE_VALUE),attribute(FILE_ACCESS_ATTRIBUTE_NUM), fileName(TEXT("")) {
	}


	//-----------------------------------------------------------------------------------
	win32_file::win32_file(const std::wstring& name, FILE_ACCESS_ATTRIBUTE attr) 
		:handle(NULL), attribute(attr), fileName(name) {
		try {
			if (!open(name, attr)) {
				throw std::domain_error("file can't open!");
			}
		}
		catch(std::exception e) {
			throw e;
		}
	}


	//-----------------------------------------------------------------------------------
	win32_file::~win32_file() {
		if (is_opened()) { close();}
	}
	

	//-----------------------------------------------------------------------------------
	bool win32_file::open(const std::wstring& name, FILE_ACCESS_ATTRIBUTE attr) {
		if (is_opened()) { close();}

		uint64_t openType = NULL;
		switch(attr) {
		case FILE_ACCESS_ATTRIBUTE_READ:
			openType = OPEN_EXISTING;
			break;
		case FILE_ACCESS_ATTRIBUTE_WRITE:
			openType = CREATE_ALWAYS;
			break;
		case FILE_ACCESS_ATTRIBUTE_READ_WRITE:
			openType = OPEN_EXISTING;
			break;
		default:
			return false;
		} 

		handle = ::CreateFile(name.c_str(), attr, FILE_SHARE_READ,  NULL, openType, FILE_ATTRIBUTE_NORMAL, NULL);
		if (handle == INVALID_HANDLE_VALUE) {
			return false;
		}

		//ファイル名のコピー
		fileName = name;

		return true;
	}

	//-----------------------------------------------------------------------------------
	bool  win32_file::close() {
		return CloseHandle(handle) != 0;
	}

	//-----------------------------------------------------------------------------------
	uint64_t  win32_file::get_current_position() const {
		return ::SetFilePointer(handle, 0, NULL, FILE_CURRENT); 
	}

	//-----------------------------------------------------------------------------------
	uint64_t  win32_file::get_size() const {
		return  ::GetFileSize(handle, NULL);
	}

	//-----------------------------------------------------------------------------------
	std::wstring win32_file::get_file_name() const {
		return fileName;
	}

	//-----------------------------------------------------------------------------------
	HANDLE win32_file::GetHandle() {
		return handle;
	}

	//-----------------------------------------------------------------------------------
	uint64_t  win32_file::read(void* buffer, uint64_t size) {
		if (handle == INVALID_HANDLE_VALUE) {
			return 0;
		}
		uint64_t readBytes;
		::ReadFile(handle, buffer, size, &readBytes, NULL); 
		return readBytes;
	}

	//-----------------------------------------------------------------------------------
	uint64_t  win32_file::write(void* buffer, uint64_t size) {
		if (handle == INVALID_HANDLE_VALUE) {
			return 0;
		}
		uint64_t writeBytes;
		::WriteFile(handle, buffer, size, &writeBytes, NULL); 

		return writeBytes;
	}

	//-----------------------------------------------------------------------------------
	uint64_t  win32_file::seek(long offSet) {
		if (handle == INVALID_HANDLE_VALUE) {
			return 0;
		}
		return ::SetFilePointer(handle, offSet, NULL, FILE_CURRENT);
	}

	//-----------------------------------------------------------------------------------
	uint64_t  win32_file::seek_begin(long offSet) {
		if (handle == INVALID_HANDLE_VALUE) {
			return 0;
		}
		return ::SetFilePointer(handle, offSet, NULL, FILE_BEGIN);
	}

	//-----------------------------------------------------------------------------------
	uint64_t  win32_file::seek_end(long offSet) {
		if (handle == INVALID_HANDLE_VALUE) {
			return 0;
		}
		return ::SetFilePointer(handle, offSet, NULL, FILE_END);
	}

	//-----------------------------------------------------------------------------------
	bool  win32_file::is_opened() {
		return handle != INVALID_HANDLE_VALUE;
	}

	//-----------------------------------------------------------------------------------
	bool win32_file::flush() {
		return FlushFileBuffers(handle) != 0;
	}
}