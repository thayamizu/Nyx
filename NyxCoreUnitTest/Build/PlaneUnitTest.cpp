#pragma once
#include "PCH/PCH.h"

using namespace nyx;

BEGIN_TEST(Plane001)
{
	plane<float> p ;
	WIN_ASSERT_TRUE(math::abs(p.a) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(p.b) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(p.c) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(p.d) <= math::EPSILON);
}
END_TEST


BEGIN_TEST(Plane002)
{
	plane<float> p;
	p.set(0.5f, 0.2f, 0.3f, 1.f);
	WIN_ASSERT_TRUE(math::abs(p.a - 0.5f) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(p.b - 0.2f) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(p.c - 0.3f) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(p.d - 1.f) <= math::EPSILON);

}
END_TEST


BEGIN_TEST(Plane003)
{
	plane<float> p;
	p.set(0.5f, 0.2f, 0.3f, 1.f);
	p.normalize();

	const auto distance = math::sqrt(0.5f*0.5f + 0.2f * 0.2f + (0.3f * 0.3f));
	const auto expA = 0.5f / distance;
	const auto expB = 0.2f / distance;
	const auto expC = 0.3f / distance;

	WIN_ASSERT_TRUE(math::abs(p.a - expA) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(p.b - expB) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(p.c - expC) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(p.d - 1.f) <= math::EPSILON);

}
END_TEST


BEGIN_TEST(Plane004)
{
	plane<float>   p(0.5f, 0.2f, 0.3f, 1.f);
	const vector3<float> v(0.2f, 0.3f, 0.4f);

	const auto exp   = math::sqrt(0.5f * 0.2f + 0.2f * 0.3f + 0.3f * 0.4f + 1.f); 
	const auto value = p.get_signed_distance(v);

	WIN_ASSERT_TRUE(math::abs(value -  exp) <= math::EPSILON);
}
END_TEST


BEGIN_TEST(Plane005)
{
	plane<float>   p(0.5f, 0.2f, 0.3f, 1.f);
	const vector3<float> v(0.2f, 0.3f, 0.4f);

	const auto exp   = math::abs(math::sqrt(0.5f * 0.2f + 0.2f * 0.3f + 0.3f * 0.4f + 1.f)); 
	const auto value = p.get_signed_distance(v);

	WIN_ASSERT_TRUE(math::abs(value -  exp) <= math::EPSILON);
}
END_TEST
