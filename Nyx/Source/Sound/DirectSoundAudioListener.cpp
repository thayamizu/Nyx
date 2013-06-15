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
				DebugOutput::Trace("�v���C�}���o�b�t�@�̎擾�Ɏ��s���܂����B[%s,%d]",__FILE__, __LINE__);
				throw COMException("�v���C�}���o�b�t�@�̎擾�Ɏ��s���܂����B", hr);
			}

			LPDIRECTSOUND3DLISTENER8 listener;
			hr = primary->QueryInterface(IID_IDirectSound3DListener8, (void**)&listener);
			if (FAILED(hr)) {
				DebugOutput::Trace("IDirectSound3DListener8�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B[%s,%d]", __FILE__, __LINE__);
				throw COMException("IDirectSound3DListener8�C���^�t�F�[�X�̎擾�Ɏ��s���܂����B", hr);
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

	//---------------------------------------------------------------------------------------
	//
	void DirectSoundAudioListener::SetRolloffFactor(const float rolloffFactor) {
		Assert(listener_ != nullptr);
		HRESULT hr = listener_->SetRolloffFactor(rolloffFactor, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("���[���I�t�W���̐ݒ�Ɏ��s���܂����B[%s,%d]", __FILE__, __LINE__);
			throw COMException("���[���I�t�W���̐ݒ�Ɏ��s���܂����B", hr);
		}
	}
}