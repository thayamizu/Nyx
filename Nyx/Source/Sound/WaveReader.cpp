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
#include "Debug/DebugOutput.h"
#include "IO/File.h"
#include "WaveFileHeader.h"
#include "WaveReader.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	WaveReader::WaveReader() 
		: isReadHeader_(false), waveFile_(nullptr), cursor_(0), fileName_(L"") {
		::ZeroMemory((void*)&waveHeader_, sizeof(WaveFileHeader));
	}


	//-------------------------------------------------------------------------------------------------------
	//
	WaveReader::WaveReader(const std::wstring& fileName) 
		: isReadHeader_(false), waveFile_(nullptr), cursor_(0), fileName_(fileName) {
		::ZeroMemory((void*)&waveHeader_, sizeof(WaveFileHeader));

		Open(fileName);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void WaveReader::Open(const std::wstring& fileName) {
		fileName_ = fileName;
		waveFile_ = std::make_shared<File>(fileName);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void WaveReader::SetCursor(ulong cursor) {
		cursor_ = cursor;
		const auto waveSize = waveHeader_.dataChunk.chunkSize;
		if (waveSize <= cursor_) {
			cursor_ = 0;
		} 
	}


	//-------------------------------------------------------------------------------------------------------
	//
	ulong WaveReader::GetCursor() const {
		return cursor_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	//void WaveReader::ReadFromFile(const std::wstring& fileName) {
	//	std::unique_ptr<File> file(new File(fileName, Nyx::ReadMode));
	//
	//	//Waveファイルヘッダ読み取り
	//	file->Read(&waveHeader_, sizeof(WaveFileHeader)); 

	//	//Waveデータの読み取り
	//	const int waveDataSize = waveHeader_.dataChunk.chunkSize;
	//	char * buffer = new char[waveDataSize];
	//	file->Read(buffer, waveDataSize); 

	//	//スマートポインタの管理下に置く
	//	waveData_ = std::shared_ptr<char>(
	//		buffer, std::default_delete<char[]>());
	//}


	//-------------------------------------------------------------------------------------------------------
	//
	const WaveFileHeader& WaveReader::ReadHeader() {
		Assert(waveFile_->IsOpened());
		if (isReadHeader_) {
			return waveHeader_;
		}
		//Waveファイルヘッダ読み取り
		waveFile_->Read(&waveHeader_, sizeof(WaveFileHeader)); 

		return waveHeader_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<char> WaveReader::Read(const size_t bufferSize){
		Assert(waveFile_->IsOpened());
		if (!isReadHeader_) {
			ReadHeader();
		} 
		//バッファ初期化
		char * buffer = new char[bufferSize];
		ZeroMemory(buffer, bufferSize);

		//現在のカーソル位置から実際に読み込むサイズを決定する
		const auto waveSize = waveHeader_.dataChunk.chunkSize;
		size_t readSize;
		if (waveSize <= (cursor_ + bufferSize)) {
			readSize = waveSize - cursor_;
		}
		else {
			readSize = bufferSize;
		}
		waveFile_->Read(buffer, readSize); 
		
		//カーソル位置を実際に読み込んだサイズ分進める
		SetCursor(cursor_ + readSize);
	
		//スマートポインタの管理下に置く
		auto waveData = std::shared_ptr<char>(
			buffer, std::default_delete<char[]>());
	
		return waveData;
	}
}