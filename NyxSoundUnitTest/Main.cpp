#include <NyxCore.h>
#include <iostream>
#include <string>

using namespace std;

HWND g_hwnd;
std::unique_ptr<Nyx::AudioManager> g_manager;

std::shared_ptr<Nyx::IAudioBuffer> g_audio1;
std::shared_ptr<Nyx::IAudioBuffer> g_audio2;
std::shared_ptr<Nyx::IAudioBuffer> g_audio3;


std::wstring g_wavFile1 = L"2.wav";
std::wstring g_wavFile2 = L"Chopper.wav";
std::wstring g_wavFile3 = L"1.wav";

void SetUp()
{
	g_hwnd = ::GetConsoleWindow();

	g_manager = std::unique_ptr<Nyx::AudioManager>(new Nyx::AudioManager(g_hwnd, 100));
}

void Load1() {
	size_t index;
	g_audio1 = g_manager->Load(g_wavFile2, Nyx::AudioUtil::Static3D, index);

	Assert(index == 0);
	Assert(g_audio1 != nullptr);
}
void Load2() {
	size_t index;
	g_audio2 = g_manager->Load(g_wavFile2, Nyx::AudioUtil::Streaming, index);

}
void Message(std::string str) {
	std::cout << str << std::endl;
}
void Play1() {
	g_audio1->Play();
}

void Stop1() {
	g_audio1->Stop();
}

void Reset1() {
	g_audio1->Reset();
}

void Resume1() {
	g_audio1->Resume();
}

void SetPause1_t() {
	g_audio1->SetPause(true);
	std::cout << g_audio1->IsPause() << std::endl;
}

void SetPause1_f() {
	g_audio1->SetPause(false);
	std::cout << g_audio1->IsPause() << std::endl;
}

void SetLoop_t() {
	g_audio1->SetLooping(true);
	std::cout << g_audio1->IsLooping() << std::endl;
}

void SetLoop_f() {
	g_audio1->SetLooping(false);
	std::cout << g_audio1->IsLooping() << std::endl;
}

void SetVolume50() {
	g_audio1->SetVolume(50);
	std::cout << g_audio1->GetVolume() << std::endl;
}

void SetLooping_t() {
	g_audio1->SetLooping(true);
	std::cout << g_audio1->IsLooping() << std::endl;

}

void Play2() {
	g_audio2->Play();
}

void Stop2() {
	g_audio2->Stop();
}

void Reset2() {
	g_audio2->Reset();
}

void Resume2() {
	g_audio2->Resume();
}

void SetPause2_t() {
	g_audio2->SetPause(true);
	std::cout << g_audio2->IsPause() << std::endl;
}

void SetPause2_f() {
	g_audio2->SetPause(false);
	std::cout << g_audio2->IsPause() << std::endl;
}

void SetLoop2_t() {
	g_audio2->SetLooping(true);
	std::cout << g_audio2->IsLooping() << std::endl;
}

void SetLoop2_f() {
	g_audio2->SetLooping(false);
	std::cout << g_audio2->IsLooping() << std::endl;
}

void SetVolume50_2() {
	g_audio2->SetVolume(50);
	std::cout << g_audio2->GetVolume() << std::endl;
}

void SetLooping2_t() {
	g_audio2->SetLooping(true);
	std::cout << g_audio2->IsLooping() << std::endl;

}

void Play3() {
	g_audio3->Play();
}

void Stop3() {
	g_audio3->Stop();
}

void Reset3() {
	g_audio3->Reset();
}

void Resume3() {
	g_audio3->Resume();
}

void SetPause3_t() {
	g_audio3->SetPause(true);
	std::cout << g_audio3->IsPause() << std::endl;
}

void SetPause3_f() {
	g_audio3->SetPause(false);
	std::cout << g_audio3->IsPause() << std::endl;
}

void SetLoop3_t() {
	g_audio3->SetLooping(true);
	std::cout << g_audio3->IsLooping() << std::endl;
}

void SetLoop3_f() {
	g_audio3->SetLooping(false);
	std::cout << g_audio3->IsLooping() << std::endl;
}

