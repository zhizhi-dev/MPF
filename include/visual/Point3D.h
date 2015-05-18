//
// MPF
// 3维顶点
//
// (c) SunnyCase 
// 创建日期 2015-05-18
#pragma once
#include "../Type.h"
#include "Point.h"
#include "Matrix3D.h"
#include "Projector3D.h"

NS_MPF
NS_VSL

//点
class Point3D
{
public:
	//创建 Point3D 的新实例
	Point3D(float x = 0.f, float y = 0.f, float z = 0.0f, float u = 0.f, float v = 0.f)
		:x(x), y(y), z(z), u(u), v(v)
	{

	}

	//获取 X 坐标
	float GetX() const noexcept
	{
		return x;
	}

	//获取 Y 坐标
	float GetY() const noexcept
	{
		return y;
	}

	//获取 Z 坐标
	float GetZ() const noexcept
	{
		return z;
	}

	//设置 X 坐标
	void SetX(float x) noexcept
	{
		this->x = x;
	}

	//设置 Y 坐标
	void SetY(float y) noexcept
	{
		this->y = y;
	}

	//设置 Z 坐标
	void SetZ(float z) noexcept
	{
		this->z = z;
	}

	//获取 U 坐标
	float GetU() const noexcept
	{
		return u;
	}

	//获取 V 坐标
	float GetV() const noexcept
	{
		return v;
	}

	//设置 U 坐标
	void SetU(float u) noexcept
	{
		this->u = u;
	}

	//设置 V 坐标
	void SetV(float v) noexcept
	{
		this->v = v;
	}

	mproperty(float, X);
	mproperty(float, Y);
	mproperty(float, Z);
	mproperty(float, U);
	mproperty(float, V);

	const Point3D& operator+=(const Point3D& point) noexcept
	{
		x += point.x;
		y += point.y;
		z += point.z;
		u += point.u;
		v += point.v;

		return *this;
	}

	Point3D operator+(const Point3D& point) const noexcept
	{
		Point3D pt(*this);
		pt.x += point.x;
		pt.y += point.y;
		pt.z += point.z;
		pt.u += point.u;
		pt.v += point.v;

		return pt;
	}

	Point3D operator-(const Point3D& point) const noexcept
	{
		Point3D pt(*this);
		pt.x -= point.x;
		pt.y -= point.y;
		pt.z -= point.z;
		pt.u -= point.u;
		pt.v -= point.v;

		return pt;
	}

	void Transform(const Matrix3D<>& transform) noexcept
	{
		auto value = Vector3D<>(x, y, z) * transform;
		x = value.x;
		y = value.y;
		z = value.z;
	}

	Point Project(const Projector3D<>& proj) const noexcept
	{
		auto vec = Vector3D<>(x, y, z) * proj;
		return{ vec.x, vec.y, u, v };
	}
private:
	float x;
	float y;
	float z;
	float u;
	float v;
};

inline Point operator*(const Point3D& left, const Projector3D<>& right) noexcept
{
	return left.Project(right);
}

inline Point operator*(const Projector3D<>& left, const Point3D& right) noexcept
{
	return right.Project(left);
}

NS_ED
NS_ED