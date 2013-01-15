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

namespace Nyx {

	struct Logger::PImpl
	{
		std::unique_ptr<Win32File> logger;
	};
	//-----------------------------------------------------------------------------------
	Logger::Logger() 
		:pimpl_(new PImpl())
	{
		pimpl_->logger = std::unique_ptr<Win32File>(new Win32File());
	}

	//-----------------------------------------------------------------------------------
	Logger::Logger(const tstring& name)
		:pimpl_(new PImpl())
	{
		pimpl_->logger = std::unique_ptr<Win32File>(new Win32File(name));

	}

	//-----------------------------------------------------------------------------------
	Logger::~Logger() {
	}

	//-----------------------------------------------------------------------------------
	bool Logger::Open(const tstring& name, AccessAttribute attr) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->Open(name, attr);
	}

	//-----------------------------------------------------------------------------------
	bool Logger::Close() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);

		return pimpl_->logger->Close();
	}

	//-----------------------------------------------------------------------------------
	ulong Logger::GetCurrentPosition() const {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->GetCurrentPosition();
	}

	//-----------------------------------------------------------------------------------
	HANDLE Logger::GetHandle() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->GetHandle();
	}

	//-----------------------------------------------------------------------------------
	ulong Logger:: GetSize() const {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->GetSize();
	}

	//-----------------------------------------------------------------------------------
	tstring Logger::GetFileName() const {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->GetFileName();
	}

	//-----------------------------------------------------------------------------------
	ulong Logger::Read(void* buffer, ulong size) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->Read(buffer, size);
	}

	//-----------------------------------------------------------------------------------
	ulong Logger::Write(void* buffer, ulong size) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->Write(buffer, size);
	}

	//-----------------------------------------------------------------------------------
	ulong Logger::Seek(long offSet) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->Seek(offSet);
	}

	//-----------------------------------------------------------------------------------
	ulong Logger::SeekBegin(long offSet) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->SeekBegin(offSet);
	}

	//-----------------------------------------------------------------------------------
	ulong Logger::SeekEnd(long offSet) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->SeekEnd(offSet);
	}

	//-----------------------------------------------------------------------------------
	bool Logger::IsOpened() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->IsOpened();
	}

	//-----------------------------------------------------------------------------------
	bool Logger::Flush() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		return pimpl_->logger->Flush();
	}

	//-----------------------------------------------------------------------------------
	void Logger::Print(char* message) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		pimpl_->logger->Write(message,  ::strlen(message));
		pimpl_->logger->Flush();

	}

	//-----------------------------------------------------------------------------------
	void Logger::Printf(const char* format,...) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		va_list list;
		va_start(list, format);
		static const int length = 1024;
		static char tmp[length];
		vsprintf_s(tmp, length, format, list);
		Print(tmp); 
		va_end(list);

	}

	//-----------------------------------------------------------------------------------
	void Logger::PrintLn(char* message) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		pimpl_->logger->Write(message, ::strlen(message));       
		pimpl_->logger->Write("\r\n", sizeof("\r\n")); 
		pimpl_->logger->Flush();
	}

	//-----------------------------------------------------------------------------------
	void Logger::PrintfLn(const char* format,...) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->logger != nullptr);
		va_list list;
		va_start(list, format);
		static const int length = 1024;
		static char tmp[length];
		vsprintf_s(tmp, length, format, list);
		PrintLn(tmp); 
		va_end(list);
	}

	//-----------------------------------------------------------------------------------
	void Logger::PrintThickLine() {
		PrintLn("===========================================================");
	}

	//-----------------------------------------------------------------------------------
	void Logger::PrintThinLine() {
		PrintLn("-----------------------------------------------------------");
	}
}