void SetVolume50_3() {
	g_audio3->SetVolume(50);
	std::cout << g_audio3->GetVolume() << std::endl;
}

void SetLooping3_t() {
	g_audio3->SetLooping(true);
	std::cout << g_audio3->IsLooping() << std::endl;

}
void Test1() {
	std::cout << "テストケース1" <<std::endl;
	Play1();
	Nyx::Thread::Sleep(5000);
	Stop1();
	Nyx::Thread::Sleep(5000);
	Resume1();
	Nyx::Thread::Sleep(5000);
	Reset1();
	Stop1();
	std::cout << "テストケース1が終了しました" <<std::endl;
}

void Test2() 
{
	std::cout << "テストケース2" <<std::endl;
	SetPause1_t();
	Play1();
	Nyx::Thread::Sleep(25);
	Stop1();
	Nyx::Thread::Sleep(25);
	Resume1();
	Nyx::Thread::Sleep(25);
	Reset1();
	std::cout << "テストケース2が終了しました" <<std::endl;
}


void Test3() {
	std::cout << "テストケース3" <<std::endl;
	SetPause1_f();
	Play1();
	Nyx::Thread::Sleep(5000);
	Stop1();
	Nyx::Thread::Sleep(5000);
	Resume1();
	Nyx::Thread::Sleep(5000);
	Reset1();
	std::cout << "テストケース3が終了しました" <<std::endl;
}

void Test4() {
	std::cout << "テストケース4" <<std::endl;
	SetVolume50();
	Play1();
	Nyx::Thread::Sleep(5000);
	Stop1();
	Nyx::Thread::Sleep(5000);
	Resume1();
	Nyx::Thread::Sleep(5000);
	Reset1();
	std::cout << "テストケース4が終了しました" <<std::endl;
}
void Test5() {
	std::cout << "テストケース5" << std::endl;
	SetLooping_t();
	Play1();
	std::cout << "テストケース5が終了しました" <<std::endl;
}

void Test21() {
	std::cout << "テストケース1" <<std::endl;
	Play2();
	Nyx::Thread::Sleep(5000);
	Stop2();
	Nyx::Thread::Sleep(5000);
	Resume2();
	Nyx::Thread::Sleep(5000);
	Reset2();
	Stop2();
	std::cout << "テストケース1が終了しました" <<std::endl;
}

void Test22() 
{
	std::cout << "テストケース2" <<std::endl;
	SetPause2_t();
	Play2();
	Nyx::Thread::Sleep(25);
	Stop2();
	Nyx::Thread::Sleep(25);
	Resume2();
	Nyx::Thread::Sleep(25);
	Reset2();
	std::cout << "テストケース2が終了しました" <<std::endl;
}


void Test23() {
	std::cout << "テストケース3" <<std::endl;
	SetPause2_f();
	Play2();
	Nyx::Thread::Sleep(5000);
	Stop2();
	Nyx::Thread::Sleep(5000);
	Resume2();
	Nyx::Thread::Sleep(5000);
	Reset2();
	std::cout << "テストケース3が終了しました" <<std::endl;
}

void Test24() {
	std::cout << "テストケース4" <<std::endl;
	SetVolume50_2();
	Play2();
	Nyx::Thread::Sleep(5000);
	Stop2();
	Nyx::Thread::Sleep(5000);
	Resume2();
	Nyx::Thread::Sleep(5000);
	Reset2();
	std::cout << "テストケース4が終了しました" <<std::endl;
}
void Test25() {
	std::cout << "テストケース5" << std::endl;
	SetLooping2_t();
	Play2();
	std::cout << "テストケース5が終了しました" <<std::endl;
}
void DirectSoundStaticAudioBufferTest()
{
	SetUp();
	Load1();
	Test1();
	Test2();
	Test3();
	Test4();
}

void DirectSoundStreamingAudioBufferTest()
{
	SetUp();
	Load2();
	Test21();
	Test22();
	Test23();
	Test24();
	Test25();
}

void TearDown() 
{

}
int main()
{
	DirectSoundStaticAudioBufferTest();
	//getchar();
	//DirectSoundStreamingAudioBufferTest();

	getchar();
	return 0;
}
