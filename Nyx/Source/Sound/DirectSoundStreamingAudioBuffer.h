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
#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STREAMING_AUDIOBUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STREAMING_AUDIOBUFFER_H_
#include "Sound/IAudioBuffer.h"
#include "DirectSoundDefinition.h"

namespace Nyx {
	class AudioBuffer;
	struct AudioBufferDesc;
	class DirectSoundAudioBuffer;

	class DirectSoundStreamingAudioBuffer : public IAudioBuffer {
	public:
		/**
		* �R���X�g���N�^
		*/
		explicit DirectSoundStreamingAudioBuffer();

		/**
		* �R���X�g���N�^
		* @param const DirectSound DirectSound�I�u�W�F�N�g
		* @param std::wstring �t�@�C����
		*/
		explicit DirectSoundStreamingAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds, const std::wstring& fileName);

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
		virtual AudioUtility::BufferType GetBufferType() const = 0;


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