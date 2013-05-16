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
	//	//Wave�t�@�C���w�b�_�ǂݎ��
	//	file->Read(&waveHeader_, sizeof(WaveFileHeader)); 

	//	//Wave�f�[�^�̓ǂݎ��
	//	const int waveDataSize = waveHeader_.dataChunk.chunkSize;
	//	char * buffer = new char[waveDataSize];
	//	file->Read(buffer, waveDataSize); 

	//	//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
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
		//Wave�t�@�C���w�b�_�ǂݎ��
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
		//�o�b�t�@������
		char * buffer = new char[bufferSize];
		ZeroMemory(buffer, bufferSize);

		//���݂̃J�[�\���ʒu������ۂɓǂݍ��ރT�C�Y�����肷��
		const auto waveSize = waveHeader_.dataChunk.chunkSize;
		size_t readSize;
		if (waveSize <= (cursor_ + bufferSize)) {
			readSize = waveSize - cursor_;
		}
		else {
			readSize = bufferSize;
		}
		waveFile_->Read(buffer, readSize); 
		
		//�J�[�\���ʒu�����ۂɓǂݍ��񂾃T�C�Y���i�߂�
		SetCursor(cursor_ + readSize);
	
		//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
		auto waveData = std::shared_ptr<char>(
			buffer, std::default_delete<char[]>());
	
		return waveData;
	}
}