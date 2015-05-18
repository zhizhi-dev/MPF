//
// MPF
// 3维向量
//
// (c) SunnyCase 
// 创建日期 2015-05-19
#pragma once
#include "../core.h"

NS_MPF
NS_VSL

///<summary>3维向量</summary>
template<typename T = float>
struct alignas(sizeof(T) * 4) Vector3D
{
	constexpr Vector3D() noexcept
		:x(), y(), z()
	{

	}

	constexpr Vector3D(T x, T y, T z) noexcept
		: x(x), y(y), z(z)
	{

	}

	T x, y, z;
};

NS_ED
NS_ED