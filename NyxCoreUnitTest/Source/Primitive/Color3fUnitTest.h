#ifndef NYX_CORE_UNIT_TEST_COLOR3F_H_
#define NYX_CORE_UNIT_TEST_COLOR3F_H_

#include "PCH/PCH.h"

using namespace Nyx;

BEGIN_TEST(Color3f001)
{
	Color3f c=Color3f();

	WIN_TRACE(_T("Color3f::Color3f"));
	WIN_ASSERT_TRUE(c.r == 0);
	WIN_ASSERT_TRUE(c.g == 0);
	WIN_ASSERT_TRUE(c.b == 0);
}
END_TEST

	
BEGIN_TEST(Color3f002)
{
	WIN_TRACE(_T("Color3f::Color3f(uchar, uchar, uchar)"));
	Color3f c=Color3f(0.5f, 0.5f, 0.5f);
	

	WIN_ASSERT_TRUE(c.r == 0.5);
	WIN_ASSERT_TRUE(c.g == 0.5);
	WIN_ASSERT_TRUE(c.b == 0.5);
}
END_TEST

BEGIN_TEST(Color3f003)
{
	WIN_TRACE(_T("Color3f::Color3f(const Color3f&)"));
	Color3f _c = Color3f(125, 125, 125);
	Color3f c(_c);
	WIN_ASSERT_TRUE(c.r == _c.r);
	WIN_ASSERT_TRUE(c.g == _c.g);
	WIN_ASSERT_TRUE(c.b == _c.b);
}
END_TEST

	
BEGIN_TEST(Color3f004)
{
	WIN_TRACE(_T("Color3f::White"));

	Color3f c = Color3f();
	WIN_ASSERT_TRUE(c.White.r == 1.f);
	WIN_ASSERT_TRUE(c.White.g == 1.f);
	WIN_ASSERT_TRUE(c.White.b == 1.f);
}
END_TEST

BEGIN_TEST(Color3f005)
{
	WIN_TRACE(_T("Color3f::Black"));
	Color3f c = Color3f();
	WIN_ASSERT_TRUE(c.Black.r == 0.f);
	WIN_ASSERT_TRUE(c.Black.g == 0.f);
	WIN_ASSERT_TRUE(c.Black.b == 0.f);
}
END_TEST

BEGIN_TEST(Color3f006)
{
	WIN_TRACE(_T("Color3f::Red"));
	Color3f c = Color3f();
	WIN_ASSERT_TRUE(c.Red.r == 1.f);
	WIN_ASSERT_TRUE(c.Red.g == 0.f);
	WIN_ASSERT_TRUE(c.Red.b == 0.f);
}
END_TEST

BEGIN_TEST(Color3f007)
{
	WIN_TRACE(_T("Color3f::Blue"));

	Color3f c = Color3f();
	WIN_ASSERT_TRUE(c.Blue.r == 0.f);
	WIN_ASSERT_TRUE(c.Blue.g == 0.f);
	WIN_ASSERT_TRUE(c.Blue.b == 1.f);
}
END_TEST

BEGIN_TEST(Color3f008)
{
	WIN_TRACE(_T("Color3f::Green"));

	Color3f c = Color3f();
	WIN_ASSERT_TRUE(c.Green.r == 0.f);
	WIN_ASSERT_TRUE(c.Green.g == 1.f);
	WIN_ASSERT_TRUE(c.Green.b == 0.f);
}
END_TEST

BEGIN_TEST(Color3f009)
{
	WIN_TRACE(_T("Color3f::Gray"));

	Color3f c = Color3f();
	WIN_ASSERT_TRUE(c.Gray.r == 0.5f);
	WIN_ASSERT_TRUE(c.Gray.g == 0.5f);
	WIN_ASSERT_TRUE(c.Gray.b == 0.5f);
}
END_TEST

BEGIN_TEST(Color3f010)
{
	WIN_TRACE(_T("Color3f::Cyan"));
	Color3f c = Color3f();
	WIN_ASSERT_TRUE(c.Cyan.r == 0.f);
	WIN_ASSERT_TRUE(c.Cyan.g == 1.f);
	WIN_ASSERT_TRUE(c.Cyan.b == 1.f);
}
END_TEST

BEGIN_TEST(Color3f011)
{
	WIN_TRACE(_T("Color3f::Magenta"));

	Color3f c = Color3f();
	WIN_ASSERT_TRUE(c.Magenta.r == 1.f);
	WIN_ASSERT_TRUE(c.Magenta.g == 0.f);
	WIN_ASSERT_TRUE(c.Magenta.b == 1.f);
}
END_TEST

