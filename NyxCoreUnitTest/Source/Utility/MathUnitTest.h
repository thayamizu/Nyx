#pragma once
#include "PCH/PCH.h"
#include <cmath>
using namespace Nyx;

static const float M_PI = 3.14159265358979323846f;
static const float M_E  = 2.71828182845904523536f;
static const float EPS  = 1e-6f;

static inline bool EQ(float x, float y) {
	return (abs((x) - (y)) < EPS) ? true :false;
}
BEGIN_TEST(Math001)
{
	WIN_ASSERT_TRUE(EQ(Math::E, M_E));
	WIN_ASSERT_TRUE(EQ(Math::PI, M_PI));
	WIN_ASSERT_TRUE(EQ(Math::HalfPI, M_PI/2));
	WIN_ASSERT_TRUE(EQ(Math::QuadraplePI, M_PI/4));
	WIN_ASSERT_TRUE(EQ(Math::DoublePI, M_PI*2));
	WIN_ASSERT_TRUE(EQ(Math::QuadrantPI, M_PI*4));
}
END_TEST

	BEGIN_TEST(Math002)
{
	float f1 = Math::ToRadian(180);
	float f2 = Math::ToRadian(90);
	float f3 = Math::ToRadian(45);

	WIN_ASSERT_TRUE(EQ(f1, Math::PI));
	WIN_ASSERT_TRUE(EQ(f2, Math::HalfPI));
	WIN_ASSERT_TRUE(EQ(f3, Math::QuadraplePI));
}
END_TEST
	BEGIN_TEST(Math003)
{
	float f1 = Math::ToDegree(Math::PI);
	float f2 = Math::ToDegree(Math::HalfPI);
	float f3 = Math::ToDegree(Math::QuadraplePI);

	WIN_ASSERT_TRUE(EQ(f1, 180.f));
	WIN_ASSERT_TRUE(EQ(f2, 90.f));
	WIN_ASSERT_TRUE(EQ(f3, 45.f));
}
END_TEST
	BEGIN_TEST(Math004)
{
	int abs = 2;
	int a = Math::Abs(2);
	int b = Math::Abs(-2);

	WIN_ASSERT_TRUE(a == abs);
	WIN_ASSERT_TRUE(b == abs);
}
END_TEST
	BEGIN_TEST(Math005)
{
	float abs = 2;
	float a = Math::Abs(2.f);
	float b = Math::Abs(-2.f);

	WIN_ASSERT_TRUE(a == abs);
	WIN_ASSERT_TRUE(b == abs);
}
END_TEST;

