#pragma once
#include "Point.h"
#include "Geometry.h"

NS_MPF
NS_VSL

//DPI 辅助
class DPIHelper
{
public:
	DPIHelper();
	MPF_API std::pair<uint32_t, uint32_t> LogicalPointToDevicePoint(float x, float y) const;
	MPF_API std::pair<uint32_t, uint32_t> LogicalPointToDevicePoint(const Point& point) const;
	MPF_API Point DevicePointToLogicalPoint(uint32_t x, uint32_t y) const;
	MPF_API std::vector<std::pair<uint32_t, uint32_t>> LogicalGeometryToDevicePoints(const std::vector<Point>& points) const;
public:
	MPF_API static DPIHelper Current;
private:
	void InitializeDPIScale();
private:
	float dpiScaleX;
	float dpiScaleY;
};

NS_ED
NS_ED