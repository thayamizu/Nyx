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
#ifndef NYX_CORE_INCLUDED_IAUDIO_MANAGER_H_
#define NYX_CORE_INCLUDED_IAUDIO_MANAGER_H_
#include "AudioUtility.h"

namespace nyx {
	//�O���錾
	class iaudio_listener;
	class audio_cache;

	///�I�[�f�B�I�}�l�[�W���C���^�t�F�[�X
	class iaudio_manager {
	public:
		/**
		* �f�X�g���N�^
		*/
		virtual ~iaudio_manager() {}


		/**
		* �I�[�f�B�I�}�l�[�W���̏��������܂�
		* const AudioDesc& �I�[�f�B�I�������L�q�q
		*/
		virtual void initialize(const audio_desc& desc) = 0;


		/**
		* �I�[�f�B�I�o�b�t�@�𐶐����܂�
		* @param const std::wstring& �t�@�C����
		* @param AudioBufferDesc �o�b�t�@�^�C�v
		* @return std::shared_ptr<AudioBuffer> �I�[�f�B�I�o�b�t�@
		*/
		virtual std::shared_ptr<iaudio_buffer> create_audio_buffer(const std::wstring& fileName, const audio_buffer_desc& bufferDesc) = 0;


		/**
		* �I�[�f�B�I���X�i�[�𐶐����܂�
		* @return std::shared_ptr<IAudioListener> 
		*/
		virtual std::shared_ptr<iaudio_listener> create_audio_listener() = 0;	


		/**
		* �I�[�f�B�I�f�[�^�������[�h���܂�
		* @param const std::wstring& �t�@�C����
		* @param SoundBufferType �o�b�t�@�^�C�v
		* @param std::int& index �ǂݍ���ł����I�[�f�B�I�̊Ǘ��ԍ�
		*/
		virtual std::shared_ptr<audio_cache> load_audio(const std::wstring& fileName, const audio_buffer_desc& desc) = 0;
	};
}
#endif