#pragma once
#include "PCH/PCH.h"

using namespace Nyx;


BEGIN_TEST(Quaternion_0001)
{
	Quaternion<float> q;
	WIN_ASSERT_TRUE(q.w == 0);
	WIN_ASSERT_TRUE(q.x == 0);
	WIN_ASSERT_TRUE(q.y == 0);
	WIN_ASSERT_TRUE(q.z == 0);
}
END_TEST

BEGIN_TEST(Quaternion_0002)
{
	Quaternion<float> q(1,2,3,4);
	WIN_ASSERT_TRUE(q.w == 1);
	WIN_ASSERT_TRUE(q.x == 2);
	WIN_ASSERT_TRUE(q.y == 3);
	WIN_ASSERT_TRUE(q.z == 4);
}
END_TEST

BEGIN_TEST(Quaternion_0003)
{
	const Vector4f v(1, 2, 3, 4);
	Quaternion<float> q(v);
	WIN_ASSERT_TRUE(q.w == 4);
	WIN_ASSERT_TRUE(q.x == 1);
	WIN_ASSERT_TRUE(q.y == 2);
	WIN_ASSERT_TRUE(q.z == 3);
}
END_TEST

BEGIN_TEST(Quaternion_0004)
{
	const Quaternion<float> q1(1, 2, 3, 4);
	const Quaternion<float> q2(5, 6, 7, 8);
	const Quaternion<float> exp(6,8,10,12);
	const Quaternion<float> value = q1 + q2;
	WIN_ASSERT_TRUE(exp.w == value.w);
	WIN_ASSERT_TRUE(exp.x == value.x);
	WIN_ASSERT_TRUE(exp.y == value.y);
	WIN_ASSERT_TRUE(exp.z == value.z);
}
END_TEST

BEGIN_TEST(Quaternion_0005)
{
	const Quaternion<float> q1(1, 2, 3, 4);
	const Quaternion<float> q2(5, 6, 7, 8);
	const Quaternion<float> exp(-4, -4 , -4 ,-4);
	const Quaternion<float> value = q1 - q2;
	WIN_ASSERT_TRUE(exp.w == value.w);
	WIN_ASSERT_TRUE(exp.x == value.x);
	WIN_ASSERT_TRUE(exp.y == value.y);
	WIN_ASSERT_TRUE(exp.z == value.z);
}
END_TEST

BEGIN_TEST(Quaternion_0006)
{
	const float s = 3;
	const Quaternion<float> q(1, 2, 3, 4);
	const Quaternion<float> exp(3, 6 , 9 , 12);
	const Quaternion<float> value = q * s;
	WIN_ASSERT_TRUE(exp.w == value.w);
	WIN_ASSERT_TRUE(exp.x == value.x);
	WIN_ASSERT_TRUE(exp.y == value.y);
	WIN_ASSERT_TRUE(exp.z == value.z);
}
END_TEST

BEGIN_TEST(Quaternion_0007)
{
	const float s = 3;
	const Quaternion<float> q(1, 2, 3, 4);
	const Quaternion<float> exp(0.33333333333333333f, 0.66666666666666666f , 1.0f , 1.33333333333f);
	const Quaternion<float> value = q / s;
	WIN_ASSERT_TRUE(Math::Abs(exp.w -value.w) <=Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(exp.x -value.x) <=Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(exp.y -value.y) <=Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(exp.z -value.z) <=Math::Epsilon);
}
END_TEST

BEGIN_TEST(Quaternion_0008)
{
	const float s = 0;
	const Quaternion<float> q(1, 2, 3, 4);
	const Quaternion<float> exp(1, 2 , 3 , 4);
	const Quaternion<float> value = q / s;
	WIN_ASSERT_TRUE(exp.w == value.w);
	WIN_ASSERT_TRUE(exp.x == value.x);
	WIN_ASSERT_TRUE(exp.y == value.y);
	WIN_ASSERT_TRUE(exp.z == value.z);
}
END_TEST

BEGIN_TEST(Quaternion_0009)
{
	      Quaternion<float>  q1(1, 2, 3, 4);
	const Quaternion<float>  q2(4, 5, 6, 7);
	const Quaternion<float> exp(5, 7 , 9 , 11);
	q1 += q2;
	WIN_ASSERT_TRUE(exp.w == q1.w);
	WIN_ASSERT_TRUE(exp.x == q1.x);
	WIN_ASSERT_TRUE(exp.y == q1.y);
	WIN_ASSERT_TRUE(exp.z == q1.z);
}
END_TEST

BEGIN_TEST(Quaternion_0010)
{
	      Quaternion<float>  q1(1, 2, 3, 4);
	const Quaternion<float>  q2(4, 5, 6, 7);
	const Quaternion<float> exp(-3, -3 , -3 , -3);
	q1 -= q2;
	WIN_ASSERT_TRUE(exp.w == q1.w);
	WIN_ASSERT_TRUE(exp.x == q1.x);
	WIN_ASSERT_TRUE(exp.y == q1.y);
	WIN_ASSERT_TRUE(exp.z == q1.z);
}
END_TEST

BEGIN_TEST(Quaternion_0011)
{
	      Quaternion<>  q1(1, 2, 3, 4);
	const float               s(3);
	const Quaternion<> exp(3, 6 , 9 , 12);
	q1 *= s;
	WIN_ASSERT_TRUE(exp.w == q1.w);
	WIN_ASSERT_TRUE(exp.x == q1.x);
	WIN_ASSERT_TRUE(exp.y == q1.y);
	WIN_ASSERT_TRUE(exp.z == q1.z);
}
END_TEST

