#ifndef NYX_CORE_INCLUDED_IAUDIO_LISTENER_
#define NYX_CORE_INCLUDED_IAUDIO_LISTENER_

namespace Nyx {
	
	class Vector3f;
	///�I�[�f�B�I���X�i�[
	class IAudioListener {
	public:
		~IAudioListener() {}
	
		/**
		* ���X�i�[�̈ʒu���擾���܂�
		* @return Vecto3f ���X�i�[�̈ʒu�x�N�g��
		*/
		virtual Vector3f GetPosition() const = 0;
	

		/**
		*�@���X�i�[�̈ʒu��ݒ肵�܂�
		* @param const Vector3f&�@���X�i�[�̈ʒu�x�N�g��
		*/
		virtual void SetPosition(const Vector3f& pos) = 0;
		
		
		/**
		* ���x�x�N�g�����擾���܂�
		* @return Vector3f�@���X�i�[�̑��x�x�N�g��
		*/
		virtual Vector3f GetVelocity() const = 0;
		
		
		/**
		*�@���x�x�N�g����ݒ肵�܂�
		* @param const Vector3f& ���X�i�[�̑��x�x�N�g��
		*/
		virtual void SetVelocity(const Vector3f& velocity) = 0;


		/**
		* �h�b�v���[�W�����擾���܂�
		* @return float �h�b�v���[�W��
		*/
		virtual float GetDopplerFactor() const = 0;
		

		/**
		* �h�b�v���[�W����ݒ肵�܂�
		* @param float �h�b�v���[�W��
		*/
		virtual void SetDopplerFactor(float dopplerFactor) = 0;
		

		/**
		* ���[���I�t�W�����擾���܂�
		* @return ���[���I�t�W��
		*/
		virtual float GetRolloffFactor() const = 0;
		
		
		/**
		* ���[���I�t�W����ݒ肵�܂�
		* @param float ���[���I�t�W��
		*/
		virtual void SetRolloffFactor(float rolloffFactor) = 0;
	};
}
#endif