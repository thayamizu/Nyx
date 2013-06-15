#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_AUDIO_LISTENER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_AUDIO_LISTENER_H_
#include "IAudioListener.h"
#include "DirectSoundDefinition.h"

namespace Nyx {
	class DirectSoundAudioListener : public IAudioListener{
	public:
		DirectSoundAudioListener(DirectSoundPtr dsound);
		virtual ~DirectSoundAudioListener();
		/**
		* ���X�i�[�̈ʒu���擾���܂�
		* @return Vecto3f ���X�i�[�̈ʒu�x�N�g��
		*/
		Vector3f GetPosition() const ;


		/**
		*�@���X�i�[�̈ʒu��ݒ肵�܂�
		* @param const Vector3f&�@���X�i�[�̈ʒu�x�N�g��
		*/
		void SetPosition(const Vector3f& pos) ;


		/**
		* ���x�x�N�g�����擾���܂�
		* @return Vector3f�@���X�i�[�̑��x�x�N�g��
		*/
		Vector3f GetVelocity() const ;


		/**
		*�@���x�x�N�g����ݒ肵�܂�
		* @param const Vector3f& ���X�i�[�̑��x�x�N�g��
		*/
		void SetVelocity(const Vector3f& velocity) ;


		/**
		* �h�b�v���[�W�����擾���܂�
		* @return float �h�b�v���[�W��
		*/
		float GetDopplerFactor() const ;


		/**
		* �h�b�v���[�W����ݒ肵�܂�
		* @param float �h�b�v���[�W��
		*/
		void SetDopplerFactor(float dopplerFactor) ;


		/**
		* ���[���I�t�W�����擾���܂�
		* @return ���[���I�t�W��
		*/
		float GetRolloffFactor() const ;


		/**
		* ���[���I�t�W����ݒ肵�܂�
		* @param float ���[���I�t�W��
		*/
		void SetRolloffFactor(float rolloffFactor) ;
	private:
		DirectSound3DListenerPtr listener_;
	};
}
#endif