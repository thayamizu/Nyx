#include "PCH/PCH.h"

using namespace Nyx;

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0001)
{
	WIN_TRACE("Vector2::Vector3");
	Vector2f v;
	WIN_ASSERT_TRUE(v.x == 0);
	WIN_ASSERT_TRUE(v.y == 0);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0002)
{
	WIN_TRACE("Vector2::Vector3(float x, float y, float z)");
	Vector2f v(1, 2);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0003)
{
	WIN_TRACE("Vector2::Vector3(const Vector3& )");
	Vector2f v1(10, 20);
	Vector2f v2(v1);
	WIN_ASSERT_TRUE(v2.x == 10);
	WIN_ASSERT_TRUE(v2.y == 20);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0004)
{
	WIN_TRACE("Vector2::Set(float x, float y, float z)");
	Vector2f v;
	v.Set(1, 2);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0005)
{
	WIN_TRACE("Vector2::Set(float x, float y, float z)");
	Vector2f v;
	v.Set(1, 2);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0006)
{
	WIN_TRACE("Vector2::operator + (const Vector3&)");
	Vector2f v1(1,2);
	Vector2f v2(4,5);
	Vector2f v = v1 + v2 ; 

	WIN_ASSERT_TRUE(v.x == 5);
	WIN_ASSERT_TRUE(v.y == 7);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0007)
{
	WIN_TRACE("Vector2::operator - (const Vector3&)");
	Vector2f v1(1,2), v2(4,5);
	Vector2f v = v1 - v2; 
	WIN_ASSERT_TRUE(v.x == -3.f);
	WIN_ASSERT_TRUE(v.y == -3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0008)
{
	WIN_TRACE("Vector2::operator *(const float u)");
	float u = 3;
	Vector2f v1(1,2);
	Vector2f v = v1 * u; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0009)
{
	WIN_TRACE("Vector2::operator * (const float, const Vector3& )");
	float u = 3;
	Vector2f v1(1,2);
	Vector2f v = v1 *u ; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0010)
{
	WIN_TRACE("Vector2::operator /(const float )");
	float u = 3;
	Vector2f v1(3,6);
	Vector2f v = v1 / u; 
	WIN_ASSERT_TRUE(v.x == 1.f);
	WIN_ASSERT_TRUE(v.y == 2.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0011)
{
	WIN_TRACE("Vector2::operator += (const Vector3&)");
	Vector2f v(1, 2);
	Vector2f u(4, 5);
	v += u; 
	WIN_ASSERT_TRUE(v.x == 5.f);
	WIN_ASSERT_TRUE(v.y == 7.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0012)
{
	WIN_TRACE("Vector2::operator -= (const Vector3&)");
	Vector2f v(1, 2);
	Vector2f u(4, 5);
	v -= u; 
	WIN_ASSERT_TRUE(v.x == -3.f);
	WIN_ASSERT_TRUE(v.y == -3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0013)
{
    WIN_TRACE("Vector2::operator *= (const float)");
	float u = 3;
	Vector2f v(1,2);
	v *= u; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0014)
{
	WIN_TRACE("Vector2::operator /= (const float)");
	float u = 3;
	Vector2f v(3, 6);
	v /= u; 
	WIN_ASSERT_TRUE(v.x == 1.f);
	WIN_ASSERT_TRUE(v.y == 2.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0015)
{
	WIN_TRACE("Vector2::Dot");
	Vector2f v1(1.f, 0.f);
	Vector2f v2(0.f, 1.f);
	const float exp = 0.f;

	const float value = v1.Dot(v2);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0016)
{
	WIN_TRACE("Vector2::Dot");
	Vector2f v1(1.f, 2.f);
	Vector2f v2(2.f, 1.f);
	const float exp = 4.f;

	const float value = v1.Dot(v2);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

	//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0017)
{
	WIN_TRACE("Vector2::Length");
	Vector2f v(1.f, 2.f);
	const float exp = Math::Sqrt(5.f);
	const float value = v.Length();

	WIN_ASSERT_TRUE(Math::Abs(exp - value) <= Math::Epsilon);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0018)
{
	WIN_TRACE("Vector2::SquaredLength");
	Vector2f v(1.f, 2.f);
	const float exp =  5.f;
	const float value = v.SquaredLength();

	WIN_ASSERT_TRUE(Math::Abs(exp - value) <= Math::Epsilon);
}
END_TEST
	
//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0019)
{
	WIN_TRACE("Vector2::Normalize");
	Vector2f v(1.f, 2.f);
	const float exp =  1.f;
	v.Normalize();


	WIN_ASSERT_TRUE(Math::Abs((v.x*v.x + v.y*v.y ) - exp) <= Math::Epsilon);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0020)
{
	WIN_TRACE("Vector2::Inverse");
	Vector2f v(1.f, 2.f);
	v.Inverse();

	const float expX = -1.f;
	const float expY = -2.f;

	WIN_ASSERT_TRUE(v.x == expX);
	WIN_ASSERT_TRUE(v.y == expY);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0021)
{
	WIN_TRACE("Vector2::IsUnit");
	const Vector2f v(1,1);

	WIN_ASSERT_FALSE(v.IsUnit());
	WIN_ASSERT_TRUE(Vector2f::UnitX.IsUnit());
	WIN_ASSERT_TRUE(Vector2f::UnitY.IsUnit());
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0022)
{
	WIN_TRACE("Vector2::IsZero");
	const Vector2f v(1,1);

	WIN_ASSERT_FALSE(v.IsZero());
	WIN_ASSERT_TRUE(Vector2f::Zero.IsZero());
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0023)
{
	WIN_TRACE("Vector2::Equal");
	const Vector2f v1(1,1);
	const Vector2f v2(1,2);

	WIN_ASSERT_FALSE(v1 == v2);
	WIN_ASSERT_TRUE(v1 == Vector2f::ScaleUnit);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0024)
{
	WIN_TRACE("Vector2::Equal");
	const Vector2f v1(1,1);
	const Vector2f v2(1,2);

	WIN_ASSERT_TRUE(v1 != v2);
	WIN_ASSERT_FALSE(v1 != Vector2f::ScaleUnit);
}
END_TEST