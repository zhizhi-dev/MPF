#pragma once
#include "Geometry.h"

NS_MPF
NS_VSL

//矩形
class Rectangle : public Geometry
{
public:
	//创建一个矩形
	MPF_API explicit Rectangle(const Point& pointA, const Point& pointB);

	//获取顶点数据
	MPF_API virtual std::vector<Point> GetPoints() const;

	//获取类型
	MPF_API DECLARE_GETTYPE(Rectangle)
	MPF_API DECLARE_GETINSTANTTYPE(Rectangle)
private:
	Point pointA;
	Point pointB;

	DECLARE_TYPE(Rectangle)
};

NS_ED
NS_ED