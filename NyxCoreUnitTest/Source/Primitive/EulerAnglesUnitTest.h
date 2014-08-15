#pragma once
#include "PCH/PCH.h"

using namespace nyx;

BEGIN_TEST(EulerAngles_Test01)
{
	auto euler=euler_angles<float>();

	WIN_ASSERT_TRUE(euler.pitch   == 0);
	WIN_ASSERT_TRUE(euler.heading == 0);
	WIN_ASSERT_TRUE(euler.bank    == 0);
}
END_TEST

BEGIN_TEST(EulerAngles_Test02)
{
	auto euler=euler_angles<float>();
	euler.set(0.5f, 0.2f, 0.3f);

	WIN_TRACE("%f,%f,%f\n", euler.heading, euler.pitch, euler.bank);
	WIN_ASSERT_TRUE(math::abs(euler.heading - 0.5f) <=math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(euler.bank -0.3f) <=math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(euler.pitch - 0.2f) <=math::EPSILON);
}
END_TEST

BEGIN_TEST(EulerAngles_Test03)
{
	auto euler = euler_angles<float>(0.5f, math::PI*2, math::PI*4);
	euler.canonize();
	WIN_TRACE("%f,%f,%f\n", euler.heading, euler.pitch, euler.bank);
	WIN_ASSERT_TRUE(-math::PI <= math::abs(euler.heading) );
	WIN_ASSERT_TRUE( math::abs(euler.heading) <= math::PI);

	WIN_ASSERT_TRUE(-math::PI <= math::abs(euler.pitch) );
	WIN_ASSERT_TRUE( math::abs(euler.pitch) <= math::PI);

	WIN_ASSERT_TRUE(-math::PI <= math::abs(euler.bank) );
	WIN_ASSERT_TRUE( math::abs(euler.bank) <= math::PI);
}
END_TEST
