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

namespace nyx {
//-------------------------------------------------------------------------------------------------------
	//
	struct audio_cache::PImpl {
		typedef std::vector<std::shared_ptr<iaudio_buffer> > AudioBufferList;
		typedef std::map<std::wstring,  std::shared_ptr<iaudio_buffer>> AudioBufferMap;
		AudioBufferList audioBufferList_;
		AudioBufferMap  audioBufferMap_;
	};


	//-------------------------------------------------------------------------------------------------------
	//
	audio_cache::audio_cache()
		:pimpl_(new PImpl()) {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	audio_cache::audio_cache(size_t cacheSize) 
		:pimpl_(new PImpl()) {
		pimpl_->audioBufferList_.resize(cacheSize);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<iaudio_buffer> audio_cache::operator[](const std::wstring& fileName) {
		size_t begin = fileName.find_last_of(L"\\/");
		size_t end = fileName.find_last_of(L".");
		size_t num = end - begin - 1;
		auto name = fileName.substr(begin + 1, num);
		return pimpl_->audioBufferMap_[name];
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::add(const std::wstring& fileName, std::shared_ptr<iaudio_buffer> audioBuffer) {
		NYX_ASSERT(pimpl_ != nullptr);
		
		size_t begin = fileName.find_last_of(L"\\/");
		size_t end = fileName.find_last_of(L".");
		size_t num = end - begin - 1;
		auto name = fileName.substr(begin + 1, num);
		pimpl_->audioBufferList_.push_back(audioBuffer);
		pimpl_->audioBufferMap_.insert(PImpl::AudioBufferMap::value_type(name, audioBuffer));
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::remove(const std::wstring& fileName) {
		NYX_ASSERT(pimpl_ != nullptr);
		
		size_t begin = fileName.find_last_of(L"\\/");
		size_t end = fileName.find_last_of(L".");
		size_t num = end - begin - 1;
		auto name = fileName.substr(begin + 1, num);
		auto mapIter = pimpl_->audioBufferMap_.find(name);
		if (mapIter == pimpl_->audioBufferMap_.end()) {
			return;
		}
		
		
		auto audioBuffer = mapIter->second;
		auto listIter = std::find(
			pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end()  , audioBuffer);
		if (listIter != pimpl_->audioBufferList_.end()) {
			pimpl_->audioBufferList_.erase(listIter);
		}

		pimpl_->audioBufferMap_.erase(mapIter);

	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::clear() {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->audioBufferList_.clear();
		pimpl_->audioBufferMap_.clear();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::play(const std::wstring& fileName, const bool isLoop) {
		NYX_ASSERT(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->play(isLoop);
		}
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::play_all(const bool isLoop) {
		NYX_ASSERT(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[&isLoop](std::shared_ptr<iaudio_buffer> buffer) {
				buffer->play(isLoop);
		});
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::stop(const std::wstring& fileName) {
		NYX_ASSERT(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->stop();
		}
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::stop_all() {
		NYX_ASSERT(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[](std::shared_ptr<iaudio_buffer> buffer) {
				buffer->stop();
		});
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::resume(const std::wstring& fileName) {
		NYX_ASSERT(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->resume();
		}
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::resume_all() {
		NYX_ASSERT(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[](std::shared_ptr<iaudio_buffer> buffer) {
				buffer->resume();
		});
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::reset(const std::wstring& fileName) {
		NYX_ASSERT(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->reset();
		}

	}


	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::reset_all() {
		NYX_ASSERT(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[](std::shared_ptr<iaudio_buffer> buffer) {
				buffer->reset();
		});
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::set_effect(const std::wstring& fileName, const audio_effect_desc& effectDesc) {
		NYX_ASSERT(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->set_effect(effectDesc);
		}
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::set_effect_all(const audio_effect_desc& effectDesc) {
		NYX_ASSERT(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[&effectDesc](std::shared_ptr<iaudio_buffer> buffer) {
				buffer->set_effect(effectDesc);
		});
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::reset_effect(const std::wstring& fileName) {
		NYX_ASSERT(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			it->second->reset_effect();
		}

	}
	//-------------------------------------------------------------------------------------------------------
	//
	void audio_cache::reset_effect_all() {
		NYX_ASSERT(pimpl_ != nullptr);
		std::for_each(pimpl_->audioBufferList_.begin(), 
			pimpl_->audioBufferList_.end(), 
			[](std::shared_ptr<iaudio_buffer> buffer) {
				buffer->reset_effect();
		});
	}

	//-------------------------------------------------------------------------------------------------------
	//
	const std::shared_ptr<iaudio_buffer> audio_cache::get_audio_buffer(const std::wstring& fileName) {
		NYX_ASSERT(pimpl_ != nullptr);
		auto it = pimpl_->audioBufferMap_.find(fileName);
		if (it != pimpl_->audioBufferMap_.end()) {
			return it->second;
		}
		return nullptr;
	}
}