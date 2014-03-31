#pragma once
#include "Geometry.h"

NS_MPF
NS_VSL

//�ı���
class Quad : public Geometry
{
public:
	//����һ���ı���
	MPF_API explicit Quad(const Point& pointA, const Point& pointB,
		const Point& pointC, const Point& pointD);
	//����һ������
	MPF_API explicit Quad(const Point& leftTop, const Point& rightBottom);

	//��ȡ��������
	MPF_API virtual std::vector<Point> GetPoints() const;

	const Point& GetPointA() const mnoexcept{ return pointA; }
	Point& GetPointA() mnoexcept{ return pointA; }
	void SetPointA(const Point& point) mnoexcept{ pointA = point; }
	mproperty(Point&, PointA);

	MPF_API virtual void Transform(std::function<void(Point&)> func);

	//��ȡ����
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