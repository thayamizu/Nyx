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
#ifndef NYX_CORE_INCLUDED_DIRECTSOUND_3D_STREAMING_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECTSOUND_3D_STREAMING_AUDIO_BUFFER_H_
#include "Sound/IAudioBuffer.h"
#include "DirectSoundDefinition.h"

namespace Nyx {

	///3D�I�[�f�B�I�o�b�t�@��DirectSound�ɂ�����
	class DirectSound3DStreamingAudioBuffer : public IAudioBuffer {
	public:
		/**
		* �R���X�g���N�^
		* @param const DirectSound DirectSound�I�u�W�F�N�g
		* @param std::wstring �t�@�C����
		*/
		DirectSound3DStreamingAudioBuffer(const DirectSound ds, const std::wstring fileName);

		/**
		* �R���X�g���N�^
		* @param const DirectSound DirectSound�I�u�W�F�N�g
		* @param  shared_ptr<char> waveData
		*/
		DirectSound3DStreamingAudioBuffer(const DirectSound ds, std::shared_ptr<char> wave);

		/**
		* �f�X�g���N�^
		*/
		virtual ~DirectSound3DStreamingAudioBuffer();

		/**
		*�@�Đ�
		*/
		void Play();
		/**
		*�@��~
		*/
		void Stop();

		/**
		*�@���W���[��
		*/
		void Resume();

		/**
		*�@���Z�b�g
		*/
		void Reset();

		/**
		*�@�p����ݒ�
		*/
		void SetPan(long pan);

		/**
		*�@�{�����[����ݒ�
		*/
		void SetVolume(long v);

		/**
		*�@�{�����[���̎擾
		*/
		long GetVolume() const ;

		/**
		*�@�p���̎擾
		*/
		long GetPan() const;
		
		/**
		* �����ʒu��ݒ�
		* @param float x���W
		* @param float y���W
		* @param float z���W
		*/
		void SetPos(float x, float y, float z);

		/**
		* �T�E���h�\�[�X�̍ŏ�������ݒ�
		* @param float �ŏ�����
		*/
		void SetMinDistance(float min);

		/**
		* �T�E���h�\�[�X�̍ő勗����ݒ�
		* @param float �ő勗��
		*/
		void SetMaxDistance(float max);

	private:
		long volume;///< �{�����[��
		long pan;///< �p��
		DirectSoundBuffer soundBuffer; ///< �T�E���h�o�b�t�@
		DirectSound3DBuffer sound3DBuffer;///< 3D�o�b�t�@
		DirectSound3DListener listener; ///<�@���X�i�[

	};
}
#endif
