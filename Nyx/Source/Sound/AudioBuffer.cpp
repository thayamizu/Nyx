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
#include "AudioBuffer.h"
#include "AudioUtility.h"
#include "detail/DirectSound/DirectSoundAudioBuffer.h"

namespace Nyx 
{
	//-------------------------------------------------------------------------------------------------------
	//
	AudioBuffer::AudioBuffer(std::shared_ptr<IAudioBuffer> audioBuffer) 
		:audio_(audioBuffer) {
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Play(bool isLoop)  {
		Assert(audio_ != nullptr);
		audio_->Play(isLoop);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Stop()  {
		Assert(audio_ != nullptr);
		audio_->Stop();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Resume()  {
		Assert(audio_ != nullptr);
		audio_->Resume();

	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::Reset()   {
		Assert(audio_ != nullptr);
		audio_->Reset();
	} 


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::SetPan(const long pan) {
		Assert(audio_ != nullptr);
		audio_->SetPan(pan);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long AudioBuffer::GetPan() const  {
		Assert(audio_ != nullptr);
		return audio_->GetPan();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioBuffer::SetVolume(const long volume)  {
		Assert(audio_ != nullptr);
		audio_->SetVolume(volume);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long AudioBuffer::GetVolume() const  {
		Assert(audio_ != nullptr);
		return audio_->GetVolume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioState AudioBuffer::GetState() const {
		Assert(audio_ != nullptr);
		return audio_->GetState();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	const std::wstring& AudioBuffer::GetName() const {
		return fileName_;
	}
}