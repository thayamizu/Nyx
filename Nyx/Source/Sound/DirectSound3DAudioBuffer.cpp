/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "IO/File.h"
#include "Primitive/Vector3.h"
#include "WaveReader.h"
#include "DirectSoundDefinition.h"
#include "DirectSound3DAudioBuffer.h"

namespace nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	dsound_3d_audio_buffer::dsound_3d_audio_buffer()
	:dsound_audio_buffer(), buffer_(nullptr) {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	dsound_3d_audio_buffer::~dsound_3d_audio_buffer() {
	}


	//-------------------------------------------------------------------------------------------------------
	//
	vector3f dsound_3d_audio_buffer::get_position() const {
		NYX_ASSERT(buffer_ != nullptr);
		D3DXVECTOR3 pos;
		HRESULT hr = buffer_->GetPosition(&pos);
		if (FAILED(hr)) {
			debug_out::trace("�����̈ʒu�̎擾�Ɏ��s���܂����B[%s,%n]", __FILE__, __LINE__);
			throw com_exception("�����̈ʒu�̎擾�Ɏ��s���܂����B", hr);
		}
		return vector3f(pos.x, pos.y, pos.z);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_3d_audio_buffer::set_position(const vector3f& pos) {
		NYX_ASSERT(buffer_ != nullptr);
		HRESULT hr = buffer_->SetPosition(pos.x, pos.y, pos.z, NULL);
		if (FAILED(hr)) {
			debug_out::trace("�����̈ʒu�̐ݒ�Ɏ��s���܂����B[%s, %n]", __FILE__, __LINE__);
			throw com_exception("�����̈ʒu�̐ݒ�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	vector3f dsound_3d_audio_buffer::get_velocity() const {
		NYX_ASSERT(buffer_ != nullptr);
		D3DXVECTOR3 velocity;
		HRESULT hr = buffer_->GetVelocity(&velocity);
		if (FAILED(hr)) {
			debug_out::trace("�����̑��x�̎擾�Ɏ��s���܂����B[%s, %n]", __FILE__, __LINE__);
			throw com_exception("�����̑��x�̎擾�Ɏ��s���܂����B", hr);
		}
		return vector3f(velocity.x, velocity.y, velocity.z);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_3d_audio_buffer::set_velocity(const vector3f& velocity) {
		NYX_ASSERT(buffer_ != nullptr);
		HRESULT hr = buffer_->SetVelocity(velocity.x, velocity.y, velocity.z, NULL);
		if (FAILED(hr)) {
			debug_out::trace("�����̑��x�̐ݒ�Ɏ��s���܂����B[%s, %n]", __FILE__, __LINE__);
			throw com_exception("�����̑��x�̐ݒ�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	float dsound_3d_audio_buffer::get_max_distance() const {
		float distance;
		NYX_ASSERT(buffer_ != nullptr);
		HRESULT hr = buffer_->GetMaxDistance(&distance);
		if (FAILED(hr)) {
			debug_out::trace("�����̍ő勗���̎擾�Ɏ��s���܂����B[%s, %d]",__FILE__, __LINE__);
			throw com_exception("�����̍ő勗���̎擾�Ɏ��s���܂����B", hr);
		}
		return distance;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_3d_audio_buffer::set_max_distance(float maxDistance) {
		NYX_ASSERT(buffer_ != nullptr);
		HRESULT hr = buffer_->SetMaxDistance(maxDistance, NULL);
		if (FAILED(hr)) {
			debug_out::trace("�����̍ő勗���̐ݒ�Ɏ��s���܂����B[%s, %d]",__FILE__, __LINE__);
			throw com_exception("�����̍ő勗���̐ݒ�Ɏ��s���܂���", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	float dsound_3d_audio_buffer::get_min_distance() const {
		float distance;
		NYX_ASSERT(buffer_ != nullptr);
		HRESULT hr = buffer_->GetMinDistance(&distance);
		if (FAILED(hr)) {
			debug_out::trace("�����̍ŏ������̎擾�Ɏ��s���܂����B[%s, %d]",__FILE__, __LINE__);
			throw com_exception("�����̍ŏ������̎擾�Ɏ��s���܂����B",hr);
		}
		return distance;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_3d_audio_buffer::set_min_distance(float minDistance) {
		NYX_ASSERT(buffer_ != nullptr);
		HRESULT hr = buffer_->SetMinDistance(minDistance, NULL);
		if (FAILED(hr)) {
			debug_out::trace("�����̍ŏ������̐ݒ�Ɏ��s���܂����B[%s,%d]",__FILE__, __LINE__);
			throw com_exception("�����̍ŏ������̐ݒ�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void  dsound_3d_audio_buffer::create_3d_buffer() {
		auto handle = get_handle();
		NYX_ASSERT(handle != nullptr);
		
		IDirectSound3DBuffer8* buffer;
		HRESULT hr = handle->QueryInterface(IID_IDirectSound3DBuffer8, reinterpret_cast<void**>(&buffer));
		if (FAILED(hr)) {
			debug_out::trace("IDirectSound3DBuffer8�̎擾�Ɏ��s���܂����B[%s,%d]",__FILE__, __LINE__);
			throw com_exception("IDirectSound3DBuffer8�̎擾�Ɏ��s���܂����B", hr);
		}

		//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
		buffer_ = buffer;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_3d_audio_buffer::set_pan(long pan) {
		pan;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	long dsound_3d_audio_buffer::get_pan() const {
		return 1L;
	}
}