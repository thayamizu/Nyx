#pragma once
#include "PCH.h"
#include "Sound/AudioUtility.h"
#include "Sound/DirectSoundAudioManager.h"
#include "Sound/DirectSoundStatic3DAudioBuffer.h"

using namespace Nyx;
extern const std::wstring g_waveFile;

class DirectSoundStatic3DAudioBufferTest {
public:
	DirectSoundStatic3DAudioBufferTest()
		: hwnd_(nullptr), audio_(nullptr), manager_(nullptr)
	{
		hwnd_ = ::GetConsoleWindow();

		AudioDesc desc;
		desc.handle = hwnd_;
		desc.apiType = AudioUtility::APIType_DirectSound;
		manager_ = std::shared_ptr<AudioManager>(new AudioManager(desc));
	}

	~DirectSoundStatic3DAudioBufferTest() {
		::DestroyWindow(hwnd_);
	}

	void Test() {
		LoadStatic3DAudio();
		Play();
		Thread::Sleep(2000);

		SetMinDistance(50);
		SetMaxDistance(20);
		for (float z = -150; z < 150; z+=20.f) {
			SetPosition(Vector3f(0, 0, z));
			GetPosition();
			Thread::Sleep(1000);
		}
		Thread::Sleep(1000);
	}

	
	void LoadStatic3DAudio() {
		Assert(manager_!=nullptr)
		AudioBufferDesc desc;
		ZeroMemory(&desc, sizeof(AudioBufferDesc));
		desc.algorithm = DS3DALG_HRTF_FULL;
		desc.focusType  = AudioUtility::FocusType_GlobalFocus;
		desc.bufferType = AudioUtility::BufferType_Static3DAudioBuffer;
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
	
	
	void SetPosition(const Vector3f& pos) {
		Assert(audio_ != nullptr);
		auto a = dynamic_cast<Nyx::I3DAudioBuffer*>(audio_.get());
		a->SetPosition(pos);
	}


	void GetPosition() {
		Assert(audio_ != nullptr);
		auto buffer = dynamic_cast<Nyx::I3DAudioBuffer* >(audio_.get());
		auto pos = buffer->GetPosition();
		printf("pos=(%f, %f, %f)\n", pos.x, pos.y, pos.z);
	}


	void SetMinDistance(float distance) {
		Assert(audio_ != nullptr);
		auto buffer = dynamic_cast<Nyx::I3DAudioBuffer* >(audio_.get());
		buffer->SetMinDistance(distance);
	}
	
	
	void GetMinDistance() {
		Assert(audio_ != nullptr);
		auto buffer = dynamic_cast<Nyx::I3DAudioBuffer* >(audio_.get());
		printf("min distance=%f\n", buffer->GetMinDistance());
	}


	void SetMaxDistance(float distance) {
		Assert(audio_ != nullptr);
		auto buffer = dynamic_cast<Nyx::I3DAudioBuffer* >(audio_.get());
		buffer->SetMaxDistance(distance);

	}

	void GetMaxDistance() {
		Assert(audio_ != nullptr);
		auto buffer = dynamic_cast<Nyx::I3DAudioBuffer* >(audio_.get());
		printf("max distance=%f\n", buffer->GetMaxDistance());

	}
private:
	HWND hwnd_;
	std::shared_ptr<IAudioBuffer>  audio_;
	std::shared_ptr<AudioManager> manager_;
};