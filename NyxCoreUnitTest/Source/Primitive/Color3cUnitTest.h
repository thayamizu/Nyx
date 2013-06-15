#ifndef NYX_CORE_UNIT_TEST_COLOR3C_H_
#define NYX_CORE_UNIT_TEST_COLOR3C_H_

#include "PCH/PCH.h"

using namespace Nyx;

BEGIN_TEST(Color3c001)
{
	Color3c c=Color3c();

	WIN_TRACE(_T("Color3c::Color3c"));
	WIN_ASSERT_TRUE(c.r == 0);
	WIN_ASSERT_TRUE(c.g == 0);
	WIN_ASSERT_TRUE(c.b == 0);
}
END_TEST

	
BEGIN_TEST(Color3c002)
{
	WIN_TRACE(_T("Color3c::Color3c(uchar, uchar, uchar)"));
	Color3c c=Color3c(125, 125, 125);
	

	WIN_ASSERT_TRUE(c.r == 125);
	WIN_ASSERT_TRUE(c.g == 125);
	WIN_ASSERT_TRUE(c.b == 125);
}
END_TEST

BEGIN_TEST(Color3c003)
{
	WIN_TRACE(_T("Color3c::Color3c(const Color3c&)"));
	Color3c _c = Color3c(125, 125, 125);
	Color3c c(_c);
	WIN_ASSERT_TRUE(c.r == _c.r);
	WIN_ASSERT_TRUE(c.g == _c.g);
	WIN_ASSERT_TRUE(c.b == _c.b);
}
END_TEST

	
BEGIN_TEST(Color3c004)
{
	WIN_TRACE(_T("Color3c::White"));

	Color3c c = Color3c();
	WIN_ASSERT_TRUE(c.White.r == 255);
	WIN_ASSERT_TRUE(c.White.g == 255);
	WIN_ASSERT_TRUE(c.White.b == 255);
}
END_TEST

BEGIN_TEST(Color3c005)
{
	WIN_TRACE(_T("Color3c::Black"));
	Color3c c = Color3c();
	WIN_ASSERT_TRUE(c.Black.r == 0);
	WIN_ASSERT_TRUE(c.Black.g == 0);
	WIN_ASSERT_TRUE(c.Black.b == 0);
}
END_TEST

BEGIN_TEST(Color3c006)
{
	WIN_TRACE(_T("Color3c::Red"));
	Color3c c = Color3c();
	WIN_ASSERT_TRUE(c.Red.r == 255);
	WIN_ASSERT_TRUE(c.Red.g == 0);
	WIN_ASSERT_TRUE(c.Red.b == 0);
}
END_TEST

BEGIN_TEST(Color3c007)
{
	WIN_TRACE(_T("Color3c::Blue"));

	Color3c c = Color3c();
	WIN_ASSERT_TRUE(c.Blue.r == 0);
	WIN_ASSERT_TRUE(c.Blue.g == 0);
	WIN_ASSERT_TRUE(c.Blue.b == 255);
}
END_TEST

BEGIN_TEST(Color3c008)
{
	WIN_TRACE(_T("Color3c::Green"));

	Color3c c = Color3c();
	WIN_ASSERT_TRUE(c.Green.r == 0);
	WIN_ASSERT_TRUE(c.Green.g == 255);
	WIN_ASSERT_TRUE(c.Green.b == 0);
}
END_TEST

BEGIN_TEST(Color3c009)
{
	WIN_TRACE(_T("Color3c::Gray"));

	Color3c c = Color3c();
	WIN_ASSERT_TRUE(c.Gray.r == 128);
	WIN_ASSERT_TRUE(c.Gray.g == 128);
	WIN_ASSERT_TRUE(c.Gray.b == 128);
}
END_TEST

BEGIN_TEST(Color3c010)
{
	WIN_TRACE(_T("Color3c::Cyan"));
	Color3c c = Color3c();
	WIN_ASSERT_TRUE(c.Cyan.r == 0);
	WIN_ASSERT_TRUE(c.Cyan.g == 255);
	WIN_ASSERT_TRUE(c.Cyan.b == 255);
}
END_TEST

BEGIN_TEST(Color3c011)
{
	WIN_TRACE(_T("Color3c::Magenta"));

	Color3c c = Color3c();
	WIN_ASSERT_TRUE(c.Magenta.r == 255);
	WIN_ASSERT_TRUE(c.Magenta.g == 0);
	WIN_ASSERT_TRUE(c.Magenta.b == 255);
}
END_TEST

