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
#include "Sound/AudioBuffer.h"

namespace Nyx {
	using std::shared_ptr;
	///�I�[�f�B�I�o�b�t�@��DirectSound�ɂ�����
	class DirectSoundAudioBuffer : public AudioBuffer {
	public:
		/**
		* �R���X�g���N�^
		* @param const DirectSound DirectSound�I�u�W�F�N�g
		* @param tstring �t�@�C����
		*/
		DirectSoundAudioBuffer(const DirectSound ds, tstring fileName_);

		/**
		* �R���X�g���N�^
		* @param const DirectSound DirectSound�I�u�W�F�N�g
		* @param  shared_ptr<char> waveData
		*/
		DirectSoundAudioBuffer(const DirectSound ds, shared_ptr<char> waveData);

		/**
		*�@�f�X�g���N�^
		*/
		virtual ~DirectSoundAudioBuffer();

		/**
		* �Đ�
		*/
		void Play();

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
		* @param int �p��
		*/
		void SetPan(int pan_);

		/**
		* �{�����[���̐ݒ�
		* @param int �{�����[��
		*/
		void SetVolume(int v);

		/**
		* �{�����[���̎擾
		* @return long
		*/
		long GetVolume() const {
			return volume;
		}

		/**
		* �p���̎擾
		* @return long
		*/
		long GetPan() const {
			return pan;
		}
	private:
		long pan;
		long volume;
		DirectSoundBuffer soundBuffer;
	};
}
#endif