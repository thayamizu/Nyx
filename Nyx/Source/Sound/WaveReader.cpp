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

		//RIFF�w�b�_(4byte) �ǂݎ��
		file->Read(&buffer, 4); 
		//				Assert(buffer == "RIFF");
		if (strncmp(buffer, "RIFF", 4) == 0) {
			file->Read(&riffChunk_, sizeof(RIFFChunk)); 
		}

		//WAVE�w�b�_(4byte) �ǂݎ��
		file->Read(&buffer, 4);
		if (strncmp(buffer, "WAVE", 4) != 0 ) {
			exit(-1);
		}

		//�`�����N���̓ǂݎ��
		while (file->GetCurrentPosition() < riffChunk_.fileSize) {
			file->Read(&buffer, 4);
			if (strncmp(buffer, "fmt ",4) == 0) {
				file->Read(&fmtChunk_, sizeof(FmtChunk));
			}
			else if (strncmp(buffer, "data", 4) ==0) {
				//�f�[�^�`�����N�̃T�C�Y���擾
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

		//RIFF�w�b�_(4byte) �ǂݎ��
		memcpy(buffer, &*waveData, 4); offset += 4;
		//				Assert(buffer == "RIFF");
		if (strncmp(buffer, "RIFF", 4) == 0) {
			memcpy(&riffChunk_, (void*)(&*waveData + offset), sizeof(RIFFChunk)); 
			offset += sizeof(RIFFChunk); 
		}

		//WAVE�w�b�_(4byte) �ǂݎ��
		memcpy(buffer, (void*)(&*waveData + offset), 4); offset += 4;
		//		Assert(buffer == "WAVE");
		//�`�����N���̓ǂݎ��
		while (offset < riffChunk_.fileSize) {
			memcpy(buffer, (void*)(&*waveData + offset), 4); offset += 4;
			if (strncmp(buffer, "fmt ",4) == 0) {
				memcpy(&fmtChunk_, (void*)(&*waveData + offset), sizeof(FmtChunk));
				offset += sizeof(FmtChunk);
			}
			else if (strncmp(buffer, "data", 4) ==0) {
				//�f�[�^�`�����N�̃T�C�Y���擾
				memcpy(&dataChunk_.chunkSize, (void*)(&*waveData + offset), 4); offset += 4;
				dataChunk_.waveData = new uchar[dataChunk_.chunkSize];
				memcpy(dataChunk_.waveData, (void*)(&*waveData + offset), dataChunk_.chunkSize);
				offset += dataChunk_.chunkSize;

			}
			else {
				//fmt, data�ȊO�̃`�����N����ǂݔ�΂�
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
		printf("\t\tfmt�`�����N�T�C�Y  = %ld\n", fmtChunk_.chunkSize);
		printf("\t\t�t�H�[�}�b�g�^�O   = %hd\n", fmtChunk_.formatTag);
		printf("\t\t�`�����l����       = %d\n", fmtChunk_.channelNum);
		printf("\t\t�T���v�����O���[�g = %d\n", fmtChunk_.samplingRate);
		printf("\t\t�f�[�^���x         = %d\n", fmtChunk_.bytesPerSec);
		printf("\t\t�r�b�g���[�g       = %d\n", fmtChunk_.bitsRate);
		printf("<data>\n");
		printf("Data�`�����N�T�C�Y     = %d\n", dataChunk_.chunkSize);
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