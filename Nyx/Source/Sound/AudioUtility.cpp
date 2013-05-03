#include "PCH/PCH.h"
#include "AudioUtility.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	const double AudioUtility::DefaultBitRate      = 16;

	const double AudioUtility::DefaultSamplingRate = 44100;

	//-------------------------------------------------------------------------------------------------------
	//
	long AudioUtility::VolumeToDecibel(long volume) {
		volume  = Math::Clamp(volume, 1L, 100L);
		return 33.2 * Math::Log10(volume) * 100;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	long AudioUtility::DecibelToVolume(long decibel) {
		decibel = Math::Clamp(decibel, -10000L, 10000L);
		return Math::Pow(10, (decibel/ 33.2));
	}
}