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
	MPF_API Font(std::shared_ptr<MPF::String> faceName, float size);

	//从字体文件、字体序号和大小创建字体
	MPF_API Font(std::shared_ptr<MPF::String> fileName, uint faceIndex, float size);

	MPF_API Font(const Font& font);

	//绘制单个字符并返回字符的像素大小
	MPF_API std::pair<uint, uint> DrawChar(BitmapData<byte>& bitmap, uint left, 
		uint top, wchar_t chr);

	MPF_API void DrawText(BitmapData<byte>& bitmap, uint left, uint top, const MPF::String& text);

	//计算文本要占用的像素大小
	MPF_API std::pair<uint, uint> MeasureText(const MPF::String& text);

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