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
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̎擾�Ɏ��s���܂����B", hr);
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
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̐ݒ�Ɏ��s���܂����B", hr);
		}
	}
}