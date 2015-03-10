//
// MPF
// BMP 解码器
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#pragma once
#include "ImageDecoder.h"

NS_MPF
NS_MEDIA

// BMP 解码器
class BitmapDecoder final : public ImageDecoder
{
public:
	MPF_API BitmapDecoder();
	MPF_API virtual ~BitmapDecoder();

	MPF_API virtual DecodedImage Decode(IO::Stream& input);
private:
};

NS_ED
NS_ED