#pragma once
#include "../include/String.h"
#include "../include/visual/BitmapData.h"

NS_MPF
NS_VSL

struct FontFaceKey
{
	MPF::String FileName;
	uint32_t FaceIndex;

	bool operator==(const FontFaceKey& key) const noexcept
	{
		return FileName == key.FileName && FaceIndex == key.FaceIndex;
	}
};

struct FontFaceCacheKey
{
	wchar_t Char;
	uint32_t XInPixels;
	uint32_t YInPixels;

	bool operator==(const FontFaceCacheKey& key) const noexcept
	{
		return Char == key.Char && XInPixels == key.XInPixels && YInPixels == key.YInPixels;
	}
};

struct FontGlyph
{
	std::shared_ptr<BitmapData<byte>> Glyph;
	uint32_t Left;
	uint32_t Top;
	std::pair<uint32_t, uint32_t> Advance;
};

NS_ED
NS_ED

namespace std
{
	template<>
	class hash<MPF::Visual::FontFaceKey>
	{
	public:
		size_t operator()(const MPF::Visual::FontFaceKey& key) const
		{
			return key.FileName.GetHashCode() ^ key.FaceIndex;
		}
	};

	template<>
	class hash<MPF::Visual::FontFaceCacheKey>
	{
	public:
		size_t operator()(const MPF::Visual::FontFaceCacheKey& key) const
		{
			return key.Char ^ key.XInPixels ^ key.YInPixels;
		}
	};
}