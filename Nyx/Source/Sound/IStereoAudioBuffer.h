#ifndef NYX_CORE_INCLUDED_ISTEREO_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_ISTEREO_AUDIO_BUFFER_H_

namespace Nyx {
	
	///�X�e���I�T�E���h�̋@�\�����I�[�f�B�I�o�b�t�@�C���^�t�F�[�X
	class IStereoAudioBuffer {
	public:
		virtual ~IStereoAudioBuffer() {}
		/**
		* �I�[�f�B�I�o�b�t�@�̃p���l��ݒ肵�܂�
		* @param long �p��
		*/
		virtual void SetPan(long pan) = 0;


		/**
		* �I�[�f�B�I�o�b�t�@�̃p���l���擾���܂�
		* @return long 
		*/
		virtual long GetPan()= 0;

	};
}
#endif

