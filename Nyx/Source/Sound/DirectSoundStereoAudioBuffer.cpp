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
#include "DirectSoundStereoAudioBuffer.h"

namespace nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	dsound_stereo_audio_buffer::dsound_stereo_audio_buffer() 
		: dsound_audio_buffer(){

	}


	//-------------------------------------------------------------------------------------------------------
	//
	dsound_stereo_audio_buffer::~dsound_stereo_audio_buffer() {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	long dsound_stereo_audio_buffer::get_pan() const {
		auto soundBuffer = get_handle();
		long pan;
		HRESULT hr = soundBuffer->GetPan(&pan);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファのパン値の取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファのパン値の取得に失敗しました。", hr);
		}
		auto volume = decibel_to_volume((pan > 0) ? - pan : pan);
		return (pan > 0)? 100L - volume : volume - 100L;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_stereo_audio_buffer::set_pan(long volume) {
		auto soundBuffer = get_handle();
		NYX_ASSERT(soundBuffer != nullptr);
		const auto ref = 100L;
		volume = math::clamp(volume, -100L, 100L);
		auto pan = volume_to_decibel(ref - math::abs(volume));
		pan = (volume > 0)? pan : -pan;
		HRESULT hr = soundBuffer->SetPan(pan);
		if (FAILED(hr)) {
			debug_out::trace("DirectSoundオーディオバッファのパン値の設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSoundオーディオバッファのパン値の設定に失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	vector3f dsound_stereo_audio_buffer::get_position() const{
		return vector3f();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_stereo_audio_buffer::set_position(const vector3f& velocity){
		velocity;
	}
	
	//-------------------------------------------------------------------------------------------------------
	//
	vector3f dsound_stereo_audio_buffer::get_velocity() const{
		return vector3f();
	}
	
	
	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_stereo_audio_buffer::set_velocity(const vector3f& velocity) {
		velocity;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	float dsound_stereo_audio_buffer::get_max_distance() const{
		return 1.F;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_stereo_audio_buffer::set_max_distance(float maxDistance){
		maxDistance;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	float dsound_stereo_audio_buffer::get_min_distance() const {
		return 1.F;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_stereo_audio_buffer::set_min_distance(float minDistance) {
		minDistance;
	}
}