#ifndef NYX_CORE_UNIT_TEST_COLOR4F_H_
#define NYX_CORE_UNIT_TEST_COLOR4F_H_

#include "PCH/PCH.h"
BEGIN_TEST(Color4f001)
{
	Color4f c;

	WIN_TRACE("Color4f001");
	WIN_ASSERT_TRUE(c.r == 0.f);
	WIN_ASSERT_TRUE(c.g == 0.f);
	WIN_ASSERT_TRUE(c.b == 0.f);
	WIN_ASSERT_TRUE(c.a == 0.f);
}
END_TEST

BEGIN_TEST(Color4f002)
{
	

	Color4f c(0.5f, 0.5f, 0.5f, 0.5);
	
	WIN_TRACE("Color4f002");
	WIN_ASSERT_TRUE(c.r == 0.5f);
	WIN_ASSERT_TRUE(c.g == 0.5f);
	WIN_ASSERT_TRUE(c.b == 0.5f);
	WIN_ASSERT_TRUE(c.a == 0.5f);
}
END_TEST

BEGIN_TEST(Color4f003)
{
	Color4f _c(0.5f, 0.5f, 0.5f, 0.5);
	Color4f c(_c);
	
	WIN_TRACE("Color4f003");
	WIN_ASSERT_TRUE(c.r == 0.5f);
	WIN_ASSERT_TRUE(c.g == 0.5f);
	WIN_ASSERT_TRUE(c.b == 0.5f);
	WIN_ASSERT_TRUE(c.a == 0.5f);
}
END_TEST

BEGIN_TEST(Color4f004)
{
	WIN_TRACE("Color4f004");

	WIN_ASSERT_TRUE(Color4f::White.r == 1.f);
	WIN_ASSERT_TRUE(Color4f::White.g == 1.f);
	WIN_ASSERT_TRUE(Color4f::White.b == 1.f);
	WIN_ASSERT_TRUE(Color4f::White.a == 1.f);

	WIN_ASSERT_TRUE(Color4f::Gray.r == 0.5f);
	WIN_ASSERT_TRUE(Color4f::Gray.g == 0.5f);
	WIN_ASSERT_TRUE(Color4f::Gray.b == 0.5f);
	WIN_ASSERT_TRUE(Color4f::Gray.a == 1.f);

	WIN_ASSERT_TRUE(Color4f::Black.r == 0.f);
	WIN_ASSERT_TRUE(Color4f::Black.g == 0.f);
	WIN_ASSERT_TRUE(Color4f::Black.b == 0.f);
	WIN_ASSERT_TRUE(Color4f::Black.a == 1.f);

	WIN_ASSERT_TRUE(Color4f::Red.r == 1.f);
	WIN_ASSERT_TRUE(Color4f::Red.g == 0.f);
	WIN_ASSERT_TRUE(Color4f::Red.b == 0.f);
	WIN_ASSERT_TRUE(Color4f::Red.a == 1.f);


	WIN_ASSERT_TRUE(Color4f::Green.r == 0.f);
	WIN_ASSERT_TRUE(Color4f::Green.g == 1.f);
	WIN_ASSERT_TRUE(Color4f::Green.b == 0.f);
	WIN_ASSERT_TRUE(Color4f::Green.a == 1.f);

	WIN_ASSERT_TRUE(Color4f::Blue.r == 0.f);
	WIN_ASSERT_TRUE(Color4f::Blue.g == 0.f);
	WIN_ASSERT_TRUE(Color4f::Blue.b == 1.f);
	WIN_ASSERT_TRUE(Color4f::Blue.a == 1.f);


	WIN_ASSERT_TRUE(Color4f::Cyan.r == 0.f);
	WIN_ASSERT_TRUE(Color4f::Cyan.g == 1.f);
	WIN_ASSERT_TRUE(Color4f::Cyan.b == 1.f);
	WIN_ASSERT_TRUE(Color4f::Cyan.a == 1.f);

	WIN_ASSERT_TRUE(Color4f::Magenta.r == 1.f);
	WIN_ASSERT_TRUE(Color4f::Magenta.g == 0.f);
	WIN_ASSERT_TRUE(Color4f::Magenta.b == 1.f);
	WIN_ASSERT_TRUE(Color4f::Magenta.a == 1.f);

	WIN_ASSERT_TRUE(Color4f::Yellow.r == 1.f);
	WIN_ASSERT_TRUE(Color4f::Yellow.g == 1.f);
	WIN_ASSERT_TRUE(Color4f::Yellow.b == 0.f);
	WIN_ASSERT_TRUE(Color4f::Yellow.a == 1.f);
}
END_TEST

