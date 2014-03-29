#pragma once
#include "Brush.h"

NS_MPF
NS_VSL

//固定颜色画刷
class SolidColorBrush : public Brush
{
public:
	//创建 SolidColorBrush 的新实例
	MPF_API SolidColorBrush() mnoexcept;

	//创建 SolidColorBrush 的新实例
	MPF_API SolidColorBrush(color_t color) mnoexcept;

	//采样
	MPF_API virtual color_t TakeSample(float u, float v) const;

	//获取颜色
	MPF_API color_t GetColor() const mnoexcept;
	//设置颜色
	MPF_API void SetColor(color_t color) mnoexcept;

	//获取类型
	MPF_API DECLARE_GETTYPE(SolidColorBrush)
	MPF_API DECLARE_GETINSTANTTYPE(SolidColorBrush)
private:
	//颜色（默认黑色）
	color_t color = 0xFF000000;

	DECLARE_TYPE(SolidColorBrush)
};

NS_ED
NS_ED