#include "PCH.h"
#include "Sound/detail/DirectSound/DirectSoundAudioManager.h"
#include "Sound/detail/DirectSound/DirectSoundAudioBuffer.h"

using namespace std;
using namespace Nyx;


static const std::wstring g_WavFile = L"..\\..\\TestData\\Sound\\test.wav";

class DirectSoundStaticAudioBufferTest
{
public:
	DirectSoundStaticAudioBufferTest()
		: hwnd_(nullptr), audio_(nullptr), manager_(nullptr)
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
		Play();
		audio_->SetChorusEffect(AudioEffectDesc());
		::Sleep(2000);
		Stop();
		::Sleep(1000);
		
		Play();
		getchar();

	}
	void TestCase2() {
		Load();
		Play();
		::Sleep(2000);
		Stop();
		::Sleep(1000);

		Resume();
		Play();
		::Sleep(2000);
		Reset();
		Play();
		::Sleep(2000);
	}

	void TestCase3() {
		Load();
		Play();
		::Sleep(2000);
		Stop();
		::Sleep(1000);

		Resume();
		Play();
		::Sleep(2000);
		Reset();
		Play();
		::Sleep(2000);
	}
	void TestCase4() {
		Load();
		Play();
		::Sleep(2000);
		Stop();
		::Sleep(1000);

		Resume();
		Play();
		::Sleep(2000);
		Reset();
		Play();
		::Sleep(2000);
	}

	void TestCase5() {
		Load();
		Play();
		::Sleep(2000);
		Stop();
		::Sleep(1000);
		
	}
	void Load() {
		audio_ = std::make_shared<DirectSoundAudioBuffer>();
		audio_->Load(manager_->GetHandle(), g_WavFile);
		Assert(audio_ != nullptr);
	}

	void Play() {
		DebugOutput::Trace("オーディオバッファを再生します...");
		audio_->Play(true);
	}

	void Stop() {
		DebugOutput::Trace("オーディオバッファを停止します...");
		audio_->Stop();
	}
	void Resume() {
		DebugOutput::Trace("オーディオバッファをレジュームします...");
		audio_->Resume();
	}
	void Reset() {
		DebugOutput::Trace("オーディオバッファをリセットします...");
		audio_->Reset();
	}

	void GetStatus() {
		DebugOutput::Trace("オーディオバッファのステータスコードを取得します...");
		ulong status = audio_->GetStatus();
	}

	void GetPan() {
		DebugOutput::Trace("オーディオバッファの相対ボリュームを取得します...");
		long pan = audio_->GetPan();

	}	
	void GetVolume() {
		DebugOutput::Trace("オーディオバッファのボリュームを取得します...");
		long volume  = audio_->GetVolume();
	}		
	void SetPan() {
		DebugOutput::Trace("オーディオバッファの相対ボリュームを設定します...");
		audio_->SetPan(100);
	}	
	void SetVolume() {
		DebugOutput::Trace("オーディオバッファのボリュームを設定します...");
		audio_->SetVolume(100);
	}
private:
	HWND hwnd_;
	std::shared_ptr<DirectSoundAudioBuffer>  audio_;
	std::shared_ptr<DirectSoundAudioManager> manager_;
};



int main()
{
	try {
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
	catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}