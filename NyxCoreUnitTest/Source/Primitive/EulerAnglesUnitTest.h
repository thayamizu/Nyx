#pragma once
#include "PCH/PCH.h"

using namespace Nyx;

BEGIN_TEST(EulerAngles_Test01)
{
	auto euler=EulerAngles<float>();

	WIN_ASSERT_TRUE(euler.pitch   == 0);
	WIN_ASSERT_TRUE(euler.heading == 0);
	WIN_ASSERT_TRUE(euler.bank    == 0);
}
END_TEST

BEGIN_TEST(EulerAngles_Test02)
{
	auto euler=EulerAngles<float>();
	euler.Set(0.5f, 0.2f, 0.3f);

	WIN_TRACE("%f,%f,%f\n", euler.heading, euler.pitch, euler.bank);
	WIN_ASSERT_TRUE(Math::Abs(euler.heading - 0.5f) <=Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(euler.bank -0.3f) <=Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(euler.pitch - 0.2f) <=Math::Epsilon);
}
END_TEST

BEGIN_TEST(EulerAngles_Test03)
{
	auto euler = EulerAngles<float>(0.5f, Math::PI*2, Math::PI*4);
	euler.Canonize();
	WIN_TRACE("%f,%f,%f\n", euler.heading, euler.pitch, euler.bank);
	WIN_ASSERT_TRUE(-Math::PI <= Math::Abs(euler.heading) );
	WIN_ASSERT_TRUE( Math::Abs(euler.heading) <= Math::PI);

	WIN_ASSERT_TRUE(-Math::PI <= Math::Abs(euler.pitch) );
	WIN_ASSERT_TRUE( Math::Abs(euler.pitch) <= Math::PI);

	WIN_ASSERT_TRUE(-Math::PI <= Math::Abs(euler.bank) );
	WIN_ASSERT_TRUE( Math::Abs(euler.bank) <= Math::PI);
}
END_TEST
