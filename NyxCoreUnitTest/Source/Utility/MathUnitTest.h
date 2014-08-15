#pragma once
#include "PCH/PCH.h"
#include <cmath>
using namespace nyx;

static const float M_PI = 3.14159265358979323846f;
static const float M_E  = 2.71828182845904523536f;
static const float EPS  = 1e-6f;

static inline bool EQ(float x, float y) {
	return (abs((x) - (y)) < EPS) ? true :false;
}
BEGIN_TEST(Math001)
{
	WIN_ASSERT_TRUE(EQ(math::E, M_E));
	WIN_ASSERT_TRUE(EQ(math::PI, M_PI));
	WIN_ASSERT_TRUE(EQ(math::HALF_PI, M_PI/2));
	WIN_ASSERT_TRUE(EQ(math::QUADRAPLE_PI, M_PI/4));
	WIN_ASSERT_TRUE(EQ(math::DOUBLE_PI, M_PI*2));
	WIN_ASSERT_TRUE(EQ(math::QUADRANT_PI, M_PI*4));
}
END_TEST

	BEGIN_TEST(Math002)
{
	float f1 = math::to_radian(180);
	float f2 = math::to_radian(90);
	float f3 = math::to_radian(45);

	WIN_ASSERT_TRUE(EQ(f1, math::PI));
	WIN_ASSERT_TRUE(EQ(f2, math::HALF_PI));
	WIN_ASSERT_TRUE(EQ(f3, math::QUADRAPLE_PI));
}
END_TEST
	BEGIN_TEST(Math003)
{
	float f1 = math::to_degree(math::PI);
	float f2 = math::to_degree(math::HALF_PI);
	float f3 = math::to_degree(math::QUADRAPLE_PI);

	WIN_ASSERT_TRUE(EQ(f1, 180.f));
	WIN_ASSERT_TRUE(EQ(f2, 90.f));
	WIN_ASSERT_TRUE(EQ(f3, 45.f));
}
END_TEST
	BEGIN_TEST(Math004)
{
	int abs = 2;
	int a = math::abs(2);
	int b = math::abs(-2);

	WIN_ASSERT_TRUE(a == abs);
	WIN_ASSERT_TRUE(b == abs);
}
END_TEST
	BEGIN_TEST(Math005)
{
	float abs = 2;
	float a = math::abs(2.f);
	float b = math::abs(-2.f);

	WIN_ASSERT_TRUE(a == abs);
	WIN_ASSERT_TRUE(b == abs);
}
END_TEST;

