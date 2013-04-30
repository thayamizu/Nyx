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
#include "AudioBuffer.h"
#include "AudioUtility.h"
#include "detail/DirectSound/DirectSoundAudioBuffer.h"

namespace Nyx 
{
	//-------------------------------------------------------------------------------------------------------
	//
	AudioBuffer::AudioBuffer() 
		:isLoop_(false), isPause_(false), isPlay_(false), audio_(nullptr) {
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioBuffer::AudioBuffer(const AudioBufferDesc& bufferDesc) 
		:isLoop_(false), isPause_(false), isPlay_(false), audio_(nullptr) {
			CreateBuffer(bufferDesc);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::CreateBuffer(const AudioBufferDesc& bufferDesc) {
		
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Play()  {
		Assert(audio_ != nullptr);
		if (isPause_) {
			return;
		}
		audio_->Play(isLoop_);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Stop()  {
		Assert(audio_ != nullptr);
		if (isPause_) {
			return;
		}
		audio_->Stop();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Resume()  {
		Assert(audio_ != nullptr);
		if (isPause_) {
			return;
		}
		audio_->Resume();

	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Reset()   {
		Assert(audio_ != nullptr);
		if (isPause_) {
			return;
		}
		audio_->Reset();
	} 


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::SetPan(const long pan) {
		Assert(audio_ != nullptr);
		audio_->SetPan(pan);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long AudioBuffer::GetPan() const  {
		Assert(audio_ != nullptr);
		return audio_->GetPan();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::SetVolume(const long volume)  {
		Assert(audio_ != nullptr);
		audio_->SetVolume(volume);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long AudioBuffer::GetVolume() const  {
		Assert(audio_ != nullptr);
		return audio_->GetVolume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioBuffer::IsLooping()  {
		return isLoop_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioBuffer::IsPlaying()  const {
		return isPlay_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioBuffer::IsPause() const  {
		return isPause_;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::SetLooping(const bool loop)  {
		isLoop_ = loop;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::SetPause(const bool pause)   {
		isPause_ = pause;
	}
}