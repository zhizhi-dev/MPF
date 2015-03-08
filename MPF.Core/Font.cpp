#include "stdafx.h"
#include "../include/visual/Font.h"
#include "FontManager.h"

using namespace MPF;
using namespace MPF::Visual;

DEFINE_TYPE(Font, MPF::Visual::Font)

Font::Font(const MPF::String& faceName, float size)
:size(size)
{
	face = FontManager::GetCurrent()->GetFontFace(faceName);
}

Font::Font(MPF::String&& fileName, uint32_t faceIndex, float size)
: size(size)
{
	face = FontManager::GetCurrent()->GetFontFace(std::move(fileName), faceIndex);
}

Font::Font(const MPF::String& fileName, uint32_t faceIndex, float size)
: size(size)
{
	face = FontManager::GetCurrent()->GetFontFace(fileName, faceIndex);
}

Font::Font(const Font& font)
: size(font.size)
{
	face = font.face;
}

Font::Font(Font&& font) noexcept
: size(font.size)
{
	face = std::move(font.face);
}

const Font& Font::operator = (const Font& font)
{
	size = font.size;
	face = font.face;

	return *this;
}

const Font& Font::operator = (Font&& font) noexcept
{
	size = font.size;
	face = std::move(font.face);

	return *this;
}

std::pair<uint32_t, uint32_t> Font::DrawChar(BitmapData<byte>& bitmap, uint32_t left, uint32_t top, wchar_t chr)
{
	return face->DrawChar(bitmap, left, top, chr, size);
}

void Font::DrawText(BitmapData<byte>& bitmap, uint32_t left, uint32_t top, const MPF::String& text)
{
	auto curLeft(left);
	auto curTop(top);
	auto length(text.GetLength());

	for (size_t i = 0; i < length; i++)
	{
		curLeft += DrawChar(bitmap, curLeft, curTop, text[i]).first;
	}
}

std::pair<uint32_t, uint32_t> Font::MeasureText(const MPF::String& text)
{
	return face->MeasureText(text, size);
}

bool Font::operator != (const Font& font)const noexcept
{
	return face.get() == font.face.get() &&
	size == font.size;
}