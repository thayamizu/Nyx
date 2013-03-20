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
#include "Sound/AudioManager.h"
#include "Sound/AudioBuffer.h"
#include "detail/DirectSound/DirectSoundAudioManager.h"
namespace Nyx {

	struct AudioManager::PImpl{
		std::unique_ptr<DirectSoundAudioManager> manager;
	};

	AudioManager::AudioManager() 
		: pimpl_( new PImpl())	
	{

	}
	//--------------------------------------------------------------------------------------
	//
	AudioManager::AudioManager(HWND hwnd, int volume) 
		: pimpl_( new PImpl())	
	{
		Assert(pimpl_ != nullptr);
		pimpl_->manager = std::unique_ptr<DirectSoundAudioManager>( new DirectSoundAudioManager(hwnd, volume));

	}

	//-------------------------------------------------------------------------------------------------------
	//
	AudioManager::~AudioManager() {

	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Create(HWND hwnd, int volume) {
		Assert(pimpl_ != nullptr);
		pimpl_->manager = std::unique_ptr<DirectSoundAudioManager>( new DirectSoundAudioManager(hwnd, volume));

	}
	
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Play(size_t index) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->Play(index);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::PlayAll() {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->PlayAll();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Stop(size_t index) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->Stop(index);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::StopAll() {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->StopAll();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Resume(size_t index) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->Resume(index);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::ResumeAll() {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->ResumeAll();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Reset(size_t index) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->Reset(index);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::ResetAll() {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->ResetAll();
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::SetPause(size_t index, bool p) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->SetPause(index, p);
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::SetPauseAll(bool p) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->SetPauseAll(p);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	int AudioManager::GetMasterVolume() const {
		Assert(pimpl_->manager != nullptr);
		return pimpl_->manager->GetMasterVolume();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::SetMasterVolume(int v) {
		Assert(pimpl_->manager != nullptr);
		pimpl_->manager->SetMasterVolume(v);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioBuffer> AudioManager::GetAudioBuffer(size_t index) {
		Assert(pimpl_->manager != nullptr);
		return pimpl_->manager->GetAudioBuffer(index);
	}

	//---------------------------------------------------------------------------------------
	//
	bool AudioManager::Load(const std::wstring fileName, SoundBufferType bufferType) {
		Assert(pimpl_->manager != nullptr);
		return pimpl_->manager->Load(fileName, bufferType);
	}	
}
