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
#include "AudioCache.h"
#include "IAudioBuffer.h"

namespace Nyx {
//-------------------------------------------------------------------------------------------------------
	//
	struct AudioCache::PImpl {
		typedef std::map<std::wstring,  std::shared_ptr<IAudioBuffer>> AudioBufferList;
		AudioBufferList audioBufferList_;
	};


	//-------------------------------------------------------------------------------------------------------
	//
	AudioCache::AudioCache()
		:pimpl_(new PImpl())
	{

	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioCache::AudioCache(size_t cacheSize) 
		:pimpl_(new PImpl())
	{
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioCache::~AudioCache() {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Add(const std::shared_ptr<IAudioBuffer>& audioBuffer) {
		Assert(pimpl_ != nullptr);
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	void AudioCache::Remove(const std::shared_ptr<IAudioBuffer>& audioBuffer) {
		Assert(pimpl_ != nullptr);

	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::Play(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;	
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::PlayAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::Stop(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::StopAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::Resume(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::ResumeAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::Pause(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return false;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool AudioCache::PauseAll() {
		Assert(pimpl_ != nullptr);

		return false;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	const std::shared_ptr<IAudioBuffer> AudioCache::GetAudioBuffer(const std::wstring& fileName) {
		Assert(pimpl_ != nullptr);

		return nullptr;
	}
}