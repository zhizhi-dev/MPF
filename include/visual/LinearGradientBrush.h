#pragma once
#include "Brush.h"

NS_MPF
NS_VSL

//线性渐变颜色画刷
class LinearGradientBrush : public Brush
{
public:
	//创建 LinearGradientBrush 的新实例
	MPF_API LinearGradientBrush(color_t startColor, color_t endColor) mnoexcept;

	//采样
	MPF_API virtual color_t TakeSample(float u, float v) const;

	//获取颜色
	MPF_API color_t GetStartColor() const mnoexcept;
	//设置颜色
	MPF_API void SetStartColor(color_t color) mnoexcept;
	//获取颜色
	MPF_API color_t GetEndColor() const mnoexcept;
	//设置颜色
	MPF_API void SetEndColor(color_t color) mnoexcept;

	//获取类型
	MPF_API DECLARE_GETTYPE(LinearGradientBrush)
	MPF_API DECLARE_GETINSTANTTYPE(LinearGradientBrush)
private:
	//颜色
	argb_color startColor;
	argb_color endColor;

	DECLARE_TYPE(LinearGradientBrush)
};

NS_ED
NS_ED