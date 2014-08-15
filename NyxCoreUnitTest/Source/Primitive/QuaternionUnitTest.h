#pragma once
#include "PCH/PCH.h"

using namespace nyx;


BEGIN_TEST(Quaternion_0001)
{
	quaternion<float> q;
	WIN_ASSERT_TRUE(q.w == 0);
	WIN_ASSERT_TRUE(q.x == 0);
	WIN_ASSERT_TRUE(q.y == 0);
	WIN_ASSERT_TRUE(q.z == 0);
}
END_TEST

BEGIN_TEST(Quaternion_0002)
{
	quaternion<float> q(1,2,3,4);
	WIN_ASSERT_TRUE(q.w == 1);
	WIN_ASSERT_TRUE(q.x == 2);
	WIN_ASSERT_TRUE(q.y == 3);
	WIN_ASSERT_TRUE(q.z == 4);
}
END_TEST

BEGIN_TEST(Quaternion_0003)
{
	const vector4f v(1, 2, 3, 4);
	quaternion<float> q(v);
	WIN_ASSERT_TRUE(q.w == 4);
	WIN_ASSERT_TRUE(q.x == 1);
	WIN_ASSERT_TRUE(q.y == 2);
	WIN_ASSERT_TRUE(q.z == 3);
}
END_TEST

BEGIN_TEST(Quaternion_0004)
{
	const quaternion<float> q1(1, 2, 3, 4);
	const quaternion<float> q2(5, 6, 7, 8);
	const quaternion<float> exp(6,8,10,12);
	const quaternion<float> value = q1 + q2;
	WIN_ASSERT_TRUE(exp.w == value.w);
	WIN_ASSERT_TRUE(exp.x == value.x);
	WIN_ASSERT_TRUE(exp.y == value.y);
	WIN_ASSERT_TRUE(exp.z == value.z);
}
END_TEST

BEGIN_TEST(Quaternion_0005)
{
	const quaternion<float> q1(1, 2, 3, 4);
	const quaternion<float> q2(5, 6, 7, 8);
	const quaternion<float> exp(-4, -4 , -4 ,-4);
	const quaternion<float> value = q1 - q2;
	WIN_ASSERT_TRUE(exp.w == value.w);
	WIN_ASSERT_TRUE(exp.x == value.x);
	WIN_ASSERT_TRUE(exp.y == value.y);
	WIN_ASSERT_TRUE(exp.z == value.z);
}
END_TEST

BEGIN_TEST(Quaternion_0006)
{
	const float s = 3;
	const quaternion<float> q(1, 2, 3, 4);
	const quaternion<float> exp(3, 6 , 9 , 12);
	const quaternion<float> value = q * s;
	WIN_ASSERT_TRUE(exp.w == value.w);
	WIN_ASSERT_TRUE(exp.x == value.x);
	WIN_ASSERT_TRUE(exp.y == value.y);
	WIN_ASSERT_TRUE(exp.z == value.z);
}
END_TEST

BEGIN_TEST(Quaternion_0007)
{
	const float s = 3;
	const quaternion<float> q(1, 2, 3, 4);
	const quaternion<float> exp(0.33333333333333333f, 0.66666666666666666f , 1.0f , 1.33333333333f);
	const quaternion<float> value = q / s;
	WIN_ASSERT_TRUE(math::abs(exp.w -value.w) <=math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(exp.x -value.x) <=math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(exp.y -value.y) <=math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(exp.z -value.z) <=math::EPSILON);
}
END_TEST

BEGIN_TEST(Quaternion_0008)
{
	const float s = 0;
	const quaternion<float> q(1, 2, 3, 4);
	const quaternion<float> exp(1, 2 , 3 , 4);
	const quaternion<float> value = q / s;
	WIN_ASSERT_TRUE(exp.w == value.w);
	WIN_ASSERT_TRUE(exp.x == value.x);
	WIN_ASSERT_TRUE(exp.y == value.y);
	WIN_ASSERT_TRUE(exp.z == value.z);
}
END_TEST

BEGIN_TEST(Quaternion_0009)
{
	      quaternion<float>  q1(1, 2, 3, 4);
	const quaternion<float>  q2(4, 5, 6, 7);
	const quaternion<float> exp(5, 7 , 9 , 11);
	q1 += q2;
	WIN_ASSERT_TRUE(exp.w == q1.w);
	WIN_ASSERT_TRUE(exp.x == q1.x);
	WIN_ASSERT_TRUE(exp.y == q1.y);
	WIN_ASSERT_TRUE(exp.z == q1.z);
}
END_TEST

BEGIN_TEST(Quaternion_0010)
{
	      quaternion<float>  q1(1, 2, 3, 4);
	const quaternion<float>  q2(4, 5, 6, 7);
	const quaternion<float> exp(-3, -3 , -3 , -3);
	q1 -= q2;
	WIN_ASSERT_TRUE(exp.w == q1.w);
	WIN_ASSERT_TRUE(exp.x == q1.x);
	WIN_ASSERT_TRUE(exp.y == q1.y);
	WIN_ASSERT_TRUE(exp.z == q1.z);
}
END_TEST

