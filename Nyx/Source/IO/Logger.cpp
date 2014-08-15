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
#include "IO/File.h"
#include "IO/Logger.h"
#include "Debug/Assert.h"
#include "IO/detail/Win32/Win32File.h"

namespace nyx {

	struct logger::PImpl
	{
		std::unique_ptr<win32_file> logger;
	};
	//-----------------------------------------------------------------------------------
	logger::logger() 
		:pimpl_(new PImpl())
	{
		pimpl_->logger = std::unique_ptr<win32_file>(new win32_file());
	}

	//-----------------------------------------------------------------------------------
	logger::logger(const std::wstring& name)
		:pimpl_(new PImpl())
	{
		pimpl_->logger = std::unique_ptr<win32_file>(new win32_file(name, FILE_ACCESS_ATTRIBUTE_WRITE));

	}

	//-----------------------------------------------------------------------------------
	logger::~logger() {
	}

	//-----------------------------------------------------------------------------------
	bool logger::open(const std::wstring& name, FILE_ACCESS_ATTRIBUTE attr) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->open(name, attr);
	}

	//-----------------------------------------------------------------------------------
	bool logger::close() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);

		return pimpl_->logger->close();
	}

	//-----------------------------------------------------------------------------------
	uint64_t logger::get_current_position() const {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->get_current_position();
	}

	//-----------------------------------------------------------------------------------
	HANDLE logger::get_handle() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->GetHandle();
	}

	//-----------------------------------------------------------------------------------
	uint64_t logger:: get_size() const {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->get_size();
	}

	//-----------------------------------------------------------------------------------
	std::wstring logger::get_file_name() const {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->get_file_name();
	}

	//-----------------------------------------------------------------------------------
	uint64_t logger::read(void* buffer, uint64_t size) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->read(buffer, size);
	}

	//-----------------------------------------------------------------------------------
	uint64_t logger::write(void* buffer, uint64_t size) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->write(buffer, size);
	}

	//-----------------------------------------------------------------------------------
	uint64_t logger::seek(long offSet) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->seek(offSet);
	}

	//-----------------------------------------------------------------------------------
	uint64_t logger::seek_begin(long offSet) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->seek_begin(offSet);
	}

	//-----------------------------------------------------------------------------------
	uint64_t logger::seek_end(long offSet) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->seek_end(offSet);
	}

	//-----------------------------------------------------------------------------------
	bool logger::is_opened() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->is_opened();
	}

	//-----------------------------------------------------------------------------------
	bool logger::flush() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		return pimpl_->logger->flush();
	}

	//-----------------------------------------------------------------------------------
	void logger::print(char* message) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		pimpl_->logger->write(message,  ::strlen(message));
		pimpl_->logger->flush();

	}

	//-----------------------------------------------------------------------------------
	void logger::printf(const char* format,...) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		va_list list;
		va_start(list, format);
		static const int length = 1024;
		static char tmp[length];
		vsprintf_s(tmp, length, format, list);
		print(tmp); 
		va_end(list);

	}

	//-----------------------------------------------------------------------------------
	void logger::printfln(char* message) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		pimpl_->logger->write(message, ::strlen(message));       
		pimpl_->logger->write("\r\n", sizeof("\r\n")); 
		pimpl_->logger->flush();
	}

	//-----------------------------------------------------------------------------------
	void logger::printfln(const char* format,...) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->logger != nullptr);
		va_list list;
		va_start(list, format);
		static const int length = 1024;
		static char tmp[length];
		vsprintf_s(tmp, length, format, list);
		printfln(tmp); 
		va_end(list);
	}

	//-----------------------------------------------------------------------------------
	void logger::print_thick_line() {
		printfln("===========================================================");
	}

	//-----------------------------------------------------------------------------------
	void logger::print_thin_line() {
		printfln("-----------------------------------------------------------");
	}
}