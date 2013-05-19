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
		const auto size = waveHeader_.dataChunk.chunkSize;
		cursor_ += cursor;
		if (size <= cursor) {
			cursor_ = 0;
		}
		waveFile_->SeekBegin(sizeof(WaveFileHeader) + cursor_);
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

		//�t�H�[�}�b�g�`�F�b�N
		if (strncmp(waveHeader_.riffID, "RIFF", 4) != 0) {
			DebugOutput::Trace("Wave�t�@�C���̃t�H�[�}�b�g���s���ł��BRIFF�`�����N������������܂���B");
			throw FormatException("Wave�t�@�C���̃t�H�[�}�b�g���s���ł��BRIFF�`�����N������������܂���B");
		}
		else if (strncmp(waveHeader_.waveID, "WAVE", 4) != 0) {
			DebugOutput::Trace("Wave�t�@�C���̃t�H�[�}�b�g���s���ł��BWAVE�^�O������������܂���B");
			throw FormatException("Wave�t�@�C���̃t�H�[�}�b�g���s���ł��BWAVE�^�O������������܂���B");
		}
		else if (strncmp(waveHeader_.formatChunk.formatChunkID, "fmt ", 4) != 0) {
			DebugOutput::Trace("Wave�t�@�C���̃t�H�[�}�b�g���s���ł��Bfmt�`�����N������������܂���B");
			throw FormatException("Wave�t�@�C���̃t�H�[�}�b�g���s���ł��Bfmt�`�����N������������܂���B");
		}
		else if (strncmp(waveHeader_.dataChunk.dataChunkID, "data", 4) != 0) {
			DebugOutput::Trace("Wave�t�@�C���̃t�H�[�}�b�g���s���ł��Bdata�`�����N������������܂���B");
			throw FormatException("Wave�t�@�C���̃t�H�[�}�b�g���s���ł��Bdata�`�����N������������܂���B");
		}

		isReadHeader_= true;
		return waveHeader_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<char> WaveReader::Read(const size_t bufferSize, ulong* readSize){
		Assert(waveFile_->IsOpened());
		if (!isReadHeader_) {
			ReadHeader();
		} 
		const auto size = waveHeader_.dataChunk.chunkSize;
		if (size < (cursor_ + bufferSize)) {
			*readSize = size - cursor_;
		}
		else {
			*readSize = bufferSize;
		}

		//�o�b�t�@������
		char * buffer = new char[*readSize];
		waveFile_->Read(buffer, *readSize); 

		//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
		return std::shared_ptr<char>(
			buffer, std::default_delete<char[]>());
	}
}