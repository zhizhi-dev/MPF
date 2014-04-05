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
	MPF_API std::pair<uint, uint> LogicalPointToDevicePoint(float x, float y) const;
	MPF_API std::pair<uint, uint> LogicalPointToDevicePoint(const Point& point) const;
	MPF_API Point DevicePointToLogicalPoint(uint x, uint y) const;
	MPF_API std::vector<std::pair<uint, uint>> LogicalGeometryToDevicePoints(const Geometry& geometry) const;
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