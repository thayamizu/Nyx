#include "PCH/PCH.h"

using namespace nyx;

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0001)
{
	WIN_TRACE("Vector3::Vector3");
	vector3f v;
	WIN_ASSERT_TRUE(v.x == 0);
	WIN_ASSERT_TRUE(v.y == 0);
	WIN_ASSERT_TRUE(v.z == 0);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0002)
{
	WIN_TRACE("Vector3::Vector3(float x, float y, float z)");
	vector3f v(1, 2, 3);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
	WIN_ASSERT_TRUE(v.z == 3);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0003)
{
	WIN_TRACE("Vector3::Vector3(const Vector3& )");
	vector3f v1(10, 20, 30);
	vector3f v2(v1);
	WIN_ASSERT_TRUE(v2.x == 10);
	WIN_ASSERT_TRUE(v2.y == 20);
	WIN_ASSERT_TRUE(v2.z == 30);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0004)
{
	WIN_TRACE("Vector3::Set(float x, float y, float z)");
	vector3f v;
	v.set(1, 2, 3);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
	WIN_ASSERT_TRUE(v.z == 3);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0005)
{
	WIN_TRACE("Vector3::Set(float x, float y, float z)");
	vector3f v;
	v.set(1, 2, 3);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
	WIN_ASSERT_TRUE(v.z == 3);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0006)
{
	WIN_TRACE("Vector3::operator + (const Vector3&)");
	vector3f v1(1,2,3);
	vector3f v2(4,5,6);
	vector3f v = v1 + v2 ; 

	WIN_ASSERT_TRUE(v.x == 5);
	WIN_ASSERT_TRUE(v.y == 7);
	WIN_ASSERT_TRUE(v.z == 9);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0007)
{
	WIN_TRACE("Vector3::operator - (const Vector3&)");
	vector3f v1(1,2,3), v2(4,5,6);
	vector3f v = v1 - v2; 
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
	vector3f v1(1,2,3);
	vector3f v = v1 * u; 
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
	vector3f v1(1,2,3);
	vector3f v = v1 *u ; 
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
	vector3f v1(3,6,9);
	vector3f v = v1 / u; 
	WIN_ASSERT_TRUE(v.x == 1.f);
	WIN_ASSERT_TRUE(v.y == 2.f);
	WIN_ASSERT_TRUE(v.z == 3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0011)
{
	WIN_TRACE("Vector3::operator += (const Vector3&)");
	vector3f v(1, 2, 3);
	vector3f u(4, 5, 6);
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
	vector3f v(1, 2, 3);
	vector3f u(4, 5, 6);
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
	vector3f v(1,2,3);
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
	vector3f v(3, 6, 9);
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
	vector3f v1(1.f, 0.f, 0.f);
	vector3f v2(0.f, 1.f, 0.f);
	const float exp = 0.f;

	const float value = v1.dot(v2);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0016)
{
	WIN_TRACE("Vector3::Dot");
	vector3f v1(1.f, 2.f, 0.f);
	vector3f v2(2.f, 1.f, 5.f);
	const float exp = 4.f;

	const float value = v1.dot(v2);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

	//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0017)
{
	WIN_TRACE("Vector3::Length");
	vector3f v(1.f, 2.f, 3.f);
	const float exp = math::sqrt(14.f);
	const float value = v.norm();

	WIN_ASSERT_TRUE(math::abs(exp - value) <= math::EPSILON);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0018)
{
	WIN_TRACE("Vector3::SquaredLength");
	vector3f v(1.f, 2.f, 3.f);
	const float exp =  14.f;
	const float value = v.squared_norm();

	WIN_ASSERT_TRUE(math::abs(exp - value) <= math::EPSILON);
}
END_TEST
	
//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0019)
{
	WIN_TRACE("Vector3::Normalize");
	vector3f v(1.f, 2.f, 3.f);
	const float exp =  1.f;
	v.normalize();


	WIN_ASSERT_TRUE(math::abs((v.x*v.x + v.y*v.y + v.z*v.z) - exp) <= math::EPSILON);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0020)
{
	WIN_TRACE("Vector3::Inverse");
	vector3f v(1.f, 2.f, 3.f);
	v.inverse();

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
	const vector3f v(1,1,1);

	WIN_ASSERT_FALSE(v.is_unit());
	WIN_ASSERT_TRUE(vector3f::UNIT_X.is_unit());
	WIN_ASSERT_TRUE(vector3f::UNIT_Y.is_unit());
	WIN_ASSERT_TRUE(vector3f::UNIT_Z.is_unit());
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0022)
{
	WIN_TRACE("Vector3::IsZero");
	const vector3f v(1,1,1);

	WIN_ASSERT_FALSE(v.is_zero());
	WIN_ASSERT_TRUE(vector3f::ZERO.is_zero());
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0023)
{
	WIN_TRACE("Vector3::Equal");
	const vector3f v1(1,1,1);
	const vector3f v2(1,2,1);

	WIN_ASSERT_FALSE(v1 == v2);
	WIN_ASSERT_TRUE(v1 == vector3f::SCALE_UNIT);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector3_0024)
{
	WIN_TRACE("Vector3::Equal");
	const vector3f v1(1,1,1);
	const vector3f v2(1,2,1);

	WIN_ASSERT_TRUE(v1 != v2);
	WIN_ASSERT_FALSE(v1 != vector3f::SCALE_UNIT);
}
END_TEST

BEGIN_TEST(Vector3_0025)
{
	WIN_TRACE("Vector3::Cross");
	vector3f v1(2, 3, 4);
	vector3f v2(6, 7, 8);
	const auto exp = vector3f(44, 0, -11);
	const auto value = v1.cross(v2);
	WIN_TRACE("cross = (%f, %f, %f)", value.x, value.y, value.z);
}
END_TEST