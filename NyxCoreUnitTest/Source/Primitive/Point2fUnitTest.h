#ifndef NYX_CORE_UNIT_TEST_POINT2F_H_
#define NYX_CORE_UNIT_TEST_POINT2F_H_

#include "PCH/PCH.h"

using namespace Nyx;

BEGIN_TEST(Point2f001)
{
	Point2f p;

	WIN_TRACE("Point2f001");
	WIN_ASSERT_TRUE(p.x == 0);
	WIN_ASSERT_TRUE(p.y == 0);
}
END_TEST

BEGIN_TEST(Point2f002)
{
	Point2f p(10, 20);

	WIN_TRACE("Point2f002");
	WIN_ASSERT_TRUE(p.x == 10);
	WIN_ASSERT_TRUE(p.y == 20);
}
END_TEST

BEGIN_TEST(Point2f003)
{
	float a[2] ={10, 20};
	Point2f p(a);
	WIN_TRACE("Point2f003");
	WIN_ASSERT_TRUE(p.x == a[0]);
	WIN_ASSERT_TRUE(p.y == a[1]);
}
END_TEST

BEGIN_TEST(Point2f004)
{
	Point2f _p(10, 20);
	Point2f p(_p);
	WIN_TRACE("Point2f004");
	WIN_ASSERT_TRUE(p.x == _p.x);
	WIN_ASSERT_TRUE(p.y == _p.y);
}
END_TEST

BEGIN_TEST(Point2f005)
{
	WIN_TRACE("Pointi2i005");
	WIN_ASSERT_TRUE(Point2f::Zero.x == 0);
	WIN_ASSERT_TRUE(Point2f::Zero.y == 0);
}
END_TEST

BEGIN_TEST(Point2f006)
{
	WIN_TRACE("Pointi2i006");
	WIN_ASSERT_TRUE(Point2f::Unit.x == 1);
	WIN_ASSERT_TRUE(Point2f::Unit.y == 1);
}
END_TEST

BEGIN_TEST(Point2f007)
{
	Point2f _p1(10, 20);
	Point2f _p2(2, 3);

	Point2f p = _p1 + _p2;

	WIN_TRACE("Point2f007");
	WIN_ASSERT_TRUE(p.x == (_p1.x + _p2.x));
	WIN_ASSERT_TRUE(p.y == (_p1.y + _p2.y));
}
END_TEST

BEGIN_TEST(Point2f008)
{
	Point2f _p1(10, 20);
	Point2f _p2(2, 3);

	Point2f p = _p1 - _p2; 
	
	WIN_TRACE("Point2f008");
	WIN_ASSERT_TRUE(p.x == (_p1.x - _p2.x));
	WIN_ASSERT_TRUE(p.y == (_p1.y - _p2.y));
}
END_TEST

BEGIN_TEST(Point2f009)
{
	const float value = 2;
	Point2f _p1(10, 20);

	Point2f p = _p1 * value; 
	WIN_TRACE("Point2f009");
	WIN_ASSERT_TRUE(p.x == (_p1.x * value));
	WIN_ASSERT_TRUE(p.y == (_p1.y * value));
}
END_TEST

BEGIN_TEST(Point2f010)
{
	const float value = 2;
	Point2f _p1(10, 20);

	Point2f p = _p1 / value; 
	WIN_TRACE("Point2f010");
	WIN_ASSERT_TRUE(p.x == (_p1.x / value));
	WIN_ASSERT_TRUE(p.y == (_p1.y / value));
}
END_TEST


BEGIN_TEST(Point2f011)
{
	const float x = 10, y = 20;
	Point2f _p1(3, 4);
	Point2f p(x, y);

	p += _p1;
	
	WIN_TRACE("Point2f011");
	WIN_ASSERT_TRUE(p.x == (x + _p1.x));
	WIN_ASSERT_TRUE(p.y == (y + _p1.y));
}
END_TEST

BEGIN_TEST(Point2f012)
{
	const float x=10, y=20;
	Point2f _p1(3, 4);
	Point2f p(x, y);

	p -= _p1; 
	
	WIN_TRACE("Point2f012");
	WIN_ASSERT_TRUE(p.x == (x - _p1.x));
	WIN_ASSERT_TRUE(p.y == (y - _p1.y));
}
END_TEST

BEGIN_TEST(Point2f013)
{
	const float x=10, y=20;
	const float value = 2;
	
	Point2f p(x, y);
	p *= value; 
	
	WIN_TRACE("Point2f012");
	WIN_ASSERT_TRUE(p.x == (x * value));
	WIN_ASSERT_TRUE(p.y == (y * value));
}
END_TEST

BEGIN_TEST(Point2f014)
{
	const float x=10, y=20;
	const float value = 2;
	
	Point2f p(x, y);
	p /= value; 
	
	WIN_TRACE("Point2f012");
	WIN_ASSERT_TRUE(p.x == (x / value));
	WIN_ASSERT_TRUE(p.y == (y / value));
}
END_TEST

#endif