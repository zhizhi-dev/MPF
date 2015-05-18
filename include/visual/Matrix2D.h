//
// MPF
// 2维矩阵
//
// (c) SunnyCase 
// 创建日期 2015-05-18
#pragma once
#include "Vector2D.h"
#include <cmath>
NS_MPF
NS_VSL

///<summary>2维矩阵</summary>
template<typename T = float>
struct alignas(sizeof(T) * 4) Matrix2D
{
	Matrix2D() noexcept
		:arr{ 0 }
	{

	}

	constexpr Matrix2D(const T(&elem)[3][3]) noexcept
		:arr(elem)
	{

	}

	Matrix2D(T m11, T m12, T m13,
		T m21, T m22, T m23,
		T m31, T m32, T m33) noexcept
		:arr{
			{ m11, m12, m13 },
			{ m21, m22, m23 },
			{ m31, m32, m33 } }
	{

	}

	///<summary>对向量进行变换</summary>
	Vector2D<T> Transform(const Vector2D<T>& vec) const noexcept
	{
		return{ vec.x * m.m11 + vec.y * m.m21 + m.m31,
				vec.x * m.m12 + vec.y * m.m22 + m.m32 };
	}

	///<summary>创建一个单位矩阵</summary>
	static constexpr Matrix2D MakeIdentity()
	{
		return{ 1, 0, 0,
				0, 1, 0,
				0, 0, 1 };
	}

	///<summary>创建一个平移变换矩阵</summary>
	///<param name="x">X 轴平移距离</param>
	///<param name="y">Y 轴平移距离</param>
	static constexpr Matrix2D MakeTranslate(T x, T y)
	{
		return{ 1, 0, 0,
				0, 1, 0,
				x, y, 1 };
	}

	///<summary>创建一个相对原点缩放变换矩阵</summary>
	///<param name="x">X 轴方向缩放因子</param>
	///<param name="y">Y 轴方向缩放因子</param>
	static constexpr Matrix2D MakeScale(T x, T y)
	{
		return{ x, 0, 0,
				0, y, 0,
				0, 0, 1 };
	}

	///<summary>创建一个相对原点缩放变换矩阵</summary>
	///<param name="scale">X，Y 轴方向缩放因子</param>
	static constexpr Matrix2D MakeScale(T scale)
	{
		return MakeScale(scale, scale);
	}

	///<summary>创建一个相对原点逆时针旋转矩阵</summary>
	///<param name="rad">旋转角度（弧度制）</param>
	static Matrix2D MakeRotate(T rad)
	{
		const auto sin = std::sin(rad), cos = std::cos(rad);
		return{ cos,  sin, 0,
				-sin, cos, 0,
				0,	  0,   1 };
	}

	union
	{
		T arr[3][3];

		struct
		{
			T	m11, m12, m13,
				m21, m22, m23,
				m31, m32, m33;
		} m;
	};
};

template<typename T>
inline constexpr Matrix2D<T> operator*(const Matrix2D<T>& left, const Matrix2D<T>& right)
{
	return{ left.m.m11 * right.m.m11 + left.m.m12 * right.m.m21 + left.m.m13 * right.m.m31,
			left.m.m11 * right.m.m12 + left.m.m12 * right.m.m22 + left.m.m13 * right.m.m32,
			left.m.m11 * right.m.m13 + left.m.m12 * right.m.m23 + left.m.m13 * right.m.m33,
				 
			left.m.m21 * right.m.m11 + left.m.m22 * right.m.m21 + left.m.m23 * right.m.m31,
			left.m.m21 * right.m.m12 + left.m.m22 * right.m.m22 + left.m.m23 * right.m.m32,
			left.m.m21 * right.m.m13 + left.m.m22 * right.m.m23 + left.m.m23 * right.m.m33,
				
			left.m.m31 * right.m.m11 + left.m.m32 * right.m.m21 + left.m.m33 * right.m.m31,
			left.m.m31 * right.m.m12 + left.m.m32 * right.m.m22 + left.m.m33 * right.m.m32,
			left.m.m31 * right.m.m13 + left.m.m32 * right.m.m23 + left.m.m33 * right.m.m33 };
}

template<typename T>
inline Vector2D<T> operator*(const Matrix2D<T>& left, const Vector2D<T>& right)
{
	return left.Transform(right);
}

template<typename T>
inline Vector2D<T> operator*(const Vector2D<T>& left, const Matrix2D<T>& right)
{
	return right.Transform(left);
}

NS_ED
NS_ED