BEGIN_TEST(Math006)
{
	const int _v1 =3, _v2=2;
	const int value = Math::Max(_v1, _v2);
	WIN_ASSERT_TRUE(_v1 == value);
}
END_TEST
	BEGIN_TEST(Math007)
{
	const int _v1 =3, _v2=3;
	const int value = Math::Max(_v1, _v2);
	WIN_ASSERT_TRUE(_v2 == value);
}
END_TEST

	BEGIN_TEST(Math008)
{
	const float _v1 =3, _v2=2;
	const float value = Math::Max(_v1, _v2);
	WIN_ASSERT_TRUE(_v1 == value);
}
END_TEST

	BEGIN_TEST(Math009)
{
	const float _v1 =3, _v2=3;
	const float value = Math::Max(_v1, _v2);
	WIN_ASSERT_TRUE(_v2 == value);
}
END_TEST


	BEGIN_TEST(Math010)
{
	const int _v1 =3, _v2=2;
	const int value = Math::Min(_v1, _v2);
	WIN_ASSERT_TRUE(_v2 == value);
}
END_TEST
	BEGIN_TEST(Math011)
{
	const int _v1 =3, _v2=3;
	const int value = Math::Min(_v1, _v2);
	WIN_ASSERT_TRUE(_v1 == value);
}
END_TEST

	BEGIN_TEST(Math012)
{
	const float _v1 =3, _v2=2;
	const float value = Math::Min(_v1, _v2);
	WIN_ASSERT_TRUE(_v2 == value);
}
END_TEST

	BEGIN_TEST(Math013)
{
	const float exp = 2.f;
	const float _v = 2.0;
	const float value = Math::Ceil(_v);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math014)
{
	const float exp = 3.f;
	const float _v = 2.1f;
	const float value = Math::Ceil(_v);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math015)
{
	const float exp = 2.f;
	const float _v =2.f;
	const float value = Math::Floor(_v);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

	BEGIN_TEST(Math016)
{
	const float exp = 1.0f;
	const float _v =1.5f;
	const float value = Math::Floor(_v);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

	BEGIN_TEST(Math017)
{
	const float exp = 1.41421356f;
	const float _v =2.f;
	const float value = Math::Sqrt(_v);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math018)
{
	const float exp = 8.f;
	const int x = 2, y = 3;
	const float value = Math::Pow(x, y);

	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math019)
{
	const float exp = 8.f;
	const int y = 3;
	const float value = Math::Pow2(y);

	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math020)
{
	const float exp = Math::Pow(Math::E, 2);
	const float y = 2;
	const float value = Math::Exp(y);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST

	BEGIN_TEST(Math021)
{
	const float exp = 1.000000;
	const float y   = Math::E;
	const float value = Math::Log(y);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math022)
{
	const float exp = 1;
	const float y   = 10;
	const float value = Math::Log10(y);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math023)
{
	const bool exp = true;
	const float y   = 4;
	const bool value = Math::IsPow2(y);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math024)
{
	const bool exp = false;
	const float y   = 3;
	const bool value = Math::IsPow2(y);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST
	BEGIN_TEST(Math025)
{
	const float exp = 1;
	const float rad = Math::ToRadian(90);
	const float value = Math::Sin(rad);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math026)
{
	const float exp = 0;
	const float rad = Math::ToRadian(90);
	const float value = Math::Cos(rad);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math027)
{
	const float exp = 1;
	const float rad = Math::ToRadian(45);
	const float value = Math::Tan(rad);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math028)
{
	const float exp = (Math::Exp(2) - Math::Exp(-2))/2;
	const float value = Math::Sinh(2);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math029)
{
	const float exp = (Math::Exp(2) + Math::Exp(-2))/2;
	const float value = Math::Cosh(2);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math030)
{
	const float _v = 2;
	const float exp = Math::Sinh(_v)/Math::Cosh(_v);
	const float value = Math::Tanh(_v);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math031)
{
	const float exp = Math::HalfPI;
	const float value = Math::Asin(1);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math032)
{
	const float exp = Math::HalfPI;
	const float value = Math::Acos(0);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math033)
{
	const float exp = Math::QuadraplePI;
	const float value = Math::Atan(1);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST
	BEGIN_TEST(Math034)
{
	const float exp = Math::QuadraplePI;
	const float value = Math::Atan2(1,1);
	WIN_ASSERT_TRUE(EQ(exp, value));
}
END_TEST


	BEGIN_TEST(Math035)
{
	const int value = 10;
	const int upper = 5;
	const int result = Math::UpperClamp(value, upper);
	WIN_ASSERT_TRUE(result == upper);
}
END_TEST


	BEGIN_TEST(Math036)
{
	const int value = 5;
	const int upper = 5;
	const int result = Math::UpperClamp(value, upper);
	WIN_ASSERT_TRUE(result == upper);
}
END_TEST


	BEGIN_TEST(Math037)
{
	const int value = 5;
	const int  upper = 4;
	const int result = Math::UpperClamp(value, upper);
	WIN_ASSERT_TRUE(result == upper);
}
END_TEST

	BEGIN_TEST(Math038)
{
	const int value = -5;
	const int lower = 0;
	const int result = Math::LowerClamp(value, lower);
	WIN_ASSERT_TRUE(result == lower);
}
END_TEST


	BEGIN_TEST(Math039)
{
	const int value = -5;
	const int lower = -5;
	const int result = Math::LowerClamp(value, lower);
	WIN_ASSERT_TRUE(result == lower);
}
END_TEST


	BEGIN_TEST(Math040)
{
	const int value = -5;
	const int lower = -10;
	const int result = Math::LowerClamp(value, lower);
	WIN_ASSERT_TRUE(result == value);
}
END_TEST
