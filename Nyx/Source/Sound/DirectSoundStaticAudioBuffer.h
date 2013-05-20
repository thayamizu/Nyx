#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STATIC_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STATIC_AUDIO_BUFFER_H_
#include "DirectSoundDefinition.h"
#include "DirectSoundStereoAudioBuffer.h"

namespace Nyx {
	struct AudioBuffeDesc;
	class WaveReader;

	///�ÓI�o�b�t�@
	class DirectSoundStaticAudioBuffer : public DirectSoundStereoAudioBuffer {
	public:
		/**
		* �R���X�g���N�^
		* @param const AudioBufferDesc& bufferDesc
		* @param const DirectSoundPtr 
		* @param const std::wstring& fileName
		*/
		DirectSoundStaticAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr dsound, const std::wstring& fileName);
		

		/**
		* �I�[�f�B�I�o�b�t�@�̏�Ԃ̎擾���܂�
		* @return AudioUtility::BufferType
		*/
		AudioUtility::BufferType GetBufferType() const;
	private:
		/**
		* DirectSound�̃Z�J���_���o�b�t�@��wave�f�[�^���������݂܂�
		* @param size_t �o�b�t�@�T�C�Y
		*/
		void WriteWaveData(size_t bufferSize);


		/**
		* �ÓI��DirectSound�Z�J���_���o�b�t�@�L�q�q���쐬���܂�
		* @param DSBUFFERDESC*
		* @param WAVEFORMATEX& wfx
		*/
		void BuildDirectSoundBufferDesc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx);
	private:
		AudioBufferDesc bufferDesc_;
		std::shared_ptr<WaveReader> waveReader_;
	};
}
#endif