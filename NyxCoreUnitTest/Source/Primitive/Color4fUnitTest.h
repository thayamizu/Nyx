#ifndef NYX_CORE_UNIT_TEST_COLOR4F_H_
#define NYX_CORE_UNIT_TEST_COLOR4F_H_

#include "PCH/PCH.h"
BEGIN_TEST(Color4f001)
{
	color4f c;

	WIN_TRACE("Color4f001");
	WIN_ASSERT_TRUE(c.r == 0.f);
	WIN_ASSERT_TRUE(c.g == 0.f);
	WIN_ASSERT_TRUE(c.b == 0.f);
	WIN_ASSERT_TRUE(c.a == 0.f);
}
END_TEST

BEGIN_TEST(Color4f002)
{
	

	color4f c(0.5f, 0.5f, 0.5f, 0.5);
	
	WIN_TRACE("Color4f002");
	WIN_ASSERT_TRUE(c.r == 0.5f);
	WIN_ASSERT_TRUE(c.g == 0.5f);
	WIN_ASSERT_TRUE(c.b == 0.5f);
	WIN_ASSERT_TRUE(c.a == 0.5f);
}
END_TEST

BEGIN_TEST(Color4f003)
{
	color4f _c(0.5f, 0.5f, 0.5f, 0.5);
	color4f c(_c);
	
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

	WIN_ASSERT_TRUE(color4f::WHITE.r == 1.f);
	WIN_ASSERT_TRUE(color4f::WHITE.g == 1.f);
	WIN_ASSERT_TRUE(color4f::WHITE.b == 1.f);
	WIN_ASSERT_TRUE(color4f::WHITE.a == 1.f);

	WIN_ASSERT_TRUE(color4f::GRAY.r == 0.5f);
	WIN_ASSERT_TRUE(color4f::GRAY.g == 0.5f);
	WIN_ASSERT_TRUE(color4f::GRAY.b == 0.5f);
	WIN_ASSERT_TRUE(color4f::GRAY.a == 1.f);

	WIN_ASSERT_TRUE(color4f::BLACK.r == 0.f);
	WIN_ASSERT_TRUE(color4f::BLACK.g == 0.f);
	WIN_ASSERT_TRUE(color4f::BLACK.b == 0.f);
	WIN_ASSERT_TRUE(color4f::BLACK.a == 1.f);

	WIN_ASSERT_TRUE(color4f::RED.r == 1.f);
	WIN_ASSERT_TRUE(color4f::RED.g == 0.f);
	WIN_ASSERT_TRUE(color4f::RED.b == 0.f);
	WIN_ASSERT_TRUE(color4f::RED.a == 1.f);


	WIN_ASSERT_TRUE(color4f::GREEN.r == 0.f);
	WIN_ASSERT_TRUE(color4f::GREEN.g == 1.f);
	WIN_ASSERT_TRUE(color4f::GREEN.b == 0.f);
	WIN_ASSERT_TRUE(color4f::GREEN.a == 1.f);

	WIN_ASSERT_TRUE(color4f::BLUE.r == 0.f);
	WIN_ASSERT_TRUE(color4f::BLUE.g == 0.f);
	WIN_ASSERT_TRUE(color4f::BLUE.b == 1.f);
	WIN_ASSERT_TRUE(color4f::BLUE.a == 1.f);


	WIN_ASSERT_TRUE(color4f::CYAN.r == 0.f);
	WIN_ASSERT_TRUE(color4f::CYAN.g == 1.f);
	WIN_ASSERT_TRUE(color4f::CYAN.b == 1.f);
	WIN_ASSERT_TRUE(color4f::CYAN.a == 1.f);

	WIN_ASSERT_TRUE(color4f::MAGENTA.r == 1.f);
	WIN_ASSERT_TRUE(color4f::MAGENTA.g == 0.f);
	WIN_ASSERT_TRUE(color4f::MAGENTA.b == 1.f);
	WIN_ASSERT_TRUE(color4f::MAGENTA.a == 1.f);

	WIN_ASSERT_TRUE(color4f::YELLOW.r == 1.f);
	WIN_ASSERT_TRUE(color4f::YELLOW.g == 1.f);
	WIN_ASSERT_TRUE(color4f::YELLOW.b == 0.f);
	WIN_ASSERT_TRUE(color4f::YELLOW.a == 1.f);
}
END_TEST

BEGIN_TEST(Color4f005)
{
	
	WIN_TRACE("Color4f005");

	color4f _c(0.5f, 0.5f, 0.5f, 0.5);
	color4f c;

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
	color4f _c(0.5f, 0.5f, 0.5f, 0.5);
	color4f c(r, g, b, a);
	
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
	color4f c(r, g, b, a);
	
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
	color4f c(r, g, b, a);
	
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

	color4f _c(0.5f, 0.5f, 0.5f, 0.5);
	color4f c;

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

	color4f _c(0.5f, 0.5f, 0.5f, 0.5);
	color4f c;

	c -= _c;
	WIN_ASSERT_TRUE(c.r == 0.f);
	WIN_ASSERT_TRUE(c.g == 0.f);
	WIN_ASSERT_TRUE(c.b == 0.f);
	WIN_ASSERT_TRUE(c.a == 0.f);
}
END_TEST

BEGIN_TEST(Color4f011)
{
	const float r=0.2f, g=0.3f, b=0.4f, a=0.5f; 
	const float value = 2;
	color4f c(r, g, b, a);
	
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
	color4f c(r, g, b, a);
	
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
	color4f c1(0.2f, 0.2f, 0.2f, 0.2f);
	color4f c2(0.2f, 0.2f, 0.2f, 0.2f);

	WIN_TRACE("Color4f013");
	WIN_ASSERT_TRUE(c1 == c2);
}
END_TEST

BEGIN_TEST(Color4f014)
{
	color4f c1(0.2f, 0.2f, 0.2f, 0.2f);
	color4f c2(0.1f, 0.2f, 0.2f, 0.2f);

	WIN_TRACE("Color4f014");
	WIN_ASSERT_TRUE(c1 != c2);
}
END_TEST
#endif