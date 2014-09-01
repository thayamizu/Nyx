#include "PCH/PCH.h"
#include "AudioUtility.h"
#include "OggReader.h"
#include "Debug/DebugOutput.h"
#include "Debug/Assert.h"
#pragma comment(lib, "libogg_static.lib")
#pragma comment(lib, "libvorbis_static.lib")
#pragma comment(lib, "libvorbisfile_static.lib")
namespace nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	ogg_reader::ogg_reader()
		:fileName_(L""), waveHeader_(), vorbisFile_(), vorbisInfo_()
	{

	}


	//-------------------------------------------------------------------------------------------------------
	//
	ogg_reader::ogg_reader(const std::wstring& fileName)
		:fileName_(fileName), waveHeader_(), vorbisFile_(), vorbisInfo_()

	{
		open(fileName_);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	ogg_reader::~ogg_reader()
	{
		close();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void ogg_reader::open(const std::wstring& fileName) {
		FILE * fp = _wfopen(fileName.c_str(), L"rb");
		if (fp == NULL) {
			fclose(fp);
		}
		NYX_ASSERT(fp != NULL);
		if (ov_open(fp, &vorbisFile_, NULL, NULL) < 0) {
			fclose(fp);
		}
		vorbisInfo_ = *ov_info(&vorbisFile_, -1);

		auto timeLength = ov_time_total(&vorbisFile_, -1);
		fileSize_ = timeLength * (vorbisInfo_.rate * 2 * 2);
	}

	void ogg_reader::close()
	{
		ov_clear(&vorbisFile_);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void ogg_reader::set_cursor(uint64_t cursor) {
		const auto size = waveHeader_.dataChunk.chunkSize;
		cursor_ += cursor;
		if (size <= cursor) {
			cursor_ = 0;
			::ov_pcm_seek(&vorbisFile_, 0);
		}
		//::ov_pcm_seek(&vorbisFile_, cursor_);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	uint64_t ogg_reader::get_cursor() const{
		return cursor_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	const wav_file_header& ogg_reader::read_header() {
		memcpy(waveHeader_.riffID, "RIFF", 4);
		memcpy(waveHeader_.waveID, "WAVE", 4);
		memcpy(waveHeader_.formatChunk.formatChunkID, "fmt ", 4);
		memcpy(waveHeader_.dataChunk.dataChunkID, "data", 4);

		waveHeader_.formatChunk.channelNum = vorbisInfo_.channels;
		waveHeader_.formatChunk.chunkSize = 16;
		waveHeader_.formatChunk.samplingRate = vorbisInfo_.rate;
		waveHeader_.formatChunk.bytesPerSec = vorbisInfo_.rate * 2 * 2;
		waveHeader_.formatChunk.blockSize = 2 * 2;
		waveHeader_.formatChunk.bitsRate = 16;
		waveHeader_.formatChunk.formatTag = 1;
		waveHeader_.dataChunk.chunkSize = fileSize_;
		waveHeader_.fileSize = fileSize_;

		return waveHeader_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<char> ogg_reader::read(size_t bufferSize, uint64_t *readBytes) {
		char* buffer = new char[bufferSize];
		int requestSize(bufferSize);
		int bitStream(0);
		long readSize(0);
		uint32_t comSize(0);
		while (true) {
			readSize = ov_read(&vorbisFile_, buffer + comSize, requestSize, 0, 2, 1, &bitStream);
			// �Ȃ��I����Ă�
			if (!readSize) {
				ov_pcm_seek(&vorbisFile_, 0);
				break;
			}

			// �������񂾃T�C�Y��������
			comSize += readSize;
			
			// �g�`�f�[�^�z��̎��̏������݈ʒu���o�b�t�@�T�C�Y�𒴂��Ă��烋�[�v�𔲂���
			if (comSize >= bufferSize) {
				break;
			}
			// �o�b�t�@��S����������łȂ������玟�̏������ݗv���T�C�Y���o�b�t�@�T�C�Y���珑�����񂾃T�C�Y�����������̂ɂ���
			if (bufferSize - comSize < 4096) {
				requestSize = bufferSize - comSize;
			}
		}
		*readBytes = comSize;
		//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
		return std::shared_ptr<char>(
			buffer, std::default_delete<char[]>());
	}
}