BEGIN_TEST(Color4f005)
{
	
	WIN_TRACE("Color4f005");

	Color4f _c(0.5f, 0.5f, 0.5f, 0.5);
	Color4f c;

	c = c + _c;
	WIN_ASSERT_TRUE(c.r == 0.5f);
	WIN_ASSERT_TRUE(c.g == 0.5f);
	WIN_ASSERT_TRUE(c.b == 0.5f);
	WIN_ASSERT_TRUE(c.a == 0.5f);
}
END_TEST

BEGIN_TEST(Color4f006)
{

	const float r=0.7f, g=0.7f, b=0.7f, a=0.7f; 
	Color4f _c(0.5f, 0.5f, 0.5f, 0.5);
	Color4f c(r, g, b, a);
	
	c = c - _c;

	WIN_TRACE("Color4f006");
	WIN_ASSERT_TRUE(c.r == (r - _c.r));
	WIN_ASSERT_TRUE(c.g == (g - _c.g));
	WIN_ASSERT_TRUE(c.b == (b - _c.b));
	WIN_ASSERT_TRUE(c.a == (a - _c.a));
}
END_TEST

BEGIN_TEST(Color4f007)
{
	const float r=0.2f, g=0.3f, b=0.4f, a=0.5f; 
	const float value = 2;
	Color4f c(r, g, b, a);
	
	c = c * value;

	WIN_TRACE("Color4f007");
	WIN_ASSERT_TRUE(c.r == (r * value));
	WIN_ASSERT_TRUE(c.g == (g * value));
	WIN_ASSERT_TRUE(c.b == (b * value));
	WIN_ASSERT_TRUE(c.a == (a * value));
}
END_TEST

BEGIN_TEST(Color4f008)
{
	const float r=0.2f, g=0.3f, b=0.4f, a=0.5f; 
	const float value = 2;
	Color4f c(r, g, b, a);
	
	c = c / value;

	WIN_TRACE("Color4f008");
	WIN_ASSERT_TRUE(c.r == (r / value));
	WIN_ASSERT_TRUE(c.g == (g / value));
	WIN_ASSERT_TRUE(c.b == (b / value));
	WIN_ASSERT_TRUE(c.a == (a / value));
}
END_TEST

BEGIN_TEST(Color4f009)
{
		WIN_TRACE("Color4f009");

	Color4f _c(0.5f, 0.5f, 0.5f, 0.5);
	Color4f c;

	c += _c;
	WIN_ASSERT_TRUE(c.r == 0.5f);
	WIN_ASSERT_TRUE(c.g == 0.5f);
	WIN_ASSERT_TRUE(c.b == 0.5f);
	WIN_ASSERT_TRUE(c.a == 0.5f);
}
END_TEST

BEGIN_TEST(Color4f010)
{
		WIN_TRACE("Color4f010");

	Color4f _c(0.5f, 0.5f, 0.5f, 0.5);
	Color4f c;

	c -= _c;
	WIN_ASSERT_TRUE(c.r == -0.5f);
	WIN_ASSERT_TRUE(c.g == -0.5f);
	WIN_ASSERT_TRUE(c.b == -0.5f);
	WIN_ASSERT_TRUE(c.a == -0.5f);
}
END_TEST

BEGIN_TEST(Color4f011)
{
	const float r=0.2f, g=0.3f, b=0.4f, a=0.5f; 
	const float value = 2;
	Color4f c(r, g, b, a);
	
	c *= value;

	WIN_TRACE("Color4f011");
	WIN_ASSERT_TRUE(c.r == (r * value));
	WIN_ASSERT_TRUE(c.g == (g * value));
	WIN_ASSERT_TRUE(c.b == (b * value));
	WIN_ASSERT_TRUE(c.a == (a * value));
}
END_TEST

BEGIN_TEST(Color4f012)
{
	const float r=0.2f, g=0.3f, b=0.4f, a=0.5f; 
	const float value = 2;
	Color4f c(r, g, b, a);
	
	c /= value;

	WIN_TRACE("Color4f012");
	WIN_ASSERT_TRUE(c.r == (r / value));
	WIN_ASSERT_TRUE(c.g == (g / value));
	WIN_ASSERT_TRUE(c.b == (b / value));
	WIN_ASSERT_TRUE(c.a == (a / value));
}
END_TEST

BEGIN_TEST(Color4f013)
{
	Color4f c1(0.2f, 0.2f, 0.2f, 0.2f);
	Color4f c2(0.2f, 0.2f, 0.2f, 0.2f);

	WIN_TRACE("Color4f013");
	WIN_ASSERT_TRUE(c1 == c2);
}
END_TEST

BEGIN_TEST(Color4f014)
{
	Color4f c1(0.2f, 0.2f, 0.2f, 0.2f);
	Color4f c2(0.1f, 0.2f, 0.2f, 0.2f);

	WIN_TRACE("Color4f014");
	WIN_ASSERT_TRUE(c1 != c2);
}
END_TEST
#endif