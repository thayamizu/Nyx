#include "PCH/PCH.h"
#include "WaveReader.h"
#include "OggReader.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	OggReader::OggReader() {}


	//-------------------------------------------------------------------------------------------------------
	//
	OggReader::OggReader(const std::wstring& fileName) {
		fileName;

	}


	//-------------------------------------------------------------------------------------------------------
	//
	void OggReader::Open(const std::wstring& fileName) {
		fileName;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void OggReader::SetCursor(ulong cursor) {
		cursor=0;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	ulong OggReader::GetCursor() const{
			return 1;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	const WaveFileHeader& OggReader::ReadHeader() {
		return header;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<char> OggReader::Read(size_t bufferSize) {
		bufferSize=0;
		return  nullptr;
	}
}