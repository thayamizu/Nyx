#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "DirectSoundAudioListenerh.h"

namespace Nyx {
	//---------------------------------------------------------------------------------------
	//
	DirectSoundAudioListener::DirectSoundAudioListener() 
		:listener_(nullptr){

	}

	//---------------------------------------------------------------------------------------
	//
	DirectSoundAudioListener::~DirectSoundAudioListener() {

	}

	//---------------------------------------------------------------------------------------
	//
	Vector3f DirectSoundAudioListener::GetPosition() const {
		Assert(listener_ != nullptr);
		D3DVECTOR pos;
		HRESULT hr = listener_->GetPosition(&pos);
		if (FAILED(hr)) {
			DebugOutput::Trace("���X�i�[�̈ʒu�̎擾�Ɏ��s���܂����B[%s,%d]", __FILE__, __LINE__);
			throw COMException("���X�i�[�̈ʒu�̎擾�Ɏ��s���܂����B", hr);
		}
		return Vector3f(pos.x, pos.y, pos.z);
	}

	//---------------------------------------------------------------------------------------
	//
	void DirectSoundAudioListener::SetPosition(const Vector3f& pos)  {
		Assert(listener_ != nullptr);
		HRESULT hr = listener_->SetPosition(pos.x, pos.y, pos.z, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("���X�i�[�̈ʒu�̐ݒ�Ɏ��s���܂����B[%s,%d]", __FILE__, __LINE__);
			throw COMException("���X�i�[�̈ʒu�̐ݒ�Ɏ��s���܂����B", hr);
		}
	}


	//---------------------------------------------------------------------------------------
	//
	Vector3f DirectSoundAudioListener::GetVelocity() const {
		Assert(listener_ != nullptr);
		D3DVECTOR velocity;
		HRESULT hr = listener_->GetVelocity(&velocity);
		if (FAILED(hr)) {
			DebugOutput::Trace("���X�i�[�̑��x�̎擾�Ɏ��s���܂����B[%s,%d]", __FILE__, __LINE__);
			throw COMException("���X�i�[�̑��x�̎擾�Ɏ��s���܂����B", hr);
		}
		return Vector3f(velocity.x, velocity.y, velocity.z);
	}

	//---------------------------------------------------------------------------------------
	//
	void DirectSoundAudioListener::SetVelocity(const Vector3f& velocity) {
		Assert(listener_ != nullptr);
		HRESULT hr = listener_->SetVelocity(velocity.x, velocity.y, velocity.z, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("���X�i�[�̑��x�̐ݒ�Ɏ��s���܂����B[%s,%d]", __FILE__, __LINE__);
			throw COMException("���X�i�[�̑��x�̐ݒ�Ɏ��s���܂����B", hr);
		}
	}


	//---------------------------------------------------------------------------------------
	//
	float DirectSoundAudioListener::GetDopplerFactor() const {
		Assert(listener_ != nullptr);
		float factor;
		HRESULT hr = listener_->GetDopplerFactor(&factor);
		if (FAILED(hr)) {
			DebugOutput::Trace("�h�b�v���[�W���̎擾�Ɏ��s���܂����B[%s,%d]", __FILE__, __LINE__);
			throw COMException("�h�b�v���[�W���̎擾�Ɏ��s���܂����B", hr);
		}
		return factor;
	}


	//---------------------------------------------------------------------------------------
	//
	void DirectSoundAudioListener::SetDopplerFactor(const float dopplerFactor) {
		Assert(listener_ != nullptr);
		HRESULT hr = listener_->SetDopplerFactor(dopplerFactor, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("�h�b�v���[�W���̐ݒ�Ɏ��s���܂����B[%s,%d]", __FILE__, __LINE__);
			throw COMException("�h�b�v���[�W���̐ݒ�Ɏ��s���܂����B", hr);
		}
	}


	//---------------------------------------------------------------------------------------
	//
	float DirectSoundAudioListener::GetRolloffFactor() const {
		Assert(listener_ != nullptr);
		float factor;
		HRESULT hr = listener_->GetRolloffFactor(&factor);
		if (FAILED(hr)) {
			DebugOutput::Trace("���[���I�t�W���̎擾�Ɏ��s���܂����B[%s,%d]", __FILE__, __LINE__);
			throw COMException("���[���I�t�W���̎擾�Ɏ��s���܂����B", hr);
		}
		return factor;
	}


	void DirectSoundAudioListener::SetRolloffFactor(const float rolloffFactor) {
		Assert(listener_ != nullptr);
		HRESULT hr = listener_->SetRolloffFactor(rolloffFactor, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("���[���I�t�W���̐ݒ�Ɏ��s���܂����B[%s,%d]", __FILE__, __LINE__);
			throw COMException("���[���I�t�W���̐ݒ�Ɏ��s���܂����B", hr);
		}
	}
}