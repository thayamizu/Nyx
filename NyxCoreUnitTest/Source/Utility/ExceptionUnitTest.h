#pragma once
#include "PCH/PCH.h"
using namespace nyx;

BEGIN_TEST(Exception001)
{
	const std::string message("�s���ȃt�H�[�}�b�g�ł��B");
	nyx::format_exception e(message.c_str());

	WIN_ASSERT_TRUE(message == e.get_message());
}
END_TEST

BEGIN_TEST(Exception002)
{
	const std::string message("Win32�G���[�ł��B");
	const auto status = ERROR_ACCESS_DENIED;
	nyx::win32_exception e(message.c_str(), status);

	WIN_ASSERT_TRUE(message == e.get_message());
	WIN_ASSERT_TRUE(status  == e.get_status());
}
END_TEST

BEGIN_TEST(Exception003)
{
const std::string message("Win32�G���[�ł��B");
	const auto status = E_ACCESSDENIED;
	nyx::com_exception e(message.c_str(), status);

	WIN_ASSERT_TRUE(message == e.get_message());
	WIN_ASSERT_TRUE(status  == e.get_status());
}
END_TEST

