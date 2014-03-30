#include "stdafx.h"
#include "FontFace.h"
#include "FontManager.h"

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

FT_Face FontFace::GetFace() const mnoexcept
{
	return face;
}

FontFace::operator FT_Face() const mnoexcept
{
	return GetFace();
}

std::pair<uint, uint> FontFace::DrawChar(BitmapData<byte>& bitmap, uint left, uint top, wchar_t chr, float size)
{
	auto& glyph = GetGlyphCache(chr, size);

	bitmap.CopyFrom(*glyph.Glyph, 0, 0, left + glyph.Left, top + glyph.Top);
	return std::make_pair(glyph.Glyph->GetWidth() + glyph.Left, glyph.Glyph->GetHeight() + glyph.Top);
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
	auto sizeInPixels(fontMgr->LogicalPointToDevicePoint(size, size));

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
	auto height(((face->size->metrics.height >> 6) + ascender + descender) / 2);
	auto width(face->glyph->advance.x >> 6);

	auto& srcBitmap(face->glyph->bitmap);
	auto bitmap = std::make_shared<BitmapData<byte>>(width, height);
	bitmap->CopyFrom(BitmapData<byte>(srcBitmap.buffer, srcBitmap.width,
		srcBitmap.rows, srcBitmap.pitch), 0, 0);

	return cache.emplace(key, FontGlyph{ bitmap, left, top }).first->second;
}

std::pair<uint, uint> FontFace::MeasureText(const MPF::String& text, float size)
{
	uint realSize(size * 64);
	auto length(text.GetLength());
	auto pair(std::make_pair(0u, 0u));
	auto sizeInPixels(fontMgr->LogicalPointToDevicePoint(size, size));

	for (size_t i = 0; i < length; i++)
	{
		auto& glyph = GetGlyphCache(FontFaceCacheKey{ text[i], sizeInPixels.first, sizeInPixels.second });
		pair.first += glyph.Glyph->GetWidth() + glyph.Left;
		pair.second = max(pair.second, glyph.Glyph->GetHeight() + glyph.Top);
	}

	return pair;
}