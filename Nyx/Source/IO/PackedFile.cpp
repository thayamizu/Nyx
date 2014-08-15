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
#include "IO/PackedFile.h"

namespace nyx
{

	struct packed_file::PImpl
	{
		uint32_t packedFileNum_; ///パックされたファイル数
		uint64_t headerSize_;	 ///ヘッダサイズ
		std::unique_ptr<file> packedFile_;///パックされたファイル
		std::map<uint32_t , uint64_t> packedSize_;   ///パックされたファイル毎のサイズ
		std::map<uint32_t , std::shared_ptr<char>  > packedData_;///パックされたファイルごとのデータ

	};
	//----------------------------------------------------------------------------------------------------
	//
	packed_file::packed_file(const wchar_t*  name, FILE_ACCESS_ATTRIBUTE attr)
	{
		pimpl_ = unique_ptr<PImpl>(new PImpl());
		pimpl_->packedFile_ = unique_ptr<file>(new file(name,attr));

		//ファイル数の読み取り
		int n;
		pimpl_->packedFile_->read(&n, sizeof(unsigned int));
		pimpl_->packedFileNum_ = n;

		//ヘッダサイズの読み取り
		int headerSize;
		pimpl_->packedFile_->read(&headerSize,sizeof(unsigned int));
		pimpl_->headerSize_ = headerSize;

		//情報の読み取り
		for (uint32_t i=0; i < pimpl_->packedFileNum_; ++i) {

			//ファイル名の取得
			char path[255];
			memset(path, 0, sizeof(path));
			pimpl_->packedFile_->read(path, sizeof(path));

			//オフセットの取得
			long offset=0;
			pimpl_->packedFile_->read(&offset, sizeof(unsigned int));

			//ファイルサイズの取得
			long size=0;
			pimpl_->packedFile_->read(&size, sizeof(unsigned int));

			//現在のオフセットを記憶する
			uint64_t current=pimpl_->packedFile_->get_current_position();
			std::shared_ptr<char> packedData = std::shared_ptr<char>(new char[255]);
			memset(&packedData, 0, size+1);
			pimpl_->packedFile_->seek_begin(offset);
			pimpl_->packedFile_->read(&packedData, size);

			pimpl_->packedSize_.insert( std::map<uint32_t, uint64_t>::value_type(i, size));
			pimpl_->packedData_.insert( std::map<uint32_t, std::shared_ptr<char> >::value_type(i, packedData));

			//シーク位置をもとに戻す
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