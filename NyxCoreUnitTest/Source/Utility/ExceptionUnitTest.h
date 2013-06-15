#pragma once
#include "PCH/PCH.h"
using namespace Nyx;

BEGIN_TEST(Exception001)
{
	const std::string message("�s���ȃt�H�[�}�b�g�ł��B");
	Nyx::FormatException e(message.c_str());

	WIN_ASSERT_TRUE(message == e.GetMessage());
}
END_TEST

BEGIN_TEST(Exception002)
{
	const std::string message("Win32�G���[�ł��B");
	const auto status = ERROR_ACCESS_DENIED;
	Nyx::Win32Exception e(message.c_str(), status);

	WIN_ASSERT_TRUE(message == e.GetMessage());
	WIN_ASSERT_TRUE(status  == e.GetStatus());
}
END_TEST

BEGIN_TEST(Exception003)
{
const std::string message("Win32�G���[�ł��B");
	const auto status = E_ACCESSDENIED;
	Nyx::COMException e(message.c_str(), status);

	WIN_ASSERT_TRUE(message == e.GetMessage());
	WIN_ASSERT_TRUE(status  == e.GetStatus());
}
END_TEST

