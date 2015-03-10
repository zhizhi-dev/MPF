//
// MPF
// 平台相关
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#include "stdafx.h"
#include "../include/platform.h"

using namespace MPF;

void win32_handle_deleter::operator()(handle_t handle) const noexcept
{
	if (handle != INVALID_HANDLE_VALUE)
		CloseHandle(handle);
}

String win32_exception::format_message(int error)
{
	LPTSTR p_str = nullptr;
	auto len = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&p_str, 0, nullptr);
	if (len)
	{
		String str(p_str, p_str + len);
		LocalFree(p_str);
		return str;
	}
	return String();
}