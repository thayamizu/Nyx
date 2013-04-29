#include "PCH.h"
#include "Sound/AudioUtility.h"

using Nyx::AudioUtility;
BEGIN_TEST(AudioUtilityTest01)
{
	WIN_ASSERT_TRUE(AudioUtility::DefaultBitRate == 16);
}
END_TEST

BEGIN_TEST(AudioUtilityTest02)
{
	WIN_ASSERT_TRUE(AudioUtility::DefaultSamplingRate == 44100);
}
END_TEST

BEGIN_TEST(AudioUtilityTest03)
{
	WIN_ASSERT_TRUE(AudioUtility::Focus::DefaultFoucus == 0);
	WIN_ASSERT_TRUE(AudioUtility::Focus::GlobalFocus   == 1);
	WIN_ASSERT_TRUE(AudioUtility::Focus::StickyFocus   == 2);
}
END_TEST

BEGIN_TEST(AudioUtilityTest04)
{
	WIN_ASSERT_TRUE(AudioUtility::Priority::DefaultPriority == 0);
	WIN_ASSERT_TRUE(AudioUtility::Priority::MaxPriority     == 1);
	WIN_ASSERT_TRUE(AudioUtility::Priority::MinPriority     == 2);
}
END_TEST

BEGIN_TEST(AudioUtilityTest05)
{
	const auto volume = 0;
	const auto expect = 0;
	WIN_ASSERT_TRUE(AudioUtility::VolumeToDecibel(volume) == expect);
}
END_TEST

BEGIN_TEST(AudioUtilityTest06)
{
	const auto volume = 50;
	const auto expect = 50;
	WIN_ASSERT_TRUE(AudioUtility::VolumeToDecibel(volume) == expect);

}
END_TEST

BEGIN_TEST(AudioUtilityTest07)
{
	const auto volume = 100;
	const auto expect = 100;
	WIN_ASSERT_TRUE(AudioUtility::VolumeToDecibel(volume) == expect);
}
END_TEST

BEGIN_TEST(AudioUtilityTest08)
{
	const auto volume = 100;
	const auto expect = 100;
	WIN_ASSERT_TRUE(AudioUtility::VolumeToDecibel(volume) == expect);
}
END_TEST
BEGIN_TEST(AudioUtilityTest09)
{
	const auto volume = 100;
	const auto expect = 100;
	WIN_ASSERT_TRUE(AudioUtility::VolumeToDecibel(volume) == expect);
}
END_TEST

BEGIN_TEST(AudioUtilityTest10)
{
	const auto volume = 100;
	const auto expect = 100;
	WIN_ASSERT_TRUE(AudioUtility::VolumeToDecibel(volume) == expect);
}
END_TEST

BEGIN_TEST(AudioUtilityTest11)
{
	const auto volume = 100;
	const auto expect = 100;
	WIN_ASSERT_TRUE(AudioUtility::VolumeToDecibel(volume) == expect);
}
END_TEST

BEGIN_TEST(AudioUtilityTest12)
{
	const auto volume = 100;
	const auto expect = 100;
	WIN_ASSERT_TRUE(AudioUtility::VolumeToDecibel(volume) == expect);
}
END_TEST


BEGIN_TEST(AudioUtilityTest13)
{
	const auto volume = 100;
	const auto expect = 100;
	WIN_ASSERT_TRUE(AudioUtility::VolumeToDecibel(volume) == expect);
}
END_TEST

BEGIN_TEST(AudioUtilityTest14)
{
	const auto volume = 100;
	const auto expect = 100;
	WIN_ASSERT_TRUE(AudioUtility::VolumeToDecibel(volume) == expect);
}
END_TEST
