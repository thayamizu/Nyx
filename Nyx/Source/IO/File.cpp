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

namespace Nyx {
	struct File::PImpl {
		std::unique_ptr<Win32File> file;
	};
	//-----------------------------------------------------------------------------------
	File::File() 
		:pimpl_(new PImpl()) {
			pimpl_->file = std::unique_ptr<Win32File>(new Win32File());
	}

	//-----------------------------------------------------------------------------------
	File::File(const std::wstring& name, AccessAttribute attr) 
		:pimpl_(new PImpl()){
			pimpl_->file = std::unique_ptr<Win32File>(new Win32File(name, attr));
	}

	//-----------------------------------------------------------------------------------
	File::~File() {

	}

	//-----------------------------------------------------------------------------------
	bool File::Open(const std::wstring& name, AccessAttribute attr) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->Open(name, attr);
	}

	//-----------------------------------------------------------------------------------
	bool  File::Close() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->Close();
	}

	//-----------------------------------------------------------------------------------
	ulong  File::GetCurrentPosition() const {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->GetCurrentPosition();
	}

	//-----------------------------------------------------------------------------------
	ulong  File::GetSize() const {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return  pimpl_->file->GetSize();
	}

	//-----------------------------------------------------------------------------------
	std::wstring File::GetFileName() const {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->GetFileName();
	}

	//-----------------------------------------------------------------------------------
	HANDLE File::GetHandle() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->GetHandle();
	}

	//-----------------------------------------------------------------------------------
	ulong  File::Read(void* buffer, ulong size) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->Read(buffer, size);
	}

	//-----------------------------------------------------------------------------------
	ulong  File::Write(void* buffer, ulong size) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->Write(buffer, size);
	}

	//-----------------------------------------------------------------------------------
	ulong  File::Seek(long offSet) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->Seek(offSet);
	}

	//-----------------------------------------------------------------------------------
	ulong  File::SeekBegin(long offSet) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->SeekBegin(offSet);
	}

	//-----------------------------------------------------------------------------------
	ulong  File::SeekEnd(long offSet) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->SeekEnd(offSet);
	}

	//-----------------------------------------------------------------------------------
	bool  File::IsOpened() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->IsOpened();
	}

	//-----------------------------------------------------------------------------------
	bool File::Flush() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->file != nullptr);
		return pimpl_->file->Flush();
	}
}