#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STEREO_AUDIO_BUFFER
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STEREO_AUDIO_BUFFER
#include "IStereoAudioBuffer.h"
#include "DirectSoundAudioBuffer.h"

namespace Nyx {

	///�X�e���I�T�E���h
	class DirectSoundStereoAudioBuffer : public DirectSoundAudioBuffer, public IStereoAudioBuffer {
	public:
		/**
		* �R���X�g���N�^
		*/
		DirectSoundStereoAudioBuffer();


		/**
		* �f�X�g���N�^
		*/
		virtual ~DirectSoundStereoAudioBuffer();


		/**
		* �p���̐ݒ�
		* @param long �p��
		*/
		void SetPan(long pan);


		/**
		* �p���̎擾
		* @return long
		*/
		long GetPan();
	};
}
#endif