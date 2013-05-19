#include "PCH.h"

//コンストラクタ
BEGIN_TEST(WaveReader001)
{
	Nyx::WaveReader wave_reader;
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.dataChunk.chunkSize == 0);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.fileSize == 0);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.bitsRate == 0);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.blockSize == 0);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.bytesPerSec == 0);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.channelNum == 0);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.chunkSize == 0);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.formatTag == 0);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.samplingRate == 0);
}
END_TEST


//ReadFromFileメンバ関数テスト
BEGIN_TEST(WaveReader002)
{
	Nyx::WaveReader wave_reader;
	wave_reader.Open(L"../../TestData/Sound/test.wav");
	wave_reader.ReadHeader();
	std::ofstream ofs("wave_file.txt");
	
	ofs << wave_reader.waveHeader_.riffID << "\n";
	ofs << wave_reader.waveHeader_.fileSize << "\n";
	ofs << wave_reader.waveHeader_.waveID <<"\n";
	ofs << wave_reader.waveHeader_.formatChunk.formatChunkID << "\n";
	ofs << wave_reader.waveHeader_.formatChunk.chunkSize << "\n";
	ofs << wave_reader.waveHeader_.formatChunk.formatTag << "\n";
	ofs << wave_reader.waveHeader_.formatChunk.channelNum << "\n";
	ofs << wave_reader.waveHeader_.formatChunk.samplingRate << "\n";
	ofs << wave_reader.waveHeader_.formatChunk.bytesPerSec << "\n";
	ofs << wave_reader.waveHeader_.formatChunk.blockSize << "\n";
	ofs << wave_reader.waveHeader_.dataChunk.dataChunkID << "\n";
	ofs << wave_reader.waveHeader_.dataChunk.chunkSize << "\n";
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.fileSize == 264674);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.bitsRate == 16);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.blockSize == 2);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.bytesPerSec == 44100);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.channelNum == 1);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.chunkSize == 16);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.formatTag == 1);
	WIN_ASSERT_TRUE(wave_reader.waveHeader_.formatChunk.samplingRate == 22050);
}
END_TEST



//ReadFromMemメンバ関数テスト
BEGIN_TEST(WaveReader003)
{
}
END_TEST



//ReadFromMemメンバ関数テスト
BEGIN_TEST(WaveReader004)
{

}
END_TEST



//ReadFromMemメンバ関数テスト
BEGIN_TEST(WaveReader005)
{
}
END_TEST

//ReadFromMemメンバ関数テスト
BEGIN_TEST(WaveReader006)
{
}
END_TEST
