#pragma once
#include "Geometry.h"
#include "Matrix2D.h"

NS_MPF
NS_VSL

//直线
class Line : public Geometry
{
public:
	//创建一条直线
	MPF_API Line(const Point& startPoint, const Point& endPoint);

	//获取顶点数据
	MPF_API virtual std::vector<Point> GetPoints() const;

	//获取起始点
	const Point& GetStartPoint() const noexcept { return startPoint; }
	//获取结束点
	const Point& GetEndPoint() const noexcept { return endPoint; }

	//通过Y求直线上的X
	float GetX(float y) const noexcept;
	///<summary>通过Y求线段上的X</summary>
	///<return>如果Y值在线段上则返回true,X值，否则返回false,0</return>
	std::pair<bool, float> GetXInSegment(float y) const noexcept;
	//通过Y求直线上的UV
	std::pair<float, float> GetUV(uint32_t y) const noexcept;

	MPF_API virtual void Transform(std::function<void(Point&)> func);

	//获取类型
	DECLARE_GETTYPE(Line)
private:
	Point startPoint;
	Point endPoint;

	DECLARE_TYPE(Line)
};

inline Line operator*(const Line& left, const Matrix2D<>& right) noexcept
{
	return{ left.GetStartPoint() * right, left.GetEndPoint() * right };
}

inline Line operator*(const Matrix2D<>& left, const Line& right) noexcept
{
	return{ right.GetStartPoint() * left, right.GetEndPoint() * left };
}

NS_ED
NS_ED