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