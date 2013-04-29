#include "PCH.h"
using namespace std;
using namespace Nyx;
HWND g_hwnd;

std::shared_ptr<AudioManager> g_manager;
std::shared_ptr<IAudioBuffer> g_audio1;


std::wstring g_wavFile1 = L"..\..\TestData\Sound\2.wav";

void SetUp()
{
	g_hwnd = ::GetConsoleWindow();
	g_manager = std::shared_ptr<AudioManager>(new Nyx::AudioManager());
}

void Load1() {
}
void Play1() {
}

int main()
{

}