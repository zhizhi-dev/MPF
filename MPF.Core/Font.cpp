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

Font::Font(const MPF::String& fileName, uint faceIndex, float size)
: size(size)
{
	face = FontManager::GetCurrent()->GetFontFace(fileName, faceIndex);
}

Font::Font(const Font& font)
: size(font.size)
{
	face = font.face;
}

std::pair<uint, uint> Font::DrawChar(BitmapData<byte>& bitmap, uint left, uint top, wchar_t chr)
{
	return face->DrawChar(bitmap, left, top, chr, size);
}

void Font::DrawText(BitmapData<byte>& bitmap, uint left, uint top, const MPF::String& text)
{
	auto curLeft(left);
	auto curTop(top);
	auto length(text.GetLength());

	for (size_t i = 0; i < length; i++)
	{
		curLeft += DrawChar(bitmap, curLeft, curTop, text[i]).first;
	}
}

std::pair<uint, uint> Font::MeasureText(const MPF::String& text)
{
	return face->MeasureText(text, size);
}

bool Font::operator != (const Font& font)const mnoexcept
{
	return face.get() == font.face.get() &&
	size == font.size;
}