#pragma once
#include "../Type.h"
#include "Point.h"

NS_MPF
NS_VSL

//图元
class Geometry : public Object
{
public:
	//创建 Geometry 的新实例
	explicit Geometry() { }

	//获取顶点数据
	virtual std::vector<Point> GetPoints() const = 0;

	//获取类型
	DECLARE_GETTYPE(Geometry)
private:
	DECLARE_TYPE(Geometry)
};

NS_ED
NS_ED