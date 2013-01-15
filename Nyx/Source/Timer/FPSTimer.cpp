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

namespace Nyx {
	//---------------------------------------------------------------------------------------
	const uint FPSTimer::FPS30 = 30;
	const uint FPSTimer::FPS60 = 60;

	struct FPSTimer::PImpl
	{
		PImpl():
			fps(0), nowFPS(0), frames(0), beforeTime(0), fpsWait(0), fpsWaitTT(0), lastDraw(0), timer(new Timer())
		{

		}
		uint fps;		///< FPS
		uint nowFPS;	///< ���݂�FPS�l
		uint frames;	///< �O�t���[���̎���
		ulong beforeTime;///< �O��̎���
		ulong fpsWaitTT;///<  1000 * 0x10000 / fps�̒l
		ulong fpsWait;  ///<�o�ߎ���
		ulong lastDraw; ///<�Ō�ɕ`�悵������
		std::unique_ptr<Timer> timer;	///<FPS�v���^�C�}�[
	};
	

	//---------------------------------------------------------------------------------------
	FPSTimer::FPSTimer(ulong fps)
		:ITimer(), pimpl_(new PImpl())
	{
	
		SetFPS(fps);
	}
	
	//---------------------------------------------------------------------------------------
	FPSTimer::~FPSTimer() {
	}

	//---------------------------------------------------------------------------------------
	ulong FPSTimer::Get() {
		Assert(pimpl_->timer != NULL);
		return pimpl_->timer->Get();
	}

	//---------------------------------------------------------------------------------------
	void FPSTimer::Set(ulong now) {
		Assert(pimpl_->timer != NULL);
		pimpl_->timer->Set(now);
	}

	//---------------------------------------------------------------------------------------
	void FPSTimer::Reset() {
		Assert(pimpl_->timer != NULL);
		pimpl_->timer->Reset();
	}

	//---------------------------------------------------------------------------------------
	void FPSTimer::Restart() {
		Assert(pimpl_->timer != NULL);
		pimpl_->timer->Restart();
	}

	//---------------------------------------------------------------------------------------
	void FPSTimer::Pause(bool pause) {
		Assert(pimpl_->timer != NULL);
		pimpl_->timer->Pause(pause);
	}

	//---------------------------------------------------------------------------------------
	bool FPSTimer::IsPause() {
		Assert(pimpl_->timer != NULL);
		return pimpl_->timer->IsPause();
	}
	//---------------------------------------------------------------------------------------
	uint FPSTimer::GetFPS() {
		return pimpl_->fps;
	}

	//---------------------------------------------------------------------------------------
	uint FPSTimer::GetNowFPS(){
		return pimpl_->nowFPS;
	}

	//---------------------------------------------------------------------------------------
	void FPSTimer::SetFPS(uint fps) {
		pimpl_->fps = fps;
		if (pimpl_->fps != 0 ) {
			pimpl_->fpsWait = 1000 * 0x10000 / pimpl_->fps;
		}
	}
	//---------------------------------------------------------------------------------------
	void FPSTimer::WaitFrame() {
		Assert(pimpl_->timer != NULL);
		// ��˂��炨����FPSTimer���Q�l�ɂ��܂���
		if (pimpl_->fps == 0) {return ;}//non-wait

		ulong t = pimpl_->timer->Get(); // ���ݎ���

		pimpl_->fpsWaitTT = (pimpl_->fpsWaitTT & 0xffff) + pimpl_->fpsWait; // ����̑҂����Ԃ��v�Z

		// fpsWait�́C�҂����Ԃ̏����ȉ���16�r�b�g�̐��x�Ŏ����Ă���ƍl����
		// ����ɂ��Cdouble�^�������o���K�v���Ȃ��Ȃ�
		// fpsWaitTT = 1000 * 0x10000 / fps;
		ulong wait = pimpl_->fpsWaitTT >> 16; // ���~���b�҂̂����v�Z

		// 1�t���[�����Ԃ��o�߂��Ă�����C�������ɕ`��
		ulong elapse = (ulong)(t - pimpl_->lastDraw); // �O��`�悩�炢����o�߂��Ă��邩
		if (elapse >= wait) {
			pimpl_->lastDraw = t;
			if ((pimpl_->timer->Get() - pimpl_->beforeTime) > 1000) {
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
			Nyx::Thread::Sleep(wait-elapse-3);
		}
		// ����wait > elp�Ȃ̂�wait - wlp >= 0�ƍl���ėǂ�
		// sleep�̐��x��3ms�ȓ��Ɖ���
		// ���ԂԂ�����
		while ((pimpl_->timer->Get() - pimpl_->lastDraw) < wait) ;


		pimpl_->lastDraw += wait; // �҂�����ŕ`�悪�����������肷��B�i�[�����������܂Ȃ����߁j

		if ((pimpl_->timer->Get() - pimpl_->beforeTime) > 1000) {
			pimpl_->beforeTime = t;
			pimpl_->nowFPS = pimpl_->frames;
			pimpl_->frames = 0;
		}
		pimpl_->frames++;
	}
}