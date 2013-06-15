#pragma once
#include "PCH/PCH.h"

using namespace Nyx;
FIXTURE(RandomFixture);

namespace {
	Random * g_rand;
}

SETUP(RandomFixture)
{
	::g_rand = new Random();
	::g_rand->Init(0);
}

TEARDOWN(RandomFixture)
{
	SafeDelete(::g_rand);
}
BEGIN_TESTF(Random001, RandomFixture)
{
	const int N = 1000;
	for (int i=0; i< N; i++) {
		long r = ::g_rand->Int31();
		WIN_TRACE("%d=%ld\n", i, r);
		WIN_ASSERT_TRUE((r >= 0) && (r <= 0x7fffffff));
	}
	WIN_TRACE("\n\n");
}
END_TESTF

	BEGIN_TESTF(Random002, RandomFixture)
{
	const int N = 1000;
	for (int i=0; i< N; i++) {
		ulong r = ::g_rand->Int32();
		WIN_TRACE("%d=%uld\n", i, r);

		WIN_ASSERT_TRUE((r >= 0) && (r <=0xffffffff));
	}
	WIN_TRACE("\n\n");
}
END_TESTF
	BEGIN_TESTF(Random003, RandomFixture)
{
	const int N = 1000;
	for (int i=0; i< N; i++) {
		const double r = ::g_rand->Real1();
		WIN_TRACE("%d=%f\n", i, r);

		WIN_ASSERT_TRUE((r >= 0) && (r <= 1));
	}
	WIN_TRACE("\n\n");
}
END_TESTF

	BEGIN_TESTF(Random004, RandomFixture)
{
	const int N = 1000;
	for (int i=0; i< N; i++) {
		const double r= ::g_rand->Real2();
		WIN_TRACE("%d=%f\n", i, r);

		WIN_ASSERT_TRUE((r >= 0) && (r < 1));
	}
	WIN_TRACE("\n\n");
}
END_TESTF

	BEGIN_TESTF(Random005, RandomFixture)
{
	const int N = 1000;
	for (int i=0; i< N; i++) {
		const double r = ::g_rand->Real3();
		WIN_TRACE("%d=%lf\n", i, r);

		WIN_ASSERT_TRUE((r > 0) && (r < 1));
	}
	WIN_TRACE("\n\n");
}
END_TESTF

	BEGIN_TESTF(Random006, RandomFixture)
{
	const int N = 1000;
	for (int i=0; i< N; i++) {
		const double r = ::g_rand->Res53();
		WIN_TRACE("%d=%lf\n", i, r);

		WIN_ASSERT_TRUE((r >= 0) && (r < 1));
	}
	WIN_TRACE("\n\n");
}
END_TESTF