#ifndef NYX_CORE_UNIT_TEST_POINT3F_H_
#define NYX_CORE_UNIT_TEST_POINT3F_H_

#include "PCH/PCH.h"


BEGIN_TEST(Point3f001)
{
	Point3f p;

	WIN_TRACE("Point3f001");
	WIN_ASSERT_TRUE(p.x == 0);
	WIN_ASSERT_TRUE(p.y == 0);
	WIN_ASSERT_TRUE(p.z == 0);
}
END_TEST

BEGIN_TEST(Point3f002)
{
	Point3f p(10,20,30);

	WIN_TRACE("Point3f002");
	WIN_ASSERT_TRUE(p.x == 10);
	WIN_ASSERT_TRUE(p.y == 20);
	WIN_ASSERT_TRUE(p.z == 30);
}
END_TEST

BEGIN_TEST(Point3f003)
{
	Point3f _p(10, 20, 30);
	Point3f p(_p);

	WIN_TRACE("Point3f003");
	WIN_ASSERT_TRUE(p.x = _p.x);
	WIN_ASSERT_TRUE(p.y = _p.y);
	WIN_ASSERT_TRUE(p.z = _p.z);
}
END_TEST

BEGIN_TEST(Point3f004)
{
	WIN_TRACE("Point3f004");

	WIN_ASSERT_TRUE(Point3f::Unit.x == 1);
	WIN_ASSERT_TRUE(Point3f::Unit.y == 1);
	WIN_ASSERT_TRUE(Point3f::Unit.z == 1);

	WIN_ASSERT_TRUE(Point3f::Zero.x == 0);
	WIN_ASSERT_TRUE(Point3f::Zero.y == 0);
	WIN_ASSERT_TRUE(Point3f::Zero.z == 0);
}
END_TEST

BEGIN_TEST(Point3f005)
{
	const float x=11, y=12, z=13;
	Point3f _p(10, 20, 30);
	Point3f  p(x, y, z);

	p = p + _p;

	WIN_TRACE("Point3f005");
	WIN_ASSERT_TRUE(p.x == (x + _p.x));
	WIN_ASSERT_TRUE(p.y == (y + _p.y));
	WIN_ASSERT_TRUE(p.z == (z + _p.z));
}
END_TEST
	
BEGIN_TEST(Point3f006)
{
	const float x=11, y=12, z=13;
	Point3f _p(10, 20, 30);
	Point3f  p(x, y, z);

	p = p - _p;

	WIN_TRACE("Point3f006");
	WIN_ASSERT_TRUE(p.x == (x - _p.x));
	WIN_ASSERT_TRUE(p.y == (y - _p.y));
	WIN_ASSERT_TRUE(p.z == (z - _p.z));
}
END_TEST

BEGIN_TEST(Point3f007)
{
	const float x=11, y=12, z=13;
	const float value = 2;
	Point3f  p(x, y, z);

	p = p * value;

	WIN_TRACE("Point3f007");
	WIN_ASSERT_TRUE(p.x == (x * value));
	WIN_ASSERT_TRUE(p.y == (y * value));
	WIN_ASSERT_TRUE(p.z == (z * value));
}
END_TEST

BEGIN_TEST(Point3f008)
{
	const float x=11, y=12, z=13;
	const float value = 2;
	Point3f  p(x, y, z);

	p = p / value;

	WIN_TRACE("Point3f008");
	WIN_ASSERT_TRUE(p.x == (x / value));
	WIN_ASSERT_TRUE(p.y == (y / value));
	WIN_ASSERT_TRUE(p.z == (z / value));
}
END_TEST

BEGIN_TEST(Point3f009)
{
	const float x=11, y=12, z=13;
	Point3f _p(10, 20, 30);
	Point3f  p(x, y, z);

	p += _p;

	WIN_TRACE("Point3f009");
	WIN_ASSERT_TRUE(p.x == (x + _p.x));
	WIN_ASSERT_TRUE(p.y == (y + _p.y));
	WIN_ASSERT_TRUE(p.z == (z + _p.z));
}
END_TEST
	
BEGIN_TEST(Point3f010)
{
	const float x=11, y=12, z=13;
	Point3f _p(10, 20, 30);
	Point3f  p(x, y, z);

	p -= _p;

	WIN_TRACE("Point3f010");
	WIN_ASSERT_TRUE(p.x == (x - _p.x));
	WIN_ASSERT_TRUE(p.y == (y - _p.y));
	WIN_ASSERT_TRUE(p.z == (z - _p.z));
}
END_TEST

BEGIN_TEST(Point3f011)
{
	const float x=11, y=12, z=13;
	const float value = 2;
	Point3f  p(x, y, z);

	p  *= value;

	WIN_TRACE("Point3f011");
	WIN_ASSERT_TRUE(p.x == (x * value));
	WIN_ASSERT_TRUE(p.y == (y * value));
	WIN_ASSERT_TRUE(p.z == (z * value));
}
END_TEST

BEGIN_TEST(Point3f012)
{
	const float x=11, y=12, z=13;
	const float value = 2;
	Point3f  p(x, y, z);

	p /= value;

	WIN_TRACE("Point3f012");
	WIN_ASSERT_TRUE(p.x == (x / value));
	WIN_ASSERT_TRUE(p.y == (y / value));
	WIN_ASSERT_TRUE(p.z == (z / value));
}
END_TEST

BEGIN_TEST(Point3f013)
{
	const float x=11, y=12, z=13;
	Point3f  p1(x, y, z);
	Point3f  p2(x, y, z);

	WIN_TRACE("Point3f013");
	WIN_ASSERT_TRUE(p1 == p2);
	WIN_ASSERT_FALSE(p1 != p2);
}
END_TEST

BEGIN_TEST(Point3f014)
{
	const float x=11, y=12, z=13;
	Point3f  p1(x, y, z);
	Point3f  p2(-x, y, z);

	WIN_TRACE("Point3f013");
	WIN_ASSERT_TRUE(p1 != p2);
	WIN_ASSERT_FALSE(p1 == p2);
}
END_TEST
#endif