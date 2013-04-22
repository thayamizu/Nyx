#pragma once
#include "PCH/PCH.h"
using namespace Nyx;

BEGIN_TEST(Limits001)
{
	WIN_ASSERT_TRUE(Limits::CharMin == CHAR_MIN);
	WIN_ASSERT_TRUE(Limits::CharMax == CHAR_MAX);

}
END_TEST;

BEGIN_TEST(Limits002)
{
	WIN_ASSERT_TRUE(Limits::UCharMin == 0);
	WIN_ASSERT_TRUE(Limits::UCharMax == UCHAR_MAX);	
}
END_TEST;

BEGIN_TEST(Limits003)
{
	WIN_ASSERT_TRUE(Limits::ShortMin == SHRT_MIN);
	WIN_ASSERT_TRUE(Limits::ShortMax == SHRT_MAX);
}
END_TEST;

BEGIN_TEST(Limits004)
{
	WIN_ASSERT_TRUE(Limits::UShortMin == 0);
	WIN_ASSERT_TRUE(Limits::UShortMax == USHRT_MAX);
}
END_TEST;

BEGIN_TEST(Limits005)
{
	WIN_ASSERT_TRUE(Limits::IntMin == INT_MIN);
	WIN_ASSERT_TRUE(Limits::IntMax == INT_MAX);
}
END_TEST;

BEGIN_TEST(Limits006)
{
	WIN_ASSERT_TRUE(Limits::UIntMin == 0);
	WIN_ASSERT_TRUE(Limits::UIntMax == UINT_MAX);
}
END_TEST;

BEGIN_TEST(Limits007)
{
	WIN_ASSERT_TRUE(Limits::FloatMin == FLT_MIN);
	WIN_ASSERT_TRUE(Limits::FloatMax == FLT_MAX);	
}
END_TEST;

BEGIN_TEST(Limits008)
{
	WIN_ASSERT_TRUE(Limits::DoubleMin == DBL_MIN);
	WIN_ASSERT_TRUE(Limits::DoubleMax == DBL_MAX);	
}
END_TEST;

BEGIN_TEST(Limits009)
{
	WIN_ASSERT_TRUE(Limits::IsCharRange(CHAR_MIN));
	WIN_ASSERT_TRUE(Limits::IsCharRange(CHAR_MAX));
}
END_TEST;
BEGIN_TEST(Limits010)
{	
	WIN_ASSERT_TRUE(Limits::IsUCharRange(0));
	WIN_ASSERT_TRUE(Limits::IsUCharRange(UCHAR_MAX));
}
END_TEST;
BEGIN_TEST(Limits011)
{
	WIN_ASSERT_TRUE(Limits::IsShortRange(SHRT_MIN));
	WIN_ASSERT_TRUE(Limits::IsShortRange(SHRT_MAX));
}
END_TEST;
BEGIN_TEST(Limits012)
{
	WIN_ASSERT_TRUE(Limits::IsUShortRange(0));
	WIN_ASSERT_TRUE(Limits::IsUShortRange(USHRT_MAX));
}
END_TEST;
BEGIN_TEST(Limits013)
{
	WIN_ASSERT_TRUE(Limits::IsIntRange(INT_MIN));
	WIN_ASSERT_TRUE(Limits::IsIntRange(INT_MAX));
}
END_TEST;
BEGIN_TEST(Limits014)
{
	WIN_ASSERT_TRUE(Limits::IsUIntRange(0));
	WIN_ASSERT_TRUE(Limits::IsUIntRange(UINT_MAX));
}
END_TEST;

BEGIN_TEST(Limits015)
{
	WIN_ASSERT_TRUE(Limits::IsFloatRange(FLT_MIN));
	WIN_ASSERT_TRUE(Limits::IsFloatRange(FLT_MAX));
}
END_TEST;
BEGIN_TEST(Limits016)
{
	WIN_ASSERT_TRUE(Limits::IsDoubleRange(DBL_MIN));
	WIN_ASSERT_TRUE(Limits::IsDoubleRange(DBL_MAX));
}
END_TEST;
