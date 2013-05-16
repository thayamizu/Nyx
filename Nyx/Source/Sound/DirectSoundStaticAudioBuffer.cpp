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
#include "AudioUtility.h"
#include "DirectSoundAudioBuffer.h"
#include "DirectSoundStaticAudioBuffer.h"

namespace Nyx {
	DirectSoundStaticAudioBuffer::DirectSoundStaticAudioBuffer() 
		: audio_(nullptr) {
	}


	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStaticAudioBuffer::DirectSoundStaticAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr dsound, const std::wstring& fileName)
		: audio_(new DirectSoundAudioBuffer(bufferDesc, dsound, fileName)){


			audio_->WriteWaveData(bufferDesc.bufferSize);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::Load(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds, const std::wstring& fileName) {
		if (audio_== nullptr) {
			audio_ = std::make_shared<DirectSoundAudioBuffer>();
		}
		audio_->Load(bufferDesc, ds, fileName);
		audio_->WriteWaveData(bufferDesc.bufferSize);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::Play(bool isLoop) {
		Assert(audio_ != nullptr);
		audio_->Play(isLoop);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::Stop() {
		Assert(audio_ != nullptr);
		audio_->Stop();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::Resume() {
		Assert(audio_ != nullptr);
		audio_->Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::Reset() {
		Assert(audio_ != nullptr);
		audio_->Reset();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::SetPan(long pan) {
		Assert(audio_ != nullptr);
		audio_->SetPan(pan);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::SetVolume(long volume) {
		Assert(audio_ != nullptr);
		audio_->SetVolume(volume);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSoundStaticAudioBuffer::GetPan() const {
		Assert(audio_ != nullptr);
		return audio_->GetPan();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSoundStaticAudioBuffer::GetVolume() const {
		Assert(audio_ != nullptr);
		return audio_->GetVolume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioState DirectSoundStaticAudioBuffer::GetState() const {
		Assert(audio_ != nullptr);
		return audio_->GetState();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::ResetEffect() {
		Assert(audio_ != nullptr);
		audio_->ResetEffect();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::SetEffect(const AudioEffectDesc& effectDesc) {
		Assert(audio_ != nullptr);
		audio_->SetEffect(effectDesc);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	AudioUtility::BufferType DirectSoundStaticAudioBuffer::GetBufferType() const {
		return AudioUtility::BufferType_StaticAudioBuffer;
	}
}