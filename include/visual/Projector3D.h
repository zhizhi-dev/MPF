//
// MPF
// 3维投影器
//
// (c) SunnyCase 
// 创建日期 2015-05-18
#pragma once
#include "Matrix3D.h"
#include "Vector2D.h"
#include <cmath>

NS_MPF
NS_VSL

///<summary>3维投影器</summary>
template<typename T = float>
class Projector3D
{
public:
	explicit Projector3D(const Matrix3D<T>& projection) noexcept
		:projection(projection)
	{

	}

	Vector2D<T> Project(const Vector3D<T>& vec) const noexcept
	{
		auto value = vec * projection;
		return{ value.x, value.y };
	}
private:
	Matrix3D<T> projection;
};

template<typename T>
inline Vector2D<T> operator*(const Projector3D<T>& left, const Vector3D<T>& right) noexcept
{
	return left.Project(right);
}

template<typename T>
inline Vector2D<T> operator*(const Vector3D<T>& left, const Projector3D<T>& right) noexcept
{
	return right.Project(left);
}

NS_ED
NS_ED