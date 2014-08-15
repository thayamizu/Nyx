#include "PCH/PCH.h"

using namespace nyx;

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0001)
{
	WIN_TRACE("Vector4::Vector4");
	vector4f v;
	WIN_ASSERT_TRUE(v.x == 0);
	WIN_ASSERT_TRUE(v.y == 0);
	WIN_ASSERT_TRUE(v.z == 0);
	WIN_ASSERT_TRUE(v.w == 0);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0002)
{
	WIN_TRACE("Vector4::Vector4(float x, float y, float z)");
	vector4f v(1, 2, 3, 4);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
	WIN_ASSERT_TRUE(v.z == 3);
	WIN_ASSERT_TRUE(v.w == 4);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0003)
{
	WIN_TRACE("Vector4::Vector3(const Vector3& )");
	vector4f v1(10, 20, 30, 40);
	vector4f v2(v1);
	WIN_ASSERT_TRUE(v2.x == 10);
	WIN_ASSERT_TRUE(v2.y == 20);
	WIN_ASSERT_TRUE(v2.z == 30);
	WIN_ASSERT_TRUE(v2.w == 40);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0004)
{
	WIN_TRACE("Vector4::Set(float x, float y, float z)");
	vector4f v;
	v.set(1, 2, 3, 4);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
	WIN_ASSERT_TRUE(v.z == 3);
	WIN_ASSERT_TRUE(v.w == 4);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0005)
{
	WIN_TRACE("Vector4::Set(float x, float y, float z)");
	vector4f v;
	v.set(1, 2, 3, 4);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
	WIN_ASSERT_TRUE(v.z == 3);
	WIN_ASSERT_TRUE(v.w == 4);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0006)
{
	WIN_TRACE("Vector4::operator + (const Vector3&)");
	vector4f v1(1,2,3, 4);
	vector4f v2(4,5,6, 7);
	vector4f v = v1 + v2 ; 

	WIN_ASSERT_TRUE(v.x == 5);
	WIN_ASSERT_TRUE(v.y == 7);
	WIN_ASSERT_TRUE(v.z == 9);
	WIN_ASSERT_TRUE(v.w == 11);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0007)
{
	WIN_TRACE("Vector4::operator - (const Vector3&)");
	vector4f v1(1,2,3, 4), v2(4,5,6, 7);
	vector4f v = v1 - v2; 
	WIN_ASSERT_TRUE(v.x == -3.f);
	WIN_ASSERT_TRUE(v.y == -3.f);
	WIN_ASSERT_TRUE(v.z == -3.f);
	WIN_ASSERT_TRUE(v.z == -3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0008)
{
	WIN_TRACE("Vector4::operator *(const float u)");
	float u = 3;
	vector4f v1(1,2,3, 4);
	vector4f v = v1 * u; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
	WIN_ASSERT_TRUE(v.z == 9.f);
	WIN_ASSERT_TRUE(v.w == 12.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0009)
{
	WIN_TRACE("Vector4::operator * (const float, const Vector3& )");
	float u = 3;
	vector4f v1(1,2,3, 4);
	vector4f v = v1 *u ; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
	WIN_ASSERT_TRUE(v.z == 9.f);
	WIN_ASSERT_TRUE(v.w == 12.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0010)
{
	WIN_TRACE("Vector4::operator /(const float )");
	float u = 3;
	vector4f v1(3,6,9, 12);
	vector4f v = v1 / u; 
	WIN_ASSERT_TRUE(v.x == 1.f);
	WIN_ASSERT_TRUE(v.y == 2.f);
	WIN_ASSERT_TRUE(v.z == 3.f);
	WIN_ASSERT_TRUE(v.w == 4.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0011)
{
	WIN_TRACE("Vector4::operator += (const Vector3&)");
	vector4f v(1, 2, 3, 4);
	vector4f u(4, 5, 6, 7);
	v += u; 
	WIN_ASSERT_TRUE(v.x == 5.f);
	WIN_ASSERT_TRUE(v.y == 7.f);
	WIN_ASSERT_TRUE(v.z == 9.f);
	WIN_ASSERT_TRUE(v.w == 11.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0012)
{
	WIN_TRACE("Vector4::operator -= (const Vector3&)");
	vector4f v(1, 2, 3, 4);
	vector4f u(4, 5, 6, 7);
	v -= u; 
	WIN_ASSERT_TRUE(v.x == -3.f);
	WIN_ASSERT_TRUE(v.y == -3.f);
	WIN_ASSERT_TRUE(v.z == -3.f);
	WIN_ASSERT_TRUE(v.w == -3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0013)
{
    WIN_TRACE("Vector4::operator *= (const float)");
	float u = 3;
	vector4f v(1,2,3, 4);
	v *= u; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
	WIN_ASSERT_TRUE(v.z == 9.f);
	WIN_ASSERT_TRUE(v.w == 12.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0014)
{
	WIN_TRACE("Vector4::operator /= (const float)");
	float u = 3;
	vector4f v(3, 6, 9, 12);
	v /= u; 
	WIN_ASSERT_TRUE(v.x == 1.f);
	WIN_ASSERT_TRUE(v.y == 2.f);
	WIN_ASSERT_TRUE(v.z == 3.f);
	WIN_ASSERT_TRUE(v.w == 4.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0015)
{
	WIN_TRACE("Vector4::Dot");
	vector4f v1(1.f, 0.f, 0.f, 1.f);
	vector4f v2(0.f, 1.f, 0.f, 0.f);
	const float exp = 0.f;

	const float value = v1.dot(v2);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0016)
{
	WIN_TRACE("Vector4::Dot");
	vector4f v1(1.f, 2.f, 0.f, 3.f);
	vector4f v2(2.f, 1.f, 5.f, 1.f);
	const float exp = 7.f;

	const float value = v1.dot(v2);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

	//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0017)
{
	WIN_TRACE("Vector4::Length");
	vector4f v(1.f, 2.f, 3.f, 4.f);
	const float exp = math::sqrt(30.f);
	const float value = v.norm();

	WIN_ASSERT_TRUE(math::abs(exp - value) <= math::EPSILON);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0018)
{
	WIN_TRACE("Vector4::SquaredLength");
	vector4f v(1.f, 2.f, 3.f, 4.f);
	const float exp =  30.f;
	const float value = v.squared_norm();

	WIN_ASSERT_TRUE(math::abs(exp - value) <= math::EPSILON);
}
END_TEST
	
//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0019)
{
	WIN_TRACE("Vector4::Normalize");
	vector4f v(1.f, 2.f, 3.f, 4.f);
	const float exp =  1.f;
	v.normalize();


	WIN_ASSERT_TRUE(math::abs((v.x*v.x + v.y*v.y + v.z*v.z +v.w*v.w) - exp) <= math::EPSILON);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0020)
{
	WIN_TRACE("Vector4::Inverse");
	vector4f v(1.f, 2.f, 3.f, 4.f);
	v.inverse();

	const float expX = -1.f;
	const float expY = -2.f;
	const float expZ = -3.f;
	const float expW = -4.f;

	WIN_ASSERT_TRUE(v.x == expX);
	WIN_ASSERT_TRUE(v.y == expY);
	WIN_ASSERT_TRUE(v.z == expZ);
	WIN_ASSERT_TRUE(v.w == expW);
	
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0021)
{
	WIN_TRACE("Vector4::IsUnit");
	const vector4f v(1,1,1, 1);

	WIN_ASSERT_FALSE(v.is_unit());
	WIN_ASSERT_TRUE(vector4f::UNIT_X.is_unit());
	WIN_ASSERT_TRUE(vector4f::UNIT_Y.is_unit());
	WIN_ASSERT_TRUE(vector4f::UNIT_Z.is_unit());
	WIN_ASSERT_TRUE(vector4f::UNIT_W.is_unit());
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0022)
{
	WIN_TRACE("Vector4::IsZero");
	const vector4f v(1,1,1, 1);

	WIN_ASSERT_FALSE(v.is_zero());
	WIN_ASSERT_TRUE(vector4f::ZERO.is_zero());
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0023)
{
	WIN_TRACE("Vector4::Equal");
	const vector4f v1(1,1,1, 1);
	const vector4f v2(1,2,1, 1);

	WIN_ASSERT_FALSE(v1 == v2);
	WIN_ASSERT_TRUE(v1 == vector4f::SCALE_UNIT);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector4_0024)
{
	WIN_TRACE("Vector4::Equal");
	const vector4f v1(1,1,1, 1);
	const vector4f v2(1,2,1, 1);

	WIN_ASSERT_TRUE(v1 != v2);
	WIN_ASSERT_FALSE(v1 != vector4f::SCALE_UNIT);
}
END_TEST