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
#include "Sound/AudioManager.h"
#include "Sound/AudioBuffer.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	AudioManager::~AudioManager() {
		SetPauseAll(false);//�|�[�Y����
		//StopAll();		   //���ׂẲ����~

		AudioBufferListIterator it  = audioBufferList.begin();
		AudioBufferListIterator end = audioBufferList.end();

		while (it != end) {
			SafeDelete(*it);
			it++;
		}
		audioBufferList.clear();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Play(uint index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Play();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::PlayAll() {

		AudioBufferListIterator it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Play();
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Stop(uint index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Stop();


	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::StopAll() {
		AudioBufferListIterator it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Stop();
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Resume(uint index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Resume();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::ResumeAll() {
		AudioBufferListIterator it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Resume();
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Reset(uint index) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->Reset();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::ResetAll() {
		AudioBufferListIterator it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->Reset();
			++it;
		}
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::SetPause(uint index, bool p) {
		if (index >= audioBufferList.size()) return;

		audioBufferList[index]->SetPause(p);
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::SetPauseAll(bool p) {

		AudioBufferListIterator it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->SetPause(p);
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	int AudioManager::GetMasterVolume() const {
		return masterVolume;
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::SetMasterVolume(int v) {
		if (v > 100) { v = 100;}
		else if (v < 0) {v=0;}
		masterVolume = v;

		AudioBufferListIterator it = audioBufferList.begin();
		while (it != audioBufferList.end()) {
			(*it)->SetVolume(v);
			++it;
		}
	}

	//-------------------------------------------------------------------------------------------------------
	//
	AudioBuffer* AudioManager::GetAudioBuffer(uint index) {
		if (index >= audioBufferList.size()) return NULL;

		return audioBufferList[index];
	}
}