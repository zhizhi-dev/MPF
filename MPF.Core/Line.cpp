#include "stdafx.h"
#include "../include/visual/line.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(Line, MPF::Visual::Line)

Line::Line(const Point& startPoint, const Point& endPoint)
:startPoint(startPoint), endPoint(endPoint)
{

}

std::vector<Point> Line::GetPoints() const
{
	std::vector<Point> data = { startPoint, endPoint };

	return data;
}

float Line::GetX(float y) const mnoexcept
{
	const auto x1 = startPoint.GetX(), y1 = startPoint.GetY(),
	x2 = endPoint.GetX(), y2 = endPoint.GetY();
	const auto dy = y2 - y1, dx = x2 - x1;

	if (dy == 0) return y1;
	return (y - y1) * dx / dy + x1;
}

std::pair<float, float> Line::GetUV(uint y) const mnoexcept
{
	const int x1 = startPoint.GetX(), y1 = startPoint.GetY(),
	x2 = endPoint.GetX(), y2 = endPoint.GetY();
	const double dy = y2 - y1, dx = x2 - x1;
	const double x = ((int)y - y1) * dx / dy + x1;

	const auto gradU = dx ? (endPoint.GetU() - startPoint.GetU()) / dx : 0.f;
	const auto gradV = dy ? (endPoint.GetV() - startPoint.GetV()) / dy : 0.f;

	return std::make_pair(startPoint.GetU() + gradU * (x - x1), startPoint.GetV() + gradV * (y - y1));
}

void Line::Transform(std::function<void(Point&)> func)
{
	func(startPoint);
	func(endPoint);
}