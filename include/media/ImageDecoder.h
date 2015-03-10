//
// MPF
// 图像解码器
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#pragma once
#include "../Type.h"
#include "../io/Stream.h"
#include <map>

NS_MPF
NS_MEDIA

// 解码后的图像
struct DecodedImage
{
	size_t width;
	size_t height;
	size_t bpp;
	std::map<String, String> metadata;

	std::unique_ptr<color_t[]> decodedBitmap;
};

// 图像解码器
class ImageDecoder
{
public:
	ImageDecoder(){}
	virtual ~ImageDecoder(){}

	virtual DecodedImage Decode(IO::Stream& input) = 0;

	typedef std::function<std::unique_ptr<ImageDecoder>()> factory_t;

	///<summary>注册图像解码器</summary>
	///<param name="mimeType">MIME 类型</param>
	///<param name="factory">解码器工厂</param>
	MPF_API static void RegisterImageDecoder(const String& mimeType, factory_t&& factory);

	MPF_API static DecodedImage DecodeImage(IO::Stream& input);
};

NS_ED
NS_ED