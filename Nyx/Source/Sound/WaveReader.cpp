#include "PCH/PCH.h"
#include "IO/File.h"
#include "Sound/WaveReader.h"

class format_error : public std::domain_error
{
public:
	format_error(const char* message) 
		: std::domain_error(message) {}
};

class com_error : public std::runtime_error
{
public:
	com_error(const char* message, HRESULT hr)
		:std::runtime_error(message), hResult(hr) {}
	HRESULT get_status() {
		return hResult;
	}
private:
	HRESULT hResult;
};

namespace Nyx {

	//-------------------------------------------------------------------------------------------------------
	//
	WaveReader::WaveReader() 
		:waveData_(nullptr)
	{
		::ZeroMemory((void*)&waveHeader_, sizeof(WaveFileHeader));
	}

	WaveReader::WaveReader(const std::wstring& fileName) 
		:waveData_(nullptr)
	{
		::ZeroMemory((void*)&waveHeader_, sizeof(WaveFileHeader));

		ReadFromFile(fileName);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	WaveReader::~WaveReader() {
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void WaveReader::ReadFromFile(const std::wstring& fileName) {
		std::unique_ptr<File> file(new File(fileName, Nyx::ReadMode));
	
		//Waveファイルヘッダ読み取り
		file->Read(&waveHeader_, sizeof(WaveFileHeader)); 
		//フォーマットチェック

		const int waveDataSize = waveHeader_.dataChunk.chunkSize;
		char * buffer = new char[waveDataSize];
		file->Read(buffer, waveDataSize); 

		waveData_ = std::shared_ptr<char>(
			buffer, std::default_delete<char[]>());
		
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void WaveReader::ReadFromMem(char* waveData) {
		::memcpy(&waveHeader_, waveData, sizeof(WaveFileHeader));

		const int waveDataSize = waveHeader_.dataChunk.chunkSize;
		char * buffer = new char[waveDataSize];
		memcpy(buffer,(waveData + sizeof(WaveFileHeader)), waveDataSize); 

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