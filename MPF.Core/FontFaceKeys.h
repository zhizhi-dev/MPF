#pragma once
#include "../include/String.h"
#include "../include/visual/BitmapData.h"

NS_MPF
NS_VSL

struct FontFaceKey
{
	std::shared_ptr<MPF::String> FileName;
	uint FaceIndex;

	bool operator==(const FontFaceKey& key) const mnoexcept
	{
		return FileName == key.FileName && FaceIndex == key.FaceIndex;
	}
};

struct FontFaceCacheKey
{
	wchar_t Char;
	uint XInPixels;
	uint YInPixels;

	bool operator==(const FontFaceCacheKey& key) const mnoexcept
	{
		return Char == key.Char && XInPixels == key.XInPixels && YInPixels == key.YInPixels;
	}
};

struct FontGlyph
{
	std::shared_ptr<BitmapData<byte>> Glyph;
	uint Left;
	uint Top;
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
			return key.FileName->GetHashCode() ^ key.FaceIndex;
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