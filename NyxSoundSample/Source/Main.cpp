#include "PCH.h"
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
		Load();
		Play1();
	}
	void TestCase2() {
		Load();
		Play1();
		::Sleep(2000);
		Stop();
		::Sleep(1000);

		Resume();
		Play1();
		::Sleep(2000);
		Reset();
		Play1();
		::Sleep(2000);
	}
	void Load() {
		AudioBufferDesc desc;
		desc.focusType  = AudioUtility::FocusType_GlobalFocus;
		desc.bufferType = AudioUtility::BufferType_StaticAudioBuffer;
		desc.algorithm = DS3DALG_DEFAULT;
		audio1_ = std::make_shared<DirectSoundStreamingAudioBuffer>(desc,manager_->GetHandle(), g_WavFile1);
		Assert(audio1_ != nullptr);
	}
void Play1() {
		DebugOutput::Trace("オーディオバッファを再生します...");
		audio1_->Play(true);
	}
	void Play2() {
		DebugOutput::Trace("オーディオバッファを再生します...");
		audio2_->Play(true);
	}
	
	void Stop() {
		DebugOutput::Trace("オーディオバッファを停止します...");
		audio2_->Stop();
	}
	void Resume() {
		DebugOutput::Trace("オーディオバッファをレジュームします...");
		audio2_->Resume();
	}
	void Reset() {
		DebugOutput::Trace("オーディオバッファをリセットします...");
		audio2_->Reset();
	}

	void GetStatus() {
		DebugOutput::Trace("オーディオバッファのステータスコードを取得します...");
		//ulong status = audio_->GetStatus();
	}

	void GetPan() {
		DebugOutput::Trace("オーディオバッファの相対ボリュームを取得します...");
		long pan = audio2_->GetPan();

	}	
	void GetVolume() {
		DebugOutput::Trace("オーディオバッファのボリュームを取得します...");
		long volume  = audio2_->GetVolume();
	}		
	void SetPan() {
		DebugOutput::Trace("オーディオバッファの相対ボリュームを設定します...");
		audio2_->SetPan(100);
	}	
	void SetVolume() {
		DebugOutput::Trace("オーディオバッファのボリュームを設定します...");
		audio2_->SetVolume(100);
	}
private:
	HWND hwnd_;
	std::shared_ptr<DirectSoundStreamingAudioBuffer>  audio1_;
	std::shared_ptr<DirectSoundStaticAudioBuffer>  audio2_;
	std::shared_ptr<DirectSoundAudioManager> manager_;
};


int main()
{Nyx::MemoryState state;
	try {
		MemoryChecker::Initialize();
	state= MemoryChecker::GetMemoryState();

		std::shared_ptr<DirectSoundStaticAudioBufferTest> test(std::make_shared<DirectSoundStaticAudioBufferTest>());
		std::cout <<"テストケース1を開始します" << std::endl;
		test->TestCase1();
		getchar();
		/*	std::cout <<"テストケース2を開始します" << std::endl;
		test->TestCase2();

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