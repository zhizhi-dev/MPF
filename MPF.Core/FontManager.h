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

	std::shared_ptr<FontFace> GetFontFace(std::shared_ptr<String> fileName, uint faceIndex);
	std::shared_ptr<FontFace> GetFontFace(std::shared_ptr<String> familyName);

	void SetFontFaceSize(FT_Face face, float size) const;
	void SetFontFaceSize(FT_Face face, uint size26Dot6) const;

	///<summary>获取当前字体管理器</summary>
	static std::shared_ptr<FontManager> GetCurrent();
private:
	///<summary>通过字体文件加载字体</summary>
	///<param name = "fileName">字体文件路径</param>
	std::shared_ptr<FontFace> LoadFontFromFileName(std::shared_ptr<MPF::String> fileName, uint faceIndex);

	static std::shared_ptr<String> GetFileNameFromFamilyName(std::shared_ptr<MPF::String> familyName,
		uint& faceIndex);
	std::shared_ptr<FontFace> LookupFontFace(std::shared_ptr<String> fileName, uint faceIndex);

	void InitializeDPI();
protected:
	FontManager();

	friend class std::_Ref_count_obj<FontManager>;
private:
	FT_Library freeType;
	uint logicalPixelsInX;
	uint logicalPixelsInY;
	std::unordered_map<FontFaceKey, std::weak_ptr<FontFace>> fonts;
private:
	static std::shared_ptr<FontManager> current;
};

NS_ED
NS_ED