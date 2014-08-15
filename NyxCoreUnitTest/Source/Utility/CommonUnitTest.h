#pragma once
#include "PCH/PCH.h"
using namespace nyx;

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
	std::wstring str = to_string(1234);
	WIN_ASSERT_TRUE(str == TEXT("1234"));
}
END_TEST

	BEGIN_TEST(Common005)
{
	std::wstring str = to_string(1234.1f);
	WIN_ASSERT_TRUE(str == TEXT("1234.1"));
}
END_TEST

	BEGIN_TEST(Common006)
{
	char c = to_char(0);
	WIN_TRACE("char=%d", c);
	WIN_ASSERT_TRUE(c == 0);
}
END_TEST

	BEGIN_TEST(Common007)
{
	char c = to_char(-128);
	WIN_TRACE("char=%d", c);
	WIN_ASSERT_TRUE(c == -3);
}
END_TEST

	BEGIN_TEST(Common008)
{
	char c = to_char(127);
	WIN_TRACE("char=%d", c);

	WIN_ASSERT_TRUE(c == 1);
}
END_TEST

	BEGIN_TEST(Common009)
{
	char c = to_char("0");
	WIN_TRACE("char=%d", c);

	WIN_ASSERT_TRUE(c == 0);
}
END_TEST

	BEGIN_TEST(Common010)
{
	char c = to_char("0");
	WIN_TRACE("char=%c", c);
	WIN_ASSERT_TRUE(c == 0);
}
END_TEST

	BEGIN_TEST(Common011)
{
	int i = to_int("0");
	WIN_TRACE("int=%d", i);
	WIN_ASSERT_TRUE(i == 0);
}
END_TEST

	BEGIN_TEST(Common012)
{
	int i = to_int("-128");
	WIN_TRACE("int=%d", i);
	WIN_ASSERT_TRUE(i == -128);
}
END_TEST

	BEGIN_TEST(Common013)
{
	int i = to_int(127);
	WIN_TRACE("int=%d", i);

	WIN_ASSERT_TRUE(i == 127);
}
END_TEST

	BEGIN_TEST(Common014)
{
	int i = to_int("-129");
	WIN_TRACE("int=%d", i);

	WIN_ASSERT_TRUE(i == -129);
}
END_TEST

	BEGIN_TEST(Common015)
{
	int i = to_int("-129");
	WIN_TRACE("int=%d", i);

	WIN_ASSERT_TRUE(i == -129);
}
END_TEST

	BEGIN_TEST(Common016)
{
	short s = to_short("0");
	WIN_TRACE("short=%d", s);
	WIN_ASSERT_TRUE(s == 0);
}
END_TEST

	BEGIN_TEST(Common017)
{
	short s = to_short("-128");
	WIN_TRACE("short=%d", s);
	WIN_ASSERT_TRUE(s == -128);
}
END_TEST

	BEGIN_TEST(Common018)
{
	short s = to_short(127);
	WIN_TRACE("short=%d", s);

	WIN_ASSERT_TRUE(s == 127);
}
END_TEST

	BEGIN_TEST(Common019)
{
	short s = to_short("-129");
	WIN_TRACE("short=%d", s);

	WIN_ASSERT_TRUE(s == -129);
}
END_TEST

	BEGIN_TEST(Common020)
{
	short s = to_short("128");
	WIN_TRACE("short=%d", s);
	WIN_ASSERT_TRUE(s == 128);
}
END_TEST

	BEGIN_TEST(Common021)
{
	float f= to_float("0");
	WIN_TRACE("float=%f", f);
	WIN_ASSERT_TRUE(f == 0);
}
END_TEST

	BEGIN_TEST(Common022)
{
	float f= to_float("-128");
	WIN_TRACE("float=%f", f);
	WIN_ASSERT_TRUE(f == -128);
}
END_TEST

	BEGIN_TEST(Common023)
{
	float f= to_float(127);
	WIN_TRACE("float=%f", f);

	WIN_ASSERT_TRUE(f == 127);
}
END_TEST

	BEGIN_TEST(Common024)
{
	float f= to_float("-129");
	WIN_TRACE("float=%f", f);

	WIN_ASSERT_TRUE(f == -129);
}
END_TEST

	BEGIN_TEST(Common025)
{
	float f= to_float("128");
	WIN_TRACE("float=%f", f);
	WIN_ASSERT_TRUE(f == 128);
}
END_TEST

	BEGIN_TEST(Common026)
{
	double d= to_double("0");
	WIN_TRACE("double=%f", d);
	WIN_ASSERT_TRUE(d == 0);
}
END_TEST

	BEGIN_TEST(Common027)
{
	double d= to_double("-128");
	WIN_TRACE("double=%f", d);
	WIN_ASSERT_TRUE(d == -128);
}
END_TEST

	BEGIN_TEST(Common028)
{
	double d= to_double(127);
	WIN_TRACE("double=%f", d);

	WIN_ASSERT_TRUE(d == 127);
}
END_TEST

	BEGIN_TEST(Common029)
{
	double d= to_double("-129");
	WIN_TRACE("double=%f", d);

	WIN_ASSERT_TRUE(d == -129);
}
END_TEST

	BEGIN_TEST(Common030)
{
	double d= to_double("128");
	WIN_TRACE("double=%f", d);
	WIN_ASSERT_TRUE(d == 128);
}
END_TEST
