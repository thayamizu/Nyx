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
			DebugOutput::Trace("�����̈ʒu�̎擾�Ɏ��s���܂����B[%s,%n]", __FILE__, __LINE__);
			throw COMException("�����̈ʒu�̎擾�Ɏ��s���܂����B", hr);
		}
		return Vector3f(pos.x, pos.y, pos.z);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetPosition(const Vector3f& pos) {
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->SetPosition(pos.x, pos.y, pos.z, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("�����̈ʒu�̐ݒ�Ɏ��s���܂����B[%s, %n]", __FILE__, __LINE__);
			throw COMException("�����̈ʒu�̐ݒ�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	Vector3f DirectSound3DAudioBuffer::GetVelocity() const {
		Assert(buffer_ != nullptr);
		D3DXVECTOR3 velocity;
		HRESULT hr = buffer_->GetVelocity(&velocity);
		if (FAILED(hr)) {
			DebugOutput::Trace("�����̑��x�̎擾�Ɏ��s���܂����B[%s, %n]", __FILE__, __LINE__);
			throw COMException("�����̑��x�̎擾�Ɏ��s���܂����B", hr);
		}
		return Vector3f(velocity.x, velocity.y, velocity.z);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetVelocity(const Vector3f& velocity) {
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->SetVelocity(velocity.x, velocity.y, velocity.z, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("�����̑��x�̐ݒ�Ɏ��s���܂����B[%s, %n]", __FILE__, __LINE__);
			throw COMException("�����̑��x�̐ݒ�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	float DirectSound3DAudioBuffer::GetMaxDistance() const {
		float distance;
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->GetMaxDistance(&distance);
		if (FAILED(hr)) {
			DebugOutput::Trace("�����̍ő勗���̎擾�Ɏ��s���܂����B[%s, %d]",__FILE__, __LINE__);
			throw COMException("�����̍ő勗���̎擾�Ɏ��s���܂����B", hr);
		}
		return distance;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetMaxDistance(float maxDistance) {
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->SetMaxDistance(maxDistance, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("�����̍ő勗���̐ݒ�Ɏ��s���܂����B[%s, %d]",__FILE__, __LINE__);
			throw COMException("�����̍ő勗���̐ݒ�Ɏ��s���܂���", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	float DirectSound3DAudioBuffer::GetMinDistance() const {
		float distance;
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->GetMinDistance(&distance);
		if (FAILED(hr)) {
			DebugOutput::Trace("�����̍ŏ������̎擾�Ɏ��s���܂����B[%s, %d]",__FILE__, __LINE__);
			throw COMException("�����̍ŏ������̎擾�Ɏ��s���܂����B",hr);
		}
		return distance;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSound3DAudioBuffer::SetMinDistance(float minDistance) {
		Assert(buffer_ != nullptr);
		HRESULT hr = buffer_->SetMinDistance(minDistance, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("�����̍ŏ������̐ݒ�Ɏ��s���܂����B[%s,%d]",__FILE__, __LINE__);
			throw COMException("�����̍ŏ������̐ݒ�Ɏ��s���܂����B", hr);
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
			DebugOutput::Trace("IDirectSound3DBuffer8�̎擾�Ɏ��s���܂����B[%s,%d]",__FILE__, __LINE__);
			throw COMException("IDirectSound3DBuffer8�̎擾�Ɏ��s���܂����B", hr);
		}

		//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
		buffer_ = buffer;
	}
}