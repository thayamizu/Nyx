#include "PCH/PCH.h"
#include "WaveReader.h"
#include "OggReader.h"

namespace nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	ogg_reader::ogg_reader() {}


	//-------------------------------------------------------------------------------------------------------
	//
	ogg_reader::ogg_reader(const std::wstring& fileName) {
		fileName;

	}


	//-------------------------------------------------------------------------------------------------------
	//
	void ogg_reader::open(const std::wstring& fileName) {
		fileName;
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
		return header;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<char> ogg_reader::read(size_t bufferSize, uint64_t *readBytes) {
		bufferSize=0, readBytes=0;
		return  nullptr;
	}
}