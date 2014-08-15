#pragma once
#include "PCH/PCH.h"

using namespace nyx;

//-----------------------------------------------------------------------------
BEGIN_TEST(RECT_001)
{
	WIN_TRACE("Rect<int>::ctor");
	rect2i r;
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
		rect2i  r(1, 2, 3, 4);
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
	rect2i r1(1, 2, 3, 4);
	rect2i r(r1);
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
	rect2i r;
	r.set(1,2,3,4);
	WIN_ASSERT_TRUE(r.x == 1);
	WIN_ASSERT_TRUE(r.y == 2);
	WIN_ASSERT_TRUE(r.width == 3);
	WIN_ASSERT_TRUE(r.height == 4);
}
END_TEST


	//-----------------------------------------------------------------------------
	BEGIN_TEST(RECT_005)
{

		rect2i r(0, 0, 100, 50);
	point2i p1(0,0);
	point2i p2(10, 20);
	point2i p3(110, 20);
	point2i p4(50, 100);
	WIN_ASSERT_TRUE(r.contain(p1));
	WIN_ASSERT_TRUE(r.contain(p2));
	WIN_ASSERT_FALSE(r.contain(p3));
	WIN_ASSERT_FALSE(r.contain(p4));

}
END_TEST

	//-----------------------------------------------------------------------------
	BEGIN_TEST(RECT_006)
{
		rect2i r1(0, 0, 100, 50);
		rect2i r2(0, 0, 100, 50);
	WIN_ASSERT_TRUE(r1 == r2);
	WIN_ASSERT_FALSE(r1 == rect2i::ZERO);


}
END_TEST

		//-----------------------------------------------------------------------------
	BEGIN_TEST(RECT_007)

{
		rect2i r1(0, 0, 0, 0);
		rect2i r2(0, 0, 100, 50);

	WIN_ASSERT_TRUE(r1  != r2);
	WIN_ASSERT_FALSE(r1 != rect2i::ZERO);
}
END_TEST
