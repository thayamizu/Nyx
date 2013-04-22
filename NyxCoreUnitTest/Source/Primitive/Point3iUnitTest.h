#ifndef NYX_CORE_UNIT_TEST_POINT3I_H_
#define NYX_CORE_UNIT_TEST_POINT3I_H_

#include "PCH/PCH.h"

BEGIN_TEST(Point3i001)
{
	Point3i p;

	WIN_TRACE("Point3i001");
	WIN_ASSERT_TRUE(p.x == 0);
	WIN_ASSERT_TRUE(p.y == 0);
	WIN_ASSERT_TRUE(p.z == 0);
}
END_TEST

BEGIN_TEST(Point3i002)
{
	Point3i p(10,20,30);

	WIN_TRACE("Point3i002");
	WIN_ASSERT_TRUE(p.x == 10);
	WIN_ASSERT_TRUE(p.y == 20);
	WIN_ASSERT_TRUE(p.z == 30);
}
END_TEST

BEGIN_TEST(Point3i003)
{
	Point3i _p(10, 20, 30);
	Point3i p(_p);

	WIN_TRACE("Point3i003");
	WIN_ASSERT_TRUE(p.x = _p.x);
	WIN_ASSERT_TRUE(p.y = _p.y);
	WIN_ASSERT_TRUE(p.z = _p.z);
}
END_TEST

BEGIN_TEST(Point3i004)
{
	WIN_TRACE("Point3i004");

	WIN_ASSERT_TRUE(Point3i::Unit.x == 1);
	WIN_ASSERT_TRUE(Point3i::Unit.y == 1);
	WIN_ASSERT_TRUE(Point3i::Unit.z == 1);

	WIN_ASSERT_TRUE(Point3i::Zero.x == 0);
	WIN_ASSERT_TRUE(Point3i::Zero.y == 0);
	WIN_ASSERT_TRUE(Point3i::Zero.z == 0);
}
END_TEST

BEGIN_TEST(Point3i005)
{
	const int x=11, y=12, z=13;
	Point3i _p(10, 20, 30);
	Point3i  p(x, y, z);

	p = p + _p;

	WIN_TRACE("Point3i005");
	WIN_ASSERT_TRUE(p.x == (x + _p.x));
	WIN_ASSERT_TRUE(p.y == (y + _p.y));
	WIN_ASSERT_TRUE(p.z == (z + _p.z));
}
END_TEST
	
BEGIN_TEST(Point3i006)
{
	const int x=11, y=12, z=13;
	Point3i _p(10, 20, 30);
	Point3i  p(x, y, z);

	p = p - _p;

	WIN_TRACE("Point3i006");
	WIN_ASSERT_TRUE(p.x == (x - _p.x));
	WIN_ASSERT_TRUE(p.y == (y - _p.y));
	WIN_ASSERT_TRUE(p.z == (z - _p.z));
}
END_TEST

BEGIN_TEST(Point3i007)
{
	const int x=11, y=12, z=13;
	const float value = 2;
	Point3i  p(x, y, z);

	p = p * value;

	WIN_TRACE("Point3i007");
	WIN_ASSERT_TRUE(p.x == (x * value));
	WIN_ASSERT_TRUE(p.y == (y * value));
	WIN_ASSERT_TRUE(p.z == (z * value));
}
END_TEST

BEGIN_TEST(Point3i008)
{
	const int x=11, y=12, z=13;
	const float value = 2;
	Point3i  p(x, y, z);

	p = p / value;

	WIN_TRACE("Point3i008");
	WIN_ASSERT_TRUE(p.x == (int)(x / value));
	WIN_ASSERT_TRUE(p.y == (int)(y / value));
	WIN_ASSERT_TRUE(p.z == (int)(z / value));
}
END_TEST

BEGIN_TEST(Point3i009)
{
	const int x=11, y=12, z=13;
	Point3i _p(10, 20, 30);
	Point3i  p(x, y, z);

	p += _p;

	WIN_TRACE("Point3i009");
	WIN_ASSERT_TRUE(p.x == (x + _p.x));
	WIN_ASSERT_TRUE(p.y == (y + _p.y));
	WIN_ASSERT_TRUE(p.z == (z + _p.z));
}
END_TEST
	
BEGIN_TEST(Point3i010)
{
	const int x=11, y=12, z=13;
	Point3i _p(10, 20, 30);
	Point3i  p(x, y, z);

	p -= _p;

	WIN_TRACE("Point3i010");
	WIN_ASSERT_TRUE(p.x == (x - _p.x));
	WIN_ASSERT_TRUE(p.y == (y - _p.y));
	WIN_ASSERT_TRUE(p.z == (z - _p.z));
}
END_TEST

BEGIN_TEST(Point3i011)
{
	const int x=11, y=12, z=13;
	const float value = 2;
	Point3i  p(x, y, z);

	p  *= value;

	WIN_TRACE("Point3i011");
	WIN_ASSERT_TRUE(p.x == (x * value));
	WIN_ASSERT_TRUE(p.y == (y * value));
	WIN_ASSERT_TRUE(p.z == (z * value));
}
END_TEST

BEGIN_TEST(Point3i012)
{
	const int x=11, y=12, z=13;
	const float value = 2;
	Point3i  p(x, y, z);

	p /= value;

	WIN_TRACE("Point3i012");
	WIN_ASSERT_TRUE(p.x == (int)(x / value));
	WIN_ASSERT_TRUE(p.y == (int)(y / value));
	WIN_ASSERT_TRUE(p.z == (int)(z / value));
}
END_TEST

BEGIN_TEST(Point3i013)
{
	const int x=11, y=12, z=13;
	Point3i  p1(x, y, z);
	Point3i  p2(x, y, z);

	WIN_TRACE("Point3i013");
	WIN_ASSERT_TRUE(p1 == p2);
	WIN_ASSERT_FALSE(p1 != p2);
}
END_TEST

BEGIN_TEST(Point3i014)
{
	const int x=11, y=12, z=13;
	Point3i  p1(x, y, z);
	Point3i  p2(-x, y, z);

	WIN_TRACE("Point3i013");
	WIN_ASSERT_TRUE(p1 != p2);
	WIN_ASSERT_FALSE(p1 == p2);
}
END_TEST
#endif