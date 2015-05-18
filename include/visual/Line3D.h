//
// MPF
// 3维直线
//
// (c) SunnyCase 
// 创建日期 2015-05-18
#pragma once
#include "Point3D.h"
#include "Line.h"

NS_MPF
NS_VSL

///<summary>3维直线</summary>
class Line3D
{
public:
	Line3D(Point3D startPoint, Point3D endPoint) noexcept
		: startPoint(startPoint), endPoint(endPoint)
	{

	}

	Line Project(const Projector3D<>& proj) const noexcept
	{
		return{ startPoint*proj, endPoint * proj };
	}
private:
	Point3D startPoint, endPoint;
};

inline Line operator*(const Line3D& left, const Projector3D<>& right) noexcept
{
	return left.Project(right);
}

inline Line operator*(const Projector3D<>& left, const Line3D& right) noexcept
{
	return right.Project(left);
}

NS_ED
NS_ED