#include "PCH/PCH.h"
#include "AudioUtility.h"

namespace Nyx {
	const double AudioUtility::DefaultBitRate      = 16;
	const double AudioUtility::DefaultSamplingRate = 44100;

	double AudioUtility::VolumeToDecibel(const double volume) {
		return 1.0;
	}
	
	double AudioUtility::DecibelToVolume(const double decibel) {
		return 1.0;
	}
}