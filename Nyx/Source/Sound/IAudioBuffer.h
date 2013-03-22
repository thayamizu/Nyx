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
		IAudioBuffer() :pan(0), volume(0), isLooping(false), isPlaying(false), isPause(false){}
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
		* ���[�v�Đ����ǂ�������
		* @return bool�@���[�v�Đ��Ȃ�true
		*/
		bool IsLooping() const {
			return isLooping;
		} 

		/**
		* �Đ������ǂ���
		* @return bool �Đ����Ȃ�true
		*/
		bool IsPlaying() const  {
			return isPlaying;
		}

		/**
		* �|�[�Y�����ǂ���
		* @return bool �|�[�Y���Ȃ�true
		*/
		bool IsPause() const {
			return isPause;
		}

		/**
		* ���[�v�Đ����邩�ǂ�����ݒ�
		* @param bool ���[�v�Đ��Ȃ�true
		*/
		void SetLooping(bool loop) {
			isLooping = loop;
		}

		/**
		* �Đ������ǂ���
		* @param bool �Đ����Ȃ�true
		*/
		void SetPlaying(bool play) {
			isPlaying = play;
		}

		/**
		* �|�[�Y�����ǂ���
		* @param bool �|�[�Y���Ȃ�true
		*/
		void SetPause(bool pause) {
			isPause = pause;
		}

		/**
		* �p����ݒ肷��
		* @param int �p��
		*/
		void SetPan(int p) {
			pan = p;
		}

		/**
		* �p�����擾����
		* @return long �p��
		*/
		int GetPan()  {
			return pan;
		}

		void SetVolume(int v) {
			volume = v;
		}
		int GetVolume() const {
			return volume;
		}
	private:
		long pan;
		int volume;
		bool isPlaying;///< �Đ���
		bool isLooping;///< ���[�v
		bool isPause;///< �|�[�Y
	};
}
#endif