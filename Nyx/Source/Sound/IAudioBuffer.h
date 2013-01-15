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
#ifndef NYX_CORE_INCLUDED_IAUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_IAUDIO_BUFFER_H_

namespace Nyx {
	///�I�[�f�B�I�o�b�t�@�C���^�t�F�[�X
	class IAudioBuffer {
	public:
		virtual ~IAudioBuffer() {}
		/**
		*�@�Đ�
		*/
		virtual void Play() = 0;
		/**
		*�@��~
		*/
		virtual void Stop() = 0;
		/**
		*�@���W���[��
		*/
		virtual void Resume() = 0;
		/**
		*�@���Z�b�g
		*/
		virtual void Reset()  = 0; 

		/**
		*�@���[�v�����ǂ���
		*/
		virtual bool IsLooping() const = 0;

		/**
		*�@�Đ������ǂ���
		*/
		virtual bool IsPlaying() const = 0;

		/**
		* �|�[�Y�����ǂ���
		*/
		virtual bool IsPause() const = 0;

		/**
		*�@�|�[�Y���邩�ǂ�����ݒ�
		* @param�@bool �|�[�Y����Ȃ�true
		*/
		virtual void SetPause(bool) = 0;

		/**
		*�@���[�v���邩�ǂ�����ݒ�
		* @param bool ���[�v����Ȃ�true
		*/
		virtual void SetLooping(bool loop) = 0;

		/**
		* �Đ������ǂ�����ݒ�
		* @param bool �Đ����Ȃ�true
		*/
		virtual void SetPlaying(bool play) = 0;

		/**
		* �Đ��{�����[����ݒ肷��
		* @param int �{�����[��
		*/
		virtual void SetVolume(int v)  = 0;

		/**
		* �Đ��{�����[�����擾����
		* @return long �{�����[��
		*/
		virtual long GetVolume() const    = 0;

		/**
		* �p����ݒ肷��
		* @param int �p��
		*/
		virtual void SetPan(int pan) = 0;

		/**
		* �p�����擾����
		* @return long �p��
		*/
		virtual long GetPan() const   = 0;
	};
}
#endif