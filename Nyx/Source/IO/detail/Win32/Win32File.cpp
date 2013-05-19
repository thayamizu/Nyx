/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
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

		//�t�@�C�����̃R�s�[
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