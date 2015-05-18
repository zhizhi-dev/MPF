//
// MPF
// 2维向量
//
// (c) SunnyCase 
// 创建日期 2015-05-18
#pragma once
#include "../core.h"

NS_MPF
NS_VSL

///<summary>2维向量</summary>
template<typename T = float>
struct alignas(sizeof(T) * 4) Vector2D
{
	constexpr Vector2D() noexcept
		:x(), y()
	{

	}

	constexpr Vector2D(T x, T y) noexcept
		: x(x), y(y)
	{

	}

	T x, y;
};

NS_ED
NS_ED