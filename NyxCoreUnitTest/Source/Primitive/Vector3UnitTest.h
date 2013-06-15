#include "PCH/PCH.h"

using namespace Nyx;

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0001)
{
	WIN_TRACE("Vector3::Vector3");
	Vector3 v;
	WIN_ASSERT_TRUE(v.x == 0);
	WIN_ASSERT_TRUE(v.y == 0);
	WIN_ASSERT_TRUE(v.z == 0);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0002)
{
	WIN_TRACE("Vector3::Vector3(float x, float y, float z)");
	Vector3 v(1, 2, 3);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
	WIN_ASSERT_TRUE(v.z == 3);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0003)
{
	WIN_TRACE("Vector3::Vector3(const Vector3& )");
	Vector3 v1(10, 20, 30);
	Vector3 v2(v1);
	WIN_ASSERT_TRUE(v2.x == 10);
	WIN_ASSERT_TRUE(v2.y == 20);
	WIN_ASSERT_TRUE(v2.z == 30);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0004)
{
	WIN_TRACE("Vector3::Set(float x, float y, float z)");
	Vector3 v;
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
	Vector3 v;
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
	Vector3 v1(1,2,3);
	Vector3 v2(4,5,6);
	Vector3 v = v1 + v2 ; 

	WIN_ASSERT_TRUE(v.x == 5);
	WIN_ASSERT_TRUE(v.y == 7);
	WIN_ASSERT_TRUE(v.z == 9);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0007)
{
	WIN_TRACE("Vector3::operator - (const Vector3&)");
	Vector3 v1(1,2,3), v2(4,5,6);
	Vector3 v = v1 - v2; 
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
	Vector3 v1(1,2,3);
	Vector3 v = v1 * u; 
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
	Vector3 v1(1,2,3);
	Vector3 v = u * v1; 
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
	Vector3 v1(3,6,9);
	Vector3 v = v1 / u; 
	WIN_ASSERT_TRUE(v.x == 1.f);
	WIN_ASSERT_TRUE(v.y == 2.f);
	WIN_ASSERT_TRUE(v.z == 3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0011)
{
	WIN_TRACE("Vector3::operator += (const Vector3&)");
	Vector3 v(1, 2, 3);
	Vector3 u(4, 5, 6);
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
	Vector3 v(1, 2, 3);
	Vector3 u(4, 5, 6);
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
	Vector3 v(1,2,3);
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
	Vector3 v(3, 6, 9);
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
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0016)
{
	WIN_TRACE("Vector3::Cross");
}
END_TEST

	//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0017)
{
	WIN_TRACE("Vector3::Length");
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0018)
{
	WIN_TRACE("Vector3::SquaredLength");
}
END_TEST
	
//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0019)
{
	WIN_TRACE("Vector3::Normalize");
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0020)
{
	WIN_TRACE("Vector3::Inverse");
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0021)
{
	WIN_TRACE("Vector3::IsUnit");
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0022)
{
	WIN_TRACE("Vector3::IsZero");
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0023)
{
	WIN_TRACE("Vector3::Equal");
}
END_TEST