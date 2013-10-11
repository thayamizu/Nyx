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
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "DirectInputDefinition.h"
#include "IKeyBase.h"
#include "KeyCode.h"

namespace Nyx {
	IKeyBase::IKeyBase() 
		: flipCounter_(1) {
			ZeroMemory((void*)&(keyBuffer_[0]), BufferSize);
			ZeroMemory((void*)&(keyBuffer_[1]), BufferSize);
	}

	/**
	*
	*/
	uchar* IKeyBase::GetKeyBuffer() {
		return keyBuffer_[flipCounter_];
	}


	/**
	*
	*/
	bool IKeyBase::IsPressed(KeyCode keycode_) {
		int keycode = static_cast<int>(keycode_);
		return (keyBuffer_[flipCounter_][keycode] & 0x80) != 0;
	}

	/**
	*
	*/
	bool IKeyBase::IsPushed(KeyCode keycode_) {
		int keycode = static_cast<int>(keycode_);
		// �����ꂽ�u�Ԃ�true�ɂ���ꍇ
		if (!(keyBuffer_[ flipCounter_][keycode])) return false;
		if (  keyBuffer_[1-flipCounter_][keycode] ) return false;
		return true;
	}

	/**
	*
	*/
	void IKeyBase::Flip() {
		flipCounter_ ^= 1;
	}
}