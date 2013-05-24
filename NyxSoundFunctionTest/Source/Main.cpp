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


static const std::wstring g_WavFile1 = L"..\\..\\TestData\\Sound\\���񂸂̂���.wav";
static const std::wstring g_WavFile2 = L"..\\..\\TestData\\Sound\\test2.wav";

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
		manager_ = std::shared_ptr<AudioManager>(new AudioManager(desc));
	}
	~DirectSoundStaticAudioBufferTest() {
		::DestroyWindow(hwnd_);
	}

	void TestCase1() {
		LoadStaticAudio();
		Play1();
			Thread::Sleep(2000);
		/*Stop1();
		Thread::Sleep(2000);
		Resume1();
		Thread::Sleep(2000);
		*/
		Reset1();
		Thread::Sleep(2000);
		Play1();
		/*Thread::Sleep(2000);
		AudioEffectDesc effect;
		effect.effectType = AudioUtility::EffectType_Reverb;
		audio1_->SetEffect(effect);
		Thread::Sleep(2000);*/
	}


	void TestCase2() {
		LoadStatic3DAudio();
		Play2();
		Thread::Sleep(2000);
		Stop2();
		Thread::Sleep(2000);
		Resume2();
		Thread::Sleep(2000);
		Reset2();
		Play2();
		Thread::Sleep(2000);
		AudioEffectDesc effect;
		effect.effectType = AudioUtility::EffectType_Echo;
		audio2_->SetEffect(effect);
		Thread::Sleep(2000);
	}

	void TestCase3() {
		LoadStreamingAudio();
		Play3();
		Thread::Sleep(2000);
		Stop3();
		Thread::Sleep(2000);

		Resume3();
		//Reset3();
		//Play3();
		//AudioEffectDesc effect;
		//effect.effectType = AudioUtility::EffectType_Gargle;
		//audio3_->SetEffect(effect);
	}

	void TestCase4() {
		LoadStreaming3DAudio();
		Play2();
		Thread::Sleep(2000);
		Stop2();
		Thread::Sleep(2000);
		Resume2();
		Thread::Sleep(2000);
		Reset2();
		Play2();
		Thread::Sleep(2000);
		AudioEffectDesc effect;
		effect.effectType = AudioUtility::EffectType_Echo;
		audio2_->SetEffect(effect);
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
		audio2_ = manager_->CreateAudioBuffer(g_WavFile2, desc);
	}
	void LoadStreamingAudio() {
		Assert(manager_!=nullptr)
			AudioBufferDesc desc;
		ZeroMemory(&desc, sizeof(AudioBufferDesc));
		desc.algorithm = DS3DALG_DEFAULT;
		desc.focusType  = AudioUtility::FocusType_GlobalFocus;
		desc.bufferType = AudioUtility::BufferType_StreamingAudioBuffer;
		audio3_ = manager_->CreateAudioBuffer(g_WavFile1, desc);
	}
	void LoadStreaming3DAudio() {
		Assert(manager_!=nullptr)
			AudioBufferDesc desc;
		ZeroMemory(&desc, sizeof(AudioBufferDesc));
		desc.algorithm = DS3DALG_HRTF_FULL;
		desc.focusType  = AudioUtility::FocusType_GlobalFocus;
		desc.bufferType = AudioUtility::BufferType_Streaming3DAudioBuffer;
		audio4_ = manager_->CreateAudioBuffer(g_WavFile2, desc);
	}
	void Play1() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@���Đ����܂�...");
		audio1_->Play(true);
	}

	void Stop1() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@���~���܂�...");
		audio1_->Stop();
	}
	void Resume1() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�����W���[�����܂�...");
		audio1_->Resume();
	}
	void Reset1() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�����Z�b�g���܂�...");
		audio1_->Reset();
	}

	void Play2() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@���Đ����܂�...");
		audio2_->Play(true);
	}

	void Stop2() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@���~���܂�...");
		audio2_->Stop();
	}
	void Resume2() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�����W���[�����܂�...");
		audio2_->Resume();
	}
	void Reset2() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�����Z�b�g���܂�...");
		audio2_->Reset();
	}
	void GetStatus() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�̃X�e�[�^�X�R�[�h���擾���܂�...");
		//ulong status = audio_->GetStatus();
	}
	void Play3() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@���Đ����܂�...");
		audio3_->Play(true);
	}

	void Stop3() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@���~���܂�...");
		audio3_->Stop();
	}
	void Resume3() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�����W���[�����܂�...");
		audio3_->Resume();
	}
	void Reset3() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�����Z�b�g���܂�...");
		audio3_->Reset();
	}
	void GetStatus3() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�̃X�e�[�^�X�R�[�h���擾���܂�...");
		//ulong status = audio_->GetStatus();
	}
	void Play4() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@���Đ����܂�...");
		audio4_->Play(true);
	}

	void Stop4() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@���~���܂�...");
		audio4_->Stop();
	}
	void Resume4() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�����W���[�����܂�...");
		audio4_->Resume();
	}
	void Reset4() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�����Z�b�g���܂�...");
		audio4_->Reset();
	}
	void GetStatus4() {
		DebugOutput::Trace("�I�[�f�B�I�o�b�t�@�̃X�e�[�^�X�R�[�h���擾���܂�...");
		//ulong status = audio_->GetStatus();
	}
private:
	HWND hwnd_;
	std::shared_ptr<IAudioBuffer>  audio1_;
	std::shared_ptr<IAudioBuffer>  audio2_;
	std::shared_ptr<IAudioBuffer>  audio3_;
	std::shared_ptr<IAudioBuffer>  audio4_;
	std::shared_ptr<AudioManager> manager_;
};


int main()
{
	Nyx::MemoryState state;
	try {
		MemoryChecker::Initialize();
		state= MemoryChecker::GetMemoryState();

		std::shared_ptr<DirectSoundStaticAudioBufferTest> test(std::make_shared<DirectSoundStaticAudioBufferTest>());
		/*std::cout <<"�e�X�g�P�[�X1���J�n���܂�" << std::endl;
		test->TestCase1();
		getchar();
		*/

		/*std::cout <<"�e�X�g�P�[�X2���J�n���܂�" << std::endl;
		test->TestCase2();
		getchar();
		*/
		
		std::cout <<"�e�X�g�P�[�X3���J�n���܂�" << std::endl;
		test->TestCase3();

		getchar();
		/*std::cout <<"�e�X�g�P�[�X4���J�n���܂�" << std::endl;
		test->TestCase4();

		std::cout <<"�e�X�g�P�[�X5���J�n���܂�" << std::endl;
		test->TestCase5();*/
	}
	catch(std::exception e) {
		std::cout << e.what() << std::endl;
		getchar();
	}

	MemoryChecker::DumpStatistics();

}