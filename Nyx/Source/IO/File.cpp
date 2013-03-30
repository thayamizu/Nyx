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