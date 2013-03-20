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
#ifndef NYX_CORE_INCLUDED_AUDIO_MANAGER_H_
#define NYX_CORE_INCLUDED_AUDIO_MANAGER_H_
#include "Sound/IAudioManager.h"

namespace Nyx {
	//�O���錾
	class IAudioBuffer;

	enum SoundBufferType
	{
		Static,		///< �ÓI�o�b�t�@
		Static3D,	///< �ÓI3D�o�b�t�@
		Streaming,	///< �X�g���[�~���O�o�b�t�@
		Streaming3D, ///< �X�g���[�~���O3D�o�b�t�@
		NumSoundBufferType
	};

	///�I�[�f�B�I�}�l�[�W��
	class AudioManager : public IAudioManager{
	public:
		AudioManager();
		AudioManager(HWND hwnd, int volume);


		/**
		* �f�X�g���N�^
		*/
		virtual ~AudioManager();

		void Create(HWND hwnd, int volume);

		/**
		* �w�肵���C���f�b�N�X�̋Ȃ��Đ�����
		* @param size_t �C���f�b�N�X
		*/
		virtual void Play(size_t index);

		/**
		* ���ׂĂ̋Ȃ��Đ�����
		*/
		virtual void PlayAll();

		/**
		* �w�肵���C���f�b�N�X�̋Ȃ��~
		* @param size_t �C���f�b�N�X
		*/
		virtual void Stop(size_t index);

		/**
		*���ׂĂ̋Ȃ��~
		*/
		virtual void StopAll();

		/**
		* �w�肵���C���f�b�N�X�̋Ȃ����W���[������
		* @param size_t �C���f�b�N�X
		*/
		virtual void Resume(size_t index);

		/**
		* ���ׂĂ̋Ȃ����W���[������
		*/
		virtual void ResumeAll();

		/**
		* �w�肵���C���f�b�N�X�̋Ȃ����Z�b�g
		* �܂�A�I�[�f�B�I����������~�߂āA�擪�܂Ŋ��߂��܂��B
		* @param size_t �C���f�b�N�X
		*/
		virtual void Reset(size_t index);

		/**
		* ���ׂĂ̋Ȃ����Z�b�g����
		*/
		virtual void ResetAll();

		/**
		*�@�w�肵���C���f�b�N�X���|�[�Y������
		* @param size_t �C���f�b�N�X
		* @param bool �|�[�Y����Ȃ�true
		*/
		virtual void SetPause(size_t index, bool);

		/**
		* ���ׂĂ̋Ȃ��|�[�Y������
		* @param bool �|�[�Y����Ȃ�true  
		*/
		virtual void SetPauseAll(bool) ;

		/**
		* �}�X�^�[�{�����[�����擾
		* @return int �}�X�^�[�{�����[���l
		*/
		virtual int GetMasterVolume() const ;

		/**
		* �}�X�^�[�{�����[����ݒ�
		* @param int �}�X�^�[�{�����[���l
		*/
		virtual void SetMasterVolume(int v) ;
		virtual bool Load(std::wstring fileName, SoundBufferType bufferType);
		/**
		* �I�[�f�B�I�o�b�t�@���擾
		* @param size_t �C���f�b�N�X
		*/
		std::shared_ptr<IAudioBuffer> GetAudioBuffer(size_t index);
	protected:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};
}
#endif