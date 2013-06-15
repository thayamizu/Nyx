#ifndef NYX_CORE_INCLUDED_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_AUDIO_BUFFER_H_

namespace Nyx
{
	class IAudioBuffer;
	struct AudioState;
	struct AudioBufferDesc;

	///�I�[�f�B�I�o�b�t�@
	class AudioBuffer {
	public:
		/**
		* �R���X�g���N�^
		*/
		explicit AudioBuffer(std::shared_ptr<IAudioBuffer> audioBuffer);
		

		/**
		*�@�I�[�f�B�I�o�b�t�@���Đ����܂�
		*/
		void Play(bool isLoop = false);


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
		*
		*/
		AudioState GetState() const;
		
		/**
		* �t�@�C�������擾���܂�
		* @return const std::wstring& �t�@�C����
		*/
		const std::wstring& GetName() const;

	private:
		std::wstring fileName_;
		std::shared_ptr<IAudioBuffer> audio_;
	};
}

#endif