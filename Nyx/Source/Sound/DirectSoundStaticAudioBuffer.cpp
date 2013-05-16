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
#include "AudioUtility.h"
#include "DirectSoundAudioBuffer.h"
#include "DirectSoundStaticAudioBuffer.h"

namespace Nyx {
	DirectSoundStaticAudioBuffer::DirectSoundStaticAudioBuffer() 
		: audio_(nullptr) {
	}


	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStaticAudioBuffer::DirectSoundStaticAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr dsound, const std::wstring& fileName)
		: audio_(new DirectSoundAudioBuffer(bufferDesc, dsound, fileName)){


			audio_->WriteWaveData(bufferDesc.bufferSize);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::Load(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds, const std::wstring& fileName) {
		if (audio_== nullptr) {
			audio_ = std::make_shared<DirectSoundAudioBuffer>();
		}
		audio_->Load(bufferDesc, ds, fileName);
		audio_->WriteWaveData(bufferDesc.bufferSize);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::Play(bool isLoop) {
		Assert(audio_ != nullptr);
		audio_->Play(isLoop);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::Stop() {
		Assert(audio_ != nullptr);
		audio_->Stop();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::Resume() {
		Assert(audio_ != nullptr);
		audio_->Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::Reset() {
		Assert(audio_ != nullptr);
		audio_->Reset();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::SetPan(long pan) {
		Assert(audio_ != nullptr);
		audio_->SetPan(pan);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::SetVolume(long volume) {
		Assert(audio_ != nullptr);
		audio_->SetVolume(volume);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSoundStaticAudioBuffer::GetPan() const {
		Assert(audio_ != nullptr);
		return audio_->GetPan();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSoundStaticAudioBuffer::GetVolume() const {
		Assert(audio_ != nullptr);
		return audio_->GetVolume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioState DirectSoundStaticAudioBuffer::GetState() const {
		Assert(audio_ != nullptr);
		return audio_->GetState();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::ResetEffect() {
		Assert(audio_ != nullptr);
		audio_->ResetEffect();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::SetEffect(const AudioEffectDesc& effectDesc) {
		Assert(audio_ != nullptr);
		audio_->SetEffect(effectDesc);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	AudioUtility::BufferType DirectSoundStaticAudioBuffer::GetBufferType() const {
		return AudioUtility::BufferType_StaticAudioBuffer;
	}
}