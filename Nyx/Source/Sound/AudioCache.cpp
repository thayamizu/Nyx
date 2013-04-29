#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "AudioCache.h"
#include "IAudioBuffer.h"

namespace Nyx {

	struct AudioCache::PImpl {
		typedef std::map<std::wstring,  std::shared_ptr<IAudioBuffer>> AudioBufferList;
		AudioBufferList audioBufferList_;
	};
	AudioCache::AudioCache()
		:pimpl_(new PImpl())
	{

	}
	AudioCache::AudioCache(size_t cacheSize) 
		:pimpl_(new PImpl())
	{
	}
	AudioCache::~AudioCache() {

	}

	void AudioCache::Add(const std::shared_ptr<IAudioBuffer>& audioBuffer) {
		Assert(pimpl_ != nullptr);
	}
	
	void AudioCache::Remove(const std::shared_ptr<IAudioBuffer>& audioBuffer) {
		Assert(pimpl_ != nullptr);

	}
	
	bool AudioCache::Play(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;	
	}
	
	bool AudioCache::PlayAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}
	
	bool AudioCache::Stop(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;
	}
	
	bool AudioCache::StopAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}
	
	bool AudioCache::Resume(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;
	}
	
	bool AudioCache::ResumeAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}
	
	bool AudioCache::Pause(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;
	}

	bool AudioCache::PauseAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}

	const std::shared_ptr<IAudioBuffer> AudioCache::GetAudioBuffer(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return nullptr;
	}
}