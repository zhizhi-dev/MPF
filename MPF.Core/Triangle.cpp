#include "stdafx.h"
#include "../include/visual/triangle.h"

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