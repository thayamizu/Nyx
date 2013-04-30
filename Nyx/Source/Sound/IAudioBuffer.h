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
		*�@�I�[�f�B�I�o�b�t�@���Đ����܂�
		*/
		virtual void Play(bool isLoop) = 0;


		/**
		*�@�I�[�f�B�I�o�b�t�@���~���܂�
		*/
		virtual void Stop() = 0;
		
		
		/**
		*�@�I�[�f�B�I�o�b�t�@�����W���[�����܂�
		*/
		virtual void Resume() = 0;
		
		
		/**
		*�@�I�[�f�B�I�o�b�t�@�����Z�b�g���܂�
		*/
		virtual void Reset()  = 0; 

		/**
		* �I�[�f�B�I�o�b�t�@�̃p���l��ݒ肵�܂�
		* @param long �p��
		*/
		virtual void SetPan(long p)=0;


		/**
		* �I�[�f�B�I�o�b�t�@�̃p���l���擾���܂�
		* @return long 
		*/
		virtual long GetPan() const = 0;


		/**
		* �I�[�f�B�I�o�b�t�@�̃{�����[���l��ݒ肵�܂�
		* @return int�@�{�����[��
		*/
		virtual void SetVolume(long volume) = 0;

		
		/**
		* �I�[�f�B�I�o�b�t�@�̃{�����[�����擾���܂�
		* @return int �{�����[��
		*/
		virtual long GetVolume() const = 0;

	};
}
#endif