#pragma once
#include "../Type.h"

NS_MPF
NS_VSL

//点
class Point : public Object
{
public:
	//创建 Point 的新实例
	Point(float x = 0.f, float y = 0.f, float u = 0.f, float v = 0.f)
		:x(x), y(y), u(u), v(v)
	{

	}

	//获取 X 坐标
	float GetX() const mnoexcept
	{
		return x;
	}

	//获取 Y 坐标
	float GetY() const mnoexcept
	{
		return y;
	}

	//设置 X 坐标
	void SetX(float x) mnoexcept
	{
		this->x = x;
	}

	//设置 Y 坐标
	void SetY(float y) mnoexcept
	{
		this->y = y;
	}

	//获取 U 坐标
	float GetU() const mnoexcept
	{
		return u;
	}

	//获取 V 坐标
	float GetV() const mnoexcept
	{
		return v;
	}

	//设置 U 坐标
	void SetU(float u) mnoexcept
	{
		this->u = u;
	}

	//设置 V 坐标
	void SetV(float v) mnoexcept
	{
		this->v = v;
	}

	mproperty(float, X);
	mproperty(float, Y);
	mproperty(float, U);
	mproperty(float, V);

	const Point& operator+=(const Point& point) mnoexcept
	{
		x += point.x;
		y += point.y;
		u += point.u;
		v += point.v;

		return *this;
	}

	Point operator+(const Point& point) const mnoexcept
	{
		Point pt(*this);
		pt.x += point.x;
		pt.y += point.y;
		pt.u += point.u;
		pt.v += point.v;

		return pt;
	}

	Point operator-(const Point& point) const mnoexcept
	{
		Point pt(*this);
		pt.x -= point.x;
		pt.y -= point.y;
		pt.u -= point.u;
		pt.v -= point.v;

		return pt;
	}

	//获取类型
	DECLARE_GETTYPE(Point)
private:
	float x;
	float y;
	float u;
	float v;

	DECLARE_TYPE(Point)
};

NS_ED
NS_ED