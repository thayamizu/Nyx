#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Sound/IAudioBuffer.h"
#include "Sound/AudioBuffer.h"
#include "Sound/AudioManager.h"

namespace Nyx
{

	struct AudioBuffer::PImpl
	{
		std::unique_ptr<IAudioBuffer> audioBuffer;
	};

	//-------------------------------------------------------------------------------------------------------
	//
	AudioBuffer::AudioBuffer() 
		: IAudioBuffer(), pimpl_(new PImpl())
	{
	
	}

	//-------------------------------------------------------------------------------------------------------
	//
	AudioBuffer::AudioBuffer(const AudioBuffer& other) 
		:IAudioBuffer(), pimpl_(new PImpl())
	{
		using std::copy;
		using std::swap;

		std::unique_ptr<IAudioBuffer> tmp = std::unique_ptr<IAudioBuffer>(other.pimpl_->audioBuffer.get());
		swap(pimpl_->audioBuffer, tmp);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Play() {
		Assert( pimpl_->audioBuffer != nullptr);
		pimpl_->audioBuffer->Play();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Stop() {
		Assert( pimpl_->audioBuffer != nullptr);
		pimpl_->audioBuffer->Stop();
	}
	
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Resume() {
		Assert( pimpl_->audioBuffer != nullptr);
		pimpl_->audioBuffer->Resume();
	}
	
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Reset() {
		Assert( pimpl_->audioBuffer != nullptr);
		pimpl_->audioBuffer->Reset();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	AudioBuffer& AudioBuffer::operator=(const AudioBuffer& other) {
		using std::copy;
		using std::swap;

		std::unique_ptr<IAudioBuffer> tmp = std::unique_ptr<IAudioBuffer>(other.pimpl_->audioBuffer.get());
		swap(pimpl_->audioBuffer, tmp);

		return *this;
	}
};