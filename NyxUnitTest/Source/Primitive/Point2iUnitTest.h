#ifndef NYX_CORE_UNIT_TEST_POINT2I_H_
#define NYX_CORE_UNIT_TEST_POINT2I_H_

#include "PCH/PCH.h"
using namespace Nyx;

BEGIN_TEST(Point2i001)
{
	Point2i p;

	WIN_TRACE("Point2i001");
	WIN_ASSERT_TRUE(p.x == 0);
	WIN_ASSERT_TRUE(p.y == 0);
}
END_TEST

BEGIN_TEST(Point2i002)
{
	Point2i p(10, 20);

	WIN_TRACE("Point2i002");
	WIN_ASSERT_TRUE(p.x == 10);
	WIN_ASSERT_TRUE(p.y == 20);
}
END_TEST

BEGIN_TEST(Point2i003)
{
	int a[2] ={10, 20};
	Point2i p(a);
	WIN_TRACE("Point2i003");
	WIN_ASSERT_TRUE(p.x == a[0]);
	WIN_ASSERT_TRUE(p.y == a[1]);
}
END_TEST

BEGIN_TEST(Point2i004)
{
	Point2i _p(10, 20);
	Point2i p(_p);
	WIN_TRACE("Point2i004");
	WIN_ASSERT_TRUE(p.x == _p.x);
	WIN_ASSERT_TRUE(p.y == _p.y);
}
END_TEST

BEGIN_TEST(Point2i005)
{
	WIN_TRACE("Pointi2i005");
	WIN_ASSERT_TRUE(Point2i::Zero.x == 0);
	WIN_ASSERT_TRUE(Point2i::Zero.y == 0);
}
END_TEST

BEGIN_TEST(Point2i006)
{
	WIN_TRACE("Pointi2i006");
	WIN_ASSERT_TRUE(Point2i::Unit.x == 1);
	WIN_ASSERT_TRUE(Point2i::Unit.y == 1);
}
END_TEST

BEGIN_TEST(Point2i007)
{
	Point2i _p1(10, 20);
	Point2i _p2(2, 3);

	Point2i p = _p1 + _p2;

	WIN_TRACE("Point2i007");
	WIN_ASSERT_TRUE(p.x == (_p1.x + _p2.x));
	WIN_ASSERT_TRUE(p.y == (_p1.y + _p2.y));
}
END_TEST

BEGIN_TEST(Point2i008)
{
	Point2i _p1(10, 20);
	Point2i _p2(2, 3);

	Point2i p = _p1 - _p2; 
	
	WIN_TRACE("Point2i008");
	WIN_ASSERT_TRUE(p.x == (_p1.x - _p2.x));
	WIN_ASSERT_TRUE(p.y == (_p1.y - _p2.y));
}
END_TEST

BEGIN_TEST(Point2i009)
{
	const int value = 2;
	Point2i _p1(10, 20);

	Point2i p = _p1 * value; 
	WIN_TRACE("Point2i009");
	WIN_ASSERT_TRUE(p.x == (_p1.x * value));
	WIN_ASSERT_TRUE(p.y == (_p1.y * value));
}
END_TEST

BEGIN_TEST(Point2i010)
{
	const int value = 2;
	Point2i _p1(10, 20);

	Point2i p = _p1 / value; 
	WIN_TRACE("Point2i010");
	WIN_ASSERT_TRUE(p.x == (_p1.x / value));
	WIN_ASSERT_TRUE(p.y == (_p1.y / value));
}
END_TEST


BEGIN_TEST(Point2i011)
{
	const int x = 10, y = 20;
	Point2i _p1(3, 4);
	Point2i p(x, y);

	p += _p1;
	
	WIN_TRACE("Point2i011");
	WIN_ASSERT_TRUE(p.x == (x + _p1.x));
	WIN_ASSERT_TRUE(p.y == (y + _p1.y));
}
END_TEST

BEGIN_TEST(Point2i012)
{
	const int x=10, y=20;
	Point2i _p1(3, 4);
	Point2i p(x, y);

	p -= _p1; 
	
	WIN_TRACE("Point2i012");
	WIN_ASSERT_TRUE(p.x == (x - _p1.x));
	WIN_ASSERT_TRUE(p.y == (y - _p1.y));
}
END_TEST

BEGIN_TEST(Point2i013)
{
	const int x=10, y=20;
	const float value = 2;
	
	Point2i p(x, y);
	p *= value; 
	
	WIN_TRACE("Point2i012");
	WIN_ASSERT_TRUE(p.x == (x * value));
	WIN_ASSERT_TRUE(p.y == (y * value));
}
END_TEST

BEGIN_TEST(Point2i014)
{
	const int x=10, y=20;
	const float value = 2;
	
	Point2i p(x, y);
	p /= value; 
	
	WIN_TRACE("Point2i012");
	WIN_ASSERT_TRUE(p.x == (x / value));
	WIN_ASSERT_TRUE(p.y == (y / value));
}
END_TEST

#endif