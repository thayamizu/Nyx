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

namespace nyx {
	///�I�[�f�B�I�o�b�t�@��DirectSound�ɂ�����
	class dsound_audio_buffer : public iaudio_buffer{
	public:
		/**
		* �R���X�g���N�^
		*/
		explicit dsound_audio_buffer();

		/**
		* �R���X�g���N�^
		* @param const AudioBufferDesc �I�[�f�B�I�o�b�t�@�L�q�q
		* @param const DirectSound DirectSound�I�u�W�F�N�g
		* @param std::wstring �t�@�C����
		*/
		virtual void load(const audio_buffer_desc& bufferDesc, const dsound_ptr ds);


		/**
		* �Đ�
		*/
		virtual void play(bool isLoop);


		/**
		* ��~
		*/
		virtual void stop();


		/**
		* ���W���[��
		*/
		virtual void resume();


		/**
		* ���Z�b�g
		*/
		virtual void reset();


		/**
		* �{�����[���̐ݒ�
		* @param long �{�����[��
		*/
		virtual void set_volume(long volume);


		/**
		* �{�����[���̎擾
		* @return long
		*/
		virtual long get_volume() const;


		/**
		* �X�e�[�^�X�R�[�h�̎擾
		* @return ulong
		*/
		virtual uint64_t get_status() const;


		/**
		*�@�I�[�f�B�I�o�b�t�@�ɃG�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		virtual void set_effect(const audio_effect_desc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�̃G�t�F�N�g�����Z�b�g���܂�
		*/
		virtual void reset_effect();


		/**
		* DirectSoundBuffer�̃|�C���^��Ԃ��܂�
		* @return const DirectSoundBufferPtr& DirectSoundBuffer�̃|�C���^
		*/
		virtual const dsound_buffer_ptr& get_handle() const;


		/**
		* �I�[�f�B�I�o�b�t�@�̏�Ԃ̎擾
		* @return AudioState
		*/
		virtual audio_state get_audio_state() const;


	protected:
		/**
		* AudioBufferDesc����DSBUFFERDESC���\�z���܂�
		* @param [out] DSBUFFERDESC
		* @param const AudioBufferDesc&
		*/
		virtual void build_dsound_buffer_desc(DSBUFFERDESC* bufferDesc, WAVEFORMATEX& wfx) = 0;


		/**
		* �o�b�t�@��Wave�f�[�^���������݂܂�
		* @param size_t �o�b�t�@�T�C�Y
		*/
		virtual void write_wave_data() = 0;
	private:	
		/**
		*�@�I�[�f�B�I�o�b�t�@�ɃR�[���X�G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void set_chorus_effect(const audio_effect_desc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�Ƀf�B�X�g�[�V�����G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void set_distortion_effect(const audio_effect_desc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�ɃG�R�[�G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void set_echo_effect(const audio_effect_desc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�Ƀt�����W���[�G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void set_flanger_effect(const audio_effect_desc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�ɃK�[�O���G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void set_gargle_effect(const audio_effect_desc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�Ƀp�����g���b�N�C�R���C�U�[�G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void set_parametric_equalizer_effect(const audio_effect_desc& effectDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@�Ƀ��o�[�u�G�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void set_reverb_effect(const audio_effect_desc& effectDesc);
	private:
		bool isLoop_;
		dsound_buffer_ptr soundBuffer_;
	};
}
#endif