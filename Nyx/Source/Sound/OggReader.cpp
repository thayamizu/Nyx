#include "PCH/PCH.h"
#include "WaveReader.h"
#include "OggReader.h"

namespace nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	ogg_reader::ogg_reader() {
		
	}


	//-------------------------------------------------------------------------------------------------------
	//
	ogg_reader::ogg_reader(const std::wstring& fileName) {
		fileName;

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
	/*	FILE * fp = _wfopen(fileName.c_str(), L"rb");
		if (fp == NULL) {
			fclose(fp);
		}

		if (ov_open(fp, &vf) < 0) {
			fclose(fp);
		}

		vorbis_info* vi;
		vi = ov_info(&vf, -1);
		if (vi == NULL) {
			return -1;
		}
*/
	}

	void ogg_reader::close()
	{
		if (vorbisFile_ != nullptr) {
			//ov_clear(&(vorbisFile_.get()));
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void ogg_reader::set_cursor(uint64_t cursor) {
		cursor=0;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	uint64_t ogg_reader::get_cursor() const{
			return 1;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	const wav_file_header& ogg_reader::read_header() {
		return this->header_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<char> ogg_reader::read(size_t bufferSize, uint64_t *readBytes) {
		bufferSize=0, readBytes=0;
		return  nullptr;
	}
}