BEGIN_TEST(Color3c012)
{
	WIN_TRACE(_T("Color3c::Yellow"));

	Color3c c = Color3c();
	WIN_ASSERT_TRUE(c.Yellow.r == 255);
	WIN_ASSERT_TRUE(c.Yellow.g == 255);
	WIN_ASSERT_TRUE(c.Yellow.b == 0);
}
END_TEST

BEGIN_TEST(Color3c013) 
{
	WIN_TRACE(_T("Color3c::operator +()"));

	Color3c c1(125, 125,125);
	Color3c c2(11, 12, 13);
	Color3c c = c1 + c2;

	WIN_ASSERT_TRUE(c.r == 136);
	WIN_ASSERT_TRUE(c.g == 137);
	WIN_ASSERT_TRUE(c.b == 138);

}
END_TEST


BEGIN_TEST(Color3c014)
{
	WIN_TRACE(_T("Color3c::operator -()"));
	Color3c c1(125, 125,125);
	Color3c c2(11, 12, 13);
	Color3c c = c1 - c2;

	WIN_ASSERT_TRUE(c.r == 114);
	WIN_ASSERT_TRUE(c.g == 113);
	WIN_ASSERT_TRUE(c.b == 112);
}
END_TEST

BEGIN_TEST(Color015)
{
	WIN_TRACE(_T("Color3c::operator *()"));
	Color3c _c(128, 128, 128);
	float value = 2;
	Color3c c = _c * value;
	WIN_ASSERT_TRUE(c.r == 0);
	WIN_ASSERT_TRUE(c.g == 0);
	WIN_ASSERT_TRUE(c.b == 0);
}
END_TEST
BEGIN_TEST(Color016)
{
	WIN_TRACE(_T("Color3c::operator /()"));
	Color3c _c(128, 128, 128);
	float value = 2;
	Color3c c = _c / value;
	WIN_ASSERT_TRUE(c.r == 64);
	WIN_ASSERT_TRUE(c.g == 64);
	WIN_ASSERT_TRUE(c.b == 64);


}
END_TEST

BEGIN_TEST(Color3c017)
{
	WIN_TRACE(_T("Color3c::operator +=()"));
	Color3c c(128, 128, 128);
	Color3c _c(10, 10, 10);
	c += _c;
	WIN_ASSERT_TRUE(c.r == 138);
	WIN_ASSERT_TRUE(c.g == 138);
	WIN_ASSERT_TRUE(c.b == 138);
}
END_TEST

BEGIN_TEST(Color3c018)
{
	WIN_TRACE(_T("Color3c::operator -=()"));
Color3c c(128, 128, 128);
	Color3c _c(10, 10, 10);
	c -= _c;
	WIN_ASSERT_TRUE(c.r == 118);
	WIN_ASSERT_TRUE(c.g == 118);
	WIN_ASSERT_TRUE(c.b == 118);
}
END_TEST

BEGIN_TEST(Color3c019)
{
	WIN_TRACE(_T("Color3c::operator *=()"));
	Color3c c(128, 128, 128);
	float value = 2;
	c *= value;
	WIN_ASSERT_TRUE(c.r == 0);
	WIN_ASSERT_TRUE(c.g == 0);
	WIN_ASSERT_TRUE(c.b == 0);
}
END_TEST

BEGIN_TEST(Color3c020)
{
	WIN_TRACE(_T("Color3c::operator /=()"));
	Color3c c(128, 128, 128);
	float value = 2;
	c /=  value;
	WIN_ASSERT_TRUE(c.r == 64);
	WIN_ASSERT_TRUE(c.g == 64);
	WIN_ASSERT_TRUE(c.b == 64);
}
END_TEST

BEGIN_TEST(Color3c021)
{
	WIN_TRACE(_T("Color3c::operator ==()"));
	Color3c c(128, 128, 128);
	Color3c c1(128, 128, 128);
	Color3c c2(0, 0, 0);

	WIN_ASSERT_TRUE(c == c1);
	WIN_ASSERT_FALSE(c == c2);
}
END_TEST

BEGIN_TEST(Color3c022)
{
WIN_TRACE(_T("Color3c::operator !=()"));
	Color3c c(128, 128, 128);
	Color3c c1(128, 128, 128);
	Color3c c2(0, 0, 0);

	WIN_ASSERT_FALSE(c != c1);
	WIN_ASSERT_TRUE(c  != c2);
}
END_TEST
#endif