#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "DirectSoundStereoAudioBuffer.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStereoAudioBuffer::DirectSoundStereoAudioBuffer() 
		: DirectSoundAudioBuffer(), IStereoAudioBuffer() {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStereoAudioBuffer::~DirectSoundStereoAudioBuffer() {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSoundStereoAudioBuffer::GetPan() {
		auto soundBuffer = GetHandle();
		long pan;
		HRESULT hr = soundBuffer->GetPan(&pan);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのパン値の取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのパン値の取得に失敗しました。", hr);
		}
		
		return 1;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStereoAudioBuffer::SetPan(long pan) {
		auto soundBuffer = GetHandle();
		Assert(soundBuffer != nullptr);
		HRESULT hr = soundBuffer->SetPan(pan);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのパン値の設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのパン値の設定に失敗しました。", hr);
		}
	}
}