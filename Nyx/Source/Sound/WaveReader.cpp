#include "PCH/PCH.h"
#include "IO/File.h"
#include "Sound/WaveReader.h"



namespace Nyx {

	//-------------------------------------------------------------------------------------------------------
	//
	WaveReader::WaveReader() 
		:waveData_(nullptr) {
		::ZeroMemory((void*)&waveHeader_, sizeof(WaveFileHeader));
	}


	//-------------------------------------------------------------------------------------------------------
	//
	WaveReader::WaveReader(const std::wstring& fileName) 
		:waveData_(nullptr) {
		::ZeroMemory((void*)&waveHeader_, sizeof(WaveFileHeader));

		ReadFromFile(fileName);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void WaveReader::ReadFromFile(const std::wstring& fileName) {
		std::unique_ptr<File> file(new File(fileName, Nyx::ReadMode));
	
		//Waveファイルヘッダ読み取り
		file->Read(&waveHeader_, sizeof(WaveFileHeader)); 

		const int waveDataSize = waveHeader_.dataChunk.chunkSize;
		char * buffer = new char[waveDataSize];
		file->Read(buffer, waveDataSize); 

		//スマートポインタの管理下に置く
		waveData_ = std::shared_ptr<char>(
			buffer, std::default_delete<char[]>());
		
	}


	//-------------------------------------------------------------------------------------------------------
	//
	const WaveFileHeader& WaveReader::GetFileHeader() {
		return waveHeader_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	const std::shared_ptr<char> WaveReader::GetWaveData() {
		return waveData_;
	}

}