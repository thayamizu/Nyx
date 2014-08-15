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

namespace nyx {
	
	//-------------------------------------------------------------------------------------------------------
	//Pimpl
	struct audio_manager::PImpl {
		PImpl()
			:isInitialized_(false), audioManager_(nullptr) {
		}
		
		bool isInitialized_;
		
		std::shared_ptr<iaudio_manager> audioManager_;
	};


	//-------------------------------------------------------------------------------------------------------
	//
	audio_manager::audio_manager()
		: pimpl_(new PImpl()){
	}


	//-------------------------------------------------------------------------------------------------------
	//
	audio_manager::audio_manager(const audio_desc& desc)
		: pimpl_(new PImpl()) {
			initialize(desc);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void audio_manager::initialize(const audio_desc& desc) {
		NYX_ASSERT(pimpl_ != nullptr);
		if (pimpl_->isInitialized_) {
			return ;
		}
		
		//オーディオマネージャを初期化
		pimpl_->audioManager_ = std::make_shared<dsound_audio_manager>();
		pimpl_->audioManager_->initialize(desc);

		//初期化フラグ
		pimpl_->isInitialized_ = true;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<iaudio_buffer> audio_manager::create_audio_buffer(const std::wstring& fileName,  const audio_buffer_desc& bufferDesc) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->audioManager_ != nullptr);
		return pimpl_->audioManager_->create_audio_buffer(fileName, bufferDesc);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<iaudio_listener> audio_manager::create_audio_listener() {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->audioManager_ != nullptr);
		return pimpl_->audioManager_->create_audio_listener();
	}	
	
	
	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<audio_cache> audio_manager::load_audio(const std::wstring& fileName,  const audio_buffer_desc& bufferDesc) {
		NYX_ASSERT(pimpl_ != nullptr);
		NYX_ASSERT(pimpl_->audioManager_ != nullptr);
		return pimpl_->audioManager_->load_audio(fileName, bufferDesc);
	}
}