BEGIN_TEST(Quaternion_0011)
{
	      quaternion<>  q1(1, 2, 3, 4);
	const float               s(3);
	const quaternion<> exp(3, 6 , 9 , 12);
	q1 *= s;
	WIN_ASSERT_TRUE(exp.w == q1.w);
	WIN_ASSERT_TRUE(exp.x == q1.x);
	WIN_ASSERT_TRUE(exp.y == q1.y);
	WIN_ASSERT_TRUE(exp.z == q1.z);
}
END_TEST

BEGIN_TEST(Quaternion_0012)
{
	      quaternion<float>  q1(3, 6, 15, 18);
	const float               s(3);
	const quaternion<float> exp(1.00, 2.00 , 5.00 , 6.00);
	q1 /= s;
	WIN_ASSERT_TRUE(math::abs(exp.w - q1.w) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(exp.x - q1.x) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(exp.y - q1.y) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(exp.z - q1.z) <= math::EPSILON);
}
END_TEST

BEGIN_TEST(Quaternion_0013)
{
	quaternion<float>  q1;
	q1.set_identity();
	WIN_ASSERT_TRUE(q1.w == 1);
	WIN_ASSERT_TRUE(q1.x == 0);
	WIN_ASSERT_TRUE(q1.y == 0);
	WIN_ASSERT_TRUE(q1.z == 0);
}
END_TEST

BEGIN_TEST(Quaternion_0014)
{
	quaternion<float>  q1(1, 2, 3, 4);
	const auto length = q1.norm();
	const auto exp    = math::sqrt(1 + 2*2 + 3*3 + 4*4);
	WIN_ASSERT_TRUE(math::abs(length - exp) <= math::EPSILON);
}
END_TEST

BEGIN_TEST(Quaternion_0015)
{
	quaternion<float>  q1(1, 2, 3, 4);
	const auto slength = q1.squared_norm();
	const auto exp     = 1+ 2*2 + 3*3 + 4*4;
	WIN_ASSERT_TRUE(math::abs(slength- exp) <= math::EPSILON);
}
END_TEST

BEGIN_TEST(Quaternion_0016)
{
	quaternion<float>  q1(1, 2, 3, 4);
	quaternion<float>  q2(3, 4, 5, 6);
	const auto exp     = 1*3+ 2*4 + 3*5 + 4*6;
	const auto value   = q1.dot(q2);
	WIN_ASSERT_TRUE(math::abs(exp - value) <= math::EPSILON);
}
END_TEST

BEGIN_TEST(Quaternion_0017)
{
	quaternion<float>  q1(1, 2, 3, 4);
	quaternion<float>  q2(3, 4, 5, 6);
	const auto exp     = 1*3+ 2*4 + 3*5 + 4*6;
	const auto value   = q1.dot(q2);
	WIN_ASSERT_TRUE(math::abs(exp - value) <= math::EPSILON);
}
END_TEST

BEGIN_TEST(Quaternion_0018)
{
	const auto w = 1.f;
	const vector3<float> v(2.f, 3.f, 4.f);

	const quaternion<float>  q1(w, v);
	const quaternion<float> exp(1.f, 2.f, 3.f, 4.f);
	WIN_ASSERT_TRUE(math::abs(exp.w - q1.w) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(exp.x - q1.x) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(exp.y - q1.y) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(exp.z - q1.z) <= math::EPSILON);
}
END_TEST

BEGIN_TEST(Quaternion_0019)
{
	quaternion<float>  q1(1, 2, 3, 4);
	quaternion<float>  q2(5, 6, 7, 8);
	const auto value   = q1.cross(q2);

	WIN_ASSERT_TRUE(value.w == -60);
	WIN_ASSERT_TRUE(value.x ==  12);
	WIN_ASSERT_TRUE(value.y ==  14);
	WIN_ASSERT_TRUE(value.z ==  24);
}
END_TEST

BEGIN_TEST(Quaternion_0020)
{
	quaternion<float> q(1,2,3,4);
	q.normalize();

	WIN_ASSERT_TRUE(math::abs(q.norm() - 1) <= math::EPSILON);

}
END_TEST

BEGIN_TEST(Quaternion_0021)
{
	quaternion<float> q(1, 2, 3, 4);
	quaternion<float> inv = q.inverse();

	quaternion<float> value = inv.cross(q);
	WIN_TRACE("value(%f, %f, %f, %f)", value.w, value.x, value.y, value.z);
	WIN_ASSERT_TRUE(math::abs(value.w - 1) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(value.x - 0) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(value.y - 0) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(value.z - 0) <= math::EPSILON);
}
END_TEST

BEGIN_TEST(Quaternion_0022) 
{
	typedef quaternion<float> qtn;
	qtn q1(0.4f, 0.1f, 0.2f, 0.3f);
	qtn q2(0.8f, 0.5f, 0.6f, 0.7f);

	const auto slerp = qtn::slerp(q1, q2, 0.5);
	const auto expW = 0.6507913734559685F;
	const auto expX = 0.32539568672798425F;
	const auto expY = 0.4338609156373123F;
	const auto expZ = 0.5423261445466404F;
	WIN_TRACE("slerp(%f, %f, %f, %f)\n",
		slerp.w, slerp.x, slerp.y, slerp.z);
	WIN_ASSERT_TRUE(math::abs(slerp.w - expW) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(slerp.x - expX) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(slerp.y - expY) <= math::EPSILON);
	WIN_ASSERT_TRUE(math::abs(slerp.z - expZ) <= math::EPSILON);

}
END_TEST