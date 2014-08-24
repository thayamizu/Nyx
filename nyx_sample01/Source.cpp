#include "../Nyx/Source/NyxCore.h"

#if defined (_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../Lib/Debug/Nyx_MTd.lib")
#else
#pragma comment(lib, "../Lib/Release/Nyx_MT.lib")
#endif
void mouse_down_callback(nyx::iwidget& widget, nyx::event_args& e)
{
	nyx::point2i p;
	widget.get_position(p);
	widget.set_position(nyx::point2i{ p.x - 10, p.y-10 });
	widget.update();
}

void resize_callback(nyx::iwidget& widget, nyx::event_args& e)
{
}

int main()
{
	auto timer = nyx::fps_timer();
	auto mainWindow = std::make_shared<nyx::window>(nullptr, L"ウインドウ",L"");
	auto movie = std::make_shared<nyx::movie_player>(*mainWindow, L"3rd 夏色えがおで1、2、jump.mp4");
	mainWindow->on_resize(mouse_down_callback);
	mainWindow->set_user_data(movie);
	movie->set_aspect_ratio_mode(false);
	movie->play();
	while (mainWindow->process_message()) {
		timer.wait_frame();
		nyx::debug_out::trace("FPS=%d\r", timer.get_current_fps());
	}

	return 0;
}