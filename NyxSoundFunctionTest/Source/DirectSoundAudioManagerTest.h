#pragma once
#include "PCH.h"
#include "Sound/AudioUtility.h"
#include "Sound/DirectSoundAudioManager.h"

using namespace Nyx;
class DirectSoundAudioManagerTest
{
public:
	DirectSoundAudioManagerTest();
	~DirectSoundAudioManagerTest();
	void CreateBufferTest();
	void LoadTest();
private:
	std::shared_ptr<DirectSoundAudioManager> manager_;
};

DirectSoundAudioManagerTest::DirectSoundAudioManagerTest()
{
}

DirectSoundAudioManagerTest::~DirectSoundAudioManagerTest()
{
}