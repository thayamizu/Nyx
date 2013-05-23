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
#include "Debug/DebugOutput.h"
#include "AudioCache.h"
#include "AudioManager.h"
#include "AudioUtility.h"
#include "DirectSoundAudioManager.h"

namespace Nyx {
	
	//-------------------------------------------------------------------------------------------------------
	//Pimpl
	struct AudioManager::PImpl {
		PImpl()
			:isInitialized_(false), audioManager_(nullptr) {
		}
		
		bool isInitialized_;
		
		std::shared_ptr<IAudioManager> audioManager_;
	};


	//-------------------------------------------------------------------------------------------------------
	//
	AudioManager::AudioManager()
		: pimpl_(new PImpl()){
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioManager::AudioManager(const AudioDesc& desc)
		: pimpl_(new PImpl()) {
			Initialize(desc);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Initialize(const AudioDesc& desc) {
		Assert(pimpl_ != nullptr);
		if (pimpl_->isInitialized_) {
			return ;
		}
		
		//オーディオマネージャを初期化
		pimpl_->audioManager_ = std::make_shared<DirectSoundAudioManager>();
		pimpl_->audioManager_->Initialize(desc);

		//初期化フラグ
		pimpl_->isInitialized_ = true;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioBuffer> AudioManager::CreateAudioBuffer(const std::wstring& fileName,  const AudioBufferDesc& bufferDesc) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->audioManager_ != nullptr);
		return pimpl_->audioManager_->CreateAudioBuffer(fileName, bufferDesc);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioListener> AudioManager::CreateAudioListener() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->audioManager_ != nullptr);
		return pimpl_->audioManager_->CreateAudioListener();
	}	
	
	
	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<AudioCache> AudioManager::Load(const std::wstring& fileName,  const AudioBufferDesc& bufferDesc) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->audioManager_ != nullptr);
		return pimpl_->audioManager_->Load(fileName, bufferDesc);
	}
}
