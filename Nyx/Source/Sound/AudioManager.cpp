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
#include "Sound/AudioManager.h"
#include "Sound/AudioBuffer.h"
#include "detail/DirectSound/DirectSoundAudioManager.h"
namespace Nyx {

	struct AudioManager::PImpl{
		std::unique_ptr<DirectSoundAudioManager> manager;
	};

	AudioManager::AudioManager() 
		: pimpl_( new PImpl())	
	{

	}
	//--------------------------------------------------------------------------------------
	//
	AudioManager::AudioManager(HWND hwnd, int volume) 
		: pimpl_( new PImpl())	
	{
		Assert(pimpl_ != nullptr);
		pimpl_->manager = std::unique_ptr<DirectSoundAudioManager>( new DirectSoundAudioManager(hwnd, volume));

	}

	//-------------------------------------------------------------------------------------------------------
	//
	AudioManager::~AudioManager() {

	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Create(HWND hwnd, int volume) {
		Assert(pimpl_ != nullptr);
		pimpl_->manager = std::unique_ptr<DirectSoundAudioManager>( new DirectSoundAudioManager(hwnd, volume));

	}
	
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Play(size_t index) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->Play(index);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::PlayAll() {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->PlayAll();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Stop(size_t index) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->Stop(index);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::StopAll() {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->StopAll();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Resume(size_t index) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->Resume(index);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::ResumeAll() {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->ResumeAll();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Reset(size_t index) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->Reset(index);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::ResetAll() {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->ResetAll();
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::SetPause(size_t index, bool p) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->SetPause(index, p);
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::SetPauseAll(bool p) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->SetPauseAll(p);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	int AudioManager::GetMasterVolume() const {
		Assert(pimpl_->manager != nullptr);
		return pimpl_->manager->GetMasterVolume();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::SetMasterVolume(int v) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->SetMasterVolume(v);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioBuffer> AudioManager::GetAudioBuffer(size_t index) {
		Assert(pimpl_->manager != nullptr);
		return pimpl_->manager->GetAudioBuffer(index);
	}

	//---------------------------------------------------------------------------------------
	//
	bool AudioManager::Load(const std::wstring fileName, SoundBufferType bufferType) {
		Assert(pimpl_->manager != nullptr);
		return pimpl_->manager->Load(fileName, bufferType);
	}	
}
