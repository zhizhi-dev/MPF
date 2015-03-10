//
// MPF
// 图像解码器
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#include "stdafx.h"
#include "../stdafx.h"
#include "../../include/media/ImageDecoder.h"
#include "../../include/media/BitmapDecoder.h"

using namespace MPF;
using namespace MPF::Media;

namespace
{
	static std::unordered_map<String, ImageDecoder::factory_t> factories =
	{
		{ L"image/bmp", [] {return std::make_unique<BitmapDecoder>(); }}
	};
}

void ImageDecoder::RegisterImageDecoder(const String& mimeType, factory_t&& factory)
{
	factories.emplace(mimeType, std::move(factory));
}

DecodedImage ImageDecoder::DecodeImage(IO::Stream& input)
{
	for (auto& it : factories)
	{
		try
		{
			auto decoder = it.second();
			return decoder->Decode(input);
		}
		catch (...)
		{

		}
	}
	throw std::exception("unknown image format.");
}