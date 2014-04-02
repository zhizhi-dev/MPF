#include "stdafx.h"
#include "FontManager.h"
#include <sstream>

using namespace MPF;
using namespace MPF::Visual;

std::shared_ptr<FontManager> FontManager::current;

FontManager::FontManager()
{
	InitializeDPIScale();
	auto error = FT_Init_FreeType(&freeType);
	massert(error == 0);
}

FontManager::~FontManager()
{
	auto expired = std::all_of(fonts.begin(), fonts.end(),
		[&](std::pair<const FontFaceKey, std::weak_ptr<FontFace>>& pair)
	{
		return pair.second.expired();
	});
	massert(expired);
	fonts.clear();

	if (freeType)
	{
		auto error = FT_Done_FreeType(freeType);
		massert(error == 0);
		freeType = nullptr;
	}
}

std::shared_ptr<FontManager> FontManager::GetCurrent()
{
	if (current == nullptr)
	{
		current = std::make_shared<FontManager>();
	}
	return current;
}

String FontManager::GetFileNameFromFamilyName(
	const MPF::String& faceName, uint& faceIndex)
{
	static const LPWSTR fontRegistryPath = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
	HKEY hKey;
	LONG result;

	// Open Windows font registry key
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, fontRegistryPath, 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS) {
		return nullptr;
	}

	DWORD maxValueNameSize, maxValueDataSize;
	result = RegQueryInfoKey(hKey, 0, 0, 0, 0, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);
	if (result != ERROR_SUCCESS) {
		return nullptr;
	}

	DWORD valueIndex = 0;
	std::vector<wchar_t> valueName(maxValueDataSize);
	std::vector<BYTE> valueData(maxValueDataSize);
	DWORD valueNameSize, valueDataSize, valueType;
	wchar_t* fileName = nullptr;

	// Look for a matching font name
	do
	{
		valueDataSize = maxValueDataSize;
		valueNameSize = maxValueNameSize;

		result = RegEnumValue(hKey, valueIndex, valueName.data(),
			&valueNameSize, 0, &valueType, valueData.data(), &valueDataSize);

		valueIndex++;

		if (result != ERROR_SUCCESS || valueType != REG_SZ)
		{
			continue;
		}

		// Found a match
		if (_wcsnicmp(faceName.GetDataPointer(), valueName.data(), faceName.GetLength()) == 0)
		{
			fileName = (wchar_t*)valueData.data();
			faceIndex = 0;
			break;
		}
	} while (result != ERROR_NO_MORE_ITEMS);

	RegCloseKey(hKey);

	// Build full font file path
	WCHAR winDir[MAX_PATH];
	GetWindowsDirectory(winDir, MAX_PATH);

	if (fileName != nullptr)
	{
		std::wstringstream ss;
		ss << winDir << L"\\Fonts\\" << fileName;
		auto str = ss.str();
		return str.c_str();
	}

	return String::GetEmpty();
}

std::shared_ptr<FontFace> FontManager::LoadFontFromFileName(const MPF::String& fileName,
	uint faceIndex)
{
	massert(!fileName.IsEmpty());

	size_t length = 0;
	wcstombs_s(&length, nullptr, 0, fileName.GetDataPointer(), 0);
	length += 1;
	std::vector<char> cFileName(length);
	wcstombs_s(&length, cFileName.data(), length, fileName.GetDataPointer(), length);

	FT_Face face = nullptr;
	auto error = FT_New_Face(freeType, cFileName.data(), faceIndex, &face);
	massert(error == 0);
	FontFaceKey key{ fileName, faceIndex };
	auto value(std::make_shared<FontFace>(face));
	fonts.emplace(key, value);

	return value;
}

std::shared_ptr<FontFace> FontManager::LoadFontFromFileName(MPF::String&& fileName,
	uint faceIndex)
{
	massert(!fileName.IsEmpty());

	size_t length = 0;
	wcstombs_s(&length, nullptr, 0, fileName.GetDataPointer(), 0);
	length += 1;
	std::vector<char> cFileName(length);
	wcstombs_s(&length, cFileName.data(), length, fileName.GetDataPointer(), length);

	FT_Face face = nullptr;
	auto error = FT_New_Face(freeType, cFileName.data(), faceIndex, &face);
	massert(error == 0);
	FontFaceKey key{ std::move(fileName), faceIndex };
	auto value(std::make_shared<FontFace>(face));
	fonts.emplace(key, value);

	return value;
}

void FontManager::InitializeDPIScale()
{
	HDC hdc = GetDC(NULL);

	dpiScaleX = GetDeviceCaps(hdc, LOGPIXELSX) / 96.f;
	dpiScaleY = GetDeviceCaps(hdc, LOGPIXELSY) / 96.f;
}

std::shared_ptr<FontFace> FontManager::LookupFontFace(const MPF::String& fileName,
	uint faceIndex)
{
	//fvck cl
	//²»ÄÜÓÃ£º
	//auto it(fonts.find(FontFaceKey{ fileName, faceIndex }));
	FontFaceKey key{ fileName, faceIndex };
	auto it(fonts.find(key));
	if (it != fonts.end())
	{
		if (it->second.expired())
		{
			return nullptr;
		}
		return it->second.lock();
	}
	return nullptr;
}

std::shared_ptr<FontFace> FontManager::GetFontFace(const MPF::String& fileName,
	uint faceIndex)
{
	auto face = LookupFontFace(fileName, faceIndex);
	if (face)
	{
		return face;
	}
	return LoadFontFromFileName(fileName, faceIndex);
}

std::shared_ptr<FontFace> FontManager::GetFontFace(MPF::String&& fileName, uint faceIndex)
{
	auto face = LookupFontFace(fileName, faceIndex);
	if (face)
	{
		return face;
	}
	return LoadFontFromFileName(std::move(fileName), faceIndex);
}

std::shared_ptr<FontFace> FontManager::GetFontFace(const MPF::String& familyName)
{
	uint faceIndex = 0;
	auto fileName = GetFileNameFromFamilyName(familyName, faceIndex);

	return GetFontFace(fileName, faceIndex);
}

void FontManager::SetFontFaceSize(FT_Face face, float size) const
{
	auto pair(LogicalPointToDevicePoint(size, size));

	SetFontFaceSize(face, pair.first, pair.second);
}

void FontManager::SetFontFaceSize(FT_Face face, uint xInPixels, uint yInPixels) const
{
	massert(face != nullptr);

	auto error = FT_Set_Pixel_Sizes(face, xInPixels, yInPixels);
	massert(error == 0);
}

std::pair<uint, uint> FontManager::LogicalPointToDevicePoint(float x, float y) const
{
	return std::make_pair<uint, uint>(x * dpiScaleX, y * dpiScaleY);
}