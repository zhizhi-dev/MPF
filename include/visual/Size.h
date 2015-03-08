#pragma once
#include "../core.h"

NS_MPF
NS_VSL

//³ß´ç
struct Size
{
	float Width;
	float Height;

	Size operator+(const Size& size) const noexcept
	{
		return{ Width + size.Width, Height + size.Height };
	}

	const Size& operator+=(const Size& size) noexcept
	{
		Width += size.Width;
		Height += size.Height;

		return *this;
	}
};

NS_ED
NS_ED