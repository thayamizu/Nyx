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
#include "Sound/AudioManager.h"
#include "Sound/AudioBuffer.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	AudioManager::~AudioManager() {
		SetPauseAll(false);//ポーズ解除
		//StopAll();		   //すべての音を停止

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