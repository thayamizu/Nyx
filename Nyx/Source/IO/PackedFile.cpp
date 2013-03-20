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
#include "IO/PackedFile.h"

namespace Nyx
{

	struct PackedFile::PImpl
	{
		uint packedFileNum_; ///�p�b�N���ꂽ�t�@�C����
		ulong headerSize_;	 ///�w�b�_�T�C�Y
		std::unique_ptr<File> packedFile_;///�p�b�N���ꂽ�t�@�C��
		std::map<uint , ulong> packedSize_;   ///�p�b�N���ꂽ�t�@�C�����̃T�C�Y
		std::map<uint , std::shared_ptr<char>  > packedData_;///�p�b�N���ꂽ�t�@�C�����Ƃ̃f�[�^

	};
	//----------------------------------------------------------------------------------------------------
	//
	PackedFile::PackedFile(const wchar_t*  name, AccessAttribute attr)
	{
		pimpl_ = unique_ptr<PImpl>(new PImpl());
		pimpl_->packedFile_ = unique_ptr<File>(new File(name,attr));

		//�t�@�C�����̓ǂݎ��
		int n;
		pimpl_->packedFile_->Read(&n, sizeof(unsigned int));
		pimpl_->packedFileNum_ = n;

		//�w�b�_�T�C�Y�̓ǂݎ��
		int headerSize;
		pimpl_->packedFile_->Read(&headerSize,sizeof(unsigned int));
		pimpl_->headerSize_ = headerSize;

		//���̓ǂݎ��
		for (uint i=0; i < pimpl_->packedFileNum_; ++i) {

			//�t�@�C�����̎擾
			char path[255];
			memset(path, 0, sizeof(path));
			pimpl_->packedFile_->Read(path, sizeof(path));

			//�I�t�Z�b�g�̎擾
			long offset=0;
			pimpl_->packedFile_->Read(&offset, sizeof(unsigned int));

			//�t�@�C���T�C�Y�̎擾
			long size=0;
			pimpl_->packedFile_->Read(&size, sizeof(unsigned int));

			//���݂̃I�t�Z�b�g���L������
			ulong current=pimpl_->packedFile_->GetCurrentPosition();
			std::shared_ptr<char> packedData = std::shared_ptr<char>(new char[255]);
			memset(&packedData, 0, size+1);
			pimpl_->packedFile_->SeekBegin(offset);
			pimpl_->packedFile_->Read(&packedData, size);

			pimpl_->packedSize_.insert( std::map<uint, ulong>::value_type(i, size));
			pimpl_->packedData_.insert( std::map<uint, std::shared_ptr<char> >::value_type(i, packedData));

			//�V�[�N�ʒu�����Ƃɖ߂�
			pimpl_->packedFile_->SeekBegin(current);

		}
	}

	//----------------------------------------------------------------------------------------------------
	//
	PackedFile::~PackedFile()
	{

	}
	//----------------------------------------------------------------------------------------------------
	//
	ulong PackedFile::GetHeaderSize() {
		return  pimpl_->headerSize_;
	}

	//----------------------------------------------------------------------------------------------------
	//
	uint PackedFile::GetFileNum() {
		return pimpl_->packedFileNum_;
	}

	//----------------------------------------------------------------------------------------------------
	//
	ulong PackedFile::GetFileSize(uint index) {
		return pimpl_->packedSize_[index];
	}

	//----------------------------------------------------------------------------------------------------
	//
	shared_ptr<char> PackedFile::GetFileData(uint index) {
		return pimpl_->packedData_[index];

	}
	//----------------------------------------------------------------------------------------------------
	//
	bool PackedFile::Open(const std::wstring&  name, AccessAttribute attr)
	{
		return pimpl_->packedFile_->Open(name, attr);
	}
	//----------------------------------------------------------------------------------------------------
	//
	bool PackedFile::Close()
	{
		return pimpl_->packedFile_->Close();
	}
	bool PackedFile::Flush()
	{
		return pimpl_->packedFile_->Flush();
	}
	//----------------------------------------------------------------------------------------------------
	//
	ulong PackedFile::GetCurrentPosition()
		const
	{
		return pimpl_->packedFile_->GetCurrentPosition();
	}

	//----------------------------------------------------------------------------------------------------
	//
	ulong PackedFile::GetSize()
		const
	{
		return pimpl_->packedFile_->GetSize();
	}

	//----------------------------------------------------------------------------------------------------
	//
	std::wstring PackedFile::GetFileName()
		const
	{
		return pimpl_->packedFile_->GetFileName();
	}

	//----------------------------------------------------------------------------------------------------
	//
	ulong PackedFile::Read(void* buffer, ulong size)
	{
		return pimpl_->packedFile_->Read(buffer, size);
	}

	//----------------------------------------------------------------------------------------------------
	//
	ulong PackedFile::Write(void* buffer, ulong size)
	{
		return pimpl_->packedFile_->Write(buffer, size);
	}

	//----------------------------------------------------------------------------------------------------
	//
	ulong PackedFile::Seek(long offSet)
	{
		return pimpl_->packedFile_->Seek(offSet);
	}

	//----------------------------------------------------------------------------------------------------
	//
	ulong PackedFile::SeekBegin(long offSet)
	{
		return pimpl_->packedFile_->SeekBegin(offSet);
	}

	//----------------------------------------------------------------------------------------------------
	//
	ulong PackedFile::SeekEnd(long offSet)
	{
		return pimpl_->packedFile_->SeekEnd(offSet);
	}

	//----------------------------------------------------------------------------------------------------
	//
	bool PackedFile::IsOpened()
	{
		return pimpl_->packedFile_->IsOpened();
	}

}