BEGIN_TEST(Math006)
{
	const int _v1 =3, _v2=2;
	const int value = math::max_of(_v1, _v2);
	WIN_ASSERT_TRUE(_v1 == value);
}
END_TEST
	BEGIN_TEST(Math007)
{
	const int _v1 =3, _v2=3;
	const int value = math::max_of(_v1, _v2);
	WIN_ASSERT_TRUE(_v2 == value);
}
END_TEST

	BEGIN_TEST(Math008)
{
	const float _v1 =3, _v2=2;
	const float value = math::max_of(_v1, _v2);
	WIN_ASSERT_TRUE(_v1 == value);
}
END_TEST

	BEGIN_TEST(Math009)
{
	const float _v1 =3, _v2=3;
	const float value = math::max_of(_v1, _v2);
	WIN_ASSERT_TRUE(_v2 == value);
}
END_TEST


	BEGIN_TEST(Math010)
{
	const int _v1 =3, _v2=2;
	const int value = math::min_of(_v1, _v2);
	WIN_ASSERT_TRUE(_v2 == value);
}
END_TEST
	BEGIN_TEST(Math011)
{
	const int _v1 =3, _v2=3;
	const int value = math::min_of(_v1, _v2);
	WIN_ASSERT_TRUE(_v1 == value);
}
END_TEST

	BEGIN_TEST(Math012)
{
	const float _v1 =3, _v2=2;
	const float value = math::min_of(_v1, _v2);
	WIN_ASSERT_TRUE(_v2 == value);
}
END_TEST

	BEGIN_TEST(Math013)
{
	const float exp = 2.f;
	const float _v = 2.0;
	const float value = math::ceil(_v);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math014)
{
	const float exp = 3.f;
	const float _v = 2.1f;
	const float value = math::ceil(_v);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math015)
{
	const float exp = 2.f;
	const float _v =2.f;
	const float value = math::floor(_v);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

	BEGIN_TEST(Math016)
{
	const float exp = 1.0f;
	const float _v =1.5f;
	const float value = math::floor(_v);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

	BEGIN_TEST(Math017)
{
	const float exp = 1.41421356f;
	const float _v =2.f;
	const float value = math::sqrt(_v);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math018)
{
	const float exp = 8.f;
	const int x = 2, y = 3;
	const float value = math::power(x, y);

	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math019)
{
	const float exp = 8.f;
	const int y = 3;
	const float value = math::power2(y);

	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math020)
{
	const float exp = math::power(math::E, 2);
	const float y = 2;
	const float value = math::exponent(y);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST

	BEGIN_TEST(Math021)
{
	const float exp = 1.000000;
	const float y   = math::E;
	const float value = math::log(y);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math022)
{
	const float exp = 1;
	const float y   = 10;
	const float value = math::log10(y);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math023)
{
	const bool exp = true;
	const float y   = 4;
	const bool value = math::is_power2(y);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math024)
{
	const bool exp = false;
	const float y   = 3;
	const bool value = math::is_power2(y);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math025)
{
	const float exp = 1;
	const float rad = math::to_radian(90);
	const float value = math::sin(rad);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math026)
{
	const float exp = 0;
	const float rad = math::to_radian(90);
	const float value = math::cos(rad);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math027)
{
	const float exp = 1;
	const float rad = math::to_radian(45);
	const float value = math::tan(rad);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math028)
{
	const float exp = (math::exponent(2) - math::exponent(-2))/2;
	const float value = math::sinh(2);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math029)
{
	const float exp = (math::exponent(2) + math::exponent(-2))/2;
	const float value = math::cosh(2);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math030)
{
	const float _v = 2;
	const float exp = math::sinh(_v)/math::cosh(_v);
	const float value = math::tanh(_v);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math031)
{
	const float exp = math::HALF_PI;
	const float value = math::asin(1);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math032)
{
	const float exp = math::HALF_PI;
	const float value = math::acos(0);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math033)
{
	const float exp = math::QUADRAPLE_PI;
	const float value = math::atan(1);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math034)
{
	const float exp = math::QUADRAPLE_PI;
	const float value = math::atan2(1,1);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST


	BEGIN_TEST(Math035)
{
	const int value = 10;
	const int upper = 5;
	const int result = math::upper_clamp(value, upper);
	WIN_ASSERT_TRUE(result == upper);
}
END_TEST


	BEGIN_TEST(Math036)
{
	const int value = 5;
	const int upper = 5;
	const int result = math::upper_clamp(value, upper);
	WIN_ASSERT_TRUE(result == upper);
}
END_TEST


	BEGIN_TEST(Math037)
{
	const int value = 5;
	const int  upper = 4;
	const int result = math::upper_clamp(value, upper);
	WIN_ASSERT_TRUE(result == upper);
}
END_TEST

	BEGIN_TEST(Math038)
{
	const int value = -5;
	const int lower = 0;
	const int result = math::lower_clamp(value, lower);
	WIN_ASSERT_TRUE(result == lower);
}
END_TEST


	BEGIN_TEST(Math039)
{
	const int value = -5;
	const int lower = -5;
	const int result = math::lower_clamp(value, lower);
	WIN_ASSERT_TRUE(result == lower);
}
END_TEST


	BEGIN_TEST(Math040)
{
	const int value = -5;
	const int lower = -10;
	const int result = math::lower_clamp(value, lower);
	WIN_ASSERT_TRUE(result == value);
}
END_TEST
