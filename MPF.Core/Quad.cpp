#include "stdafx.h"
#include "../include/visual/Quad.h"
#include "../include/visual/Triangle.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(Quad, MPF::Visual::Quad)

Quad::Quad()
:pointA(), pointB(0.f, 0.f, 1.f), pointC(0.f, 0.f, 1.f, 1.f), pointD(0.f, 0.f, 0.f, 1.f)
{

}

Quad::Quad(const Point& pointA, const Point& pointB, const Point& pointC, const Point& pointD)
:pointA(pointA), pointB(pointB), pointC(pointC), pointD(pointD)
{

}

Quad::Quad(const Point& leftTop, const Point& rightBottom)
: pointA(leftTop), pointB(rightBottom.X, leftTop.Y, rightBottom.U, leftTop.V),
pointC(rightBottom), pointD(leftTop.X, rightBottom.Y, leftTop.U, rightBottom.V)
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

void Quad::Translate(const Point& point) mnoexcept
{
	pointA += point;
	pointB += point;
	pointC += point;
	pointD += point;
}

const Quad& Quad::operator -= (const Thickness& thick) mnoexcept
{
	pointA.X += thick.Left; pointA.Y += thick.Top;
	pointB.X -= thick.Right; pointB.Y += thick.Top;
	pointC.X -= thick.Right; pointC.Y -= thick.Bottom;
	pointD.X += thick.Left; pointD.Y -= thick.Bottom;

	return *this;
}

Quad Quad::operator - (const Thickness& thick) const mnoexcept
{
	Quad quad = *this;

	quad.pointA.X += thick.Left; quad.pointA.Y += thick.Top;
	quad.pointB.X -= thick.Right; quad.pointB.Y += thick.Top;
	quad.pointC.X -= thick.Right; quad.pointC.Y -= thick.Bottom;
	quad.pointD.X += thick.Left; quad.pointD.Y -= thick.Bottom;
	return quad;
}

Quad Quad::operator + (const Thickness& thick) const mnoexcept
{
	Quad quad = *this;

	quad.pointA.X -= thick.Left; quad.pointA.Y -= thick.Top;
	quad.pointB.X += thick.Right; quad.pointB.Y -= thick.Top;
	quad.pointC.X += thick.Right; quad.pointC.Y += thick.Bottom;
	quad.pointD.X -= thick.Left; quad.pointD.Y += thick.Bottom;
	return quad;
}

bool Quad::Contains(const Point& point) const mnoexcept
{
	std::array<Triangle, 2> tris =
	{
		Triangle(pointA, pointB, pointC),
		Triangle(pointA, pointD, pointC) 
	};

	return std::any_of(tris.begin(), tris.end(), [&](const Triangle& tri)
	{
		return tri.Contains(point);
	});
}