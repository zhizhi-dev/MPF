#pragma once
#include "../include/String.h"
#include "FontFace.h"

NS_MPF
NS_VSL


///<summary>字体管理器</summary>
class FontManager
{
public:
	~FontManager();

	std::shared_ptr<FontFace> GetFontFace(const MPF::String& fileName, uint faceIndex);
	std::shared_ptr<FontFace> GetFontFace(const MPF::String& familyName);

	void SetFontFaceSize(FT_Face face, float size) const;
	void SetFontFaceSize(FT_Face face, uint xInPixels, uint yInPixels) const;
	std::pair<uint, uint> LogicalPointToDevicePoint(float x, float y) const;

	///<summary>获取当前字体管理器</summary>
	static std::shared_ptr<FontManager> GetCurrent();
private:
	///<summary>通过字体文件加载字体</summary>
	///<param name = "fileName">字体文件路径</param>
	std::shared_ptr<FontFace> LoadFontFromFileName(const MPF::String& fileName, uint faceIndex);

	static String GetFileNameFromFamilyName(const MPF::String& familyName,
		uint& faceIndex);
	std::shared_ptr<FontFace> LookupFontFace(const MPF::String& fileName, uint faceIndex);

	void InitializeDPIScale();
protected:
	FontManager();

	friend class std::_Ref_count_obj<FontManager>;
private:
	FT_Library freeType;
	float dpiScaleX;
	float dpiScaleY;
	std::unordered_map<FontFaceKey, std::weak_ptr<FontFace>> fonts;
private:
	static std::shared_ptr<FontManager> current;
};

NS_ED
NS_ED