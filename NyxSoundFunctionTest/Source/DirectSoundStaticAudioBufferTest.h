#pragma once
#include "PCH.h"
#include "Sound/AudioUtility.h"
#include "Sound/DirectSoundAudioManager.h"
#include "Sound/DirectSoundStaticAudioBuffer.h"

using namespace Nyx;
extern const std::wstring g_waveFile;
class DirectSoundStaticAudioBufferTest {
public:
	DirectSoundStaticAudioBufferTest()
		: hwnd_(nullptr), audio_(nullptr), manager_(nullptr)
	{
		hwnd_ = ::GetConsoleWindow();

		AudioDesc desc;
		desc.handle = hwnd_;
		desc.apiType = AudioUtility::APIType_DirectSound;
		manager_ = std::shared_ptr<AudioManager>(new AudioManager(desc));
	}

	~DirectSoundStaticAudioBufferTest() {
		::DestroyWindow(hwnd_);
	}

	void Test() {
		LoadStaticAudio();
		Play();
		Thread::Sleep(2000);
		Stop();
		Thread::Sleep(2000);
		Resume();
		Thread::Sleep(2000);
		Play();
		Thread::Sleep(2000);
		Reset();
		Thread::Sleep(2000);
		Play();
	}

	
	void LoadStaticAudio() {
		Assert(manager_!=nullptr)
		AudioBufferDesc desc;
		ZeroMemory(&desc, sizeof(AudioBufferDesc));
		desc.algorithm = DS3DALG_DEFAULT;
		desc.focusType  = AudioUtility::FocusType_GlobalFocus;
		desc.bufferType = AudioUtility::BufferType_StaticAudioBuffer;
		audio_ = manager_->CreateAudioBuffer(g_waveFile, desc);
	}
	void Play() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@���Đ����܂�...");
		audio_->Play(true);
	}
	void Stop() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@���~���܂�...");
		audio_->Stop();
	}
	void Resume() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�����W���[�����܂�...");
		audio_->Resume();
	}
	void Reset() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�����Z�b�g���܂�...");
		audio_->Reset();
	}

private:
	HWND hwnd_;
	std::shared_ptr<IAudioBuffer>  audio_;
	std::shared_ptr<AudioManager> manager_;
};