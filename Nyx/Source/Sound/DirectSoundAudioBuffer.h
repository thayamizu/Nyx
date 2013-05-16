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
#ifndef NYX_CORE_INCLDUED_DIRECTSOUND_AUDIO_BUFFER_H_
#define NYX_CORE_INCLDUED_DIRECTSOUND_AUDIO_BUFFER_H_
#include "DirectSoundDefinition.h"
#include "Sound/IAudioBuffer.h"

namespace Nyx {
	struct AudioBufferDesc;
	class WaveReader;
	///�I�[�f�B�I�o�b�t�@��DirectSound�ɂ�����
	class DirectSoundAudioBuffer {
	public:
		/**
		* �R���X�g���N�^
		*/
		explicit DirectSoundAudioBuffer();

		/**
		* �R���X�g���N�^
		* @param const DirectSound DirectSound�I�u�W�F�N�g
		* @param std::wstring �t�@�C����
		*/
		explicit DirectSoundAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds, const std::wstring& fileName);

		/**
		* �R���X�g���N�^
		* @param const AudioBufferDesc �I�[�f�B�I�o�b�t�@�L�q�q
		* @param const DirectSound DirectSound�I�u�W�F�N�g
		* @param std::wstring �t�@�C����
		*/
		void Load(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds, const std::wstring& fileName);


		/**
		* �Đ�
		*/
		void Play(bool isLoop);


		/**
		* ��~
		*/
		void Stop();


		/**
		* ���W���[��
		*/
		void Resume();


		/**
		* ���Z�b�g
		*/
		void Reset();


		/**
		* �p���̐ݒ�
		* @param long �p��
		*/
		void SetPan(long pan);


		/**
		* �{�����[���̐ݒ�
		* @param long �{�����[��
		*/
		void SetVolume(long volume);


		/**
		* �{�����[���̎擾
		* @return long
		*/
		long GetVolume() const;


		/**
		* �p���̎擾
		* @return long
		*/
		long GetPan() const;


		/**
		* �X�e�[�^�X�R�[�h�̎擾
		* @return ulong
		*/
		ulong GetStatus() const;

		void SetEffect(AudioEffectDesc desc){}
		void ResetEffect() {}
		/**
		* DirectSoundBuffer�̃|�C���^��Ԃ��܂�
		* @return const DirectSoundBufferPtr& DirectSoundBuffer�̃|�C���^
		*/
		const DirectSoundBufferPtr& GetHandle();

		AudioState GetState() const;

		
		/**
		* �o�b�t�@��Wave�f�[�^���������݂܂�
		* @param size_t �o�b�t�@�T�C�Y
		*/
		void WriteWaveData(size_t bufferSize);
		
	protected:
		void BuildDirectSoundBufferDesc(DSBUFFERDESC bufferDesc, WAVEFORMATEX wfx) {}
		void BuildWaveFormatEx(WAVEFORMATEX& wfx);
		
		/**
		*�@�I�[�f�B�I�o�b�t�@�ɃR�[���X�G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void SetChorusEffect(const AudioEffectDesc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�Ƀf�B�X�g�[�V�����G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void SetDistortionEffect(const AudioEffectDesc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�ɃG�R�[�G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void SetEchoEffect(const AudioEffectDesc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�Ƀt�����W���[�G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void SetFlangerEffect(const AudioEffectDesc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�ɃK�[�O���G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void SetGargleEffect(const AudioEffectDesc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�Ƀp�����g���b�N�C�R���C�U�[�G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void SetParametricEqualizerEffect(const AudioEffectDesc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�Ƀ��o�[�u�G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void SetReverbEffect(const AudioEffectDesc& effectDesc);
	private:
		AudioBufferDesc bufferDesc_;
		DirectSoundBufferPtr soundBuffer_;
		std::shared_ptr<WaveReader> waveReader_;
	};
}
#endif