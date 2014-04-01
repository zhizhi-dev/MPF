#include "stdafx.h"
#include "../include/visual/RenderCoreProvider.h"
#include "../include/Enumerable.h"
#include "../include/visual/SolidColorBrush.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(RenderCoreProvider, MPF::Visual::RenderCoreProvider)

RenderCoreProvider::RenderCoreProvider(NativeWindow& window)
:window(window)
{
	InitializeDPIScale();
}

void RenderCoreProvider::DrawLine(const Line& line, color_t color)
{
	auto startPoint = LogicalPointToDevicePoint(line.GetStartPoint());
	auto endPoint = LogicalPointToDevicePoint(line.GetEndPoint());

	DrawLine(startPoint.first, startPoint.second, endPoint.first, endPoint.second, color);
}

void RenderCoreProvider::DrawLine(const Line& line, const Brush& brush)
{
	//´¿É«Ìî³ä
	if (brush.GetInstantType() == SolidColorBrush::GetType())
	{
		return DrawLine(line, reinterpret_cast<const SolidColorBrush*>(&brush)->GetColor());
	}

	auto orgStartPoint = line.GetStartPoint();
	auto orgEndPoint = line.GetEndPoint();
	auto startPoint = LogicalPointToDevicePoint(orgStartPoint);
	auto endPoint = LogicalPointToDevicePoint(orgEndPoint);

	DrawLine(startPoint.first, startPoint.second, endPoint.first, endPoint.second, 
		orgStartPoint.GetU(), orgEndPoint.GetV(), orgEndPoint.GetU(), orgEndPoint.GetV(), brush);
}

void RenderCoreProvider::DrawTriangle(const Triangle& triangle, color_t color)
{
	auto points = triangle.GetPoints();
	auto transPoints = Enumerable::ToVector(points, [=](const Point& pt)
	{
		return LogicalPointToDevicePoint(pt);
	});

	DrawTriangle(transPoints[0].first, transPoints[0].second, transPoints[1].first, 
		transPoints[1].second, transPoints[2].first, transPoints[2].second, color);
}

void RenderCoreProvider::DrawTriangle(const Triangle& triangle, const Brush& brush)
{
	//´¿É«Ìî³ä
	if (brush.GetInstantType() == SolidColorBrush::GetType())
	{
		return DrawTriangle(triangle, reinterpret_cast<const SolidColorBrush*>(&brush)->GetColor());
	}

	auto points = triangle.GetPoints();
	auto transPoints = Enumerable::ToVector(points, [=](const Point& pt)
	{
		return LogicalPointToDevicePoint(pt);
	});

	DrawTriangle(transPoints[0].first, transPoints[0].second, transPoints[1].first,
		transPoints[1].second, transPoints[2].first, transPoints[2].second,
		points[0].GetU(), points[0].GetV(), points[1].GetU(), points[1].GetV(),
		points[2].GetU(), points[2].GetV(), brush);
}

void RenderCoreProvider::FillTriangle(const Triangle& triangle, color_t color)
{
	auto points = triangle.GetPoints();
	auto transPoints = Enumerable::ToVector(points, [=](const Point& pt)
	{
		return LogicalPointToDevicePoint(pt);
	});

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
	auto transPoints = Enumerable::ToVector(points, [=](const Point& pt)
	{
		return LogicalPointToDevicePoint(pt);
	});

	FillTriangle(transPoints[0].first, transPoints[0].second, transPoints[1].first,
		transPoints[1].second, transPoints[2].first, transPoints[2].second,
		points[0].GetU(), points[0].GetV(), points[1].GetU(), points[1].GetV(),
		points[2].GetU(), points[2].GetV(), brush);
}

void RenderCoreProvider::InitializeDPIScale()
{
	HWND hWnd = (HWND)window.GetNativeHandle(); 
	HDC hdc = GetDC(hWnd);

	dpiScaleX = GetDeviceCaps(hdc, LOGPIXELSX) / 96.0f;
	dpiScaleY = GetDeviceCaps(hdc, LOGPIXELSY) / 96.0f;

	ReleaseDC(hWnd, hdc);
}

std::pair<uint, uint> RenderCoreProvider::LogicalPointToDevicePoint(const Point& point) const
{
	uint x = static_cast<uint>(point.GetX() * dpiScaleX);
	uint y = static_cast<uint>(point.GetY() * dpiScaleY);

	return std::make_pair(x, y);
}

void RenderCoreProvider::FillQuad(const MPF::Visual::Quad& quad, const Brush& brush)
{
	auto points = quad.GetPoints();
	auto transPoints = Enumerable::ToVector(points, [=](const Point& pt)
	{
		return LogicalPointToDevicePoint(pt);
	});

	FillQuad(transPoints[0].first, transPoints[0].second, transPoints[1].first,
		transPoints[1].second, transPoints[2].first, transPoints[2].second,
		transPoints[3].first, transPoints[3].second,
		points[0].GetU(), points[0].GetV(), points[1].GetU(), points[1].GetV(),
		points[2].GetU(), points[2].GetV(), points[3].GetU(), points[3].GetV(), brush);
}

void RenderCoreProvider::DrawQuad(const MPF::Visual::Quad& quad, const Brush& brush)
{
	auto points = quad.GetPoints();
	auto transPoints = Enumerable::ToVector(points, [=](const Point& pt)
	{
		return LogicalPointToDevicePoint(pt);
	});

	DrawQuad(transPoints[0].first, transPoints[0].second, transPoints[1].first,
		transPoints[1].second, transPoints[2].first, transPoints[2].second,
		transPoints[3].first, transPoints[3].second,
		points[0].GetU(), points[0].GetV(), points[1].GetU(), points[1].GetV(),
		points[2].GetU(), points[2].GetV(), points[3].GetU(), points[3].GetV(), brush);
}