BEGIN_TEST(Color3f012)
{
	WIN_TRACE(_T("Color3f::Yellow"));

	Color3f c = Color3f();
	WIN_ASSERT_TRUE(c.Yellow.r == 1.f);
	WIN_ASSERT_TRUE(c.Yellow.g == 1.f);
	WIN_ASSERT_TRUE(c.Yellow.b == 0);
}
END_TEST

BEGIN_TEST(Color3f013) 
{
	WIN_TRACE(_T("Color3f::operator +()"));

	Color3f c1(0.5f, 0.5f,0.5f);
	Color3f c2(0.1f, 0.1f, 0.1f);
	Color3f c = c1 + c2;

	WIN_ASSERT_TRUE(c.r == 0.6f);
	WIN_ASSERT_TRUE(c.g == 0.6f);
	WIN_ASSERT_TRUE(c.b == 0.6f);

}
END_TEST


BEGIN_TEST(Color3f014)
{
	WIN_TRACE(_T("Color3f::operator -()"));
	Color3f c1(0.5f, 0.5f,0.5f);
	Color3f c2(0.1f, 0.1f, 0.1f);
	Color3f c = c1 - c2;

	WIN_ASSERT_TRUE(c.r == 0.4f);
	WIN_ASSERT_TRUE(c.g == 0.4f);
	WIN_ASSERT_TRUE(c.b == 0.4f);
}
END_TEST

BEGIN_TEST(Color3f015)
{
	WIN_TRACE(_T("Color3f::operator *()"));
	Color3f _c(0.5f, 0.5f, 0.5f);
	float value = 2;
	Color3f c = _c * value;
	WIN_ASSERT_TRUE(c.r == 1.0);
	WIN_ASSERT_TRUE(c.g == 1.0);
	WIN_ASSERT_TRUE(c.b == 1.0);
}
END_TEST
BEGIN_TEST(Color3f016)
{
	WIN_TRACE(_T("Color3f::operator /()"));
	Color3f _c(0.5f, 0.5f, 0.5f);
	float value = 2;
	Color3f c = _c / value;
	WIN_ASSERT_TRUE(c.r == 0.25f);
	WIN_ASSERT_TRUE(c.g == 0.25f);
	WIN_ASSERT_TRUE(c.b == 0.25f);


}
END_TEST

BEGIN_TEST(Color3f017)
{
	WIN_TRACE(_T("Color3f::operator +=()"));
	
	Color3f  c(0.5f, 0.5f, 0.5f);
	Color3f _c(0.1f, 0.1f, 0.1f);
	c += _c;
	

	WIN_ASSERT_TRUE(c.r == 0.6f);
	WIN_ASSERT_TRUE(c.g == 0.6f);
	WIN_ASSERT_TRUE(c.b == 0.6f);
}
END_TEST

BEGIN_TEST(Color3f018)
{
	WIN_TRACE(_T("Color3f::operator -=()"));

	Color3f c(0.5f, 0.5f, 0.5f);
	Color3f _c(0.1f, 0.1f, 0.1f);
	c -= _c;

	WIN_ASSERT_TRUE(c.r == 0.4f);
	WIN_ASSERT_TRUE(c.g == 0.4f);
	WIN_ASSERT_TRUE(c.b == 0.4f);
}
END_TEST

BEGIN_TEST(Color3f019)
{
	WIN_TRACE(_T("Color3f::operator *=()"));
	Color3f c(0.5f, 0.5f, 0.5f);
	float value = 2;
	c *= value;
	WIN_ASSERT_TRUE(c.r == 1.0);
	WIN_ASSERT_TRUE(c.g == 1.0);
	WIN_ASSERT_TRUE(c.b == 1.0);
}
END_TEST

BEGIN_TEST(Color3f020)
{
	WIN_TRACE(_T("Color3f::operator /=()"));
	Color3f c(0.5f, 0.5f, 0.5f);
	float value = 2;
	c /=  value;
	WIN_ASSERT_TRUE(c.r == 0.25f);
	WIN_ASSERT_TRUE(c.g == 0.25f);
	WIN_ASSERT_TRUE(c.b == 0.25f);
}
END_TEST

BEGIN_TEST(Color3f021)
{
	WIN_TRACE(_T("Color3f::operator ==()"));
	Color3f c(0.5f, 0.5f, 0.5f);
	Color3f c1(0.5f, 0.5f, 0.5f);
	Color3f c2(0, 0, 0);

	WIN_ASSERT_TRUE(c == c1);
	WIN_ASSERT_FALSE(c == c2);
}
END_TEST

BEGIN_TEST(Color3f022)
{
WIN_TRACE(_T("Color3f::operator !=()"));
	Color3f c(0.5f, 0.5f, 0.5f);
	Color3f c1(0.5f, 0.5f, 0.5f);
	Color3f c2(0, 0, 0);

	WIN_ASSERT_FALSE(c != c1);
	WIN_ASSERT_TRUE(c  != c2);
}
END_TEST
#endif