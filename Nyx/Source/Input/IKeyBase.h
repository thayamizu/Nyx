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
#ifndef NYX_CORE_INCLUDED_IKEY_BASE_H_
#define NYX_CORE_INCLUDED_IKEY_BASE_H_


namespace Nyx {
	/// �L�[���͂̃x�[�X�N���X
	class IKeyBase {
	public:
		/**
		*
		*/
		IKeyBase():flipCounter(1) {
			::ZeroMemory((void*)&(keyBuffer[0]), bufferSize);
			::ZeroMemory((void*)&(keyBuffer[1]), bufferSize);
		}
		/**
		*
		*/
		uchar* GetKeyBuffer() {
			return keyBuffer[flipCounter];
		}
		/**
		*
		*/
		virtual bool Update() = 0;
		/**
		*
		*/
		virtual bool IsPressed(Nyx::uchar keycode) {
			return (keyBuffer[flipCounter][keycode] & 0x80) != 0;
		}

		/**
		*
		*/
		virtual bool IsPushed(Nyx::uchar keycode) {
			// �����ꂽ�u�Ԃ�true�ɂ���ꍇ
			if (!(keyBuffer[ flipCounter][keycode])) return false;
			if (  keyBuffer[1-flipCounter][keycode] ) return false;
			return true;
		}

	protected:
		/**
		*
		*/
		void Flip() {
			flipCounter ^= 1;
		}

		static const int bufferSize=256;
		uchar keyBuffer[2][bufferSize];
		int flipCounter;
	};
}
#endif