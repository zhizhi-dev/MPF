#include "stdafx.h"
#include "../include/visual/DPIHelper.h"
#include "../include/Enumerable.h"

using namespace MPF;
using namespace MPF::Visual;

DPIHelper DPIHelper::Current;

DPIHelper::DPIHelper()
{
	InitializeDPIScale();
}

void DPIHelper::InitializeDPIScale()
{
	HDC hdc = GetDC(NULL);

	dpiScaleX = GetDeviceCaps(hdc, LOGPIXELSX) / 96.0f;
	dpiScaleY = GetDeviceCaps(hdc, LOGPIXELSY) / 96.0f;
}

std::pair<uint32_t, uint32_t> DPIHelper::LogicalPointToDevicePoint(float x, float y) const
{
	uint32_t ix = (uint32_t)std::ceilf(x * dpiScaleX);
	uint32_t iy = (uint32_t)std::ceilf(y * dpiScaleY);

	return std::make_pair(ix, iy);
}

std::pair<uint32_t, uint32_t> DPIHelper::LogicalPointToDevicePoint(const Point& point) const
{
	return LogicalPointToDevicePoint(point.X, point.Y);
}

std::vector<std::pair<uint32_t, uint32_t>> DPIHelper::LogicalGeometryToDevicePoints(const std::vector<Point>& points) const
{
	return Enumerable::ToVector(points, [&](const Point& pt)
	{
		return LogicalPointToDevicePoint(pt.X, pt.Y);
	});
}

Point DPIHelper::DevicePointToLogicalPoint(uint32_t x, uint32_t y) const
{
	return{ x / dpiScaleX, y / dpiScaleY };
}