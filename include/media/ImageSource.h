//
// MPF
// 图源
//
// (c) SunnyCase 
// 创建日期 2015-03-08
#pragma once
#include "../Type.h"
#include "../io/Stream.h"
#include "ImageDecoder.h"

NS_MPF
NS_MEDIA

// 图源
class ImageSource
{
public:
	MPF_API ImageSource(const String& fileName);

	MPF_API const DecodedImage& Decode();
private:
private:
	std::shared_ptr<IO::Stream> stream;
	bool cached;
	DecodedImage decodedImage;
};

NS_ED
NS_ED