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
	uint realSize = size * 64;
	auto& glyph = GetGlyphCache(FontFaceCacheKey{ chr, realSize });

	bitmap.CopyFrom(glyph, 0, 0, left, top);
	return std::make_pair(glyph.GetWidth(), glyph.GetHeight());
}

const BitmapData<byte>& FontFace::GetGlyphCache(const FontFaceCacheKey& key)
{
	auto it(cache.find(key));
	if (it != cache.end())
	{
		return it->second;
	}
	return LoadGlyphCache(key);
}

const BitmapData<byte>& FontFace::LoadGlyphCache(const FontFaceCacheKey& key)
{
	fontMgr->SetFontFaceSize(face, key.Size);
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
	BitmapData<byte> bitmap(width, height);
	bitmap.CopyFrom(BitmapData<byte>(srcBitmap.buffer, srcBitmap.width,
		srcBitmap.rows, srcBitmap.pitch), left, top);

	return cache.emplace(key, std::move(bitmap)).first->second;
}

std::pair<uint, uint> FontFace::MeasureText(const MPF::String& text, float size)
{
	uint realSize(size * 64);
	auto length(text.GetLength());
	auto pair(std::make_pair(0u, 0u));

	for (size_t i = 0; i < length; i++)
	{
		auto& bitmap = GetGlyphCache(FontFaceCacheKey{ text[i], realSize });
		pair.first += bitmap.GetWidth();
		pair.second = max(pair.second, bitmap.GetHeight());
	}

	return pair;
}