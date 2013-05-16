/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "AudioCache.h"
#include "AudioUtility.h"
#include "IAudioBuffer.h"

namespace Nyx {
//-------------------------------------------------------------------------------------------------------
	//
	struct AudioCache::PImpl {
		typedef std::vector<std::shared_ptr<IAudioBuffer> > AudioBufferList;
		typedef std::map<std::wstring,  std::shared_ptr<IAudioBuffer>> AudioBufferMap;
		AudioBufferList audioBufferList_;
		AudioBufferMap  audioBufferMap_;
	};


	//-------------------------------------------------------------------------------------------------------
	//
	AudioCache::AudioCache()
		:pimpl_(new PImpl()) {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioCache::AudioCache(size_t cacheSize) 
		:pimpl_(new PImpl()) {
		pimpl_->audioBufferList_.resize(cacheSize);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Add(const std::wstring& fileName, std::shared_ptr<IAudioBuffer> audioBuffer) {
		Assert(pimpl_ != nullptr);
		
		pimpl_->audioBufferList_.push_back(audioBuffer);
		pimpl_->audioBufferMap_.insert(PImpl::AudioBufferMap::value_type(fileName, audioBuffer));
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Remove(const std::wstring& fileName, std::shared_ptr<IAudioBuffer> audioBuffer) {
		Assert(pimpl_ != nullptr);
		auto listIter = std::find(
			pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end()  , audioBuffer);
		if (listIter != pimpl_->audioBufferList_.end()) {
			pimpl_->audioBufferList_.erase(listIter);
		}

		auto mapIter = pimpl_->audioBufferMap_.find(fileName);
		if (mapIter != pimpl_->audioBufferMap_.end()) {
			pimpl_->audioBufferMap_.erase(mapIter);
		}
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Clear() {
		Assert(pimpl_ != nullptr);
		pimpl_->audioBufferList_.clear();
		pimpl_->audioBufferMap_.clear();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Play(const std::wstring& fileName, const bool isLoop) {
		Assert(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->Play(isLoop);
		}
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::PlayAll(const bool isLoop) {
		Assert(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[&isLoop](std::shared_ptr<IAudioBuffer> buffer) {
				buffer->Play(isLoop);
		});
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Stop(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->Stop();
		}
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::StopAll() {
		Assert(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[](std::shared_ptr<IAudioBuffer> buffer) {
				buffer->Stop();
		});
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Resume(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->Resume();
		}
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::ResumeAll() {
		Assert(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[](std::shared_ptr<IAudioBuffer> buffer) {
				buffer->Resume();
		});
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Reset(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->Reset();
		}

	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::ResetAll() {
		Assert(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[](std::shared_ptr<IAudioBuffer> buffer) {
				buffer->Reset();
		});
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::SetEffect(const std::wstring& fileName, const AudioEffectDesc& effectDesc) {
		Assert(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->SetEffect(effectDesc);
		}
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::SetEffectAll(const AudioEffectDesc& effectDesc) {
		Assert(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[&effectDesc](std::shared_ptr<IAudioBuffer> buffer) {
				buffer->SetEffect(effectDesc);
		});
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::ResetEffect(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->ResetEffect();
		}

	}
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::ResetEffectAll() {
		Assert(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[](std::shared_ptr<IAudioBuffer> buffer) {
				buffer->ResetEffect();
		});
	}

	//-------------------------------------------------------------------------------------------------------
	//
	const std::shared_ptr<IAudioBuffer>& AudioCache::GetAudioBuffer(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			return it->second;
		}
		return nullptr;
	}
}