BEGIN_TEST(Quaternion_0012)
{
	      Quaternion<float>  q1(3, 6, 15, 18);
	const float               s(3);
	const Quaternion<float> exp(1.00, 2.00 , 5.00 , 6.00);
	q1 /= s;
	WIN_ASSERT_TRUE(Math::Abs(exp.w - q1.w) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(exp.x - q1.x) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(exp.y - q1.y) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(exp.z - q1.z) <= Math::Epsilon);
}
END_TEST

BEGIN_TEST(Quaternion_0013)
{
	Quaternion<float>  q1;
	q1.SetupIdentity();
	WIN_ASSERT_TRUE(q1.w == 1);
	WIN_ASSERT_TRUE(q1.x == 0);
	WIN_ASSERT_TRUE(q1.y == 0);
	WIN_ASSERT_TRUE(q1.z == 0);
}
END_TEST

BEGIN_TEST(Quaternion_0014)
{
	Quaternion<float>  q1(1, 2, 3, 4);
	const auto length = q1.Length();
	const auto exp    = Math::Sqrt(1 + 2*2 + 3*3 + 4*4);
	WIN_ASSERT_TRUE(Math::Abs(length - exp) <= Math::Epsilon);
}
END_TEST

BEGIN_TEST(Quaternion_0015)
{
	Quaternion<float>  q1(1, 2, 3, 4);
	const auto slength = q1.SquaredLength();
	const auto exp     = 1+ 2*2 + 3*3 + 4*4;
	WIN_ASSERT_TRUE(Math::Abs(slength- exp) <= Math::Epsilon);
}
END_TEST

BEGIN_TEST(Quaternion_0016)
{
	Quaternion<float>  q1(1, 2, 3, 4);
	Quaternion<float>  q2(3, 4, 5, 6);
	const auto exp     = 1*3+ 2*4 + 3*5 + 4*6;
	const auto value   = q1.Dot(q2);
	WIN_ASSERT_TRUE(Math::Abs(exp - value) <= Math::Epsilon);
}
END_TEST

BEGIN_TEST(Quaternion_0017)
{
	Quaternion<float>  q1(1, 2, 3, 4);
	Quaternion<float>  q2(3, 4, 5, 6);
	const auto exp     = 1*3+ 2*4 + 3*5 + 4*6;
	const auto value   = q1.Dot(q2);
	WIN_ASSERT_TRUE(Math::Abs(exp - value) <= Math::Epsilon);
}
END_TEST

BEGIN_TEST(Quaternion_0018)
{
	const auto w = 1.f;
	const Vector3<float> v(2.f, 3.f, 4.f);

	const Quaternion<float>  q1(w, v);
	const Quaternion<float> exp(1.f, 2.f, 3.f, 4.f);
	WIN_ASSERT_TRUE(Math::Abs(exp.w - q1.w) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(exp.x - q1.x) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(exp.y - q1.y) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(exp.z - q1.z) <= Math::Epsilon);
}
END_TEST

BEGIN_TEST(Quaternion_0019)
{
	Quaternion<float>  q1(1, 2, 3, 4);
	Quaternion<float>  q2(5, 6, 7, 8);
	const auto value   = q1.Cross(q2);

	WIN_ASSERT_TRUE(value.w == -60);
	WIN_ASSERT_TRUE(value.x ==  12);
	WIN_ASSERT_TRUE(value.y ==  14);
	WIN_ASSERT_TRUE(value.z ==  24);
}
END_TEST

BEGIN_TEST(Quaternion_0020)
{
	Quaternion<float> q(1,2,3,4);
	q.Normalize();

	WIN_ASSERT_TRUE(Math::Abs(q.Length() - 1) <= Math::Epsilon);

}
END_TEST

BEGIN_TEST(Quaternion_0021)
{
	Quaternion<float> q(1, 2, 3, 4);
	Quaternion<float> inv = q.Inverse();

	Quaternion<float> value = inv.Cross(q);
	WIN_TRACE("value(%f, %f, %f, %f)", value.w, value.x, value.y, value.z);
	WIN_ASSERT_TRUE(Math::Abs(value.w - 1) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(value.x - 0) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(value.y - 0) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(value.z - 0) <= Math::Epsilon);
}
END_TEST

BEGIN_TEST(Quaternion_0022) 
{
	typedef Quaternion<float> qtn;
	qtn q1(0.4, 0.1, 0.2, 0.3);
	qtn q2(0.8, 0.5, 0.6, 0.7);

	const auto slerp = qtn::Slerp(q1, q2, 0.5);
	const auto expW = 0.6507913734559685F;
	const auto expX = 0.32539568672798425F;
	const auto expY = 0.4338609156373123F;
	const auto expZ = 0.5423261445466404F;
	WIN_TRACE("slerp(%f, %f, %f, %f)\n",
		slerp.w, slerp.x, slerp.y, slerp.z);
	WIN_ASSERT_TRUE(Math::Abs(slerp.w - expW) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(slerp.x - expX) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(slerp.y - expY) <= Math::Epsilon);
	WIN_ASSERT_TRUE(Math::Abs(slerp.z - expZ) <= Math::Epsilon);

}
END_TEST