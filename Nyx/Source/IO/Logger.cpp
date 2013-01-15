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