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
#include "DirectSoundAudioListenerh.h"

namespace Nyx {
	//---------------------------------------------------------------------------------------
	//
	DirectSoundAudioListener::DirectSoundAudioListener(DirectSoundPtr dsound) 
		:listener_(nullptr){
			Assert(dsound != nullptr)
				DSBUFFERDESC dsbd;
			ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));  
			dsbd.dwSize = sizeof(DSBUFFERDESC);  
			dsbd.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;  

			LPDIRECTSOUNDBUFFER primary;
			HRESULT hr = dsound->CreateSoundBuffer(&dsbd, &primary, NULL);
			if (FAILED(hr)) {
				DebugOutput::Trace("プライマリバッファの取得に失敗しました。[%s,%d]",__FILE__, __LINE__);
				throw COMException("プライマリバッファの取得に失敗しました。", hr);
			}

			LPDIRECTSOUND3DLISTENER8 listener;
			hr = primary->QueryInterface(IID_IDirectSound3DListener8, (void**)&listener);
			if (FAILED(hr)) {
				DebugOutput::Trace("IDirectSound3DListener8インタフェースの取得に失敗しました。[%s,%d]", __FILE__, __LINE__);
				throw COMException("IDirectSound3DListener8インタフェースの取得に失敗しました。", hr);
			}

			listener_ = DirectSound3DListenerPtr(listener);
			SafeRelease(primary);
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

	//---------------------------------------------------------------------------------------
	//
	void DirectSoundAudioListener::SetRolloffFactor(const float rolloffFactor) {
		Assert(listener_ != nullptr);
		HRESULT hr = listener_->SetRolloffFactor(rolloffFactor, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("ロールオフ係数の設定に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw COMException("ロールオフ係数の設定に失敗しました。", hr);
		}
	}
}