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
	AudioDesc desc;
	std::shared_ptr<DirectSoundAudioManager> manager_;
};

DirectSoundAudioManagerTest::DirectSoundAudioManagerTest()
	:manager_(nullptr)
{
	desc.apiType = AudioUtility::APIType_DirectSound;
	desc.handle = ::GetConsoleWindow();
	manager_ = std::make_shared<DirectSoundAudioManager>(desc);
}

DirectSoundAudioManagerTest::~DirectSoundAudioManagerTest()
{
	DestroyWindow(desc.handle);
}

void DirectSoundAudioManagerTest::CreateBufferTest() {
	Assert(manager_ != nullptr);

	AudioBufferDesc desc;
	ZeroMemory(&desc, sizeof(AudioBufferDesc));
	desc.algorithm = DS3DALG_HRTF_FULL;
	desc.focusType  = AudioUtility::FocusType_GlobalFocus;
	desc.bufferType = AudioUtility::BufferType_Static3DAudioBuffer;
	auto buffer = manager_->CreateAudioBuffer(g_waveFile, desc);

	buffer->Play(true);
}

void DirectSoundAudioManagerTest::LoadTest() {
	AudioBufferDesc desc;
	ZeroMemory(&desc, sizeof(AudioBufferDesc));
	desc.algorithm = DS3DALG_HRTF_FULL;
	desc.focusType  = AudioUtility::FocusType_GlobalFocus;
	desc.bufferType = AudioUtility::BufferType_Static3DAudioBuffer;
	manager_->Load(L"testcase.txt", desc);
}