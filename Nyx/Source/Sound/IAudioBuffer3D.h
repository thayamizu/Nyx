#ifndef NYX_CORE_INCLUDED_IAUDIO_BUFFER_3D_H_
#define NYX_CORE_INCLUDED_IAUDIO_BUFFER_3D_H
namespace Nyx {
	///3D�I�[�f�B�I�o�b�t�@�C���^�t�F�[�X
	class IAudioBuffer3D {
	public:
		virtual void GetPosition() = 0;
		virtual void SetPosition() = 0;
		virtual void GetVelocity() = 0;
		virtual void SetVelocity() = 0;

		/**
		* ��������̍ő勗�����擾���܂�
		* @return float ��������̍ő勗��
		*/
		virtual float GetMaxDistance() const = 0;


		/**
		* ��������̍ő勗����ݒ肵�܂�
		* @param float  �ő勗��
		*/
		virtual void SetMaxDistance(float maxDistance) = 0;
		

		/**
		* ��������̍ŏ�������ݒ肵�܂�
		* @param float  �ŏ�����
		*/
		virtual float GetMinDistance() const = 0;


		/**
		* ��������̍ŏ��������擾���܂�
		* @return float ��������̍ŏ�����
		*/
		virtual void SetMinDistance(float minDistance) = 0;
	};
}
#endif