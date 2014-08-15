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
#include "Timer/ITimer.h"
#include "Win32Timer.h"

namespace nyx {
	//---------------------------------------------------------------------------------------
	win32_timer::win32_timer()
	: offsetTime(0), pauseTime(0), 
	  isPaused(false),timeCaps(TIMECAPS()) 
	{
		//�^�C�}�[�̐��\�𒲂ׂ�
		if (::timeGetDevCaps(&timeCaps,sizeof(TIMECAPS)) != TIMERR_NOERROR) {
			timeCaps.wPeriodMin = 1;
		}

		//�^�C�}�[�̏����\�͂ɂ����GetTickCount��timeGetTime���g��������K�v�����邪
		//������Windows�}�V��(XP�ł���T�|�[�g�؂꒼�O�ł���)�ł���΃}���`���f�B�A�^�C�}������Ă���͂��Ȃ̂�timeGetTime�݂̂��g��
		//	�ŏ����Ԃ�ݒ肷��
		::timeBeginPeriod(timeCaps.wPeriodMin);

		//�f�t�H���g�ł̓I�t�Z�b�g�͂Ȃ��ɂ��Ă���
		//offsetTime = ::timeGetTime();
	}

	//---------------------------------------------------------------------------------------
	win32_timer::~win32_timer() {
		::timeEndPeriod(timeCaps.wPeriodMin);   
	}

	//---------------------------------------------------------------------------------------
	void  win32_timer::reset() {
		offsetTime = timeGetTime();
		isPaused  = false;
	}

	//---------------------------------------------------------------------------------------
	uint64_t  win32_timer::get() {
		uint64_t time = 0;
		if (isPaused) {
			time = pauseTime - offsetTime;
		}
		else {
			time = timeGetTime() - offsetTime;
		}
		return time;
	}

	//---------------------------------------------------------------------------------------
	void  win32_timer::set(uint64_t now) {
		if (isPaused) {
			offsetTime = pauseTime - now;
		}
		else {
			offsetTime  = ::timeGetTime() - now; 
		}
	}

	//---------------------------------------------------------------------------------------
	void  win32_timer::pause(bool pause) {
		isPaused   = pause;   
		pauseTime = ::timeGetTime();
	}

	//---------------------------------------------------------------------------------------
	bool  win32_timer::is_pause() {
		return isPaused;
	}

	//---------------------------------------------------------------------------------------
	void  win32_timer::restart() {
		if (isPaused == true) {
			isPaused = false;
			offsetTime = ::timeGetTime() - pauseTime;
		}
	}

}