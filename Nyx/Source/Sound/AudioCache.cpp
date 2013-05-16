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