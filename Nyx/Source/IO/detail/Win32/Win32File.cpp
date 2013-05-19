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
namespace Nyx {

	//-----------------------------------------------------------------------------------
	Win32File::Win32File() 
		:handle(INVALID_HANDLE_VALUE),attribute(None), fileName(TEXT("")) {
	}


	//-----------------------------------------------------------------------------------
	Win32File::Win32File(const std::wstring& name, AccessAttribute attr) 
		:handle(NULL), attribute(attr), fileName(name) {
		try {
			if (!Open(name, attr)) {
				throw std::exception("file can't open!");
			}
		}
		catch(std::exception e) {
			throw e;
		}
	}


	//-----------------------------------------------------------------------------------
	Win32File::~Win32File() {
		if (IsOpened()) { Close();}
	}
	

	//-----------------------------------------------------------------------------------
	bool Win32File::Open(const std::wstring& name, AccessAttribute attr) {
		if (IsOpened()) { Close();}

		ulong openType = NULL;
		switch(attr) {
		case ReadMode:
			openType = OPEN_EXISTING;
			break;
		case WriteMode:
			openType = CREATE_ALWAYS;
			break;
		case ReadWriteMode:
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
	bool  Win32File::Close() {
		return ::CloseHandle(handle);
	}

	//-----------------------------------------------------------------------------------
	ulong  Win32File::GetCurrentPosition() const {
		return ::SetFilePointer(handle, 0, NULL, FILE_CURRENT); 
	}

	//-----------------------------------------------------------------------------------
	ulong  Win32File::GetSize() const {
		return  ::GetFileSize(handle, NULL);
	}

	//-----------------------------------------------------------------------------------
	std::wstring Win32File::GetFileName() const {
		return fileName;
	}

	//-----------------------------------------------------------------------------------
	HANDLE Win32File::GetHandle() {
		return handle;
	}

	//-----------------------------------------------------------------------------------
	ulong  Win32File::Read(void* buffer, ulong size) {
		if (handle == INVALID_HANDLE_VALUE) {
			return 0;
		}
		ulong readBytes;
		::ReadFile(handle, buffer, size, &readBytes, NULL); 
		return readBytes;
	}

	//-----------------------------------------------------------------------------------
	ulong  Win32File::Write(void* buffer, ulong size) {
		if (handle == INVALID_HANDLE_VALUE) {
			return 0;
		}
		ulong writeBytes;
		::WriteFile(handle, buffer, size, &writeBytes, NULL); 

		return writeBytes;
	}

	//-----------------------------------------------------------------------------------
	ulong  Win32File::Seek(long offSet) {
		if (handle == INVALID_HANDLE_VALUE) {
			return 0;
		}
		return ::SetFilePointer(handle, offSet, NULL, FILE_CURRENT);
	}

	//-----------------------------------------------------------------------------------
	ulong  Win32File::SeekBegin(long offSet) {
		if (handle == INVALID_HANDLE_VALUE) {
			return 0;
		}
		return ::SetFilePointer(handle, offSet, NULL, FILE_BEGIN);
	}

	//-----------------------------------------------------------------------------------
	ulong  Win32File::SeekEnd(long offSet) {
		if (handle == INVALID_HANDLE_VALUE) {
			return 0;
		}
		return ::SetFilePointer(handle, offSet, NULL, FILE_END);
	}

	//-----------------------------------------------------------------------------------
	bool  Win32File::IsOpened() {
		return handle != INVALID_HANDLE_VALUE;
	}

	//-----------------------------------------------------------------------------------
	bool Win32File::Flush() {
		return FlushFileBuffers(handle);
	}
}