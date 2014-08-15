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
#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STREAMING_AUDIOBUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STREAMING_AUDIOBUFFER_H_
#include "DirectSoundDefinition.h"
#include "DirectSoundStereoAudioBuffer.h"

namespace nyx {
	struct audio_buffer_desc;
	class sound_reader;

	///�ÓI�X�g���[�~���O�o�b�t�@�N���X
	class dsound_streaming_audio_buffer : public dsound_stereo_audio_buffer {
	public:
		/**
		* �R���X�g���N�^
		* @param const AudioBufferDesc& bufferDesc
		* @param const DirectSoundPtr 
		* @param const std::wstring& fileName
		*/
		explicit dsound_streaming_audio_buffer(const audio_buffer_desc& bufferDesc, const dsound_ptr dsound, const std::shared_ptr<sound_reader> reader);
		
		
		/**
		* �f�X�g���N�^
		*/
		~dsound_streaming_audio_buffer();
		
		
		/**
		* �I�[�f�B�I�o�b�t�@�̏�Ԃ̎擾���܂�
		* @return BufferType
		*/
		AUDIO_BUFFER_TYPE get_buffer_type() const;

		/**
		* �I�[�f�B�I�o�b�t�@�����Z�b�g���܂��D
		*/
		void reset();
	private:
		/**
		* DirectSound�̃Z�J���_���o�b�t�@��wave�f�[�^���������݂܂�
		* @param size_t �o�b�t�@�T�C�Y
		*/
		void write_wave_data();

		/**
		* DirectSound�Z�J���_���o�b�t�@�L�q�q���쐬���܂�
		* @param DSBUFFERDESC*
		* @param WAVEFORMATEX& wfx
		*/
		void build_dsound_buffer_desc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx);


		/**
		* �ʒm�X���b�h�p�v���V�[�W��
		* @param void* 
		*/
		friend uint64_t _stdcall notify_proc(void* parameter);


		/**
		* �ʒm�X���b�h
		*/
		void notify_thread();
	private:
		HANDLE notifyThreadHandle_;
		static const int NotifyEventNum = 4;
		uint64_t notifySize_;
		uint64_t offset_;
		HANDLE notifyEventList_[NotifyEventNum];
		audio_buffer_desc bufferDesc_;
		std::shared_ptr<sound_reader> waveReader_;
	};
}
#endif