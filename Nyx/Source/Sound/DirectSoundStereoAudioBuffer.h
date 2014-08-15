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
#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STEREO_AUDIO_BUFFER
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STEREO_AUDIO_BUFFER
#include "DirectSoundAudioBuffer.h"
#include "Primitive/Vector3.h"

namespace nyx {

	///�X�e���I�T�E���h
	class dsound_stereo_audio_buffer : public dsound_audio_buffer{
	public:
		/**
		* �R���X�g���N�^
		*/
		dsound_stereo_audio_buffer();


		/**
		* �f�X�g���N�^
		*/
		virtual ~dsound_stereo_audio_buffer();


		/**
		* �p���̐ݒ�
		* @param long �p��
		*/
		void set_pan(long pan);


		/**
		* �p���̎擾
		* @return long
		*/
		long get_pan() const;
	protected:
		virtual vector3f get_position() const ;
		virtual void set_position(const vector3f& velocity) ;
		virtual vector3f get_velocity() const ;
		virtual void set_velocity(const vector3f& velocity) ;

		/**
		* ��������̍ő勗�����擾���܂�
		* @return float ��������̍ő勗��
		*/
		virtual float get_max_distance() const ;


		/**
		* ��������̍ő勗����ݒ肵�܂�
		* @param float  �ő勗��
		*/
		virtual void set_max_distance(float maxDistance) ;


		/**
		* ��������̍ŏ�������ݒ肵�܂�
		* @param float  �ŏ�����
		*/
		virtual float get_min_distance() const ;


		/**
		* ��������̍ŏ��������擾���܂�
		* @return float ��������̍ŏ�����
		*/
		virtual void set_min_distance(float minDistance) ;
	};
}
#endif