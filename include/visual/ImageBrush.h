//
// MPF
// 图像画刷
//
// (c) SunnyCase 
// 创建日期 2014-03-23
#pragma once
#include "Brush.h"
#include "../media/ImageSource.h"

NS_MPF
NS_VSL

//图片画刷
class ImageBrush : public Brush
{
public:
	// 创建 ImageBrush 的新实例
	MPF_API ImageBrush(std::shared_ptr<Media::ImageSource> source);
	// 创建 ImageBrush 的新实例
	MPF_API ImageBrush(Media::ImageSource& source);
	MPF_API virtual ~ImageBrush();

	// 采样
	MPF_API virtual color_t TakeSample(float u, float v) const;

	// 获取类型
	MPF_API DECLARE_GETTYPE(ImageBrush);
	MPF_API DECLARE_GETINSTANTTYPE(ImageBrush);
private:
	std::shared_ptr<Media::ImageSource> sourceHolder;
	Media::ImageSource* source;

	DECLARE_TYPE(ImageBrush)
};

NS_ED
NS_ED