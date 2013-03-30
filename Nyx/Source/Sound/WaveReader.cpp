#include "PCH/PCH.h"
#include "IO/File.h"
#include "Sound/WaveReader.h"
namespace Nyx {
	using std::unique_ptr;
	using std::shared_ptr;

	//-------------------------------------------------------------------------------------------------------
	//
	WaveReader::WaveReader() {

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
	void WaveReader::ReadFromFile(std::wstring fileName) {
		char buffer[4] = {};
		unique_ptr<File> file = unique_ptr<File>(new File(fileName, Nyx::ReadMode));

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
	void WaveReader::ReadFromMem(shared_ptr<char> waveData) {
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
	void WaveReader::PrintHeaderInfo()
	{
		printf("[RIFF] (%ld)\n", riffChunk_.fileSize);
		printf("[WAVE]\n");
		printf("<fmt>\n");
		printf("\t\tfmtチャンクサイズ  = %ld\n", fmtChunk_.chunkSize);
		printf("\t\tフォーマットタグ   = %hd\n", fmtChunk_.formatTag);
		printf("\t\tチャンネル数       = %d\n", fmtChunk_.channelNum);
		printf("\t\tサンプリングレート = %d\n", fmtChunk_.samplingRate);
		printf("\t\tデータ速度         = %d\n", fmtChunk_.bytesPerSec);
		printf("\t\tビットレート       = %d\n", fmtChunk_.bitsRate);
		printf("<data>\n");
		printf("Dataチャンクサイズ     = %d\n", dataChunk_.chunkSize);
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