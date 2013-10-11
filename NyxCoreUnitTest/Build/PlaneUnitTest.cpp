#pragma once
#include "PCH/PCH.h"

using namespace Nyx;

BEGIN_TEST(Plane001)
{
	Plane<float> p ;
	WIN_ASSERT_TRUE(Math::Abs(p.a) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(p.b) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(p.c) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(p.d) <= Math::Epsilon);
}
END_TEST


BEGIN_TEST(Plane002)
{
	Plane<float> p;
	p.Set(0.5f, 0.2f, 0.3f, 1.f);
	WIN_ASSERT_TRUE(Math::Abs(p.a - 0.5f) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(p.b - 0.2f) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(p.c - 0.3f) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(p.d - 1.f) <= Math::Epsilon);

}
END_TEST


BEGIN_TEST(Plane003)
{
	Plane<float> p;
	p.Set(0.5f, 0.2f, 0.3f, 1.f);
	p.Normalize();

	const auto distance = Math::Sqrt(0.5f*0.5f + 0.2f * 0.2f + (0.3f * 0.3f));
	const auto expA = 0.5f / distance;
	const auto expB = 0.2f / distance;
	const auto expC = 0.3f / distance;

	WIN_ASSERT_TRUE(Math::Abs(p.a - expA) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(p.b - expB) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(p.c - expC) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(p.d - 1.f) <= Math::Epsilon);

}
END_TEST


BEGIN_TEST(Plane004)
{
	Plane<float>   p(0.5f, 0.2f, 0.3f, 1.f);
	const Vector3<float> v(0.2f, 0.3f, 0.4f);

	const auto exp   = Math::Sqrt(0.5f * 0.2f + 0.2f * 0.3f + 0.3f * 0.4f + 1.f); 
	const auto value = p.GetSignedDistance(v);

	WIN_ASSERT_TRUE(Math::Abs(value -  exp) <= Math::Epsilon);
}
END_TEST


BEGIN_TEST(Plane005)
{
	Plane<float>   p(0.5f, 0.2f, 0.3f, 1.f);
	const Vector3<float> v(0.2f, 0.3f, 0.4f);

	const auto exp   = Math::Abs(Math::Sqrt(0.5f * 0.2f + 0.2f * 0.3f + 0.3f * 0.4f + 1.f)); 
	const auto value = p.GetSignedDistance(v);

	WIN_ASSERT_TRUE(Math::Abs(value -  exp) <= Math::Epsilon);
}
END_TEST
