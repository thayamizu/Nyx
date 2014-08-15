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
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�
*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_AUDIO_UTILITY_H_
#define NYX_CORE_INCLUDED_AUDIO_UTILITY_H_
#include "WaveFileHeader.h"

namespace nyx {
	///�I�[�f�B�I���[�e�B���e�B

	class AudioUtility {
	public:
		///�t�H�[�J�X�^�C�v
		enum FOCUS_TYPE {
			FOCUS_TYPE_DEFAULT,
			FOCUS_TYPE_GLOBAL,
			FOCUS_TYPE_STICKY,
			FOCUS_TYPE_NUM,
		};


		///�I�[�f�B�I�o�b�t�@�^�C�v
		enum AUDIO_BUFFER_TYPE{
			AUDIO_BUFFER_TYPE_STATIC,
			AUDIO_BUFFER_TYPE_STATIC_3D,
			AUDIO_BUFFER_TYPE_STREAMING,
			AUDIO_BUFFER_TYPE_STREAMING_3D,
			AUDIO_BUFFER_TYPE_NUM,
		};


		///�I�[�f�B�I�G�t�F�N�g�^�C�v
		enum AUDIO_EFFECT_TYPE {
			AUIO_EFFECT_TYPE_CHORUS,
			AUDIO_EFFECT_TYPE_DISTORTION,
			AUDIO_EFFECT_TYPE_ECHO,
			AUDIO_EFFECT_TYPE_FLANGER,
			AUDIO_EFFECT_TYPE_GARGLE,
			AUDIO_EFFECT_TYPE_PARAMETRIC_EQUALIZER,
			AUDIO_EFFECT_TYPE_REVERB,
			AUDIO_EFFECT_TYPE_RESET,
			AUDIO_EFFECT_TYPE_NUM
		};

		///���p�\API
		enum AUDIO_API_TYPE {
			AUDIO_API_DIRECT_SOUND,
			AUDIO_API_TYPE_NUM
		};


		///�f�t�H���g�r�b�g���[�g
		static const double DEFAULT_BIT_RATE;


		///�f�t�H���g�T���v�����O���[�g
		static const double DEFAULT_SAMPLING_RATE;


		/**
		* �{�����[�����f�V�x���ɕϊ����܂�
		* @param long �{�����[���i1 ~ 100)
		* @return long �f�V�x��
		*/
		static long volume_to_decibel(long volume);


		/**
		* �f�V�x�����{�����[���ɕϊ����܂�
		* @param  long �{�����[��
		* @return long �f�V�x��
		*/
		static long decibel_to_volume(long decibel);


		/**
		* Wave�t�@�C���w�b�_����Wave�t�H�[�}�b�g�����\�z���܂�
		* @param[out] WAVEFORMATEX    Wave�t�@�C���t�H�[�}�b�g
		* @param const WaveFileHeader Wave�t�@�C���w�b�_
		*/
		static void build_wav_format_ex(WAVEFORMATEX* wfx, const wav_file_header& waveHeader);

	};
	///�I�[�f�B�I�������L�q�q
	struct audio_desc {
		uint64_t              reserved; ///< �\��̈�
		HWND				  handle;   ///< �������n���h��
		AudioUtility::AUDIO_API_TYPE apiType;  ///< API�̎��
	};


	///�I�[�f�B�I�o�b�t�@�L�q�q
	struct audio_buffer_desc {
		uint64_t                 reserved;  ///< �\��̈�
		GUID                     algorithm; ///< 3D�o�b�t�@�̍Đ��A���S���Y��
		AudioUtility::AUDIO_BUFFER_TYPE bufferType;///< �I�[�f�B�I�o�b�t�@�̃o�b�t�@�^�C�v
		AudioUtility::FOCUS_TYPE  focusType; ///< �I�[�f�B�I�o�b�t�@�̃t�H�[�J�X�^�C�v
		wav_file_header           waveFormat;
	};


	///�I�[�f�B�I�G�t�F�N�g�L�q�q
	struct audio_effect_desc {
		uint64_t reserved;///< �\��̈�
		AudioUtility::AUDIO_EFFECT_TYPE effectType;///< �G�t�F�N�g�̎��
	};


	///�I�[�f�B�I�X�e�[�^�X
	struct audio_state {
		bool isPlaying;  ///< �Đ����Ă��邩�ǂ���
		bool isLooping;  ///< ���[�v�Đ����ǂ���
		bool isBufferLost;///< �I�[�f�B�I�o�b�t�@�����X�g���Ă邩
	};
}

#endif