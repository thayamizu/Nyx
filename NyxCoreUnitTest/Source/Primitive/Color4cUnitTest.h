#ifndef NYX_CORE_UNIT_TEST_COLOR4C_H_
#define NYX_CORE_UNIT_TEST_COLOR4C_H_

#include "PCH/PCH.h"
using  nyx::color4c;
BEGIN_TEST(Color4c001)
{
	color4c c;

	WIN_TRACE("Color4c001");
	WIN_ASSERT_TRUE(c.r == 0);
	WIN_ASSERT_TRUE(c.g == 0);
	WIN_ASSERT_TRUE(c.b == 0);
	WIN_ASSERT_TRUE(c.a == 0);
}
END_TEST

BEGIN_TEST(Color4c002)
{
	

	color4c c(128, 128, 128, 128);
	
	WIN_TRACE("Color4c002");
	WIN_ASSERT_TRUE(c.r == 128);
	WIN_ASSERT_TRUE(c.g == 128);
	WIN_ASSERT_TRUE(c.b == 128);
	WIN_ASSERT_TRUE(c.a == 128);
}
END_TEST

BEGIN_TEST(Color4c003)
{
	color4c _c(128, 128, 128, 128);
	color4c c(_c);
	
	WIN_TRACE("Color4c003");
	WIN_ASSERT_TRUE(c.r == 128);
	WIN_ASSERT_TRUE(c.g == 128);
	WIN_ASSERT_TRUE(c.b == 128);
	WIN_ASSERT_TRUE(c.a == 128);
}
END_TEST

BEGIN_TEST(Color4c004)
{
	WIN_TRACE("Color4c004");

	WIN_ASSERT_TRUE(color4c::WHITE.r == 255);
	WIN_ASSERT_TRUE(color4c::WHITE.g == 255);
	WIN_ASSERT_TRUE(color4c::WHITE.b == 255);
	WIN_ASSERT_TRUE(color4c::WHITE.a == 255);

	WIN_ASSERT_TRUE(color4c::GRAY.r == 128);
	WIN_ASSERT_TRUE(color4c::GRAY.g == 128);
	WIN_ASSERT_TRUE(color4c::GRAY.b == 128);
	WIN_ASSERT_TRUE(color4c::GRAY.a == 255);

	WIN_ASSERT_TRUE(color4c::BLACK.r == 0);
	WIN_ASSERT_TRUE(color4c::BLACK.g == 0);
	WIN_ASSERT_TRUE(color4c::BLACK.b == 0);
	WIN_ASSERT_TRUE(color4c::BLACK.a == 255);

	WIN_ASSERT_TRUE(color4c::RED.r == 255);
	WIN_ASSERT_TRUE(color4c::RED.g == 0);
	WIN_ASSERT_TRUE(color4c::RED.b == 0);
	WIN_ASSERT_TRUE(color4c::RED.a == 255);


	WIN_ASSERT_TRUE(color4c::GREEN.r == 0);
	WIN_ASSERT_TRUE(color4c::GREEN.g == 255);
	WIN_ASSERT_TRUE(color4c::GREEN.b == 0);
	WIN_ASSERT_TRUE(color4c::GREEN.a == 255);

	WIN_ASSERT_TRUE(color4c::BLUE.r == 0);
	WIN_ASSERT_TRUE(color4c::BLUE.g == 0);
	WIN_ASSERT_TRUE(color4c::BLUE.b == 255);
	WIN_ASSERT_TRUE(color4c::BLUE.a == 255);


	WIN_ASSERT_TRUE(color4c::CYAN.r == 0);
	WIN_ASSERT_TRUE(color4c::CYAN.g == 255);
	WIN_ASSERT_TRUE(color4c::CYAN.b == 255);
	WIN_ASSERT_TRUE(color4c::CYAN.a == 255);

	WIN_ASSERT_TRUE(color4c::MAGENTA.r == 255);
	WIN_ASSERT_TRUE(color4c::MAGENTA.g == 0);
	WIN_ASSERT_TRUE(color4c::MAGENTA.b == 255);
	WIN_ASSERT_TRUE(color4c::MAGENTA.a == 255);

	WIN_ASSERT_TRUE(color4c::YELLOW.r == 255);
	WIN_ASSERT_TRUE(color4c::YELLOW.g == 255);
	WIN_ASSERT_TRUE(color4c::YELLOW.b == 0);
	WIN_ASSERT_TRUE(color4c::YELLOW.a == 255);
}
END_TEST

