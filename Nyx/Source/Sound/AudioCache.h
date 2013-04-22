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
#ifndef NYX_CORE_INCLUDED_AUDIO_CACHE_H_
#define NYX_CORE_INCLUDED_AUDIO_CACHE_H_

namespace Nyx
{
	class AudioBuffer;
	///オーディオキャッシュ
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