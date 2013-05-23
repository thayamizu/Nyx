#include "PCH.h"
#include "Sound/AudioUtility.h"
#include "Sound/DirectSoundAudioManager.h"
#include "Sound/DirectSoundAudioBuffer.h"
#include "Sound/DirectSoundStaticAudioBuffer.h"
#include "Sound/DirectSoundStatic3DAudioBuffer.h"
#include "Sound/DirectSoundStreamingAudioBuffer.h"
#include "Sound/DirectSoundStreaming3DAudioBuffer.h"

using namespace std;
using namespace Nyx;


static const std::wstring g_WavFile1 = L"..\\..\\TestData\\Sound\\あんずのうた.wav";
static const std::wstring g_WavFile2 = L"..\\..\\TestData\\Sound\\test3.wav";

class DirectSoundStaticAudioBufferTest
{
public:
	DirectSoundStaticAudioBufferTest()
		: hwnd_(nullptr), audio2_(nullptr), manager_(nullptr)
	{
		hwnd_ = ::GetConsoleWindow();

		AudioDesc desc;
		desc.handle = hwnd_;
		desc.apiType = AudioUtility::APIType_DirectSound;
		manager_ = std::shared_ptr<DirectSoundAudioManager>(new DirectSoundAudioManager(desc));
	}
	~DirectSoundStaticAudioBufferTest() {
		::DestroyWindow(hwnd_);
	}

	void TestCase1() {
		LoadStaticAudio();
		Play1();
		Thread::Sleep(2000);
		Stop1();
		Thread::Sleep(2000);
		Resume1();
		Thread::Sleep(2000);
		Reset1();
		Play1();
		Thread::Sleep(2000);
		AudioEffectDesc effect;
		effect.effectType = AudioUtility::EffectType_Reverb;
		audio1_->SetEffect(effect);
		Thread::Sleep(2000);
	}


	void TestCase2() {
		LoadStatic3DAudio();
		Play1();
		Thread::Sleep(2000);
		Stop1();
		Thread::Sleep(2000);
		Resume1();
		Thread::Sleep(2000);
		Reset1();
		Play1();
		Thread::Sleep(2000);
		AudioEffectDesc effect;
		effect.effectType = AudioUtility::EffectType_Echo;
		audio1_->SetEffect(effect);
		Thread::Sleep(2000);
	}
	void LoadStaticAudio() {
		Assert(manager_!=nullptr)
		AudioBufferDesc desc;
		ZeroMemory(&desc, sizeof(AudioBufferDesc));
		desc.algorithm = DS3DALG_DEFAULT;
		desc.focusType  = AudioUtility::FocusType_GlobalFocus;
		desc.bufferType = AudioUtility::BufferType_StaticAudioBuffer;
		audio1_ = manager_->CreateAudioBuffer(g_WavFile1, desc);
	}
	void LoadStatic3DAudio() {
		Assert(manager_!=nullptr)
			AudioBufferDesc desc;
		ZeroMemory(&desc, sizeof(AudioBufferDesc));
		desc.algorithm = DS3DALG_HRTF_FULL;
		desc.focusType  = AudioUtility::FocusType_GlobalFocus;
		desc.bufferType = AudioUtility::BufferType_Static3DAudioBuffer;
		audio1_ = manager_->CreateAudioBuffer(g_WavFile1, desc);
	}

	void Play1() {
		DebugOutput::Trace("オーディオバッファを再生します...");
		audio1_->Play(false);
	}
	void Play2() {
		DebugOutput::Trace("オーディオバッファを再生します...");
		audio2_->Play(true);
	}

	void Stop1() {
		DebugOutput::Trace("オーディオバッファを停止します...");
		audio1_->Stop();
	}
	void Resume1() {
		DebugOutput::Trace("オーディオバッファをレジュームします...");
		audio1_->Resume();
	}
	void Reset1() {
		DebugOutput::Trace("オーディオバッファをリセットします...");
		audio1_->Reset();
	}

	void GetStatus() {
		DebugOutput::Trace("オーディオバッファのステータスコードを取得します...");
		//ulong status = audio_->GetStatus();
	}

private:
	HWND hwnd_;
	std::shared_ptr<IAudioBuffer>  audio1_;
	std::shared_ptr<IAudioBuffer>  audio2_;
	std::shared_ptr<IAudioBuffer>  audio3_;
	std::shared_ptr<IAudioBuffer>  audio4_;
	std::shared_ptr<DirectSoundAudioManager> manager_;
};


int main()
{
	Nyx::MemoryState state;
	try {
		MemoryChecker::Initialize();
		state= MemoryChecker::GetMemoryState();

		std::shared_ptr<DirectSoundStaticAudioBufferTest> test(std::make_shared<DirectSoundStaticAudioBufferTest>());
		/*std::cout <<"テストケース1を開始します" << std::endl;
		test->TestCase1();
		getchar();*/

		std::cout <<"テストケース2を開始します" << std::endl;
		test->TestCase2();
		getchar();
		
		/*
		std::cout <<"テストケース3を開始します" << std::endl;
		test->TestCase3();

		std::cout <<"テストケース4を開始します" << std::endl;
		test->TestCase4();

		std::cout <<"テストケース5を開始します" << std::endl;
		test->TestCase5();*/
	}
	catch(std::exception e) {
		std::cout << e.what() << std::endl;
		getchar();
	}

	MemoryChecker::DumpStatistics();

}