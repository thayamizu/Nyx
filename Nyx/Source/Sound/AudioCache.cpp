/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
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