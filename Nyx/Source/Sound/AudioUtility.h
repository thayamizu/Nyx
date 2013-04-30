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

namespace Nyx
{
	///�I�[�f�B�I���[�e�B���e�B
	class AudioUtility {
	public:
		///�v���C�I���e�B
		enum Priority {
			DefaultPriority = 0,
			MaxPriority,
			MinPriority,
		};


		///�t�H�[�J�X�^�C�v
		enum Focus {
			DefaultFoucus = 0,
			GlobalFocus,
			StickyFocus,
		};


		///�I�[�f�B�I�o�b�t�@�^�C�v
		enum AudioBufferType{
			StaticAudioBuffer,
			Static3DAudioBufer,
			StreamingAudioBuffer,
			Streaming3DAudioBuffer,
		};


		///���p�\API
		enum APIType {
			DirectSound
		};


		///�f�t�H���g�r�b�g���[�g
		static const double DefaultBitRate;


		///�f�t�H���g�T���v�����O���[�g
		static const double DefaultSamplingRate;


		/**
		* �{�����[�����f�V�x���ɕϊ����܂�
		* @param int �{�����[���i1 ~ 100)
		* @return double �f�V�x��
		*/
		static long VolumeToDecibel(long volume);


		/**
		* �f�V�x�����{�����[���ɕϊ����܂�
		* @param double �{�����[��
		* @return int �f�V�x��
		*/
		static long DecibelToVolume(long decibel);
	private:
		AudioUtility();//�����֎~
	};


	///�I�[�f�B�I�������L�q�q
	struct AudioDesc {
		HWND handle;                    ///< �������n���h��
		AudioUtility::APIType apiType;  ///< API�̎��
	};


	///�I�[�f�B�I�o�b�t�@�L�q�q
	struct AudioBufferDesc {
		ulong				   flag;	  ///< �I�[�f�B�I�o�b�t�@�̃t���O
		ulong                  priority;  ///< �Đ��v���C�I���e�B
		AudioUtility::APIType  apiType;   ///< API�̎��
		AudioUtility::Focus    focusType; ///< �I�[�f�B�I�o�b�t�@�̃t�H�[�J�X���[�h
	};
}

#endif