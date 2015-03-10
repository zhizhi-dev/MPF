#include "stdafx.h"
#include "FontFace.h"
#include "FontManager.h"
#include "../include/visual/DPIHelper.h"
#include <fstream>

using namespace MPF;
using namespace MPF::Visual;

FontFace::FontFace(FT_Face face)
:face(face)
{
	fontMgr = FontManager::GetCurrent();
}

FontFace::~FontFace()
{
	if (face)
	{
		auto error = FT_Done_Face(face);
		massert(error == 0);
		face = nullptr;
	}
}

FT_Face FontFace::GetFace() const noexcept
{
	return face;
}

FontFace::operator FT_Face() const noexcept
{
	return GetFace();
}

std::pair<uint32_t, uint32_t> FontFace::DrawChar(BitmapData<byte>& bitmap, uint32_t left, uint32_t top, wchar_t chr, float size)
{
	auto& glyph = GetGlyphCache(chr, size);

	bitmap.CopyFrom(*glyph.Glyph, 0, 0, left + glyph.Left, top + glyph.Top);
	return std::make_pair(glyph.Advance.first, glyph.Glyph->GetHeight() + glyph.Top);
}

const FontGlyph& FontFace::GetGlyphCache(const FontFaceCacheKey& key)
{
	auto it(cache.find(key));
	if (it != cache.end())
	{
		return it->second;
	}
	return LoadGlyphCache(key);
}

const FontGlyph& FontFace::GetGlyphCache(wchar_t chr, float size)
{
	auto sizeInPixels(DPIHelper::Current.LogicalPointToDevicePoint(size, size));

	return GetGlyphCache(FontFaceCacheKey{ chr, sizeInPixels.first, sizeInPixels.second });
}

const FontGlyph& FontFace::LoadGlyphCache(const FontFaceCacheKey& key)
{
	fontMgr->SetFontFaceSize(face, key.XInPixels, key.YInPixels);
	auto index = FT_Get_Char_Index(face, key.Char);
	mmassert(index != 0, "FT_Get_Char_Index: Undefined character code.");
	auto error = FT_Load_Glyph(face, index, FT_LOAD_DEFAULT);
	massert(error == 0);
	//若不是位图信息需要先渲染
	if (face->glyph->format != FT_Glyph_Format::FT_GLYPH_FORMAT_BITMAP)
	{
		error = FT_Render_Glyph(face->glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL);
		massert(error == 0);
	}

	auto ascender(face->size->metrics.ascender >> 6);
	auto descender(face->size->metrics.descender >> 6);
	auto left(face->glyph->bitmap_left);
	auto top(ascender - face->glyph->bitmap_top);
	auto height(face->glyph->bitmap.rows);
	auto width(face->glyph->bitmap.width);
	auto advance = std::make_pair((uint32_t)face->glyph->advance.x >> 6, (uint32_t)face->glyph->advance.y);

	auto& srcBitmap(face->glyph->bitmap);
	auto bitmap = std::make_shared<BitmapData<byte>>(width, height);
	bitmap->CopyFrom(BitmapData<byte>(srcBitmap.buffer, srcBitmap.width,
		srcBitmap.rows, srcBitmap.pitch), 0, 0);

	return cache.emplace(key, FontGlyph{ bitmap, (uint32_t)left, (uint32_t)top, advance }).first->second;
}

std::pair<uint32_t, uint32_t> FontFace::MeasureText(const MPF::String& text, float size)
{
	uint32_t realSize(size * 64);
	auto length(text.GetLength());
	auto pair(std::make_pair(0u, 0u));
	auto sizeInPixels(DPIHelper::Current.LogicalPointToDevicePoint(size, size));

	for (size_t i = 0; i < length; i++)
	{
		auto& glyph = GetGlyphCache(FontFaceCacheKey{ text[i], sizeInPixels.first, sizeInPixels.second });
		pair.first += glyph.Advance.first;
		pair.second = std::max(pair.second, glyph.Glyph->GetHeight() + glyph.Top);
	}

	return pair;
}