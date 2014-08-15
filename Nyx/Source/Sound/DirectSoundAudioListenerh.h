#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_AUDIO_LISTENER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_AUDIO_LISTENER_H_
#include "IAudioListener.h"
#include "DirectSoundDefinition.h"

namespace nyx {
	class dsound_audio_listener : public iaudio_listener{
	public:
		dsound_audio_listener(dsound_ptr dsound);
		virtual ~dsound_audio_listener();
		/**
		* ���X�i�[�̈ʒu���擾���܂�
		* @return Vecto3f ���X�i�[�̈ʒu�x�N�g��
		*/
		vector3f get_position() const ;


		/**
		*�@���X�i�[�̈ʒu��ݒ肵�܂�
		* @param const Vector3f&�@���X�i�[�̈ʒu�x�N�g��
		*/
		void set_position(const vector3f& pos) ;


		/**
		* ���x�x�N�g�����擾���܂�
		* @return Vector3f�@���X�i�[�̑��x�x�N�g��
		*/
		vector3f get_velocity() const ;


		/**
		*�@���x�x�N�g����ݒ肵�܂�
		* @param const Vector3f& ���X�i�[�̑��x�x�N�g��
		*/
		void set_velocity(const vector3f& velocity) ;


		/**
		* �h�b�v���[�W�����擾���܂�
		* @return float �h�b�v���[�W��
		*/
		float get_doppler_factor() const ;


		/**
		* �h�b�v���[�W����ݒ肵�܂�
		* @param float �h�b�v���[�W��
		*/
		void set_doppler_factor(float dopplerFactor) ;


		/**
		* ���[���I�t�W�����擾���܂�
		* @return ���[���I�t�W��
		*/
		float get_rolloff_factor() const ;


		/**
		* ���[���I�t�W����ݒ肵�܂�
		* @param float ���[���I�t�W��
		*/
		void set_rolloff_factor(float rolloffFactor) ;
	private:
		dsound_3d_listener_ptr listener_;
	};
}
#endif