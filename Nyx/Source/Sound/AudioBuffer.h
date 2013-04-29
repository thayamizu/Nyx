#ifndef NYX_CORE_INCLUDED_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_AUDIO_BUFFER_H_

#include "IAudioBuffer.h"

namespace Nyx
{
	template<typename T>
	class AudioBuffer {
		static_assert(std::is_base_of<IAudioBuffer, T>::value, "T is base of IAudioBuffer");
	public:
		AudioBuffer() 
			:isLoop(false), isPause(false), isPlay_(false),
			pan_(0), volume_(100) {
		}

		/**
		*�@�Đ�
		*/
		void Play()  {
			buffer_->Play();
		}


		/**
		*�@��~
		*/
		void Stop()  {
			buffer->Stop();
		}


		/**
		*�@���W���[��
		*/
		void Resume()  {
			buffer->Resume();
		}


		/**
		*�@���Z�b�g
		*/
		void Reset()   {
			buffer->Reset();
		} 

		/**
		* �p����ݒ肷��
		* @param int �p��
		*/
		void SetPan(long pan) {
			pan_ = pan;
		}

		/**
		* �p�����擾����
		* @return long �p��
		*/
		long GetPan() const  {
			return pan_;
		}

		/**
		*�@�{�����[����ݒ肷��
		* @return int�@�{�����[��
		*/
		void SetVolume(long volume)  {
			volume_ = volume;
		}

		/**
		* �{�����[�����擾����
		* @return int �{�����[��
		*/
		long GetVolume() const  {
			return volume_;
		}

		/**
		* ���[�v�Đ����ǂ�������
		* @return bool�@���[�v�Đ��Ȃ�true
		*/
		bool IsLooping()  {
			return isLoop_;
		}

		/**
		* �Đ������ǂ���
		* @return bool �Đ����Ȃ�true
		*/
		bool IsPlaying()  const {
			return isPlay_
		}

		/**
		* �|�[�Y�����ǂ���
		* @return bool �|�[�Y���Ȃ�true
		*/
		bool IsPause() const  {
			return isPause_;
		}

		/**
		* ���[�v�Đ����邩�ǂ�����ݒ�
		* @param bool ���[�v�Đ��Ȃ�true
		*/
		void SetLooping(bool loop)  {
			isLoop = loop;
		}

		/**
		* �Đ������ǂ���
		* @param bool �Đ����Ȃ�true
		*/
		void SetPlaying(bool play)  {
			isPlay_ = play;
		}

		/**
		* �|�[�Y�����ǂ���
		* @param bool �|�[�Y���Ȃ�true
		*/
		void SetPause(bool pause)   {
			isPause = pause;
		}
	private:
		bool isLoop_;
		bool isPause_;
		bool isPlay_;
		long volume_;
		long pan_;
		std::shared_ptr<T> buffer_;
	};
}

#endif