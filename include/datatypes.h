#pragma once
#include "common.h"

NS_MPF

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned __int64 ulong;
typedef void* handle_t;

typedef unsigned long dword_t;

typedef dword_t color_t;

union argb_color
{
	struct
	{
		byte blue, green, red, alpha;
	};
	color_t col;

	argb_color()
	{

	}

	argb_color(color_t color)
		:col(color)
	{

	}

	operator color_t() const mnoexcept
	{
		return col;
	}
};

NS_ED