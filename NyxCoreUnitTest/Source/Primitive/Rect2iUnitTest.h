#pragma once
#include "PCH/PCH.h"

using namespace Nyx;

//-----------------------------------------------------------------------------
BEGIN_TEST(RECT_001)
{
	WIN_TRACE("Rect<int>::ctor");
	Rect2i r;
	WIN_ASSERT_TRUE(r.x == 0);
	WIN_ASSERT_TRUE(r.y == 0);
	WIN_ASSERT_TRUE(r.width == 0);
	WIN_ASSERT_TRUE(r.height == 0);
}
END_TEST

//-----------------------------------------------------------------------------
BEGIN_TEST(RECT_002)
{
		WIN_TRACE("Rect<int>::ctor");
	Rect2i r(1,2,3,4);
	WIN_ASSERT_TRUE(r.x == 1);
	WIN_ASSERT_TRUE(r.y == 2);
	WIN_ASSERT_TRUE(r.width == 3);
	WIN_ASSERT_TRUE(r.height == 4);
}
END_TEST


	//-----------------------------------------------------------------------------
	BEGIN_TEST(RECT_003)
{
	WIN_TRACE("Rect<int>::ctor");
	Rect2i r1(1,2,3,4);
	Rect2i r(r1);
	WIN_ASSERT_TRUE(r.x == 1);
	WIN_ASSERT_TRUE(r.y == 2);
	WIN_ASSERT_TRUE(r.width == 3);
	WIN_ASSERT_TRUE(r.height == 4);
}
END_TEST


	//-----------------------------------------------------------------------------
	BEGIN_TEST(RECT_004)
{
	WIN_TRACE("Rect<int>::set");
	Rect2i r;
	r.Set(1,2,3,4);
	WIN_ASSERT_TRUE(r.x == 1);
	WIN_ASSERT_TRUE(r.y == 2);
	WIN_ASSERT_TRUE(r.width == 3);
	WIN_ASSERT_TRUE(r.height == 4);
}
END_TEST


	//-----------------------------------------------------------------------------
	BEGIN_TEST(RECT_005)
{

	Rect2i r(0 ,0, 100, 50);
	Point2i p1(0,0);
	Point2i p2(10, 20);
	Point2i p3(110, 20);
	Point2i p4(50, 100);
	WIN_ASSERT_TRUE(r.Contain(p1));
	WIN_ASSERT_TRUE(r.Contain(p2));
	WIN_ASSERT_FALSE(r.Contain(p3));
	WIN_ASSERT_FALSE(r.Contain(p4));

}
END_TEST

	//-----------------------------------------------------------------------------
	BEGIN_TEST(RECT_006)
{
	Rect2i r1(0 ,0, 100, 50);
	Rect2i r2(0 ,0, 100, 50);
	WIN_ASSERT_TRUE(r1 == r2);
	WIN_ASSERT_FALSE(r1 == Rect2i::Zero);


}
END_TEST

		//-----------------------------------------------------------------------------
	BEGIN_TEST(RECT_007)

{
	Rect2i r1(0 ,0, 0, 0);
	Rect2i r2(0 ,0, 100, 50);

	WIN_ASSERT_TRUE(r1  != r2);
	WIN_ASSERT_FALSE(r1 != Rect2i::Zero);
}
END_TEST
