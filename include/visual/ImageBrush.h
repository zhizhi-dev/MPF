#pragma once
#include "Brush.h"

NS_MPF
NS_VSL

//图片画刷
class ImageBrush : public Brush
{
public:
	//创建 ImageBrush 的新实例
	MPF_API ImageBrush() noexcept;

	//创建 ImageBrush 的新实例
	MPF_API ImageBrush(color_t color) noexcept;

	//采样
	MPF_API virtual color_t TakeSample(float u, float v) const;

	//获取颜色
	MPF_API color_t GetColor() const noexcept;
	//设置颜色
	MPF_API void SetColor(color_t color) noexcept;

	//获取类型
	MPF_API DECLARE_GETTYPE(ImageBrush)
	MPF_API DECLARE_GETINSTANTTYPE(ImageBrush)
private:
	//颜色（默认黑色）
	color_t color = 0xFF000000;

	DECLARE_TYPE(ImageBrush)
};

NS_ED
NS_ED