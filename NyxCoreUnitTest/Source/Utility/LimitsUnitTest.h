#pragma once
#include "PCH/PCH.h"
using namespace nyx;

BEGIN_TEST(Limits001)
{
	WIN_ASSERT_TRUE(limits::CHAR_MINIMUM == CHAR_MIN);
	WIN_ASSERT_TRUE(limits::CHAR_MINIMUM == CHAR_MAX);

}
END_TEST;

BEGIN_TEST(Limits002)
{
	WIN_ASSERT_TRUE(limits::UCHAR_MINIMUM == 0);
	WIN_ASSERT_TRUE(limits::UCHAR_MAXIMUM == UCHAR_MAX);	
}
END_TEST;

BEGIN_TEST(Limits003)
{
	WIN_ASSERT_TRUE(limits::SHORT_MINIMUM == SHRT_MIN);
	WIN_ASSERT_TRUE(limits::SHORT_MAXIMUM == SHRT_MAX);
}
END_TEST;

BEGIN_TEST(Limits004)
{
	WIN_ASSERT_TRUE(limits::USHORT_MINIMUM == 0);
	WIN_ASSERT_TRUE(limits::USHORT_MAXIMUM == USHRT_MAX);
}
END_TEST;

BEGIN_TEST(Limits005)
{
	WIN_ASSERT_TRUE(limits::INT_MINIMUM == INT_MIN);
	WIN_ASSERT_TRUE(limits::INT_MAXIMUM == INT_MAX);
}
END_TEST;

BEGIN_TEST(Limits006)
{
	WIN_ASSERT_TRUE(limits::UINT_MINIMUM == 0);
	WIN_ASSERT_TRUE(limits::UINT_MAXIMUM == UINT_MAX);
}
END_TEST;

BEGIN_TEST(Limits007)
{
	WIN_ASSERT_TRUE(limits::FLOAT_MINIMUM == FLT_MIN);
	WIN_ASSERT_TRUE(limits::FLOAT_MAXIMUM == FLT_MAX);	
}
END_TEST;

BEGIN_TEST(Limits008)
{
	WIN_ASSERT_TRUE(limits::DOUBLE_MINIMUM == DBL_MIN);
	WIN_ASSERT_TRUE(limits::DOUBLE_MAXIMUM == DBL_MAX);	
}
END_TEST;

BEGIN_TEST(Limits009)
{
	WIN_ASSERT_TRUE(limits::is_char_range(CHAR_MIN));
	WIN_ASSERT_TRUE(limits::is_char_range(CHAR_MAX));
}
END_TEST;
BEGIN_TEST(Limits010)
{	
	WIN_ASSERT_TRUE(limits::is_uchar_range(0));
	WIN_ASSERT_TRUE(limits::is_uchar_range(UCHAR_MAX));
}
END_TEST;
BEGIN_TEST(Limits011)
{
	WIN_ASSERT_TRUE(limits::is_short_range(SHRT_MIN));
	WIN_ASSERT_TRUE(limits::is_short_range(SHRT_MAX));
}
END_TEST;
BEGIN_TEST(Limits012)
{
	WIN_ASSERT_TRUE(limits::is_ushort_range(0));
	WIN_ASSERT_TRUE(limits::is_ushort_range(USHRT_MAX));
}
END_TEST;
BEGIN_TEST(Limits013)
{
	WIN_ASSERT_TRUE(limits::is_int_range(INT_MIN));
	WIN_ASSERT_TRUE(limits::is_int_range(INT_MAX));
}
END_TEST;
BEGIN_TEST(Limits014)
{
	WIN_ASSERT_TRUE(limits::is_uint_range(0));
	WIN_ASSERT_TRUE(limits::is_uint_range(UINT_MAX));
}
END_TEST;

BEGIN_TEST(Limits015)
{
	WIN_ASSERT_TRUE(limits::is_float_range(FLT_MIN));
	WIN_ASSERT_TRUE(limits::is_float_range(FLT_MAX));
}
END_TEST;
BEGIN_TEST(Limits016)
{
	WIN_ASSERT_TRUE(limits::is_double_range(DBL_MIN));
	WIN_ASSERT_TRUE(limits::is_double_range(DBL_MAX));
}
END_TEST;
