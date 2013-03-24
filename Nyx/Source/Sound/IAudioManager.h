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

namespace Nyx {
	class IAudioBuffer;

	/**
 	 * �T�E���h�o�b�t�@�^�C�v
	 * DirectSound�̏ꍇ�́C3D�Đ����ł��܂���D
	 */
	struct SoundBufferType
	{
		enum enum_t {
			Static,		///< �ÓI�o�b�t�@
			Static3D,	///< �ÓI3D�o�b�t�@
			Streaming,	///< �X�g���[�~���O�o�b�t�@
			Streaming3D, ///< �X�g���[�~���O3D�o�b�t�@
			NumSoundBufferType
		};
	};

	///�I�[�f�B�I�}�l�[�W���C���^�t�F�[�X
	class IAudioManager {
	public:
		/**
		* �f�X�g���N�^
		*/
		virtual ~IAudioManager() {}

		/**
		* ���ׂĂ̋Ȃ��Đ�
		*/
		virtual void PlayAll() = 0;

		/**
		* ���ׂĂ̋Ȃ��~
		*/
		virtual void StopAll() = 0;

		/**
		* ���ׂĂ̋Ȃ����W���[��
		*/
		virtual void ResumeAll() = 0;

		/**
		* ���ׂĂ̋Ȃ����Z�b�g.
		* �Đ����̋Ȃ��~�߂������ŁA�擪�܂Ŋ��߂��܂�
		*/
		virtual void ResetAll() = 0;

		/**
		* ���ׂĂ̋Ȃ��|�[�Y
		* @param bool �|�[�Y����Ȃ�true
		*/
		virtual void SetPauseAll(bool) = 0;

		/**
		* �}�X�^�[�{�����[�����擾
		* @return int �}�X�^�[�{�����[���l
		*/
		virtual int GetMasterVolume() const = 0;

		/**
		* �}�X�^�[�{�����[����ݒ�
		* @param int �}�X�^�[�{�����[���l
		*/
		virtual  void SetMasterVolume(int v) = 0;
	};
}
#endif