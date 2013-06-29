#include "PCH/PCH.h"

using namespace Nyx;

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0001)
{
	WIN_TRACE("Vector3::Vector3");
	Vector3f v;
	WIN_ASSERT_TRUE(v.x == 0);
	WIN_ASSERT_TRUE(v.y == 0);
	WIN_ASSERT_TRUE(v.z == 0);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0002)
{
	WIN_TRACE("Vector3::Vector3(float x, float y, float z)");
	Vector3f v(1, 2, 3);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
	WIN_ASSERT_TRUE(v.z == 3);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0003)
{
	WIN_TRACE("Vector3::Vector3(const Vector3& )");
	Vector3f v1(10, 20, 30);
	Vector3f v2(v1);
	WIN_ASSERT_TRUE(v2.x == 10);
	WIN_ASSERT_TRUE(v2.y == 20);
	WIN_ASSERT_TRUE(v2.z == 30);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0004)
{
	WIN_TRACE("Vector3::Set(float x, float y, float z)");
	Vector3f v;
	v.Set(1, 2, 3);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
	WIN_ASSERT_TRUE(v.z == 3);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0005)
{
	WIN_TRACE("Vector3::Set(float x, float y, float z)");
	Vector3f v;
	v.Set(1, 2, 3);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
	WIN_ASSERT_TRUE(v.z == 3);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0006)
{
	WIN_TRACE("Vector3::operator + (const Vector3&)");
	Vector3f v1(1,2,3);
	Vector3f v2(4,5,6);
	Vector3f v = v1 + v2 ; 

	WIN_ASSERT_TRUE(v.x == 5);
	WIN_ASSERT_TRUE(v.y == 7);
	WIN_ASSERT_TRUE(v.z == 9);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0007)
{
	WIN_TRACE("Vector3::operator - (const Vector3&)");
	Vector3f v1(1,2,3), v2(4,5,6);
	Vector3f v = v1 - v2; 
	WIN_ASSERT_TRUE(v.x == -3.f);
	WIN_ASSERT_TRUE(v.y == -3.f);
	WIN_ASSERT_TRUE(v.z == -3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0008)
{
	WIN_TRACE("Vector3::operator *(const float u)");
	float u = 3;
	Vector3f v1(1,2,3);
	Vector3f v = v1 * u; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
	WIN_ASSERT_TRUE(v.z == 9.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0009)
{
	WIN_TRACE("Vector3::operator * (const float, const Vector3& )");
	float u = 3;
	Vector3f v1(1,2,3);
	Vector3f v = v1 *u ; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
	WIN_ASSERT_TRUE(v.z == 9.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0010)
{
	WIN_TRACE("Vector3::operator /(const float )");
	float u = 3;
	Vector3f v1(3,6,9);
	Vector3f v = v1 / u; 
	WIN_ASSERT_TRUE(v.x == 1.f);
	WIN_ASSERT_TRUE(v.y == 2.f);
	WIN_ASSERT_TRUE(v.z == 3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0011)
{
	WIN_TRACE("Vector3::operator += (const Vector3&)");
	Vector3f v(1, 2, 3);
	Vector3f u(4, 5, 6);
	v += u; 
	WIN_ASSERT_TRUE(v.x == 5.f);
	WIN_ASSERT_TRUE(v.y == 7.f);
	WIN_ASSERT_TRUE(v.z == 9.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0012)
{
	WIN_TRACE("Vector3::operator -= (const Vector3&)");
	Vector3f v(1, 2, 3);
	Vector3f u(4, 5, 6);
	v -= u; 
	WIN_ASSERT_TRUE(v.x == -3.f);
	WIN_ASSERT_TRUE(v.y == -3.f);
	WIN_ASSERT_TRUE(v.z == -3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0013)
{
    WIN_TRACE("Vector3::operator *= (const float)");
	float u = 3;
	Vector3f v(1,2,3);
	v *= u; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
	WIN_ASSERT_TRUE(v.z == 9.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0014)
{
	WIN_TRACE("Vector3::operator /= (const float)");
	float u = 3;
	Vector3f v(3, 6, 9);
	v /= u; 
	WIN_ASSERT_TRUE(v.x == 1.f);
	WIN_ASSERT_TRUE(v.y == 2.f);
	WIN_ASSERT_TRUE(v.z == 3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0015)
{
	WIN_TRACE("Vector3::Dot");
	Vector3f v1(1.f, 0.f, 0.f);
	Vector3f v2(0.f, 1.f, 0.f);
	const float exp = 0.f;

	const float value = v1.Dot(v2);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0016)
{
	WIN_TRACE("Vector3::Dot");
	Vector3f v1(1.f, 2.f, 0.f);
	Vector3f v2(2.f, 1.f, 5.f);
	const float exp = 4.f;

	const float value = v1.Dot(v2);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

	//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0017)
{
	WIN_TRACE("Vector3::Length");
	Vector3f v(1.f, 2.f, 3.f);
	const float exp = Math::Sqrt(14.f);
	const float value = v.Length();

	WIN_ASSERT_TRUE(Math::Abs(exp - value) <= Math::Epsilon);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0018)
{
	WIN_TRACE("Vector3::SquaredLength");
	Vector3f v(1.f, 2.f, 3.f);
	const float exp =  14.f;
	const float value = v.SquaredLength();

	WIN_ASSERT_TRUE(Math::Abs(exp - value) <= Math::Epsilon);
}
END_TEST
	
//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0019)
{
	WIN_TRACE("Vector3::Normalize");
	Vector3f v(1.f, 2.f, 3.f);
	const float exp =  1.f;
	v.Normalize();


	WIN_ASSERT_TRUE(Math::Abs((v.x*v.x + v.y*v.y + v.z*v.z) - exp) <= Math::Epsilon);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0020)
{
	WIN_TRACE("Vector3::Inverse");
	Vector3f v(1.f, 2.f, 3.f);
	v.Inverse();

	const float expX = -1.f;
	const float expY = -2.f;
	const float expZ = -3.f;

	WIN_ASSERT_TRUE(v.x == expX);
	WIN_ASSERT_TRUE(v.y == expY);
	WIN_ASSERT_TRUE(v.z == expZ);
	
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0021)
{
	WIN_TRACE("Vector3::IsUnit");
	const Vector3f v(1,1,1);

	WIN_ASSERT_FALSE(v.IsUnit());
	WIN_ASSERT_TRUE(Vector3f::UnitX.IsUnit());
	WIN_ASSERT_TRUE(Vector3f::UnitY.IsUnit());
	WIN_ASSERT_TRUE(Vector3f::UnitZ.IsUnit());
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0022)
{
	WIN_TRACE("Vector3::IsZero");
	const Vector3f v(1,1,1);

	WIN_ASSERT_FALSE(v.IsZero());
	WIN_ASSERT_TRUE(Vector3f::Zero.IsZero());
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0023)
{
	WIN_TRACE("Vector3::Equal");
	const Vector3f v1(1,1,1);
	const Vector3f v2(1,2,1);

	WIN_ASSERT_FALSE(v1 == v2);
	WIN_ASSERT_TRUE(v1 == Vector3f::ScaleUnit);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0024)
{
	WIN_TRACE("Vector3::Equal");
	const Vector3f v1(1,1,1);
	const Vector3f v2(1,2,1);

	WIN_ASSERT_TRUE(v1 != v2);
	WIN_ASSERT_FALSE(v1 != Vector3f::ScaleUnit);
}
END_TEST

BEGIN_TEST(Vector3_0025)
{
	WIN_TRACE("Vector3::Cross");
	Vector3f v1(2, 3, 4);
	Vector3f v2(6, 7, 8);
	const auto exp = Vector3f(44, 0, -11);
	const auto value = v1.Cross(v2);
	WIN_TRACE("cross = (%f, %f, %f)", value.x, value.y, value.z);
}
END_TEST