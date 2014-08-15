#include "PCH/PCH.h"

using namespace nyx;

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0001)
{
	WIN_TRACE("Vector2::Vector3");
	vector2f v;
	WIN_ASSERT_TRUE(v.x == 0);
	WIN_ASSERT_TRUE(v.y == 0);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0002)
{
	WIN_TRACE("Vector2::Vector3(float x, float y, float z)");
	vector2f v(1, 2);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0003)
{
	WIN_TRACE("Vector2::Vector3(const Vector3& )");
	vector2f v1(10, 20);
	vector2f v2(v1);
	WIN_ASSERT_TRUE(v2.x == 10);
	WIN_ASSERT_TRUE(v2.y == 20);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0004)
{
	WIN_TRACE("Vector2::Set(float x, float y, float z)");
	vector2f v;
	v.set(1, 2);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0005)
{
	WIN_TRACE("Vector2::Set(float x, float y, float z)");
	vector2f v;
	v.set(1, 2);
	WIN_ASSERT_TRUE(v.x == 1);
	WIN_ASSERT_TRUE(v.y == 2);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0006)
{
	WIN_TRACE("Vector2::operator + (const Vector3&)");
	vector2f v1(1,2);
	vector2f v2(4,5);
	vector2f v = v1 + v2 ; 

	WIN_ASSERT_TRUE(v.x == 5);
	WIN_ASSERT_TRUE(v.y == 7);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0007)
{
	WIN_TRACE("Vector2::operator - (const Vector3&)");
	vector2f v1(1,2), v2(4,5);
	vector2f v = v1 - v2; 
	WIN_ASSERT_TRUE(v.x == -3.f);
	WIN_ASSERT_TRUE(v.y == -3.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0008)
{
	WIN_TRACE("Vector2::operator *(const float u)");
	float u = 3;
	vector2f v1(1,2);
	vector2f v = v1 * u; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0009)
{
	WIN_TRACE("Vector2::operator * (const float, const Vector3& )");
	float u = 3;
	vector2f v1(1,2);
	vector2f v = v1 *u ; 
	WIN_ASSERT_TRUE(v.x == 3.f);
	WIN_ASSERT_TRUE(v.y == 6.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0010)
{
	WIN_TRACE("Vector2::operator /(const float )");
	float u = 3;
	vector2f v1(3,6);
	vector2f v = v1 / u; 
	WIN_ASSERT_TRUE(v.x == 1.f);
	WIN_ASSERT_TRUE(v.y == 2.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0011)
{
	WIN_TRACE("Vector2::operator += (const Vector3&)");
	vector2f v(1, 2);
	vector2f u(4, 5);
	v += u; 
	WIN_ASSERT_TRUE(v.x == 5.f);
	WIN_ASSERT_TRUE(v.y == 7.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0012)
{
	WIN_TRACE("Vector2::operator -= (const Vector3&)");
	vector2f v(1, 2);
	vector2f u(4, 5);
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
	vector2f v(1,2);
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
	vector2f v(3, 6);
	v /= u; 
	WIN_ASSERT_TRUE(v.x == 1.f);
	WIN_ASSERT_TRUE(v.y == 2.f);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0015)
{
	WIN_TRACE("Vector2::Dot");
	vector2f v1(1.f, 0.f);
	vector2f v2(0.f, 1.f);
	const float exp = 0.f;

	const float value = v1.dot(v2);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0016)
{
	WIN_TRACE("Vector2::Dot");
	vector2f v1(1.f, 2.f);
	vector2f v2(2.f, 1.f);
	const float exp = 4.f;

	const float value = v1.dot(v2);
	WIN_ASSERT_TRUE(exp == value);
}
END_TEST

	//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0017)
{
	WIN_TRACE("Vector2::Length");
	vector2f v(1.f, 2.f);
	const float exp = math::sqrt(5.f);
	const float value = v.norm();

	WIN_ASSERT_TRUE(math::abs(exp - value) <= math::EPSILON);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0018)
{
	WIN_TRACE("Vector2::SquaredLength");
	vector2f v(1.f, 2.f);
	const float exp =  5.f;
	const float value = v.squared_norm();

	WIN_ASSERT_TRUE(math::abs(exp - value) <= math::EPSILON);
}
END_TEST
	
//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0019)
{
	WIN_TRACE("Vector2::Normalize");
	vector2f v(1.f, 2.f);
	const float exp =  1.f;
	v.normalize();


	WIN_ASSERT_TRUE(math::abs((v.x*v.x + v.y*v.y ) - exp) <= math::EPSILON);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0020)
{
	WIN_TRACE("Vector2::Inverse");
	vector2f v(1.f, 2.f);
	v.inverse();

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
	const vector2f v(1,1);

	WIN_ASSERT_FALSE(v.is_unit());
	WIN_ASSERT_TRUE(vector2f::UNIT_X.is_unit());
	WIN_ASSERT_TRUE(vector2f::UNIT_Y.is_unit());
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0022)
{
	WIN_TRACE("Vector2::IsZero");
	const vector2f v(1,1);

	WIN_ASSERT_FALSE(v.is_zero());
	WIN_ASSERT_TRUE(vector2f::ZERO.is_zero());
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0023)
{
	WIN_TRACE("Vector2::Equal");
	const vector2f v1(1,1);
	const vector2f v2(1,2);

	WIN_ASSERT_FALSE(v1 == v2);
	WIN_ASSERT_TRUE(v1 == vector2f::SCALE_UNIT);
}
END_TEST

//-----------------------------------------------------------------
BEGIN_TEST(Vector2_0024)
{
	WIN_TRACE("Vector2::Equal");
	const vector2f v1(1,1);
	const vector2f v2(1,2);

	WIN_ASSERT_TRUE(v1 != v2);
	WIN_ASSERT_FALSE(v1 != vector2f::SCALE_UNIT);
}
END_TEST