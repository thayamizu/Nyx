#include "../Nyx/Source/NyxCore.h"

#if defined (_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../Lib/Debug/Nyx_MTd.lib")
#else
#pragma comment(lib, "../Lib/Release/Nyx_MT.lib")
#endif

void mouse_down_callback(nyx::iwidget& widget,  nyx::event_args& e)
{
	printf("mouse_down\n");
}
void mouse_up_callback(nyx::iwidget& widget, nyx::event_args& e)
{
	printf("mouse_up\n");
}
void click_callback(nyx::iwidget& widget, nyx::event_args& e)
{
	printf("window id = %d\n", widget.get_id());
	
}
void click2_callback(nyx::iwidget& widget, nyx::event_args& e)
{
	auto button = (nyx::push_button&)widget;
	printf("ボタンを押しました");
}

void button_paint_callback(nyx::iwidget& widget, nyx::event_args& e)
{
	auto button = (nyx::push_button&)widget;
	
	nyx::rect2i rect;
	button.get_size(rect);

	auto hdc = ::GetDC(button.get_handle());
	RECT r{ 0, 0, rect.width, rect.height };
	
	auto hbr = (HBRUSH)GetStockObject(GRAY_BRUSH);
	FillRect(
		hdc, // デバイスコンテキストのハンドル
		&r,  // 長方形
		hbr  // ブラシのハンドル
		);
	ReleaseDC(button.get_handle(), hdc);
}

void index_changed_callback(nyx::iwidget& widget, nyx::event_args& e)
{
	printf("index changed window id = %d\n", widget.get_id());
}
int main()
{
	auto timer = nyx::fps_timer();

	auto mainWindow = std::make_shared<nyx::window>(nullptr, L"ウインドウ", L"");
	
	mainWindow->on_mouse_down(mouse_down_callback);
	mainWindow->on_mouse_up(mouse_up_callback);

	auto button1 = std::make_shared<nyx::push_button>(mainWindow, L"ボタン1", 50, 50, 200, 20);
	button1->on_click(click_callback);
	
	auto button2 = std::make_shared<nyx::push_button>(mainWindow, L"ボタン2", 250, 50, 200, 20, true);
	button2->on_click(click2_callback);
	button2->on_paint(button_paint_callback);
	
	auto cbox1 = std::make_shared<nyx::check_box>(mainWindow, L"チェックボックス1", 50, 150, 200, 20);
	auto cbox2 = std::make_shared<nyx::check_box>(mainWindow, L"チェックボックス2", 250, 150, 200, 20);
	cbox1->on_click(click_callback);
	cbox2->on_click(click_callback);

	auto lbox1 = std::make_shared<nyx::list_box>(mainWindow, L"リストボックス1", 50, 250, 200, 20);
	auto lbox2 = std::make_shared<nyx::list_box>(mainWindow, L"リストボックス2", 250, 250, 200, 20);
	lbox1->add_item(L"矢澤いっこ");
	lbox1->add_item(L"矢澤にこ");
	lbox1->add_item(L"矢澤さんこ");
	lbox1->on_click(click_callback);
	lbox2->on_click(click_callback);
	lbox1->on_index_changed(index_changed_callback);

	auto rbtn1 = std::make_shared<nyx::radio_button>(mainWindow, L"ラジオボタン1", 50, 350, 200, 20);
	auto rbtn2 = std::make_shared<nyx::radio_button>(mainWindow, L"ラジオボタン2", 250, 350, 200, 20);
	rbtn1->on_click(click_callback);
	rbtn2->on_click(click_callback);

	while (mainWindow->process_message()) {
		timer.wait_frame();
	}

	return 0;
}