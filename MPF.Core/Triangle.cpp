#include "stdafx.h"
#include "../include/visual/triangle.h"
#include "../include/visual/Line.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(Triangle, MPF::Visual::Triangle)

Triangle::Triangle(const Point& pointA, const Point& pointB, const Point& pointC)
:pointA(pointA), pointB(pointB), pointC(pointC)
{

}

std::vector<Point> Triangle::GetPoints() const
{
	std::vector<Point> data = { pointA, pointB, pointC, pointA };

	return data;
}

void Triangle::Transform(std::function<void(Point&)> func)
{
	func(pointA);
	func(pointB);
	func(pointC);
}

bool Triangle::Contains(const Point& point) const noexcept
{
	if ((point.X == pointA.X && point.Y == pointA.Y) ||
	(point.X == pointB.X && point.Y == pointB.Y) ||
	(point.X == pointC.X && point.Y == pointC.Y))
	{
		return true;
	}

	Line lines[] = { Line(pointA, pointB), Line(pointA, pointC), Line(pointB, pointC) };
	int count = 0;//pt所在射线（x负方向）与线段相交次数

	for (auto& line : lines)
	{
		auto pair = line.GetXInSegment(point.Y);
		if (pair.first && pair.second <= point.X)
		{
			count++;
		}
	}
	//数量==1说明在三角形内
	return count == 1;
}