//
// MPF
// BMP 解码器
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#include "stdafx.h"
#include "../stdafx.h"
#include "../../include/media/BitmapDecoder.h"
#include "../../include/io/BinaryReader.h"

using namespace MPF;
using namespace MPF::IO;
using namespace MPF::Media;

#pragma pack(push, 1)
struct BMPFileHeader
{
	uint16_t id;
	uint32_t size;
	byte reserved1[2];
	byte reserved2[2];
	uint32_t startOffset;
};

struct DIBHeader
{
	uint32_t headerSize;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bitCount;
	uint32_t compression;
	uint32_t imageSize;
	uint32_t xPelsPerMeter;
	uint32_t yPelsPerMeter;
	uint32_t clrUsed;
	uint32_t clrImportant;

	enum
	{
		HeaderSize_Len = sizeof(uint32_t)
	};
};
#pragma pack(pop)

static std::vector<color_t> ReadPalette(BinaryReader& br, const DIBHeader& dibHeader)
{
	std::vector<color_t> palette;
	if (dibHeader.bitCount == 1 || dibHeader.bitCount == 4 || dibHeader.bitCount == 8)
	{
		auto colorsCount = (size_t)std::pow(2, dibHeader.bitCount);
		palette.resize(colorsCount);
		br.Read((byte*)palette.data(), colorsCount * sizeof(color_t));
	}
	else if ((dibHeader.bitCount == 16 && dibHeader.compression == BI_RGB) ||
		(dibHeader.bitCount == 32 && dibHeader.compression == BI_RGB) || dibHeader.bitCount == 24)
		;
	else if ((dibHeader.bitCount == 16 || dibHeader.bitCount == 32) && dibHeader.compression == BI_BITFIELDS)
	{
		// 掩码
		palette.resize(3);
		br.Read((byte*)palette.data(), 3 * sizeof(color_t));
	}
	else
		throw std::exception("unknown palette format.");
	return palette;
}

BitmapDecoder::BitmapDecoder()
{

}

BitmapDecoder::~BitmapDecoder()
{

}

DecodedImage BitmapDecoder::Decode(IO::Stream& input)
{
	BinaryReader br(input);

	auto fileHeader = br.Read<BMPFileHeader>();
	THROW_IF_NOT(fileHeader.id == 'MB', "only support Windows Bitmap.");

	DIBHeader dibHeader{ 0 };
	br.Read((byte*)&dibHeader, DIBHeader::HeaderSize_Len);
	auto headerRestLen = dibHeader.headerSize - DIBHeader::HeaderSize_Len;
	auto headerRestAllowLen = std::min(headerRestLen, sizeof(DIBHeader));
	br.Read((byte*)&dibHeader + DIBHeader::HeaderSize_Len, headerRestAllowLen);
	br.Seek(headerRestLen - headerRestAllowLen, SeekOrigin::Current);

	auto palette = ReadPalette(br, dibHeader);

	DecodedImage image;
	image.width = dibHeader.width;
	image.height = dibHeader.height;
	image.bpp = dibHeader.bitCount;

	br.Seek(fileHeader.startOffset, SeekOrigin::Begin);
	// 读取像素
	auto stride = (((dibHeader.width * dibHeader.bitCount) + 31) / 32) * 4;
	auto pixels = dibHeader.width * dibHeader.height;
	image.decodedBitmap = std::make_unique<color_t[]>(pixels);
	if (dibHeader.bitCount == 24 && dibHeader.compression == BI_RGB)
	{
		auto ptr = image.decodedBitmap.get() + pixels - dibHeader.width;
		auto buffer = std::make_unique<byte[]>(stride);
		for (size_t y = 0; y < dibHeader.height; y++)
		{
			br.Read(buffer.get(), stride);
			auto src = buffer.get();
			for (size_t x = 0; x < dibHeader.width; x++)
			{
				*ptr++ = argb_color(src[0], src[1], src[2], 255);
				src += 3;
			}
			ptr -= dibHeader.width * 2;
		}
	}
	else
		throw std::exception("unknown pixels format.");

	return image;
}