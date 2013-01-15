#ifndef NYX_CORE_UNIT_TEST_COLOR4C_H_
#define NYX_CORE_UNIT_TEST_COLOR4C_H_

#include "PCH/PCH.h"
using  Nyx::Color4c;
BEGIN_TEST(Color4c001)
{
	Color4c c;

	WIN_TRACE("Color4c001");
	WIN_ASSERT_TRUE(c.r == 0);
	WIN_ASSERT_TRUE(c.g == 0);
	WIN_ASSERT_TRUE(c.b == 0);
	WIN_ASSERT_TRUE(c.a == 0);
}
END_TEST

BEGIN_TEST(Color4c002)
{
	

	Color4c c(128, 128, 128, 128);
	
	WIN_TRACE("Color4c002");
	WIN_ASSERT_TRUE(c.r == 128);
	WIN_ASSERT_TRUE(c.g == 128);
	WIN_ASSERT_TRUE(c.b == 128);
	WIN_ASSERT_TRUE(c.a == 128);
}
END_TEST

BEGIN_TEST(Color4c003)
{
	Color4c _c(128, 128, 128, 128);
	Color4c c(_c);
	
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

	WIN_ASSERT_TRUE(Color4c::White.r == 255);
	WIN_ASSERT_TRUE(Color4c::White.g == 255);
	WIN_ASSERT_TRUE(Color4c::White.b == 255);
	WIN_ASSERT_TRUE(Color4c::White.a == 255);

	WIN_ASSERT_TRUE(Color4c::Gray.r == 128);
	WIN_ASSERT_TRUE(Color4c::Gray.g == 128);
	WIN_ASSERT_TRUE(Color4c::Gray.b == 128);
	WIN_ASSERT_TRUE(Color4c::Gray.a == 255);

	WIN_ASSERT_TRUE(Color4c::Black.r == 0);
	WIN_ASSERT_TRUE(Color4c::Black.g == 0);
	WIN_ASSERT_TRUE(Color4c::Black.b == 0);
	WIN_ASSERT_TRUE(Color4c::Black.a == 255);

	WIN_ASSERT_TRUE(Color4c::Red.r == 255);
	WIN_ASSERT_TRUE(Color4c::Red.g == 0);
	WIN_ASSERT_TRUE(Color4c::Red.b == 0);
	WIN_ASSERT_TRUE(Color4c::Red.a == 255);


	WIN_ASSERT_TRUE(Color4c::Green.r == 0);
	WIN_ASSERT_TRUE(Color4c::Green.g == 255);
	WIN_ASSERT_TRUE(Color4c::Green.b == 0);
	WIN_ASSERT_TRUE(Color4c::Green.a == 255);

	WIN_ASSERT_TRUE(Color4c::Blue.r == 0);
	WIN_ASSERT_TRUE(Color4c::Blue.g == 0);
	WIN_ASSERT_TRUE(Color4c::Blue.b == 255);
	WIN_ASSERT_TRUE(Color4c::Blue.a == 255);


	WIN_ASSERT_TRUE(Color4c::Cyan.r == 0);
	WIN_ASSERT_TRUE(Color4c::Cyan.g == 255);
	WIN_ASSERT_TRUE(Color4c::Cyan.b == 255);
	WIN_ASSERT_TRUE(Color4c::Cyan.a == 255);

	WIN_ASSERT_TRUE(Color4c::Magenta.r == 255);
	WIN_ASSERT_TRUE(Color4c::Magenta.g == 0);
	WIN_ASSERT_TRUE(Color4c::Magenta.b == 255);
	WIN_ASSERT_TRUE(Color4c::Magenta.a == 255);

	WIN_ASSERT_TRUE(Color4c::Yellow.r == 255);
	WIN_ASSERT_TRUE(Color4c::Yellow.g == 255);
	WIN_ASSERT_TRUE(Color4c::Yellow.b == 0);
	WIN_ASSERT_TRUE(Color4c::Yellow.a == 255);
}
END_TEST

BEGIN_TEST(Color4c005)
{
	
	WIN_TRACE("Color4c005");

	Color4c _c(128, 128, 128, 128);
	Color4c c;

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
	Color4c _c(128, 128, 128, 128);
	Color4c c(r, g, b, a);
	
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
	Color4c c(r, g, b, a);
	
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
	Color4c c(r, g, b, a);
	
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

	Color4c _c(128, 128, 128, 128);
	Color4c c;

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

	Color4c _c(64, 64, 64, 64);
	Color4c c(128, 128, 128, 128);

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
	Color4c c(r, g, b, a);
	
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
	Color4c c(r, g, b, a);
	
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
	Color4c c1(64, 64, 64, 64);
	Color4c c2(64, 64, 64, 64);

	WIN_TRACE("Color4c013");
	WIN_ASSERT_TRUE(c1 == c2);
}
END_TEST

BEGIN_TEST(Color4c014)
{
	Color4c c1(64, 64, 64, 64);
	Color4c c2(32, 64, 64, 64);

	WIN_TRACE("Color4c014");
	WIN_ASSERT_TRUE(c1 != c2);
}
END_TEST

#endif