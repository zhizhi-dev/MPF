#pragma once
#include "common.h"
#include <inttypes.h>

NS_MPF

typedef unsigned char byte;
typedef void* handle_t;

typedef unsigned long dword_t;
typedef uint32_t color_t;

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

	operator color_t() const noexcept
	{
		return col;
	}
};

NS_ED