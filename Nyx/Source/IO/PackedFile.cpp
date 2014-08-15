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

namespace nyx
{

	struct packed_file::PImpl
	{
		uint32_t packedFileNum_; ///�p�b�N���ꂽ�t�@�C����
		uint64_t headerSize_;	 ///�w�b�_�T�C�Y
		std::unique_ptr<file> packedFile_;///�p�b�N���ꂽ�t�@�C��
		std::map<uint32_t , uint64_t> packedSize_;   ///�p�b�N���ꂽ�t�@�C�����̃T�C�Y
		std::map<uint32_t , std::shared_ptr<char>  > packedData_;///�p�b�N���ꂽ�t�@�C�����Ƃ̃f�[�^

	};
	//----------------------------------------------------------------------------------------------------
	//
	packed_file::packed_file(const wchar_t*  name, FILE_ACCESS_ATTRIBUTE attr)
	{
		pimpl_ = unique_ptr<PImpl>(new PImpl());
		pimpl_->packedFile_ = unique_ptr<file>(new file(name,attr));

		//�t�@�C�����̓ǂݎ��
		int n;
		pimpl_->packedFile_->read(&n, sizeof(unsigned int));
		pimpl_->packedFileNum_ = n;

		//�w�b�_�T�C�Y�̓ǂݎ��
		int headerSize;
		pimpl_->packedFile_->read(&headerSize,sizeof(unsigned int));
		pimpl_->headerSize_ = headerSize;

		//���̓ǂݎ��
		for (uint32_t i=0; i < pimpl_->packedFileNum_; ++i) {

			//�t�@�C�����̎擾
			char path[255];
			memset(path, 0, sizeof(path));
			pimpl_->packedFile_->read(path, sizeof(path));

			//�I�t�Z�b�g�̎擾
			long offset=0;
			pimpl_->packedFile_->read(&offset, sizeof(unsigned int));

			//�t�@�C���T�C�Y�̎擾
			long size=0;
			pimpl_->packedFile_->read(&size, sizeof(unsigned int));

			//���݂̃I�t�Z�b�g���L������
			uint64_t current=pimpl_->packedFile_->get_current_position();
			std::shared_ptr<char> packedData = std::shared_ptr<char>(new char[255]);
			memset(&packedData, 0, size+1);
			pimpl_->packedFile_->seek_begin(offset);
			pimpl_->packedFile_->read(&packedData, size);

			pimpl_->packedSize_.insert( std::map<uint32_t, uint64_t>::value_type(i, size));
			pimpl_->packedData_.insert( std::map<uint32_t, std::shared_ptr<char> >::value_type(i, packedData));

			//�V�[�N�ʒu�����Ƃɖ߂�
			pimpl_->packedFile_->seek_begin(current);

		}
	}

	//----------------------------------------------------------------------------------------------------
	//
	packed_file::~packed_file()
	{

	}
	//----------------------------------------------------------------------------------------------------
	//
	uint64_t packed_file::get_header_size() {
		return  pimpl_->headerSize_;
	}

	//----------------------------------------------------------------------------------------------------
	//
	uint32_t packed_file::get_file_num() {
		return pimpl_->packedFileNum_;
	}

	//----------------------------------------------------------------------------------------------------
	//
	uint64_t packed_file::get_file_size(uint32_t index) {
		return pimpl_->packedSize_[index];
	}

	//----------------------------------------------------------------------------------------------------
	//
	shared_ptr<char> packed_file::get_file_data(uint32_t index) {
		return pimpl_->packedData_[index];

	}
	//----------------------------------------------------------------------------------------------------
	//
	bool packed_file::open(const std::wstring&  name, FILE_ACCESS_ATTRIBUTE attr)
	{
		return pimpl_->packedFile_->open(name, attr);
	}
	//----------------------------------------------------------------------------------------------------
	//
	bool packed_file::close()
	{
		return pimpl_->packedFile_->close();
	}
	bool packed_file::flush()
	{
		return pimpl_->packedFile_->flush();
	}
	//----------------------------------------------------------------------------------------------------
	//
	uint64_t packed_file::get_current_position()
		const
	{
		return pimpl_->packedFile_->get_current_position();
	}

	//----------------------------------------------------------------------------------------------------
	//
	uint64_t packed_file::get_size()
		const
	{
		return pimpl_->packedFile_->get_size();
	}

	//----------------------------------------------------------------------------------------------------
	//
	std::wstring packed_file::get_file_name()
		const
	{
		return pimpl_->packedFile_->get_file_name();
	}

	//----------------------------------------------------------------------------------------------------
	//
	uint64_t packed_file::read(void* buffer, uint64_t size)
	{
		return pimpl_->packedFile_->read(buffer, size);
	}

	//----------------------------------------------------------------------------------------------------
	//
	uint64_t packed_file::write(void* buffer, uint64_t size)
	{
		return pimpl_->packedFile_->write(buffer, size);
	}

	//----------------------------------------------------------------------------------------------------
	//
	uint64_t packed_file::seek(long offSet)
	{
		return pimpl_->packedFile_->seek(offSet);
	}

	//----------------------------------------------------------------------------------------------------
	//
	uint64_t packed_file::seek_begin(long offSet)
	{
		return pimpl_->packedFile_->seek_begin(offSet);
	}

	//----------------------------------------------------------------------------------------------------
	//
	uint64_t packed_file::seek_end(long offSet)
	{
		return pimpl_->packedFile_->seek_end(offSet);
	}

	//----------------------------------------------------------------------------------------------------
	//
	bool packed_file::is_opened()
	{
		return pimpl_->packedFile_->is_opened();
	}

}