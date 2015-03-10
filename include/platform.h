//
// MPF
// 平台相关
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#pragma once
#include "common.h"
#include "datatypes.h"
#include "String.h"

NS_MPF

struct win32_handle_deleter
{
	void operator()(handle_t handle) const noexcept;
};
typedef std::unique_ptr<void, win32_handle_deleter> unique_handle;

class win32_exception
{
public:
	win32_exception(int error)
		:error(error)
	{

	}

	const String& what() const noexcept
	{
		return format_message(error);
	}

	int code() const noexcept
	{
		return error;
	}
private:
	static String format_message(int error);

	int error;
};

#define THROW_WSA_IFNOT(val) { if(!(val)) throw ::MPF::win32_exception(WSAGetLastError()); }
#define THROW_WIN_IFNOT(val) { if(!(val)) throw ::MPF::win32_exception(GetLastError()); }

NS_ED