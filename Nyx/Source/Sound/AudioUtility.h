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

namespace Nyx {
	///�I�[�f�B�I���[�e�B���e�B
	class AudioUtility {
	public:

		///�t�H�[�J�X�^�C�v
		enum FocusType {
			FocusType_DefaultFoucus,
			FocusType_GlobalFocus,
			FocusType_StickyFocus,
			FocusType_FocusTypeNum,
		};


		///�I�[�f�B�I�o�b�t�@�^�C�v
		enum BufferType{
			BufferType_StaticAudioBuffer,
			BufferType_Static3DAudioBuffer,
			BufferType_StreamingAudioBuffer,
			BufferType_Streaming3DAudioBuffer,
			BufferType_BufferTypeNum,
		};


		///�I�[�f�B�I�G�t�F�N�g�^�C�v
		enum EffectType {
			EffectType_Chorus,
			EffectType_Distortion,
			EffectType_Echo,
			EffectType_Flanger,
			EffectType_Gargle,
			EffectType_ParametricEqualizer,
			EffectType_Reverb,
			EffectType_Reset,
			EffectType_EffectTypeNum
		};

		///���p�\API
		enum APIType {
			APIType_DirectSound,
			APIType_APITypeNum
		};


		///�f�t�H���g�r�b�g���[�g
		static const double DefaultBitRate;


		///�f�t�H���g�T���v�����O���[�g
		static const double DefaultSamplingRate;

		
		/**
		* �{�����[�����f�V�x���ɕϊ����܂�
		* @param long �{�����[���i1 ~ 100)
		* @return long �f�V�x��
		*/
		static long VolumeToDecibel(long volume);


		/**
		* �f�V�x�����{�����[���ɕϊ����܂�
		* @param  long �{�����[��
		* @return long �f�V�x��
		*/
		static long DecibelToVolume(long decibel);


		/**
		* Wave�t�@�C���w�b�_����Wave�t�H�[�}�b�g�����\�z���܂�
		* @param[out] WAVEFORMATEX    Wave�t�@�C���t�H�[�}�b�g
		* @param const WaveFileHeader Wave�t�@�C���w�b�_
		*/
		static void BuildWaveFormatEx(WAVEFORMATEX* wfx, const WaveFileHeader& waveHeader);
	private:
		AudioUtility();//�����֎~
	};


	///�I�[�f�B�I�������L�q�q
	struct AudioDesc {
		ulong                 reserved; ///< �\��̈�
		HWND				  handle;   ///< �������n���h��
		AudioUtility::APIType apiType;  ///< API�̎��
	};


	///�I�[�f�B�I�o�b�t�@�L�q�q
	struct AudioBufferDesc {
		ulong                    reserved;  ///< �\��̈�
		GUID                     algorithm; ///< 3D�o�b�t�@�̍Đ��A���S���Y��
		AudioUtility::BufferType bufferType;///< �I�[�f�B�I�o�b�t�@�̃o�b�t�@�^�C�v
		AudioUtility::FocusType  focusType; ///< �I�[�f�B�I�o�b�t�@�̃t�H�[�J�X�^�C�v
		WaveFileHeader           waveFormat;
	};


	///�I�[�f�B�I�G�t�F�N�g�L�q�q
	struct AudioEffectDesc {
		ulong reserved;///< �\��̈�
		AudioUtility::EffectType effectType;///< �G�t�F�N�g�̎��
	};


	///�I�[�f�B�I�X�e�[�^�X
	struct AudioState {
		bool isPlaying;  ///< �Đ����Ă��邩�ǂ���
		bool isLooping;  ///< ���[�v�Đ����ǂ���
		bool isBufferLost;///< �I�[�f�B�I�o�b�t�@�����X�g���Ă邩
	};
}

#endif