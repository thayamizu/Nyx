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
#include "IAudioBuffer.h"

namespace Nyx {
//-------------------------------------------------------------------------------------------------------
	//
	struct AudioCache::PImpl {
		typedef std::map<std::wstring,  std::shared_ptr<IAudioBuffer>> AudioBufferList;
		AudioBufferList audioBufferList_;
	};


	//-------------------------------------------------------------------------------------------------------
	//
	AudioCache::AudioCache()
		:pimpl_(new PImpl())
	{

	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioCache::AudioCache(size_t cacheSize) 
		:pimpl_(new PImpl())
	{
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioCache::~AudioCache() {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Add(const std::shared_ptr<IAudioBuffer>& audioBuffer) {
		Assert(pimpl_ != nullptr);
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Remove(const std::shared_ptr<IAudioBuffer>& audioBuffer) {
		Assert(pimpl_ != nullptr);

	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::Play(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;	
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::PlayAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::Stop(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::StopAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::Resume(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::ResumeAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::Pause(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::PauseAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	const std::shared_ptr<IAudioBuffer> AudioCache::GetAudioBuffer(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return nullptr;
	}
}