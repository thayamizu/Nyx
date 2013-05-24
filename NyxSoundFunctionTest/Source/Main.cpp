#include "PCH.h"
#include "DirectSoundStaticAudioBufferTest.h"
#include "DirectSoundStatic3DAudioBufferTest.h"
#include "DirectSoundStreamingAudioBufferTest.h"
#include "DirectSoundStreaming3DAudioBufferTest.h"

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
		std::shared_ptr<DirectSoundStreaming3DAudioBufferTest> test4;

		std::cout <<"テスト項目を選択してください";
		char n;
		while (n = std::cin.get(), n > 0) {
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
				test4=std::make_shared<DirectSoundStreaming3DAudioBufferTest>();
				test4->Test();
				break;
			}
		}
	}
	catch(std::exception e) {
		std::cout << e.what() << std::endl;
		getchar();
	}

	MemoryChecker::DumpStatistics();

}