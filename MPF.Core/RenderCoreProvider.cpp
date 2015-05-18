#include "stdafx.h"
#include "../include/visual/RenderCoreProvider.h"
#include "../include/Enumerable.h"
#include "../include/visual/SolidColorBrush.h"
#include "NativeWindow.h"
#include "../include/visual/DPIHelper.h"

using namespace MPF;
using namespace MPF::Visual;

RenderCoreProvider::RenderCoreProvider(NativeWindow& window)
:window(window)
{
}

void RenderCoreProvider::DrawLine(const Line& line, color_t color)
{
	auto points = DPIHelper::Current.LogicalGeometryToDevicePoints(line.GetPoints());

	DrawLine(points[0].first, points[0].second, points[1].first, points[1].second, color);
}

void RenderCoreProvider::DrawLine(const Line& line, const Brush& brush)
{
	//´¿É«Ìî³ä
	if (brush.GetInstantType() == SolidColorBrush::GetType())
	{
		return DrawLine(line, reinterpret_cast<const SolidColorBrush*>(&brush)->GetColor());
	}

	auto points = line.GetPoints();
	auto transPoints = DPIHelper::Current.LogicalGeometryToDevicePoints(line.GetPoints());

	DrawLine(transPoints[0].first, transPoints[0].second, transPoints[1].first, transPoints[1].second,
		points[0].GetU(), points[0].GetV(), points[1].GetU(), points[1].GetV(), brush);
}

void RenderCoreProvider::DrawTriangle(const Triangle& triangle, color_t color)
{
	auto points = DPIHelper::Current.LogicalGeometryToDevicePoints(triangle.GetPoints());

	DrawTriangle(points[0].first, points[0].second, points[1].first,
		points[1].second, points[2].first, points[2].second, color);
}

void RenderCoreProvider::DrawTriangle(const Triangle& triangle, const Brush& brush)
{
	//´¿É«Ìî³ä
	if (brush.GetInstantType() == SolidColorBrush::GetType())
	{
		return DrawTriangle(triangle, reinterpret_cast<const SolidColorBrush*>(&brush)->GetColor());
	}

	auto points = triangle.GetPoints();
	auto transPoints = DPIHelper::Current.LogicalGeometryToDevicePoints(triangle.GetPoints());

	DrawTriangle(transPoints[0].first, transPoints[0].second, transPoints[1].first,
		transPoints[1].second, transPoints[2].first, transPoints[2].second,
		points[0].GetU(), points[0].GetV(), points[1].GetU(), points[1].GetV(),
		points[2].GetU(), points[2].GetV(), brush);
}

void RenderCoreProvider::FillTriangle(const Triangle& triangle, color_t color)
{
	auto transPoints = DPIHelper::Current.LogicalGeometryToDevicePoints(triangle.GetPoints());

	FillTriangle(transPoints[0].first, transPoints[0].second, transPoints[1].first,
		transPoints[1].second, transPoints[2].first, transPoints[2].second, color);
}

void RenderCoreProvider::FillTriangle(const Triangle& triangle, const Brush& brush)
{
	//´¿É«Ìî³ä
	if (brush.GetInstantType() == SolidColorBrush::GetType())
	{
		return FillTriangle(triangle, reinterpret_cast<const SolidColorBrush*>(&brush)->GetColor());
	}
	auto points = triangle.GetPoints();
	auto transPoints = DPIHelper::Current.LogicalGeometryToDevicePoints(points);

	FillTriangle(transPoints[0].first, transPoints[0].second, transPoints[1].first,
		transPoints[1].second, transPoints[2].first, transPoints[2].second,
		points[0].GetU(), points[0].GetV(), points[1].GetU(), points[1].GetV(),
		points[2].GetU(), points[2].GetV(), brush);
}

void RenderCoreProvider::FillQuad(const MPF::Visual::Quad& quad, const Brush& brush)
{
	auto points = quad.GetPoints();
	auto transPoints = DPIHelper::Current.LogicalGeometryToDevicePoints(points);

	FillQuad(transPoints[0].first, transPoints[0].second, transPoints[1].first,
		transPoints[1].second, transPoints[2].first, transPoints[2].second,
		transPoints[3].first, transPoints[3].second,
		points[0].GetU(), points[0].GetV(), points[1].GetU(), points[1].GetV(),
		points[2].GetU(), points[2].GetV(), points[3].GetU(), points[3].GetV(), brush);
}

void RenderCoreProvider::DrawQuad(const MPF::Visual::Quad& quad, const Brush& brush)
{
	auto points = quad.GetPoints();
	auto transPoints = DPIHelper::Current.LogicalGeometryToDevicePoints(points);

	DrawQuad(transPoints[0].first, transPoints[0].second, transPoints[1].first,
		transPoints[1].second, transPoints[2].first, transPoints[2].second,
		transPoints[3].first, transPoints[3].second,
		points[0].GetU(), points[0].GetV(), points[1].GetU(), points[1].GetV(),
		points[2].GetU(), points[2].GetV(), points[3].GetU(), points[3].GetV(), brush);
}

void RenderCoreProvider::DrawQuad(const Quad& quad, const Brush& brush, const Matrix2D<>& transform)
{
	auto points = quad.GetPoints();
	for (auto& pt : points)
		pt.Transform(transform);
	auto transPoints = DPIHelper::Current.LogicalGeometryToDevicePoints(points);

	DrawQuad(transPoints[0].first, transPoints[0].second, transPoints[1].first,
		transPoints[1].second, transPoints[2].first, transPoints[2].second,
		transPoints[3].first, transPoints[3].second,
		points[0].GetU(), points[0].GetV(), points[1].GetU(), points[1].GetV(),
		points[2].GetU(), points[2].GetV(), points[3].GetU(), points[3].GetV(), brush);
}