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
			DebugOutput::Trace("リスナーの位置の取得に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw COMException("リスナーの位置の取得に失敗しました。", hr);
		}
		return Vector3f(pos.x, pos.y, pos.z);
	}

	//---------------------------------------------------------------------------------------
	//
	void DirectSoundAudioListener::SetPosition(const Vector3f& pos)  {
		Assert(listener_ != nullptr);
		HRESULT hr = listener_->SetPosition(pos.x, pos.y, pos.z, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("リスナーの位置の設定に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw COMException("リスナーの位置の設定に失敗しました。", hr);
		}
	}


	//---------------------------------------------------------------------------------------
	//
	Vector3f DirectSoundAudioListener::GetVelocity() const {
		Assert(listener_ != nullptr);
		D3DVECTOR velocity;
		HRESULT hr = listener_->GetVelocity(&velocity);
		if (FAILED(hr)) {
			DebugOutput::Trace("リスナーの速度の取得に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw COMException("リスナーの速度の取得に失敗しました。", hr);
		}
		return Vector3f(velocity.x, velocity.y, velocity.z);
	}

	//---------------------------------------------------------------------------------------
	//
	void DirectSoundAudioListener::SetVelocity(const Vector3f& velocity) {
		Assert(listener_ != nullptr);
		HRESULT hr = listener_->SetVelocity(velocity.x, velocity.y, velocity.z, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("リスナーの速度の設定に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw COMException("リスナーの速度の設定に失敗しました。", hr);
		}
	}


	//---------------------------------------------------------------------------------------
	//
	float DirectSoundAudioListener::GetDopplerFactor() const {
		Assert(listener_ != nullptr);
		float factor;
		HRESULT hr = listener_->GetDopplerFactor(&factor);
		if (FAILED(hr)) {
			DebugOutput::Trace("ドップラー係数の取得に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw COMException("ドップラー係数の取得に失敗しました。", hr);
		}
		return factor;
	}


	//---------------------------------------------------------------------------------------
	//
	void DirectSoundAudioListener::SetDopplerFactor(const float dopplerFactor) {
		Assert(listener_ != nullptr);
		HRESULT hr = listener_->SetDopplerFactor(dopplerFactor, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("ドップラー係数の設定に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw COMException("ドップラー係数の設定に失敗しました。", hr);
		}
	}


	//---------------------------------------------------------------------------------------
	//
	float DirectSoundAudioListener::GetRolloffFactor() const {
		Assert(listener_ != nullptr);
		float factor;
		HRESULT hr = listener_->GetRolloffFactor(&factor);
		if (FAILED(hr)) {
			DebugOutput::Trace("ロールオフ係数の取得に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw COMException("ロールオフ係数の取得に失敗しました。", hr);
		}
		return factor;
	}


	void DirectSoundAudioListener::SetRolloffFactor(const float rolloffFactor) {
		Assert(listener_ != nullptr);
		HRESULT hr = listener_->SetRolloffFactor(rolloffFactor, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("ロールオフ係数の設定に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw COMException("ロールオフ係数の設定に失敗しました。", hr);
		}
	}
}