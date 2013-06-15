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
#include "IO/File.h"
#include "Primitive/Vector3.h"
#include "WaveReader.h"
#include "DirectSoundDefinition.h"
#include "DirectSound3DAudioBuffer.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSound3DAudioBuffer::DirectSound3DAudioBuffer()
	:DirectSoundAudioBuffer(), I3DAudioBuffer(), buffer_(nullptr) {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	DirectSound3DAudioBuffer::~DirectSound3DAudioBuffer() {
	}


	//-------------------------------------------------------------------------------------------------------
	//
	Vector3f DirectSound3DAudioBuffer::GetPosition() const {
		Assert(buffer_ != nullptr);
		D3DXVECTOR3 pos;
		HRESULT hr = buffer_->GetPosition(&pos);
		if (FAILED(hr)) {
			DebugOutput::Trace("音源の位置の取得に失敗しました。[%s,%n]", __FILE__, __LINE__);
			throw COMException("音源の位置の取得に失敗しました。", hr);
		}
		return Vector3f(pos.x, pos.y, pos.z);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetPosition(const Vector3f& pos) {
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->SetPosition(pos.x, pos.y, pos.z, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("音源の位置の設定に失敗しました。[%s, %n]", __FILE__, __LINE__);
			throw COMException("音源の位置の設定に失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	Vector3f DirectSound3DAudioBuffer::GetVelocity() const {
		Assert(buffer_ != nullptr);
		D3DXVECTOR3 velocity;
		HRESULT hr = buffer_->GetVelocity(&velocity);
		if (FAILED(hr)) {
			DebugOutput::Trace("音源の速度の取得に失敗しました。[%s, %n]", __FILE__, __LINE__);
			throw COMException("音源の速度の取得に失敗しました。", hr);
		}
		return Vector3f(velocity.x, velocity.y, velocity.z);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetVelocity(const Vector3f& velocity) {
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->SetVelocity(velocity.x, velocity.y, velocity.z, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("音源の速度の設定に失敗しました。[%s, %n]", __FILE__, __LINE__);
			throw COMException("音源の速度の設定に失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	float DirectSound3DAudioBuffer::GetMaxDistance() const {
		float distance;
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->GetMaxDistance(&distance);
		if (FAILED(hr)) {
			DebugOutput::Trace("音源の最大距離の取得に失敗しました。[%s, %d]",__FILE__, __LINE__);
			throw COMException("音源の最大距離の取得に失敗しました。", hr);
		}
		return distance;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetMaxDistance(float maxDistance) {
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->SetMaxDistance(maxDistance, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("音源の最大距離の設定に失敗しました。[%s, %d]",__FILE__, __LINE__);
			throw COMException("音源の最大距離の設定に失敗しました", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	float DirectSound3DAudioBuffer::GetMinDistance() const {
		float distance;
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->GetMinDistance(&distance);
		if (FAILED(hr)) {
			DebugOutput::Trace("音源の最小距離の取得に失敗しました。[%s, %d]",__FILE__, __LINE__);
			throw COMException("音源の最小距離の取得に失敗しました。",hr);
		}
		return distance;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetMinDistance(float minDistance) {
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->SetMinDistance(minDistance, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("音源の最小距離の設定に失敗しました。[%s,%d]",__FILE__, __LINE__);
			throw COMException("音源の最小距離の設定に失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void  DirectSound3DAudioBuffer::Create3DBuffer() {
		auto handle = GetHandle();
		Assert(handle != nullptr);
		
		IDirectSound3DBuffer8* buffer;
		HRESULT hr = handle->QueryInterface(IID_IDirectSound3DBuffer8, reinterpret_cast<void**>(&buffer));
		if (FAILED(hr)) {
			DebugOutput::Trace("IDirectSound3DBuffer8の取得に失敗しました。[%s,%d]",__FILE__, __LINE__);
			throw COMException("IDirectSound3DBuffer8の取得に失敗しました。", hr);
		}

		//スマートポインタの管理下に置く
		buffer_ = buffer;
	}
}