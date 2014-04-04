#pragma once
#include "Geometry.h"

NS_MPF
NS_VSL

//直线
class Line : public Geometry
{
public:
	//创建一条直线
	MPF_API explicit Line(const Point& startPoint, const Point& endPoint);

	//获取顶点数据
	MPF_API virtual std::vector<Point> GetPoints() const;

	//获取起始点
	const Point& GetStartPoint() const mnoexcept { return startPoint; }
	//获取结束点
	const Point& GetEndPoint() const mnoexcept { return endPoint; }

	//通过Y求直线上的X
	float GetX(float y) const mnoexcept;
	///<summary>通过Y求线段上的X</summary>
	///<return>如果Y值在线段上则返回true,X值，否则返回false,0</return>
	std::pair<bool, float> GetXInSegment(float y) const mnoexcept;
	//通过Y求直线上的UV
	std::pair<float, float> GetUV(uint y) const mnoexcept;

	MPF_API virtual void Transform(std::function<void(Point&)> func);

	//获取类型
	DECLARE_GETTYPE(Line)
private:
	Point startPoint;
	Point endPoint;

	DECLARE_TYPE(Line)
};

NS_ED
NS_ED