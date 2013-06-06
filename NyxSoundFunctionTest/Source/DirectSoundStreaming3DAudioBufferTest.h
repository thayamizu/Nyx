#pragma once
#include "PCH.h"
#include "Sound/AudioUtility.h"
#include "Sound/DirectSoundAudioManager.h"
#include "Sound/DirectSoundStreaming3DAudioBuffer.h"

using namespace Nyx;
extern const std::wstring g_waveFile;
class DirectSoundStreaming3DAudioBufferTest {
public:
	DirectSoundStreaming3DAudioBufferTest()
		: hwnd_(nullptr), audio_(nullptr), manager_(nullptr)
	{
		hwnd_ = ::GetConsoleWindow();

		AudioDesc desc;
		desc.handle = hwnd_;
		desc.apiType = AudioUtility::APIType_DirectSound;
		manager_ = std::shared_ptr<AudioManager>(new AudioManager(desc));
	}

	~DirectSoundStreaming3DAudioBufferTest() {
		::DestroyWindow(hwnd_);
	}

	void Test() {
		LoadStaticAudio();
		Play();
		audio_->SetVolume(100);
		Thread::Sleep(1000);
	std::cout << audio_->GetVolume() << std::endl;
		
		audio_->SetVolume(75);
		Thread::Sleep(1000);
	std::cout << audio_->GetVolume() << std::endl;

		
		audio_->SetVolume(50);
		Thread::Sleep(1000);
	std::cout << audio_->GetVolume() << std::endl;

		
		audio_->SetVolume(25);
		Thread::Sleep(1000);
	std::cout << audio_->GetVolume() << std::endl;

		
		audio_->SetVolume(0);
		Thread::Sleep(1000);
	std::cout << audio_->GetVolume() << std::endl;


	}

	
	void LoadStaticAudio() {
		Assert(manager_!=nullptr)
		AudioBufferDesc desc;
		ZeroMemory(&desc, sizeof(AudioBufferDesc));
		desc.algorithm = DS3DALG_HRTF_FULL;
		desc.focusType  = AudioUtility::FocusType_GlobalFocus;
		desc.bufferType = AudioUtility::BufferType_Streaming3DAudioBuffer;
		audio_ = manager_->CreateAudioBuffer(g_waveFile, desc);
	}
	void Play() {
		DebugOutput::Trace("オーディオバッファを再生します...");
		audio_->Play(true);
	}
	void Stop() {
		DebugOutput::Trace("オーディオバッファを停止します...");
		audio_->Stop();
	}
	void Resume() {
		DebugOutput::Trace("オーディオバッファをレジュームします...");
		audio_->Resume();
	}
	void Reset() {
		DebugOutput::Trace("オーディオバッファをリセットします...");
		audio_->Reset();
	}

private:
	HWND hwnd_;
	std::shared_ptr<IAudioBuffer>  audio_;
	std::shared_ptr<AudioManager> manager_;
};