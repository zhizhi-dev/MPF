//
// MPF
// 图源
//
// (c) SunnyCase 
// 创建日期 2015-03-08
#include "stdafx.h"
#include "../stdafx.h"
#include "../../include/media/ImageSource.h"
#include "../../include/io/FileStream.h"
#include "../../include/media/ImageDecoder.h"

using namespace MPF;
using namespace MPF::IO;
using namespace MPF::Media;

ImageSource::ImageSource(const String& fileName)
	:stream(std::make_shared<FileStream>(fileName, AccessMode::Read, CreationDeposition::OpenExisting)),
	cached(false)
{

}

const DecodedImage& ImageSource::Decode()
{
	if (!cached)
	{
		decodedImage = ImageDecoder::DecodeImage(*stream);
		cached = true;
		stream.reset();
	}
	return decodedImage;
}