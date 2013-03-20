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

namespace Nyx
{

	struct PackedFile::PImpl
	{
		uint packedFileNum_; ///パックされたファイル数
		ulong headerSize_;	 ///ヘッダサイズ
		std::unique_ptr<File> packedFile_;///パックされたファイル
		std::map<uint , ulong> packedSize_;   ///パックされたファイル毎のサイズ
		std::map<uint , std::shared_ptr<char>  > packedData_;///パックされたファイルごとのデータ

	};
	//----------------------------------------------------------------------------------------------------
	//
	PackedFile::PackedFile(const wchar_t*  name, AccessAttribute attr)
	{
		pimpl_ = unique_ptr<PImpl>(new PImpl());
		pimpl_->packedFile_ = unique_ptr<File>(new File(name,attr));

		//ファイル数の読み取り
		int n;
		pimpl_->packedFile_->Read(&n, sizeof(unsigned int));
		pimpl_->packedFileNum_ = n;

		//ヘッダサイズの読み取り
		int headerSize;
		pimpl_->packedFile_->Read(&headerSize,sizeof(unsigned int));
		pimpl_->headerSize_ = headerSize;

		//情報の読み取り
		for (uint i=0; i < pimpl_->packedFileNum_; ++i) {

			//ファイル名の取得
			char path[255];
			memset(path, 0, sizeof(path));
			pimpl_->packedFile_->Read(path, sizeof(path));

			//オフセットの取得
			long offset=0;
			pimpl_->packedFile_->Read(&offset, sizeof(unsigned int));

			//ファイルサイズの取得
			long size=0;
			pimpl_->packedFile_->Read(&size, sizeof(unsigned int));

			//現在のオフセットを記憶する
			ulong current=pimpl_->packedFile_->GetCurrentPosition();
			std::shared_ptr<char> packedData = std::shared_ptr<char>(new char[255]);
			memset(&packedData, 0, size+1);
			pimpl_->packedFile_->SeekBegin(offset);
			pimpl_->packedFile_->Read(&packedData, size);

			pimpl_->packedSize_.insert( std::map<uint, ulong>::value_type(i, size));
			pimpl_->packedData_.insert( std::map<uint, std::shared_ptr<char> >::value_type(i, packedData));

			//シーク位置をもとに戻す
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