BEGIN_TEST(Color4c005)
{
	
	WIN_TRACE("Color4c005");

	color4c _c(128, 128, 128, 128);
	color4c c;

	c = c + _c;
	WIN_ASSERT_TRUE(c.r == 128);
	WIN_ASSERT_TRUE(c.g == 128);
	WIN_ASSERT_TRUE(c.b == 128);
	WIN_ASSERT_TRUE(c.a == 128);
}
END_TEST

BEGIN_TEST(Color4c006)
{
	const int r=128, g=128, b=128, a=128; 
	color4c _c(128, 128, 128, 128);
	color4c c(r, g, b, a);
	
	c = c - _c;

	WIN_TRACE("Color4c006");
	WIN_ASSERT_TRUE(c.r == (r - _c.r));
	WIN_ASSERT_TRUE(c.g == (g - _c.g));
	WIN_ASSERT_TRUE(c.b == (b - _c.b));
	WIN_ASSERT_TRUE(c.a == (a - _c.a));
}
END_TEST

BEGIN_TEST(Color4c007)
{
	const int r=64, g=64, b=64, a=64; 
	const float value = 2;
	color4c c(r, g, b, a);
	
	c = c * value;

	WIN_TRACE("Color4c007");
	WIN_ASSERT_TRUE(c.r == (r * value));
	WIN_ASSERT_TRUE(c.g == (g * value));
	WIN_ASSERT_TRUE(c.b == (b * value));
	WIN_ASSERT_TRUE(c.a == (a * value));
}
END_TEST

BEGIN_TEST(Color4c008)
{
	const int r=64, g=64, b=64, a=64; 
	const float value = 2;
	color4c c(r, g, b, a);
	
	c = c / value;

	WIN_TRACE("Color4c008");
	WIN_ASSERT_TRUE(c.r == (r / value));
	WIN_ASSERT_TRUE(c.g == (g / value));
	WIN_ASSERT_TRUE(c.b == (b / value));
	WIN_ASSERT_TRUE(c.a == (a / value));
}
END_TEST

BEGIN_TEST(Color4c009)
{
	WIN_TRACE("Color4c009");

	color4c _c(128, 128, 128, 128);
	color4c c;

	c += _c;
	WIN_ASSERT_TRUE(c.r == 128);
	WIN_ASSERT_TRUE(c.g == 128);
	WIN_ASSERT_TRUE(c.b == 128);
	WIN_ASSERT_TRUE(c.a == 128);
}
END_TEST

BEGIN_TEST(Color4c010)
{
	WIN_TRACE("Color4c010");

	color4c _c(64, 64, 64, 64);
	color4c c(128, 128, 128, 128);

	c -= _c;
	WIN_ASSERT_TRUE(c.r == 64);
	WIN_ASSERT_TRUE(c.g == 64);
	WIN_ASSERT_TRUE(c.b == 64);
	WIN_ASSERT_TRUE(c.a == 64);
}
END_TEST

BEGIN_TEST(Color4c011)
{
	const int r=64, g=64, b=64, a=64; 
	const float value = 2;
	color4c c(r, g, b, a);
	
	c *= value;

	WIN_TRACE("Color4c011");
	WIN_ASSERT_TRUE(c.r == (r * value));
	WIN_ASSERT_TRUE(c.g == (g * value));
	WIN_ASSERT_TRUE(c.b == (b * value));
	WIN_ASSERT_TRUE(c.a == (a * value));
}
END_TEST

BEGIN_TEST(Color4c012)
{
	const int r=64, g=64, b=64, a=64; 
	const float value = 2;
	color4c c(r, g, b, a);
	
	c /= value;

	WIN_TRACE("Color4c012");
	WIN_ASSERT_TRUE(c.r == (r / value));
	WIN_ASSERT_TRUE(c.g == (g / value));
	WIN_ASSERT_TRUE(c.b == (b / value));
	WIN_ASSERT_TRUE(c.a == (a / value));
}
END_TEST

BEGIN_TEST(Color4c013)
{
	color4c c1(64, 64, 64, 64);
	color4c c2(64, 64, 64, 64);

	WIN_TRACE("Color4c013");
	WIN_ASSERT_TRUE(c1 == c2);
}
END_TEST

BEGIN_TEST(Color4c014)
{
	color4c c1(64, 64, 64, 64);
	color4c c2(32, 64, 64, 64);

	WIN_TRACE("Color4c014");
	WIN_ASSERT_TRUE(c1 != c2);
}
END_TEST

#endif