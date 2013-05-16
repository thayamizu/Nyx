#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STATIC_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STATIC_AUDIO_BUFFER_H_
#include "DirectSoundDefinition.h"
#include "DirectSoundAudioBuffer.h"

namespace Nyx {
	class AudioBuffer;
	struct AudioBufferDesc;
	
	class DirectSoundStaticAudioBuffer : public IAudioBuffer {
	public:
		/**
		* �R���X�g���N�^
		*/
		explicit DirectSoundStaticAudioBuffer();

		/**
		* �R���X�g���N�^
		* @param const DirectSound DirectSound�I�u�W�F�N�g
		* @param std::wstring �t�@�C����
		*/
		explicit DirectSoundStaticAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds, const std::wstring& fileName);

		/**
		* �R���X�g���N�^
		* @param const AudioBufferDesc �I�[�f�B�I�o�b�t�@�L�q�q
		* @param const DirectSound DirectSound�I�u�W�F�N�g
		* @param std::wstring �t�@�C����
		*/
		virtual void Load(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds, const std::wstring& fileName);


		/**
		* �I�[�f�B�I�o�b�t�@���Đ����܂�
		*/
		virtual void Play(bool isLoop);


		/**
		* �I�[�f�B�I�o�b�t�@���~���܂�
		*/
		virtual void Stop();


		/**
		* �I�[�f�B�I�o�b�t�@�����W���[�����܂�
		*/
		virtual void Resume();


		/**
		* �I�[�f�B�I�o�b�t�@�����Z�b�g���܂�
		*/
		virtual void Reset();


		/**
		* �p���̒l��ݒ肵�܂�
		* @param long �p��
		*/
		virtual void SetPan(long pan);


		/**
		* �{�����[���̒l��ݒ肵�܂�
		* @param long �{�����[��
		*/
		virtual void SetVolume(long volume);


		/**
		* �{�����[���̒l���擾���܂�
		* @return long
		*/
		virtual long GetVolume() const;


		/**
		* �p���̒l���擾���܂�
		* @return long
		*/
		virtual long GetPan() const;


		/**
		* �I�[�f�B�I�o�b�t�@�̏�Ԃ̎擾
		* @return AudioState
		*/
		virtual AudioState GetState() const;


		/**
		* �I�[�f�B�I�o�b�t�@�̏�Ԃ̎擾���܂�
		* @return AudioUtility::BufferType
		*/
		virtual AudioUtility::BufferType GetBufferType() const;


		/**
		*�@�I�[�f�B�I�o�b�t�@�ɃG�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		virtual void SetEffect(const AudioEffectDesc& effectDesc);
		
		
		/**
		*�@�I�[�f�B�I�o�b�t�@�̃G�t�F�N�g�����Z�b�g���܂�
		*/
		virtual void ResetEffect();
	private:
		std::shared_ptr<DirectSoundAudioBuffer> audio_;
	};
}
#endif