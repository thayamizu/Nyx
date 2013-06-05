#include "PCH.h"
#include "DirectSoundStaticAudioBufferTest.h"
#include "DirectSoundStatic3DAudioBufferTest.h"
#include "DirectSoundStreamingAudioBufferTest.h"
#include "DirectSoundStreaming3DAudioBufferTest.h"
#include "DirectSoundAudioLisnterTest.h"
#include "DirectSoundAudioManagerTest.h"
#include "AudioCacheTest.h"
#include "AudioManagerTest.h"

using namespace Nyx;
int main()
{
	Nyx::MemoryState state;
	try {
		MemoryChecker::Initialize();
		state= MemoryChecker::GetMemoryState();
		std::shared_ptr<DirectSoundStaticAudioBufferTest> test1;
		std::shared_ptr<DirectSoundStatic3DAudioBufferTest> test2;
		std::shared_ptr<DirectSoundStreamingAudioBufferTest> test3;
		std::shared_ptr<DirectSoundAudioManagerTest> test4;
		std::shared_ptr<DirectSoundAudioManagerTest> test5;
		std::shared_ptr<DirectSoundAudioListenerTest> test6;
		std::shared_ptr<AudioManagerTest> test7;
		std::shared_ptr<AudioCacheTest> test8;
		std::shared_ptr<AudioCacheTest> test9;

		std::cout <<"テスト項目を選択してください";
		char n = std::cin.get();
			switch(n) {
			case '1':
				test1 = std::make_shared<DirectSoundStaticAudioBufferTest>();
				test1->Test();
				break;
			case '2':
				test2 = std::make_shared<DirectSoundStatic3DAudioBufferTest>();
				test2->Test();
				break;

			case '3':
				test3= std::make_shared<DirectSoundStreamingAudioBufferTest>();
				test3->Test();
				break;
			case '4':
				test9 = std::make_shared<AudioCacheTest>();
				test9->Test();
			case '5':
				break;
			}
	}
	catch(std::exception e) {
		std::cout << e.what() << std::endl;
		getchar();
	}

	MemoryChecker::DumpStatistics();

}