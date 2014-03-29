#pragma once
#include "../include/String.h"
#include "FontFaceKeys.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../include/visual/BitmapData.h"

NS_MPF
NS_VSL

class FontManager;

//字体
class FontFace
{
public:
	FontFace(FT_Face face);
	~FontFace();

	//不可复制
	FontFace(const FontFace& fontFace) = delete;

	//绘制单个字符并返回字符的像素大小
	std::pair<uint, uint> DrawChar(BitmapData<byte>& bitmap, uint left, uint top, wchar_t chr, float size);

	//计算文本要占用的像素大小
	std::pair<uint, uint> MeasureText(const MPF::String& text, float size);

	FT_Face GetFace() const mnoexcept;
	operator FT_Face() const mnoexcept;
private:
	const BitmapData<byte>& GetGlyphCache(const FontFaceCacheKey& key);
	const BitmapData<byte>& LoadGlyphCache(const FontFaceCacheKey& key);
private:
	FT_Face face;
	std::shared_ptr<FontManager> fontMgr;
	std::unordered_map<FontFaceCacheKey, BitmapData<byte>> cache;
};

NS_ED
NS_ED