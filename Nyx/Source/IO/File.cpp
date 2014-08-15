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
#include "Debug/Assert.h"
#include "IO/File.h"
#include "IO/detail/Win32/Win32File.h"

namespace nyx {
	struct file::PImpl {
		std::unique_ptr<win32_file> file;
	};
	//-----------------------------------------------------------------------------------
	file::file() 
		:pimpl_(new PImpl()) {
			pimpl_->file = std::unique_ptr<win32_file>(new win32_file());
	}

	//-----------------------------------------------------------------------------------
	file::file(const std::wstring& name, FILE_ACCESS_ATTRIBUTE attr) 
		:pimpl_(new PImpl()){
			pimpl_->file = std::unique_ptr<win32_file>(new win32_file(name, attr));
	}

	//-----------------------------------------------------------------------------------
	file::~file() {

	}

	//-----------------------------------------------------------------------------------
	bool file::open(const std::wstring& name, FILE_ACCESS_ATTRIBUTE attr) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->open(name, attr);
	}

	//-----------------------------------------------------------------------------------
	bool  file::close() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->close();
	}

	//-----------------------------------------------------------------------------------
	uint64_t  file::get_current_position() const {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->get_current_position();
	}

	//-----------------------------------------------------------------------------------
	uint64_t  file::get_size() const {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return  pimpl_->file->get_size();
	}

	//-----------------------------------------------------------------------------------
	std::wstring file::get_file_name() const {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->get_file_name();
	}

	//-----------------------------------------------------------------------------------
	file_handle file::get_handle() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->GetHandle();
	}

	//-----------------------------------------------------------------------------------
	uint64_t  file::read(void* buffer, uint64_t size) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->read(buffer, size);
	}

	//-----------------------------------------------------------------------------------
	uint64_t  file::write(void* buffer, uint64_t size) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->write(buffer, size);
	}

	//-----------------------------------------------------------------------------------
	uint64_t  file::seek(long offSet) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->seek(offSet);
	}

	//-----------------------------------------------------------------------------------
	uint64_t  file::seek_begin(long offSet) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->seek_begin(offSet);
	}

	//-----------------------------------------------------------------------------------
	uint64_t  file::seek_end(long offSet) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->seek_end(offSet);
	}

	//-----------------------------------------------------------------------------------
	bool  file::is_opened() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->is_opened();
	}

	//-----------------------------------------------------------------------------------
	bool file::flush() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->file != nullptr);
		return pimpl_->file->flush();
	}
}