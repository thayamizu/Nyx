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
#include "Timer/Timer.h"
#include "Timer/FPSTimer.h"
#include "Thread/Thread.h"

namespace nyx {
	//---------------------------------------------------------------------------------------
	const uint32_t fps_timer::FPS30 = 30;
	const uint32_t fps_timer::FPS60 = 60;

	struct fps_timer::PImpl
	{
		PImpl():
			fps(0), nowFPS(0), frames(0), beforeTime(0), fpsWait(0), fpsWaitTT(0), lastDraw(0), timer(new Timer())
		{

		}
		uint32_t fps;		///< FPS
		uint32_t nowFPS;	///< ���݂�FPS�l
		uint32_t frames;	///< �O�t���[���̎���
		uint64_t beforeTime;///< �O��̎���
		uint64_t fpsWaitTT;///<  1000 * 0x10000 / fps�̒l
		uint64_t fpsWait;  ///<�o�ߎ���
		uint64_t lastDraw; ///<�Ō�ɕ`�悵������
		std::unique_ptr<Timer> timer;	///<FPS�v���^�C�}�[
	};
	

	//---------------------------------------------------------------------------------------
	fps_timer::fps_timer(uint64_t fps)
		:itimer(), pimpl_(new PImpl())
	{
	
		set_fps(fps);
	}
	
	//---------------------------------------------------------------------------------------
	fps_timer::~fps_timer() {
	}

	//---------------------------------------------------------------------------------------
	uint64_t fps_timer::get() {
		NYX_ASSERT(pimpl_->timer != NULL);
		return pimpl_->timer->get();
	}

	//---------------------------------------------------------------------------------------
	void fps_timer::set(uint64_t now) {
		NYX_ASSERT(pimpl_->timer != NULL);
		pimpl_->timer->set(now);
	}

	//---------------------------------------------------------------------------------------
	void fps_timer::reset() {
		NYX_ASSERT(pimpl_->timer != NULL);
		pimpl_->timer->reset();
	}

	//---------------------------------------------------------------------------------------
	void fps_timer::restart() {
		NYX_ASSERT(pimpl_->timer != NULL);
		pimpl_->timer->restart();
	}

	//---------------------------------------------------------------------------------------
	void fps_timer::pause(bool pause) {
		NYX_ASSERT(pimpl_->timer != NULL);
		pimpl_->timer->pause(pause);
	}

	//---------------------------------------------------------------------------------------
	bool fps_timer::is_pause() {
		NYX_ASSERT(pimpl_->timer != NULL);
		return pimpl_->timer->is_pause();
	}
	//---------------------------------------------------------------------------------------
	uint32_t fps_timer::get_fps() {
		return pimpl_->fps;
	}

	//---------------------------------------------------------------------------------------
	uint32_t fps_timer::get_current_fps(){
		return pimpl_->nowFPS;
	}

	//---------------------------------------------------------------------------------------
	void fps_timer::set_fps(uint32_t fps) {
		pimpl_->fps = fps;
		if (pimpl_->fps != 0 ) {
			pimpl_->fpsWait = 1000 * 0x10000 / pimpl_->fps;
		}
	}
	//---------------------------------------------------------------------------------------
	void fps_timer::wait_frame() {
		NYX_ASSERT(pimpl_->timer != NULL);
		// ��˂��炨����FPSTimer���Q�l�ɂ��܂���
		if (pimpl_->fps == 0) {return ;}//non-wait

		uint64_t t = pimpl_->timer->get(); // ���ݎ���

		pimpl_->fpsWaitTT = (pimpl_->fpsWaitTT & 0xffff) + pimpl_->fpsWait; // ����̑҂����Ԃ��v�Z

		// fpsWait�́C�҂����Ԃ̏����ȉ���16�r�b�g�̐��x�Ŏ����Ă���ƍl����
		// ����ɂ��Cdouble�^�������o���K�v���Ȃ��Ȃ�
		// fpsWaitTT = 1000 * 0x10000 / fps;
		uint64_t wait = pimpl_->fpsWaitTT >> 16; // ���~���b�҂̂����v�Z

		// 1�t���[�����Ԃ��o�߂��Ă�����C�������ɕ`��
		uint64_t elapse = (uint64_t)(t - pimpl_->lastDraw); // �O��`�悩�炢����o�߂��Ă��邩
		if (elapse >= wait) {
			pimpl_->lastDraw = t;
			if ((pimpl_->timer->get() - pimpl_->beforeTime) > 1000) {
				pimpl_->beforeTime = t;
				pimpl_->nowFPS = pimpl_->frames;
				pimpl_->frames = 0;
			}
			pimpl_->frames++;

			return ;
		}

		// ���ԂԂ�

		// 4ms�ȏ�����K�v������̂Ȃ�΁Asleep����
		if (wait - elapse >= 4) {
			nyx::thread::sleep(wait-elapse-3);
		}
		// ����wait > elp�Ȃ̂�wait - wlp >= 0�ƍl���ėǂ�
		// sleep�̐��x��3ms�ȓ��Ɖ���
		// ���ԂԂ�����
		while ((pimpl_->timer->get() - pimpl_->lastDraw) < wait) ;


		pimpl_->lastDraw += wait; // �҂�����ŕ`�悪�����������肷��B�i�[�����������܂Ȃ����߁j

		if ((pimpl_->timer->get() - pimpl_->beforeTime) > 1000) {
			pimpl_->beforeTime = t;
			pimpl_->nowFPS = pimpl_->frames;
			pimpl_->frames = 0;
		}
		pimpl_->frames++;
	}
}