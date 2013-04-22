#pragma once
#include "PCH/PCH.h"
using namespace Nyx;

class DeleteTest
{
public:
	DeleteTest() {
		array = new int;
	}
	void Release() {
		SafeDelete(array);
	}

	int * array;
};
BEGIN_TEST(Common001)
{
	char * tmp = new char;
	SafeDelete(tmp);
	WIN_ASSERT_TRUE(tmp == NULL);
}
END_TEST

	BEGIN_TEST(Common002)
{
	char * tmp = new char[2];
	SafeDeleteArray(tmp);
	WIN_ASSERT_TRUE(tmp == NULL);
}
END_TEST

	BEGIN_TEST(Common003)
{
	DeleteTest *t = new DeleteTest();
	WIN_ASSERT_TRUE(t != NULL);
	WIN_ASSERT_TRUE(t->array != NULL);

	SafeRelease(t);
	WIN_ASSERT_TRUE(t == NULL);
}
END_TEST

	BEGIN_TEST(Common004)
{
	tstring str = ToString(1234);
	WIN_ASSERT_TRUE(str == TEXT("1234"));
}
END_TEST

	BEGIN_TEST(Common005)
{
	tstring str = ToString(1234.1f);
	WIN_ASSERT_TRUE(str == TEXT("1234.1"));
}
END_TEST

	BEGIN_TEST(Common006)
{
	char c = ToChar(0);
	WIN_TRACE("char=%d", c);
	WIN_ASSERT_TRUE(c == 0);
}
END_TEST

	BEGIN_TEST(Common007)
{
	char c = ToChar(-128);
	WIN_TRACE("char=%d", c);
	WIN_ASSERT_TRUE(c == -3);
}
END_TEST

	BEGIN_TEST(Common008)
{
	char c = ToChar(127);
	WIN_TRACE("char=%d", c);

	WIN_ASSERT_TRUE(c == 1);
}
END_TEST

	BEGIN_TEST(Common009)
{
	char c = ToChar("0");
	WIN_TRACE("char=%d", c);

	WIN_ASSERT_TRUE(c == 0);
}
END_TEST

	BEGIN_TEST(Common010)
{
	char c = ToChar("0");
	WIN_TRACE("char=%c", c);
	WIN_ASSERT_TRUE(c == 0);
}
END_TEST

	BEGIN_TEST(Common011)
{
	int i = ToInt("0");
	WIN_TRACE("int=%d", i);
	WIN_ASSERT_TRUE(i == 0);
}
END_TEST

	BEGIN_TEST(Common012)
{
	int i = ToInt("-128");
	WIN_TRACE("int=%d", i);
	WIN_ASSERT_TRUE(i == -128);
}
END_TEST

	BEGIN_TEST(Common013)
{
	int i = ToInt(127);
	WIN_TRACE("int=%d", i);

	WIN_ASSERT_TRUE(i == 127);
}
END_TEST

	BEGIN_TEST(Common014)
{
	int i = ToInt("-129");
	WIN_TRACE("int=%d", i);

	WIN_ASSERT_TRUE(i == -129);
}
END_TEST

	BEGIN_TEST(Common015)
{
	int i = ToInt("-129");
	WIN_TRACE("int=%d", i);

	WIN_ASSERT_TRUE(i == -129);
}
END_TEST

	BEGIN_TEST(Common016)
{
	short s = ToShort("0");
	WIN_TRACE("short=%d", s);
	WIN_ASSERT_TRUE(s == 0);
}
END_TEST

	BEGIN_TEST(Common017)
{
	short s = ToShort("-128");
	WIN_TRACE("short=%d", s);
	WIN_ASSERT_TRUE(s == -128);
}
END_TEST

	BEGIN_TEST(Common018)
{
	short s = ToShort(127);
	WIN_TRACE("short=%d", s);

	WIN_ASSERT_TRUE(s == 127);
}
END_TEST

	BEGIN_TEST(Common019)
{
	short s = ToShort("-129");
	WIN_TRACE("short=%d", s);

	WIN_ASSERT_TRUE(s == -129);
}
END_TEST

	BEGIN_TEST(Common020)
{
	short s = ToShort("128");
	WIN_TRACE("short=%d", s);
	WIN_ASSERT_TRUE(s == 128);
}
END_TEST

	BEGIN_TEST(Common021)
{
	float f= ToFloat("0");
	WIN_TRACE("float=%f", f);
	WIN_ASSERT_TRUE(f == 0);
}
END_TEST

	BEGIN_TEST(Common022)
{
	float f= ToFloat("-128");
	WIN_TRACE("float=%f", f);
	WIN_ASSERT_TRUE(f == -128);
}
END_TEST

	BEGIN_TEST(Common023)
{
	float f= ToFloat(127);
	WIN_TRACE("float=%f", f);

	WIN_ASSERT_TRUE(f == 127);
}
END_TEST

	BEGIN_TEST(Common024)
{
	float f= ToFloat("-129");
	WIN_TRACE("float=%f", f);

	WIN_ASSERT_TRUE(f == -129);
}
END_TEST

	BEGIN_TEST(Common025)
{
	float f= ToFloat("128");
	WIN_TRACE("float=%f", f);
	WIN_ASSERT_TRUE(f == 128);
}
END_TEST

	BEGIN_TEST(Common026)
{
	double d= ToDouble("0");
	WIN_TRACE("double=%f", d);
	WIN_ASSERT_TRUE(d == 0);
}
END_TEST

	BEGIN_TEST(Common027)
{
	double d= ToDouble("-128");
	WIN_TRACE("double=%f", d);
	WIN_ASSERT_TRUE(d == -128);
}
END_TEST

	BEGIN_TEST(Common028)
{
	double d= ToDouble(127);
	WIN_TRACE("double=%f", d);

	WIN_ASSERT_TRUE(d == 127);
}
END_TEST

	BEGIN_TEST(Common029)
{
	double d= ToDouble("-129");
	WIN_TRACE("double=%f", d);

	WIN_ASSERT_TRUE(d == -129);
}
END_TEST

	BEGIN_TEST(Common030)
{
	double d= ToDouble("128");
	WIN_TRACE("double=%f", d);
	WIN_ASSERT_TRUE(d == 128);
}
END_TEST
