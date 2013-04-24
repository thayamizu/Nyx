#include "PCH/PCH.h"
#include "IO/File.h"
#include "Sound/WaveReader.h"
namespace Nyx {

	//-------------------------------------------------------------------------------------------------------
	//
	WaveReader::WaveReader() {
		::ZeroMemory((void*)&riffChunk_, sizeof(RIFFChunk));
		::ZeroMemory((void*)&fmtChunk_,  sizeof(FmtChunk));
		::ZeroMemory((void*)&dataChunk_, sizeof(DataChunk));
	}

	//-------------------------------------------------------------------------------------------------------
	//
	WaveReader::~WaveReader() {
		if (dataChunk_.waveData !=NULL) { 
			SafeDelete(dataChunk_.waveData);
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void WaveReader::ReadFromFile(const std::wstring& fileName) {
		char buffer[4] = {};
		std::unique_ptr<File> file(new File(fileName, Nyx::ReadMode));

		//RIFFヘッダ(4byte) 読み取り
		file->Read(&buffer, 4); 
		//				Assert(buffer == "RIFF");
		if (strncmp(buffer, "RIFF", 4) == 0) {
			file->Read(&riffChunk_, sizeof(RIFFChunk)); 
		}

		//WAVEヘッダ(4byte) 読み取り
		file->Read(&buffer, 4);
		if (strncmp(buffer, "WAVE", 4) != 0 ) {
			exit(-1);
		}

		//チャンク情報の読み取り
		while (file->GetCurrentPosition() < riffChunk_.fileSize) {
			file->Read(&buffer, 4);
			if (strncmp(buffer, "fmt ",4) == 0) {
				file->Read(&fmtChunk_, sizeof(FmtChunk));
			}
			else if (strncmp(buffer, "data", 4) ==0) {
				//データチャンクのサイズを取得
				file->Read(&dataChunk_.chunkSize, 4); 
				dataChunk_.waveData = new uchar[dataChunk_.chunkSize];
				file->Read(dataChunk_.waveData, dataChunk_.chunkSize);
			}
			else {
				file->Seek(4);
			}
		}

	}

	//-------------------------------------------------------------------------------------------------------
	//
	void WaveReader::ReadFromMem(std::shared_ptr<uchar> waveData) {
		ulong offset = 0;
		char buffer[4]={};

		//RIFFヘッダ(4byte) 読み取り
		memcpy(buffer, &*waveData, 4); offset += 4;
		//				Assert(buffer == "RIFF");
		if (strncmp(buffer, "RIFF", 4) == 0) {
			memcpy(&riffChunk_, (void*)(&*waveData + offset), sizeof(RIFFChunk)); 
			offset += sizeof(RIFFChunk); 
		}

		//WAVEヘッダ(4byte) 読み取り
		memcpy(buffer, (void*)(&*waveData + offset), 4); offset += 4;
		//		Assert(buffer == "WAVE");
		//チャンク情報の読み取り
		while (offset < riffChunk_.fileSize) {
			memcpy(buffer, (void*)(&*waveData + offset), 4); offset += 4;
			if (strncmp(buffer, "fmt ",4) == 0) {
				memcpy(&fmtChunk_, (void*)(&*waveData + offset), sizeof(FmtChunk));
				offset += sizeof(FmtChunk);
			}
			else if (strncmp(buffer, "data", 4) ==0) {
				//データチャンクのサイズを取得
				memcpy(&dataChunk_.chunkSize, (void*)(&*waveData + offset), 4); offset += 4;
				dataChunk_.waveData = new uchar[dataChunk_.chunkSize];
				memcpy(dataChunk_.waveData, (void*)(&*waveData + offset), dataChunk_.chunkSize);
				offset += dataChunk_.chunkSize;

			}
			else {
				//fmt, data以外のチャンク情報を読み飛ばす
				offset += 4;
			}
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void WaveReader::GetRiffChunk(RIFFChunk* riff) {
		*riff= riffChunk_;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void  WaveReader::GetFmtChunk(FmtChunk* fmt) {
		*fmt = fmtChunk_;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void  WaveReader::GetDataChunk(DataChunk* data) {
		*data = dataChunk_;
	}
}