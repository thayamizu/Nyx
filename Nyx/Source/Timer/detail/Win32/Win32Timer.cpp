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
#include "Win32Timer.h"

namespace nyx {
	//---------------------------------------------------------------------------------------
	win32_timer::win32_timer()
	: offsetTime(0), pauseTime(0), 
	  isPaused(false),timeCaps(TIMECAPS()) 
	{
		//タイマーの性能を調べる
		if (::timeGetDevCaps(&timeCaps,sizeof(TIMECAPS)) != TIMERR_NOERROR) {
			timeCaps.wPeriodMin = 1;
		}

		//タイマーの処理能力によってGetTickCountとtimeGetTimeを使い分ける必要があるが
		//今時のWindowsマシン(XPですらサポート切れ直前である)であればマルチメディアタイマを備えているはずなのでtimeGetTimeのみを使う
		//	最小時間を設定する
		::timeBeginPeriod(timeCaps.wPeriodMin);

		//デフォルトではオフセットはなしにしておく
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