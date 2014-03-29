#pragma once
#include "../Type.h"
#include "BitmapData.h"

NS_MPF
NS_VSL

//画刷
class Brush : public Object
{
public:
	//创建 Brush 的新实例
	MPF_API Brush();

	//采样
	MPF_API virtual color_t TakeSample(float u, float v) const = 0;

	//获取类型
	MPF_API DECLARE_GETTYPE(Brush)
	MPF_API DECLARE_GETINSTANTTYPE(Brush)
private:
	DECLARE_TYPE(Brush)
};

NS_ED
NS_ED