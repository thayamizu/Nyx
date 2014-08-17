#include "../Nyx/Source/NyxCore.h"

#if defined (_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../Lib/Debug/Nyx_MTd.lib")
#else
#pragma comment(lib, "../Lib/Release/Nyx_MT.lib")
#endif

int main()
{
	auto timer = nyx::fps_timer();
	auto mainWindow = nyx::window(nullptr, L"ウインドウ",L"");
	auto movie = nyx::movie_player(mainWindow, L"3rd 夏色えがおで1、2、jump.mp4");
	movie.set_aspect_ratio_mode(false);
	movie.play();
	while (mainWindow.process_message()) {
		timer.wait_frame();
		nyx::debug_out::trace("FPS=%d\r", timer.get_current_fps());
	}

	return 0;
}