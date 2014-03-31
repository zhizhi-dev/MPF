#include "stdafx.h"
#include "../include/visual/Quad.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(Quad, MPF::Visual::Quad)

Quad::Quad(const Point& pointA, const Point& pointB, const Point& pointC, const Point& pointD)
:pointA(pointA), pointB(pointB), pointC(pointC), pointD(pointD)
{

}

std::vector<Point> Quad::GetPoints() const
{
	return{ pointA, pointB, pointC, pointD, pointA };
}

void Quad::Transform(std::function<void(Point&)> func)
{
	func(pointA);
	func(pointB);
	func(pointC);
	func(pointD);
}