#pragma once
#include "../Type.h"

NS_MPF
NS_VSL

//ºñ¶È
struct Thickness
{
	float Left;
	float Top;
	float Right;
	float Bottom;

	Thickness()
		:Thickness(0.f)
	{}

	Thickness(float all)
		:Left(all), Top(all), Right(all), Bottom(all)
	{}

	Thickness(float h, float v)
		:Left(h), Top(v), Right(h), Bottom(v)
	{}

	bool operator==(const Thickness& right) const noexcept
	{
		return Left == right.Left&&Top == right.Top&&
		Right == right.Right&&Bottom == right.Bottom;
	}

	bool operator!=(const Thickness& right) const noexcept
	{
		return !(*this == right);
	}
};

NS_ED
NS_ED