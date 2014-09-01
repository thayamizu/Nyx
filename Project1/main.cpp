#include "../Nyx/Source/NyxCore.h"
#if defined (_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../Lib/Debug/Nyx_MTd.lib")
#else
#pragma comment(lib, "../Lib/Release/Nyx_MT.lib")
#endif

int main()
{
	auto win = nyx::window(nullptr, L"ウインドウ", L"");
	auto audioManager = nyx::audio_manager(nyx::audio_desc { 
		NULL, win.get_handle(), nyx::AUDIO_API_DIRECT_SOUND });
	auto audio = audioManager.create_audio_buffer(L"sample.ogg",
			nyx::audio_buffer_desc{NULL, GUID_NULL, nyx::AUDIO_BUFFER_TYPE_STATIC, nyx::FOCUS_TYPE_GLOBAL, nyx::wav_file_header()});
	audio->play(true);
	while (win.process_message());

}