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
#ifndef NYX_CORE_INCLUDED_AUDIO_CACHE_H_
#define NYX_CORE_INCLUDED_AUDIO_CACHE_H_
#include "Utility/NonCopyable.h"

namespace nyx
{
	class iaudio_buffer;
	struct audio_effect_desc;
	///�I�[�f�B�I�L���b�V��
	class audio_cache : noncopyable {
	public:
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		explicit audio_cache();


		/**
		* �R���X�g���N�^
		* @param size_t �L���b�V���T�C�Y
		*/
		explicit audio_cache(size_t cacheSize);


		/**
		* �Y�����Z�q
		* @param const std::wstring& �t�@�C����
		* @return std::shared_ptr<IAudioBuffer> �I�[�f�B�I�o�b�t�@
		*/
		std::shared_ptr<iaudio_buffer> operator[](const std::wstring& fileName);


		/**
		* �L���b�V���Ƀo�b�t�@��ǉ����܂�
		* @param const std::wstring& �t�@�C����
		* @param std::shared_ptr<IAudioBuffer> �I�[�f�B�I�o�b�t�@
		*/
		void add(const std::wstring& fileName, std::shared_ptr<iaudio_buffer> audioBuffer);


		/**
		* �L���V������o�b�t�@���폜���܂�
		* @param const std::wstring& �t�@�C����
		* @param std::shared_ptr<IAudioBuffer> �I�[�f�B�I�o�b�t�@
		*/
		void remove(const std::wstring& fileName);


		/**
		* �L���V�����N���A���܂�
		*/
		void clear();
		
		
		/**
		* �w�肵���I�[�f�B�I�o�b�t�@���Đ����܂�
		* @param const std::wstring& �t�@�C����
		*/
		void play(const std::wstring& fileName, bool isLoop=true);


		/**
		* �S�ẴI�[�f�B�I�o�b�t�@���Đ����܂�
		*/
		void play_all(bool isLoop=true);
		
		
		/**
		* �w�肵���I�[�f�B�I�o�b�t�@���~���܂�
		* @param const std::wstring& �t�@�C����
		*/
		void stop(const std::wstring& fileName);
		
		
		/**
		* �S�ẴI�[�f�B�I�o�b�t�@���~���܂�
		*/
		void stop_all();

		/**
		* �w�肵���I�[�f�B�I�o�b�t�@�����W���[�����܂�
		*/
		void resume(const std::wstring& fileName);
		
		
		/**
		* �S�ẴI�[�f�B�I�o�b�t�@�����W���[�����܂�
		*/
		void resume_all();
		
		
		/**
		* �w�肵���I�[�f�B�I�o�b�t�@���ꎞ��~���܂�
		*/
		void reset(const std::wstring& fileName);
		
		
		/**
		* �S�ẴI�[�f�B�I�o�b�t�@���ꎞ��~���܂�
		*/
		void reset_all();
		

		/**
		* �w�肵���I�[�f�B�I�o�b�t�@�ɃG�t�F�N�g��ݒ肵�܂�
		* @param const std::wstring& �t�@�C����
		* @param const const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void set_effect(const std::wstring& fileName, const audio_effect_desc& effectDesc);


		/**
		* �S�ẴI�[�f�B�I�o�b�t�@�ɃG�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void set_effect_all(const audio_effect_desc& effectDesc);


		/**
		* �w�肵���I�[�f�B�I�o�b�t�@�̃G�t�F�N�g���폜���܂�
		* @param const std::wstring& �t�@�C����
		*/
		void reset_effect(const std::wstring& fileName);


		/**
		* �S�ẴI�[�f�B�I�o�b�t�@�̃G�t�F�N�g���폜���܂�
		*/
		void reset_effect_all();

		
		/**
		* �w�肵���I�[�f�B�I�o�b�t�@���擾���܂�
		* @param const std::wstring& �t�@�C����
		* @return const std::shared_ptr<IAudioBffer>& �I�[�f�B�Ia�o�b�t�@
		*/
		const std::shared_ptr<iaudio_buffer> get_audio_buffer(const std::wstring& fileName);
	private :
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}


#endif