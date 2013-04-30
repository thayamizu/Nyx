#ifndef NYX_CORE_INCLUDED_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_AUDIO_BUFFER_H_

#include "IAudioBuffer.h"

namespace Nyx
{
	struct AudioBufferDesc;

	///�I�[�f�B�I�o�b�t�@
	class AudioBuffer {
	public:
		/**
		* �R���X�g���N�^
		*/
		AudioBuffer();
		

		/**
		* �R���X�g���N�^
		* @param const AudioBuffer& �I�[�f�B�I�o�b�t�@�L�q�q
		*/
		AudioBuffer(const AudioBufferDesc& bufferDesc);


		/**
		* �o�b�t�@�̐���
		* @param const AudioBuffer& �I�[�f�B�I�o�b�t�@�L�q�q
		*/
		void CreateBuffer(const AudioBufferDesc& bufferDesc);


		/**
		*�@�I�[�f�B�I�o�b�t�@���Đ����܂�
		*/
		void Play();


		/**
		*�@�I�[�f�B�I�o�b�t�@���~���܂�
		*/
		void Stop();


		/**
		*�@�I�[�f�B�I�o�b�t�@�����W���[�����܂�
		*/
		void Resume();


		/**
		*�@�I�[�f�B�I�o�b�t�@�����Z�b�g���܂�
		*/
		void Reset();

		/**
		* �I�[�f�B�I�o�b�t�@�̃p���l��ݒ肵�܂�
		* @param int �p��
		*/
		void SetPan(long pan);


		/**
		* �I�[�f�B�I�o�b�t�@�̃p���l���擾���܂�
		* @return long �p��
		*/
		long GetPan() const;


		/**
		* �I�[�f�B�I�o�b�t�@�̃{�����[���l��ݒ肵�܂�
		* @return int�@�{�����[��
		*/
		void SetVolume(long volume);


		/**
		* �I�[�f�B�I�o�b�t�@�̃{�����[���l���擾���܂�
		* @return int �{�����[��
		*/
		long GetVolume() const;


		/**
		* �I�[�f�B�I�o�b�t�@�����[�v�Đ����ǂ������肵�܂�
		* @return bool�@���[�v�Đ��Ȃ�true
		*/
		bool IsLooping();

		
		/**
		* �I�[�f�B�I�o�b�t�@�����[�v�Đ����邩�ǂ�����ݒ肵�܂�
		* @param bool ���[�v�Đ��Ȃ�true
		*/
		void SetLooping(bool loop);

		
		/**
		* �I�[�f�B�I�o�b�t�@���Đ������ǂ������肵�܂�
		* @return bool �Đ����Ȃ�true
		*/
		bool IsPlaying() const;


		/**
		* �I�[�f�B�I�o�b�t�@���|�[�Y�����ǂ������肵�܂�
		* @return bool �|�[�Y���Ȃ�true
		*/
		bool IsPause() const;
	

		/**
		* �I�[�f�B�I�o�b�t�@���|�[�Y���܂�
		* @param bool �|�[�Y���Ȃ�true
		*/
		void SetPause(bool pause);
	

		/**
		* �t�@�C�������擾���܂�
		* @return const std::wstring& �t�@�C����
		*/
		const std::wstring& GetName() const;

	private:
		bool isLoop_;
		bool isPause_;
		bool isPlay_;
		std::wstring fileName;
		std::shared_ptr<IAudioBuffer> audio_;
	};
}

#endif