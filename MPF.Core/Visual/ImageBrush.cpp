//
// MPF
// 图像画刷
//
// (c) SunnyCase 
// 创建日期 2015-03-10
#include "stdafx.h"
#include "../stdafx.h"
#include "../../include/visual/ImageBrush.h"

using namespace MPF;
using namespace MPF::Media;
using namespace MPF::Visual;

DEFINE_TYPE(ImageBrush, MPF::Visual::ImageBrush)

ImageBrush::ImageBrush(std::shared_ptr<Media::ImageSource> source)
	:sourceHolder(source), source(source.get())
{

}

ImageBrush::ImageBrush(Media::ImageSource& source)
	:source(&source)
{

}

ImageBrush::~ImageBrush()
{

}

color_t ImageBrush::TakeSample(float u, float v) const
{
	auto& img = source->Decode();
	auto x = size_t(img.width * u);
	auto y = size_t(img.height * v);

	return img.decodedBitmap[y * img.width + x];
}