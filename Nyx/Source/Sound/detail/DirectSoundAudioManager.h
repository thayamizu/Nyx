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
#ifndef NYX_CORE_INCLUDED_DIRECTSOUND_AUDIO_MANAGER_H_
#define NYX_CORE_INCLUDED_DIRECTSOUND_AUDIO_MANAGER_H_
#include "Sound/AudioManager.h"

namespace Nyx {
	///�I�[�f�B�I�}�l�[�W����DirectSound�ɂ�����
	class DirectSoundAudioManager : public IAudioManager{
		typedef std::vector< std::shared_ptr<AudioBuffer> > AudioBufferList;
	public:
		/**
		* �R���X�g���N�^
		* @param HWND �E�C���h�E�n���h��
		*/
		DirectSoundAudioManager(HWND hw, int v);

		/**
		* �f�X�g���N�^
		*/
		~DirectSoundAudioManager();
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

		std::shared_ptr<IAudioBuffer> GetAudioBuffer(size_t index);
		/**
		* Wave�t�@�C�������[�h���Ă��܂�
		* @param const std::wstring �t�@�C����
		* @param SoundBufferType �o�b�t�@�̎��
		*/
		bool Load(const std::wstring fileName, SoundBufferType);
	private:

		/**
		* �p�b�L���O���ꂽ�t�@�C������f�[�^���܂Ƃ߂ēǂݍ���ł��܂��B
		* @param const std::wstring �t�@�C����
		* @param SoundBufferType �o�b�t�@�̎��
		* @return �ǂݍ��݂ɐ��������true
		*/
		bool LoadFromPackedFile(const std::wstring fileName, SoundBufferType);

		/**
		* Wave�t�@�C������f�[�^��ǂݍ���ł��܂�
		* @param const std::wstring �t�@�C����
		* @param SoundBufferType �o�b�t�@�̎��
		* @return bool �ǂݍ��݂ɐ��������true
		*/
		bool LoadFromWaveFile(const std::wstring , SoundBufferType);
	private:	
		HWND hWnd;///< �E�C���h�E�n���h��
		DirectSound dsound;///< DirectSound�I�u�W�F�N�g
		int masterVolume;
		AudioBufferList audioBufferList;

	};
}
#endif