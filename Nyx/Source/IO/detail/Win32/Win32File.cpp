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

		//�t�@�C�����̃R�s�[
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