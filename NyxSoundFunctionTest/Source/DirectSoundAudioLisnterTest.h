#pragma once
#include "PCH.h"
#include "Sound/AudioUtility.h"
#include "Sound/DirectSoundAudioManager.h"
#include "Sound/IAudioListener.h"


class DirectSoundAudioListenerTest {
public:
	DirectSoundAudioListenerTest()
		: listener_(nullptr), cache_(nullptr), manager_(nullptr) {
			
			AudioDesc desc;
			desc.handle = ::GetConsoleWindow();
			desc.apiType = AudioUtility::APIType_DirectSound;

			manager_ = std::make_shared<AudioManager>();
			Assert(manager_ != nullptr);

			manager_->Initialize(desc);
	}
	~DirectSoundAudioListenerTest() {

	}

	void Test() {
		Assert(manager_  != nullptr);

		Load();
		Play();
		Thread::Sleep(2000);

		GetPosition();
		GetVelocity();
		for (float z = -50; z < 50; z+=50) {
			for (float y = -50; y < 50; y+=50) {
				for (float x = -50; x < 50; x+=50) {
					SetPosition(Nyx::Vector3f(x, y, z));
					GetPosition();
					Thread::Sleep(200);
				}
			}
		}
		
		SetPosition(Nyx::Vector3f::Zero);
		GetPosition();
		for (float z = -50; z < 50; z+=50) {
			for (float y = -50; y< 50; y+=50) {
				for (float x = -50; x < 50; x+=50) {
					SetVelocity(Nyx::Vector3f(x, y, z));
					GetVelocity();
				}
			}
		}

		
		SetVelocity(Nyx::Vector3f::Zero);
		GetVelocity();

		const auto length  = 1.0f;
		for (float i = 0; i < length; i+=0.1f)
		{
			SetDopplerFactor(i);
			for (float x = -50; x < 50; x+=10) {
				SetPosition(Nyx::Vector3f(x, 0, 0));
			Thread::Sleep(200);
			}
			GetDopplerFactor();
		}

		for (float i = 0; i < length; i+=0.1f)
		{
			SetRolloffFactor(i);
			GetRolloffFactor();
			for (float x = -50; x < 50; x+=10) {
				SetPosition(Nyx::Vector3f(x, 0, 0));
				Thread::Sleep(200);
			}
		}
	}

	void Load() {
		Assert(manager_  != nullptr);
		Assert(cache_ == nullptr);
		Assert(listener_ == nullptr);

		AudioBufferDesc desc;
		desc.algorithm   = DS3DALG_HRTF_FULL;
		desc.bufferType  = AudioUtility::BufferType_Streaming3DAudioBuffer;
		desc.focusType	 = AudioUtility::FocusType_GlobalFocus;
		cache_ = manager_->Load(L"../../TestData/Sound/testcase.txt", desc);
		Assert(cache_ != nullptr);

		listener_ = manager_->CreateAudioListener();
		Assert(listener_ != nullptr);
	}

	void Play() {
		Assert(cache_    != nullptr);
		Assert(manager_  != nullptr);
		Assert(listener_ != nullptr);
		cache_->PlayAll();
	}

	void Stop() {
		Assert(cache_    != nullptr);
		Assert(manager_  != nullptr);
		Assert(listener_ != nullptr);
		cache_->StopAll();
	}

	void SetPosition(Vector3f v) {
		Assert(cache_    != nullptr);
		Assert(manager_  != nullptr);
		Assert(listener_ != nullptr);
		listener_->SetPosition(v);
	}

	void GetPosition() {
		Assert(cache_    != nullptr);
		Assert(manager_  != nullptr);
		Assert(listener_ != nullptr);
		auto v = listener_->GetPosition();
		printf("veclocity = (%f, %f, %f)\n", v.x, v.y, v.z);
	}

	void GetVelocity() {
		Assert(cache_    != nullptr);
		Assert(manager_  != nullptr);
		Assert(listener_ != nullptr);
		auto v = listener_->GetVelocity();
		printf("veclocity = (%f, %f, %f)\n", v.x, v.y, v.z);
	}

	void SetVelocity(Vector3f v) {
		Assert(cache_    != nullptr);
		Assert(manager_  != nullptr);
		Assert(listener_ != nullptr);
		listener_->SetVelocity(v);
	}

	void SetDopplerFactor(float factor) {
		Assert(cache_    != nullptr);
		Assert(manager_  != nullptr);
		Assert(listener_ != nullptr);
		listener_->SetDopplerFactor(factor);
	}

	void GetDopplerFactor() {
		Assert(cache_    != nullptr);
		Assert(manager_  != nullptr);
		Assert(listener_ != nullptr);
		auto factor = listener_->GetDopplerFactor();
		printf("doppler factory=%f\n", factor);
	}

	void SetRolloffFactor(float factor) {
		Assert(cache_    != nullptr);
		Assert(manager_  != nullptr);
		Assert(listener_ != nullptr);
		listener_->SetRolloffFactor(factor);
	}

	void GetRolloffFactor() {
		Assert(cache_    != nullptr);
		Assert(manager_  != nullptr);
		Assert(listener_ != nullptr);
		auto factor = listener_->GetRolloffFactor();
		printf("roffoff factory=%f\n", factor);

	}
private:
	std::shared_ptr<IAudioListener> listener_;
	std::shared_ptr<AudioCache> cache_;
	std::shared_ptr<AudioManager> manager_;
};