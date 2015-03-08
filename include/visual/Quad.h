#pragma once
#include "Geometry.h"
#include "Thickness.h"

NS_MPF
NS_VSL

//四边形
class Quad : public Geometry
{
public:
	//创建一个空四边形
	MPF_API Quad();

	//创建一个四边形
	MPF_API explicit Quad(const Point& pointA, const Point& pointB,
		const Point& pointC, const Point& pointD);
	//创建一个矩形
	MPF_API explicit Quad(const Point& leftTop, const Point& rightBottom);

	//获取顶点数据
	MPF_API virtual std::vector<Point> GetPoints() const;

	const Point& GetPointA() const noexcept{ return pointA; }
	Point& GetPointA() noexcept{ return pointA; }
	void SetPointA(const Point& point) noexcept{ pointA = point; }
	mproperty(Point&, PointA);

	const Point& GetPointB() const noexcept{ return pointB; }
	Point& GetPointB() noexcept{ return pointB; }
	void SetPointB(const Point& point) noexcept{ pointB = point; }
	mproperty(Point&, PointB);

	const Point& GetPointC() const noexcept{ return pointC; }
	Point& GetPointC() noexcept{ return pointC; }
	void SetPointC(const Point& point) noexcept{ pointC = point; }
	mproperty(Point&, PointC);

	const Point& GetPointD() const noexcept{ return pointD; }
	Point& GetPointD() noexcept{ return pointD; }
	void SetPointD(const Point& point) noexcept{ pointD = point; }
	mproperty(Point&, PointD);

	MPF_API virtual void Transform(std::function<void(Point&)> func);
	MPF_API void Translate(const Point& point) noexcept;
	MPF_API const Quad& operator-=(const Thickness& thick) noexcept;
	MPF_API Quad operator-(const Thickness& thick) const noexcept;
	MPF_API Quad operator+(const Thickness& thick) const noexcept;
	MPF_API bool Contains(const Point& point) const noexcept;

	//获取类型
	MPF_API DECLARE_GETTYPE(Quad);
	MPF_API DECLARE_GETINSTANTTYPE(Quad);
private:
	Point pointA;
	Point pointB;
	Point pointC;
	Point pointD;

	DECLARE_TYPE(Quad)
};

NS_ED
NS_ED