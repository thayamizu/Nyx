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

namespace Nyx {
	//�O���錾
	class  AudioCache;

	///�I�[�f�B�I�}�l�[�W���C���^�t�F�[�X
	class IAudioManager {
	public:
		/**
		* �f�X�g���N�^
		*/
		virtual ~IAudioManager() {}


		/**
		* �I�[�f�B�I�}�l�[�W���̏��������܂�
		*/
		virtual void Initialize(const AudioDesc& desc) = 0;


		/**
		* �I�[�f�B�I�f�[�^�������[�h���܂�
		* @param const std::wstring& �t�@�C����
		* @param SoundBufferType �o�b�t�@�^�C�v
		* @param std::int& index �ǂݍ���ł����I�[�f�B�I�̊Ǘ��ԍ�
		*/
		virtual std::shared_ptr<AudioCache> Load(const std::wstring& fileName, const AudioBufferDesc& desc) = 0;
	};
}
#endif