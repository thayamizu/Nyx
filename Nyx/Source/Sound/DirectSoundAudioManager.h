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
#include "Sound/IAudioManager.h"
#include "DirectSoundDefinition.h"

namespace nyx {
	class iaudio_listener;
	///�I�[�f�B�I�}�l�[�W����DirectSound�ɂ�����
	class dsound_audio_manager : public iaudio_manager{
	public:
		/**
		* �R���X�g���N�^
		*/
		dsound_audio_manager();
		
		
		/**
		* �R���X�g���N�^
		* @param AudioDesc �I�[�f�B�I�������L�q�q
		*/
		dsound_audio_manager(const audio_desc& desc);
		
		
		/**
		* �I�[�f�B�I�}�l�[�W���̏��������܂�
		* @param AudioDesc �I�[�f�B�I�������L�q�q
		*/
		void initialize(const audio_desc& desc);
		

		/**
		* �I�[�f�B�I�o�b�t�@�𐶐����܂�
		* @param const std::wstring& �t�@�C����
		* @param SoundBufferType �o�b�t�@�^�C�v
		* @return std::shared_ptr<AudioBuffer> �I�[�f�B�I�o�b�t�@
		*/
		std::shared_ptr<iaudio_buffer> create_audio_buffer(const std::wstring& fileName, const audio_buffer_desc& bufferDesc);	


		/**
		* �I�[�f�B�I���X�i�[�𐶐����܂�
		* @return std::shared_ptr<IAudioListener> 
		*/
		std::shared_ptr<iaudio_listener> create_audio_listener();	


		/**
		* Wave�t�@�C�������[�h���Ă��܂�
		* @param const std::wstring �t�@�C����
		* @param SoundBufferType �o�b�t�@�̎��
		* @return std::shared_ptr<AudioCache> �I�[�f�B�I�L���b�V��
		*/
		std::shared_ptr<audio_cache> load_audio(const std::wstring& fileName, const audio_buffer_desc& bufferDesc);
		

		/**
		* DirectSound�I�u�W�F�N�g��Ԃ��܂�
		* @return const DirectSoundPtr 
		*/
		const dsound_ptr get_handle();
	private:	
		/**
		* Wave�t�@�C������I�[�f�B�I�o�b�t�@�𐶐����܂�
		* @param const std::wstring& �t�@�C����
		* @param SoundBufferType �o�b�t�@�^�C�v
		* @return std::shared_ptr<AudioBuffer> �I�[�f�B�I�o�b�t�@
		*/
		std::shared_ptr<iaudio_buffer> create_audio_buffer_from_wave(const std::wstring& fileName, const audio_buffer_desc& bufferDesc);
		
	
		/**
		* Ogg�t�@�C������I�[�f�B�I�o�b�t�@�𐶐����܂�
		* @param const std::wstring& �t�@�C����
		* @param SoundBufferType �o�b�t�@�^�C�v
		* @return std::shared_ptr<AudioBuffer> �I�[�f�B�I�o�b�t�@
		*/
		std::shared_ptr<iaudio_buffer> create_audio_buffer_from_ogg(const std::wstring& fileName, const audio_buffer_desc& bufferDesc);
	
		int masterVolume_;	///< �}�X�^�[�{�����[��
		dsound_ptr directSound_;///< DirectSound�I�u�W�F�N�g
		dsound_primary_buffer_ptr primaryBuffer_;
	};
}
#endif