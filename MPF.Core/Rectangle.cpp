#include "stdafx.h"
#include "../include/visual/Rectangle.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(Rectangle, MPF::Visual::Rectangle)

Rectangle::Rectangle(const Point& pointA, const Point& pointB)
:pointA(pointA), pointB(pointB)
{

}

std::vector<Point> Rectangle::GetPoints() const
{
	return { pointA, Point(pointB.GetX(), pointA.GetY(), pointB.GetU(), pointA.GetV()),
		pointB, Point(pointA.GetX(), pointB.GetY(), pointA.GetU(), pointB.GetV()), pointA };
}