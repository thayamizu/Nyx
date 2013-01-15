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
		uint nowFPS;	///< 現在のFPS値
		uint frames;	///< 前フレームの時刻
		ulong beforeTime;///< 前回の時刻
		ulong fpsWaitTT;///<  1000 * 0x10000 / fpsの値
		ulong fpsWait;  ///<経過時間
		ulong lastDraw; ///<最後に描画した時刻
		std::unique_ptr<Timer> timer;	///<FPS計測タイマー
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
		// やねうらお氏のFPSTimerを参考にしました
		if (pimpl_->fps == 0) {return ;}//non-wait

		ulong t = pimpl_->timer->Get(); // 現在時刻

		pimpl_->fpsWaitTT = (pimpl_->fpsWaitTT & 0xffff) + pimpl_->fpsWait; // 今回の待ち時間を計算

		// fpsWaitは，待ち時間の小数以下を16ビットの精度で持っていると考える
		// これにより，double型を持ち出す必要がなくなる
		// fpsWaitTT = 1000 * 0x10000 / fps;
		ulong wait = pimpl_->fpsWaitTT >> 16; // 何ミリ秒待つのかを計算

		// 1フレーム時間を経過していたら，ただちに描画
		ulong elapse = (ulong)(t - pimpl_->lastDraw); // 前回描画からいくら経過しているか
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

		// 時間つぶし

		// 4ms以上消費する必要があるのならば、sleepする
		if (wait - elapse >= 4) {
			Nyx::Thread::Sleep(wait-elapse-3);
		}
		// いまwait > elpなのでwait - wlp >= 0と考えて良い
		// sleepの精度は3ms以内と仮定
		// 時間つぶし完了
		while ((pimpl_->timer->Get() - pimpl_->lastDraw) < wait) ;


		pimpl_->lastDraw += wait; // ぴったりで描画が完了した仮定する。（端数を持ち込まないため）

		if ((pimpl_->timer->Get() - pimpl_->beforeTime) > 1000) {
			pimpl_->beforeTime = t;
			pimpl_->nowFPS = pimpl_->frames;
			pimpl_->frames = 0;
		}
		pimpl_->frames++;
	}
}