#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STEREO_AUDIO_BUFFER
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STEREO_AUDIO_BUFFER
#include "IStereoAudioBuffer.h"
#include "DirectSoundAudioBuffer.h"

namespace Nyx {

	///ステレオサウンド
	class DirectSoundStereoAudioBuffer : public DirectSoundAudioBuffer, public IStereoAudioBuffer {
	public:
		/**
		* コンストラクタ
		*/
		DirectSoundStereoAudioBuffer();


		/**
		* デストラクタ
		*/
		virtual ~DirectSoundStereoAudioBuffer();


		/**
		* パンの設定
		* @param long パン
		*/
		void SetPan(long pan);


		/**
		* パンの取得
		* @return long
		*/
		long GetPan();
	};
}
#endif