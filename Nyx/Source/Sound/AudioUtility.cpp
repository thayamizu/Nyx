#include "PCH/PCH.h"
#include "AudioUtility.h"
#include "WaveFileHeader.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	const double AudioUtility::DefaultBitRate      = 16;

	const double AudioUtility::DefaultSamplingRate = 44100;

	//-------------------------------------------------------------------------------------------------------
	//
	long AudioUtility::VolumeToDecibel(long volume) {
		volume  = Math::Clamp(volume, 1L, 100L);
		return static_cast<long>(33.2 * Math::Log10(volume) * 100);
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	long AudioUtility::DecibelToVolume(long decibel) {
		decibel = Math::Clamp(decibel, -10000L, 10000L);
		return static_cast<long>(Math::Pow(10, (decibel/ 33.2)));
	}

	
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioUtility::BuildWaveFormatEx(WAVEFORMATEX* wfx, const WaveFileHeader& waveHeader){
		//Waveフォーマットのセットアップ
		ZeroMemory(wfx, sizeof(WAVEFORMATEX));
		wfx->wFormatTag      = waveHeader.formatChunk.formatTag;
		wfx->nChannels       = waveHeader.formatChunk.channelNum;
		wfx->wBitsPerSample  = waveHeader.formatChunk.bitsRate;
		wfx->nSamplesPerSec  = waveHeader.formatChunk.samplingRate;
		wfx->nBlockAlign     = waveHeader.formatChunk.blockSize;
		wfx->nAvgBytesPerSec = waveHeader.formatChunk.bytesPerSec;
		wfx->cbSize          = sizeof(WAVEFORMATEX);
	}
}