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
#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_3D_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_3D_AUDIO_BUFFER_H_
#include "DirectSoundAudioBuffer.h"
#include "DirectSoundDefinition.h"
#include "Primitive/Vector3.h"

namespace nyx {
	class dsound_3d_audio_buffer : public dsound_audio_buffer {
	public:
		/**
		* �R���X�g���N�^
		*/
		dsound_3d_audio_buffer();
		
		
		/**
		* �f�X�g���N�^
		*/
		~dsound_3d_audio_buffer();


		/**
		* �����̈ʒu���擾���܂�
		* @return Vector3f
		*/
		vector3f get_position() const;
		
		
		/**
		* �����̈ʒu��ݒ肵�܂�
		* @param const Vector3f&
		*/
		void set_position(const vector3f& pos);

		
		/**
		* �����̑��x���擾���܂�
		* @return Vector3f 
		*/
		vector3f get_velocity() const ;
		
		/**
		* �����̑��x��ݒ肵�܂�
		* @param const Vector3f & veclocity
		*/
		void set_velocity(const vector3f& velocity);


		/**
		* ��������̍ő勗�����擾���܂�
		* @return float ��������̍ő勗��
		*/
		float get_max_distance() const;


		/**
		* ��������̍ő勗����ݒ肵�܂�
		* @param float  �ő勗��
		*/
		void set_max_distance(float maxDistance);


		/**
		* ��������̍ŏ�������ݒ肵�܂�
		* @param float  �ŏ�����
		*/
		float get_min_distance() const;


		/**
		* ��������̍ŏ��������擾���܂�
		* @return float ��������̍ŏ�����
		*/
		void set_min_distance(float minDistance);
	protected:
		/**
		* 3D�o�b�t�@���쐬���܂��D
		*/
		void create_3d_buffer();

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
	private:
		dsound_3d_buffer_ptr buffer_;
	};
}
#endif
