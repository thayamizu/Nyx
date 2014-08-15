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