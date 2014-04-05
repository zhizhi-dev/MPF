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

std::pair<uint, uint> DPIHelper::LogicalPointToDevicePoint(float x, float y) const
{
	uint ix = (uint)std::ceilf(x * dpiScaleX);
	uint iy = (uint)std::ceilf(y * dpiScaleY);

	return std::make_pair(ix, iy);
}

std::pair<uint, uint> DPIHelper::LogicalPointToDevicePoint(const Point& point) const
{
	return LogicalPointToDevicePoint(point.X, point.Y);
}

std::vector<std::pair<uint, uint>> DPIHelper::LogicalGeometryToDevicePoints(const Geometry& geometry) const
{
	auto points = geometry.GetPoints();
	return Enumerable::ToVector(points, [&](const Point& pt)
	{
		return LogicalPointToDevicePoint(pt.X, pt.Y);
	});
}

Point DPIHelper::DevicePointToLogicalPoint(uint x, uint y) const
{
	return{ x / dpiScaleX, y / dpiScaleY };
}