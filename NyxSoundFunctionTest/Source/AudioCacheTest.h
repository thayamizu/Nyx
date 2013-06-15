#pragma once

class AudioCacheTest {
public:

	AudioCacheTest()
		: manager_(nullptr), cache_(nullptr)
	{
			Assert(cache_ == nullptr);
			Assert(manager_ == nullptr);

			AudioDesc desc;
			desc.apiType = AudioUtility::APIType_DirectSound;
			desc.handle  = ::GetConsoleWindow();

			manager_ = std::make_shared<AudioManager>(desc);
			Assert(manager_ != nullptr);
	}
	
	void Test() {
		Load();
		PlayAll();
		Thread::Sleep(2000);
		StopAll();
		Thread::Sleep(2000);
		PlayAll();
		Thread::Sleep(2000);
		ResetAll();
		Thread::Sleep(2000);
		StopAll();
		Thread::Sleep(2000);
		ResumeAll();
		SetEffectAll();	
		Thread::Sleep(2000);
		ResetEffectAll();
		Thread::Sleep(2000);
		StopAll();
		getbuffer();
		Thread::Sleep(2000);
	}
	void Load() {
		Assert(cache_   == nullptr);
		Assert(manager_ != nullptr);
		AudioBufferDesc bufferDesc;
		bufferDesc.algorithm = DS3DALG_DEFAULT;
		bufferDesc.focusType  = AudioUtility::FocusType_GlobalFocus;
		bufferDesc.bufferType = AudioUtility::BufferType_Static3DAudioBuffer;
		cache_ = manager_->Load(L"../../TestData/Sound/testcase.txt", bufferDesc);
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
	}

	void Play(){
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		cache_->Play(L"test1");
	}
	void Stop(){
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		cache_->Stop(L"test1");
		
	}
	void Resume(){
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		cache_->Resume(L"test1");
	}
	void Reset() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		cache_->Reset(L"test1");
	}
	void SetEffect() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		AudioEffectDesc effectDesc={};
		cache_->SetEffect(L"test1", effectDesc);
	}
	void Add() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		AudioBufferDesc bufferDesc;
		bufferDesc.algorithm = DS3DALG_DEFAULT;
		bufferDesc.focusType  = AudioUtility::FocusType_GlobalFocus;
		bufferDesc.bufferType = AudioUtility::BufferType_StaticAudioBuffer;
		auto buffer = manager_->CreateAudioBuffer(L"test1", bufferDesc);
		cache_->Add(L"test1", buffer);
	}
	void Delete() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		cache_->Remove(L"test2");
	}
	void PlayAll() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		cache_->PlayAll();	
	}
	void StopAll() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		cache_->StopAll();
	}
	void ResumeAll() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		cache_->ResumeAll();
	}
	void ResetAll() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		cache_->ResetAll();
	}
	void SetEffectAll() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		AudioEffectDesc effectDesc={};
		effectDesc.effectType = AudioUtility::EffectType_Chorus;
		cache_->SetEffectAll(effectDesc);
	}
	void getbuffer() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		auto buffer = cache_->operator[](L"test");
		if (buffer != nullptr) {
			buffer->Play(true);
		}
		else {
			Assert(false);
		}

		buffer = cache_->operator[](L"../../TestData/Sound/test2");
		if (buffer != nullptr) {
			buffer->Play(true);
		}
		else {
			Assert(false);
		}

		buffer = cache_->operator[](L"test3.wav");
		if (buffer != nullptr) {
			buffer->Play(true);

			buffer->Stop();
		}
		else {
			Assert(false);
		}

		cache_->Remove(L"test3.wav");
		buffer= cache_->operator[](L"test3.wav");
		if (buffer != nullptr) {
			Assert(false);
		}
	}
	void ResetEffectAll() {
		Assert(cache_ != nullptr);
		Assert(manager_ != nullptr);
		cache_->ResetEffectAll();
	}
private:
	std::shared_ptr<AudioCache> cache_;
	std::shared_ptr<AudioManager> manager_;
};