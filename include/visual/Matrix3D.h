//
// MPF
// 3维矩阵
//
// (c) SunnyCase 
// 创建日期 2015-05-18
#pragma once
#include "Vector3D.h"
#include <cmath>
NS_MPF
NS_VSL

///<summary>3维矩阵</summary>
template<typename T = float>
struct alignas(sizeof(T) * 4) Matrix3D
{
	Matrix3D() noexcept
		:arr{ 0 }
	{

	}

	constexpr Matrix3D(const T(&elem)[4][4]) noexcept
		: arr(elem)
	{

	}

	Matrix3D(T m11, T m12, T m13, T m14,
			 T m21, T m22, T m23, T m24,
			 T m31, T m32, T m33, T m34,
			 T m41, T m42, T m43, T m44) noexcept
		:arr{
			{ m11, m12, m13, m14 },
			{ m21, m22, m23, m24 },
			{ m31, m32, m33, m34 },
			{ m41, m42, m43, m44 } }
	{

	}

	///<summary>对向量进行变换</summary>
	Vector3D<T> Transform(const Vector3D<T>& vec) const noexcept
	{
		return{ vec.x * m.m11 + vec.y * m.m21 + vec.z * m.m31 + m.m41,
			vec.x * m.m12 + vec.y * m.m22 + vec.z * m.m32 + m.m42,
			vec.x * m.m13 + vec.y * m.m23 + vec.z * m.m33 + m.m43 };
	}

	///<summary>创建一个单位矩阵</summary>
	static constexpr Matrix3D MakeIdentity()
	{
		return{ 1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1 };
	}

	///<summary>创建一个平移变换矩阵</summary>
	///<param name="x">X 轴平移距离</param>
	///<param name="y">Y 轴平移距离</param>
	///<param name="z">Z 轴平移距离</param>
	static constexpr Matrix3D MakeTranslate(T x, T y, T z)
	{
		return{ 1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				x, y, z, 1 };
	}

	///<summary>创建一个相对原点缩放变换矩阵</summary>
	///<param name="x">X 轴方向缩放因子</param>
	///<param name="y">Y 轴方向缩放因子</param>
	///<param name="z">Z 轴方向缩放因子</param>
	static constexpr Matrix3D MakeScale(T x, T y, T z)
	{
		return{ x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, 1 };
	}

	///<summary>创建一个相对原点缩放变换矩阵</summary>
	///<param name="scale">X，Y 轴方向缩放因子</param>
	static constexpr Matrix3D MakeScale(T scale)
	{
		return MakeScale(scale, scale, scale);
	}

	///<summary>创建一个相对X轴逆时针旋转矩阵</summary>
	///<param name="rad">旋转角度（弧度制）</param>
	static Matrix3D MakeRotatePitch(T rad)
	{
		const auto sin = std::sin(rad), cos = std::cos(rad);
		return{ 1, 0,    0,   0,
				0, cos,  sin, 0,
				0, -sin, cos, 0,
				0,	  0, 0,	  1 };
	}

	///<summary>创建一个相对Y轴逆时针旋转矩阵</summary>
	///<param name="rad">旋转角度（弧度制）</param>
	static Matrix3D MakeRotateYaw(T rad)
	{
		const auto sin = std::sin(rad), cos = std::cos(rad);
		return{ cos, 0, -sin, 0,
				0,   1, 0,	  0,
				sin, 0, cos,  0,
				0,	 0, 0,	  1 };
	}

	///<summary>创建一个相对Z轴逆时针旋转矩阵</summary>
	///<param name="rad">旋转角度（弧度制）</param>
	static Matrix3D MakeRotateRoll(T rad)
	{
		const auto sin = std::sin(rad), cos = std::cos(rad);
		return{ cos,  sin, 0, 0,
				-sin, cos, 0, 0,
				0,	  0,   1, 0,
				0,	  0,   0, 1 };
	}

	///<summary>创建一个斜投影矩阵</summary>
	///<param name="alpha">alpha 角度（弧度制）</param>
	///<param name="beta">beta 角度（弧度制）</param>
	static Matrix3D MakeObliqueProject(T alpha, T beta)
	{
		const auto sin = std::sin(beta), cos = std::cos(beta), cot = 1 / std::tan(alpha);
		return{ 1,			0,			0, 0,
				0,			1,			0, 0,
				-cot * cos, -cot * sin, 0, 0,
				0,			0,			0, 1 };
	}

	union
	{
		T arr[4][4];

		struct
		{
			T	m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44;
		} m;
	};
};

template<typename T>
inline constexpr Matrix3D<T> operator*(const Matrix3D<T>& left, const Matrix3D<T>& right)
{
	return{ left.m.m11 * right.m.m11 + left.m.m12 * right.m.m21 + left.m.m13 * right.m.m31 + left.m.m14 * right.m.m41,
			left.m.m11 * right.m.m12 + left.m.m12 * right.m.m22 + left.m.m13 * right.m.m32 + left.m.m14 * right.m.m42,
			left.m.m11 * right.m.m13 + left.m.m12 * right.m.m23 + left.m.m13 * right.m.m33 + left.m.m14 * right.m.m43,
			left.m.m11 * right.m.m14 + left.m.m12 * right.m.m24 + left.m.m13 * right.m.m34 + left.m.m14 * right.m.m44,

			left.m.m21 * right.m.m11 + left.m.m22 * right.m.m21 + left.m.m23 * right.m.m31 + left.m.m24 * right.m.m41,
			left.m.m21 * right.m.m12 + left.m.m22 * right.m.m22 + left.m.m23 * right.m.m32 + left.m.m24 * right.m.m42,
			left.m.m21 * right.m.m13 + left.m.m22 * right.m.m23 + left.m.m23 * right.m.m33 + left.m.m24 * right.m.m43,
			left.m.m21 * right.m.m14 + left.m.m22 * right.m.m24 + left.m.m23 * right.m.m34 + left.m.m24 * right.m.m44,

			left.m.m31 * right.m.m11 + left.m.m32 * right.m.m21 + left.m.m33 * right.m.m31 + left.m.m34 * right.m.m41,
			left.m.m31 * right.m.m12 + left.m.m32 * right.m.m22 + left.m.m33 * right.m.m32 + left.m.m34 * right.m.m42,
			left.m.m31 * right.m.m13 + left.m.m32 * right.m.m23 + left.m.m33 * right.m.m33 + left.m.m34 * right.m.m43,
			left.m.m31 * right.m.m14 + left.m.m32 * right.m.m24 + left.m.m33 * right.m.m34 + left.m.m34 * right.m.m44,

			left.m.m41 * right.m.m11 + left.m.m42 * right.m.m21 + left.m.m43 * right.m.m31 + left.m.m44 * right.m.m41,
			left.m.m41 * right.m.m12 + left.m.m42 * right.m.m22 + left.m.m43 * right.m.m32 + left.m.m44 * right.m.m42,
			left.m.m41 * right.m.m13 + left.m.m42 * right.m.m23 + left.m.m43 * right.m.m33 + left.m.m44 * right.m.m43,
			left.m.m41 * right.m.m14 + left.m.m42 * right.m.m24 + left.m.m43 * right.m.m34 + left.m.m44 * right.m.m44 };
}

template<typename T>
inline Vector3D<T> operator*(const Matrix3D<T>& left, const Vector3D<T>& right)
{
	return left.Transform(right);
}

template<typename T>
inline Vector3D<T> operator*(const Vector3D<T>& left, const Matrix3D<T>& right)
{
	return right.Transform(left);
}

NS_ED
NS_ED