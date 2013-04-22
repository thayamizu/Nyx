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
#ifndef NYX_CORE_INCLUDED_AUDIO_CACHE_H_
#define NYX_CORE_INCLUDED_AUDIO_CACHE_H_

namespace Nyx
{
	class AudioBuffer;
	///�I�[�f�B�I�L���b�V��
	class AudioCache {
		explicit AudioCache();
		explicit AudioCache(size_t cacheSize);
		~AudioCache();
		void Add(const std::shared_ptr<AudioBuffer>& audioBuffer);
		void Remove(const std::shared_ptr<AudioBuffer>& audioBuffer);
		void Clear();
		bool Play(const std::wstring& fileName);
		bool PlayAll();
		bool Stop(const std::wstring& fileName);
		bool StopAll();
		bool Resume(const std::wstring& fileName);
		bool ResumeAll();
		bool Pause(const std::wstring& fileName);
		bool PauseAll();
		const std::shared_ptr<AudioBuffer> GetAudioBuffer(const std::wstring& fileName);
	private :
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};

	AudioCache::AudioCache(){

	}
	AudioCache::AudioCache(size_t cacheSize) {

	}
	AudioCache::~AudioCache() {

	}

	void AudioCache::Add(const std::shared_ptr<AudioBuffer>& audioBuffer) {

	}
	
	void AudioCache::Remove(const std::shared_ptr<AudioBuffer>& audioBuffer) {

	}
	
	void AudioCache::Play(const std::wstring& fileName) {

	}
	
	bool AudioCache::PlayAll() {
		return false;
	}
	
	bool AudioCache::Stop(const std::wstring& fileName) {
		return false;
	}
	
	bool AudioCache::StopAll() {
		return false;
	}
	
	bool AudioCache::Resume(const std::wstring& fileName) {
		return false;
	}
	
	bool AudioCache::ResumeAll() {
		return false;
	}
	
	bool AudioCache::Pause(const std::wstring& fileName) {
		return false;
	}

	bool AudioCache::PauseAll() {
		return false;
	}

	const std::shared_ptr<AudioBuffer> GetAudioBuffer(const std::wstring& fileName) {
		return nullptr;
	}
}


#endif