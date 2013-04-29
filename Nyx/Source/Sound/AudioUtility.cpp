#include "PCH/PCH.h"
#include "AudioUtility.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	const double AudioUtility::DefaultBitRate      = 16;
	const double AudioUtility::DefaultSamplingRate = 44100;


	//-------------------------------------------------------------------------------------------------------
	//
	float AudioUtility::VolumeToDecibel(const float volume) {
		const double v = Math::Clamp(volume, 1.0f, 0.02f);
		return 33.2 * Math::Log10(v) * 100;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	float AudioUtility::DecibelToVolume(const float decibel) {
		return Math::Pow(10, (decibel / 100 / 33.2));
	}
}