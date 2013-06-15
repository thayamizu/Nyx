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
#include "Object/NonCopyable.h"

namespace Nyx
{
	class IAudioBuffer;
	struct AudioEffectDesc;
	///�I�[�f�B�I�L���b�V��
	class AudioCache : NonCopyable {
	public:
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		explicit AudioCache();


		/**
		* �R���X�g���N�^
		* @param size_t �L���b�V���T�C�Y
		*/
		explicit AudioCache(size_t cacheSize);


		/**
		* �Y�����Z�q
		* @param const std::wstring& �t�@�C����
		* @return std::shared_ptr<IAudioBuffer> �I�[�f�B�I�o�b�t�@
		*/
		std::shared_ptr<IAudioBuffer> operator[](const std::wstring& fileName);


		/**
		* �L���b�V���Ƀo�b�t�@��ǉ����܂�
		* @param const std::wstring& �t�@�C����
		* @param std::shared_ptr<IAudioBuffer> �I�[�f�B�I�o�b�t�@
		*/
		void Add(const std::wstring& fileName, std::shared_ptr<IAudioBuffer> audioBuffer);


		/**
		* �L���V������o�b�t�@���폜���܂�
		* @param const std::wstring& �t�@�C����
		* @param std::shared_ptr<IAudioBuffer> �I�[�f�B�I�o�b�t�@
		*/
		void Remove(const std::wstring& fileName);


		/**
		* �L���V�����N���A���܂�
		*/
		void Clear();
		
		
		/**
		* �w�肵���I�[�f�B�I�o�b�t�@���Đ����܂�
		* @param const std::wstring& �t�@�C����
		*/
		void Play(const std::wstring& fileName, bool isLoop=true);


		/**
		* �S�ẴI�[�f�B�I�o�b�t�@���Đ����܂�
		*/
		void PlayAll(bool isLoop=true);
		
		
		/**
		* �w�肵���I�[�f�B�I�o�b�t�@���~���܂�
		* @param const std::wstring& �t�@�C����
		*/
		void Stop(const std::wstring& fileName);
		
		
		/**
		* �S�ẴI�[�f�B�I�o�b�t�@���~���܂�
		*/
		void StopAll();

		/**
		* �w�肵���I�[�f�B�I�o�b�t�@�����W���[�����܂�
		*/
		void Resume(const std::wstring& fileName);
		
		
		/**
		* �S�ẴI�[�f�B�I�o�b�t�@�����W���[�����܂�
		*/
		void ResumeAll();
		
		
		/**
		* �w�肵���I�[�f�B�I�o�b�t�@���ꎞ��~���܂�
		*/
		void Reset(const std::wstring& fileName);
		
		
		/**
		* �S�ẴI�[�f�B�I�o�b�t�@���ꎞ��~���܂�
		*/
		void ResetAll();
		

		/**
		* �w�肵���I�[�f�B�I�o�b�t�@�ɃG�t�F�N�g��ݒ肵�܂�
		* @param const std::wstring& �t�@�C����
		* @param const const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void SetEffect(const std::wstring& fileName, const AudioEffectDesc& effectDesc);


		/**
		* �S�ẴI�[�f�B�I�o�b�t�@�ɃG�t�F�N�g��ݒ肵�܂�
		* @param const AudioEffectDesc& �I�[�f�B�I�G�t�F�N�g�L�q�q
		*/
		void SetEffectAll(const AudioEffectDesc& effectDesc);


		/**
		* �w�肵���I�[�f�B�I�o�b�t�@�̃G�t�F�N�g���폜���܂�
		* @param const std::wstring& �t�@�C����
		*/
		void ResetEffect(const std::wstring& fileName);


		/**
		* �S�ẴI�[�f�B�I�o�b�t�@�̃G�t�F�N�g���폜���܂�
		*/
		void ResetEffectAll();

		
		/**
		* �w�肵���I�[�f�B�I�o�b�t�@���擾���܂�
		* @param const std::wstring& �t�@�C����
		* @return const std::shared_ptr<IAudioBffer>& �I�[�f�B�Ia�o�b�t�@
		*/
		const std::shared_ptr<IAudioBuffer> GetAudioBuffer(const std::wstring& fileName);
	private :
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}


#endif