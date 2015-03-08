#pragma once
#include "../Type.h"
#include "BitmapData.h"

#ifdef DrawText
#undef DrawText
#endif

NS_MPF
NS_VSL

class FontFace;

//字体
class Font : public MPF::Object
{
public:
	//从字体名称和大小创建字体
	MPF_API Font(const MPF::String& faceName, float size);

	//从字体文件、字体序号和大小创建字体
	MPF_API Font(const MPF::String& fileName, uint32_t faceIndex, float size);
	//从字体文件、字体序号和大小创建字体
	MPF_API Font(MPF::String&& fileName, uint32_t faceIndex, float size);

	MPF_API Font(const Font& font);
	MPF_API Font(Font&& font) noexcept;

	//绘制单个字符并返回字符的像素大小
	MPF_API std::pair<uint32_t, uint32_t> DrawChar(BitmapData<byte>& bitmap, uint32_t left, 
		uint32_t top, wchar_t chr);

	MPF_API void DrawText(BitmapData<byte>& bitmap, uint32_t left, uint32_t top, const MPF::String& text);

	//计算文本要占用的像素大小
	MPF_API std::pair<uint32_t, uint32_t> MeasureText(const MPF::String& text);

	MPF_API bool operator!=(const Font& font)const noexcept;
	MPF_API const Font& operator=(const Font& font);
	MPF_API const Font& operator=(Font&& font) noexcept;

	//获取类型
	MPF_API DECLARE_GETTYPE(Font)
	MPF_API DECLARE_GETINSTANTTYPE(Font)
private:
	float size;
	std::shared_ptr<FontFace> face;
	DECLARE_TYPE(Font)
};

NS_ED
NS_ED