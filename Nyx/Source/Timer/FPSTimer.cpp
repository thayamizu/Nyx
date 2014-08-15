/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
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
		uint32_t nowFPS;	///< 現在のFPS値
		uint32_t frames;	///< 前フレームの時刻
		uint64_t beforeTime;///< 前回の時刻
		uint64_t fpsWaitTT;///<  1000 * 0x10000 / fpsの値
		uint64_t fpsWait;  ///<経過時間
		uint64_t lastDraw; ///<最後に描画した時刻
		std::unique_ptr<Timer> timer;	///<FPS計測タイマー
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
		// やねうらお氏のFPSTimerを参考にしました
		if (pimpl_->fps == 0) {return ;}//non-wait

		uint64_t t = pimpl_->timer->get(); // 現在時刻

		pimpl_->fpsWaitTT = (pimpl_->fpsWaitTT & 0xffff) + pimpl_->fpsWait; // 今回の待ち時間を計算

		// fpsWaitは，待ち時間の小数以下を16ビットの精度で持っていると考える
		// これにより，double型を持ち出す必要がなくなる
		// fpsWaitTT = 1000 * 0x10000 / fps;
		uint64_t wait = pimpl_->fpsWaitTT >> 16; // 何ミリ秒待つのかを計算

		// 1フレーム時間を経過していたら，ただちに描画
		uint64_t elapse = (uint64_t)(t - pimpl_->lastDraw); // 前回描画からいくら経過しているか
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

		// 時間つぶし

		// 4ms以上消費する必要があるのならば、sleepする
		if (wait - elapse >= 4) {
			nyx::thread::sleep(wait-elapse-3);
		}
		// いまwait > elpなのでwait - wlp >= 0と考えて良い
		// sleepの精度は3ms以内と仮定
		// 時間つぶし完了
		while ((pimpl_->timer->get() - pimpl_->lastDraw) < wait) ;


		pimpl_->lastDraw += wait; // ぴったりで描画が完了した仮定する。（端数を持ち込まないため）

		if ((pimpl_->timer->get() - pimpl_->beforeTime) > 1000) {
			pimpl_->beforeTime = t;
			pimpl_->nowFPS = pimpl_->frames;
			pimpl_->frames = 0;
		}
		pimpl_->frames++;
	}
}