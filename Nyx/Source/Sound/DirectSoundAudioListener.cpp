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

namespace nyx {
	//---------------------------------------------------------------------------------------
	//
	dsound_audio_listener::dsound_audio_listener(dsound_ptr dsound) 
		:listener_(nullptr){
			NYX_ASSERT(dsound != nullptr)
				DSBUFFERDESC dsbd;
			ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));  
			dsbd.dwSize = sizeof(DSBUFFERDESC);  
			dsbd.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;  

			LPDIRECTSOUNDBUFFER primary;
			HRESULT hr = dsound->CreateSoundBuffer(&dsbd, &primary, NULL);
			if (FAILED(hr)) {
				debug_out::trace("プライマリバッファの取得に失敗しました。[%s,%d]",__FILE__, __LINE__);
				throw com_exception("プライマリバッファの取得に失敗しました。", hr);
			}

			LPDIRECTSOUND3DLISTENER8 listener;
			hr = primary->QueryInterface(IID_IDirectSound3DListener8, (void**)&listener);
			if (FAILED(hr)) {
				debug_out::trace("IDirectSound3DListener8インタフェースの取得に失敗しました。[%s,%d]", __FILE__, __LINE__);
				throw com_exception("IDirectSound3DListener8インタフェースの取得に失敗しました。", hr);
			}

			listener_ = dsound_3d_listener_ptr(listener);
			SafeRelease(primary);
	}

	//---------------------------------------------------------------------------------------
	//
	dsound_audio_listener::~dsound_audio_listener() {

	}

	//---------------------------------------------------------------------------------------
	//
	vector3f dsound_audio_listener::get_position() const {
		NYX_ASSERT(listener_ != nullptr);
		D3DVECTOR pos;
		HRESULT hr = listener_->GetPosition(&pos);
		if (FAILED(hr)) {
			debug_out::trace("リスナーの位置の取得に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw com_exception("リスナーの位置の取得に失敗しました。", hr);
		}
		return vector3f(pos.x, pos.y, pos.z);
	}

	//---------------------------------------------------------------------------------------
	//
	void dsound_audio_listener::set_position(const vector3f& pos)  {
		NYX_ASSERT(listener_ != nullptr);
		HRESULT hr = listener_->SetPosition(pos.x, pos.y, pos.z, NULL);
		if (FAILED(hr)) {
			debug_out::trace("リスナーの位置の設定に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw com_exception("リスナーの位置の設定に失敗しました。", hr);
		}
	}


	//---------------------------------------------------------------------------------------
	//
	vector3f dsound_audio_listener::get_velocity() const {
		NYX_ASSERT(listener_ != nullptr);
		D3DVECTOR velocity;
		HRESULT hr = listener_->GetVelocity(&velocity);
		if (FAILED(hr)) {
			debug_out::trace("リスナーの速度の取得に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw com_exception("リスナーの速度の取得に失敗しました。", hr);
		}
		return vector3f(velocity.x, velocity.y, velocity.z);
	}

	//---------------------------------------------------------------------------------------
	//
	void dsound_audio_listener::set_velocity(const vector3f& velocity) {
		NYX_ASSERT(listener_ != nullptr);
		HRESULT hr = listener_->SetVelocity(velocity.x, velocity.y, velocity.z, NULL);
		if (FAILED(hr)) {
			debug_out::trace("リスナーの速度の設定に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw com_exception("リスナーの速度の設定に失敗しました。", hr);
		}
	}


	//---------------------------------------------------------------------------------------
	//
	float dsound_audio_listener::get_doppler_factor() const {
		NYX_ASSERT(listener_ != nullptr);
		float factor;
		HRESULT hr = listener_->GetDopplerFactor(&factor);
		if (FAILED(hr)) {
			debug_out::trace("ドップラー係数の取得に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw com_exception("ドップラー係数の取得に失敗しました。", hr);
		}
		return factor;
	}


	//---------------------------------------------------------------------------------------
	//
	void dsound_audio_listener::set_doppler_factor(const float dopplerFactor) {
		NYX_ASSERT(listener_ != nullptr);
		HRESULT hr = listener_->SetDopplerFactor(dopplerFactor, NULL);
		if (FAILED(hr)) {
			debug_out::trace("ドップラー係数の設定に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw com_exception("ドップラー係数の設定に失敗しました。", hr);
		}
	}


	//---------------------------------------------------------------------------------------
	//
	float dsound_audio_listener::get_rolloff_factor() const {
		NYX_ASSERT(listener_ != nullptr);
		float factor;
		HRESULT hr = listener_->GetRolloffFactor(&factor);
		if (FAILED(hr)) {
			debug_out::trace("ロールオフ係数の取得に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw com_exception("ロールオフ係数の取得に失敗しました。", hr);
		}
		return factor;
	}

	//---------------------------------------------------------------------------------------
	//
	void dsound_audio_listener::set_rolloff_factor(const float rolloffFactor) {
		NYX_ASSERT(listener_ != nullptr);
		HRESULT hr = listener_->SetRolloffFactor(rolloffFactor, NULL);
		if (FAILED(hr)) {
			debug_out::trace("ロールオフ係数の設定に失敗しました。[%s,%d]", __FILE__, __LINE__);
			throw com_exception("ロールオフ係数の設定に失敗しました。", hr);
		}
	}
}