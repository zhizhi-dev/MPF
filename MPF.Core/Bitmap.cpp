#include "stdafx.h"
#include "GDI/Bitmap.h"
#include "../include/visual/GraphicAlgorithms.h"

using namespace MPF;
using namespace MPF::GDI;
using namespace MPF::Visual;

DEFINE_TYPE(Bitmap, MPF::GDI::Bitmap)

Bitmap::Bitmap()
:width(0u), height(0u)
{

}

std::unique_ptr<Bitmap> Bitmap::CreateDIBSection(HDC hDC, uint32_t width, uint32_t height)
{
	width &= ~(4 - 1);
	height &= ~(4 - 1);

	auto bitmap = std::make_unique<Bitmap>();
	
	BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biSize = sizeof(bmpInfo);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = -(LONG)height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;			//32 Î»Éî
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	bitmap->hBitmap = ::CreateDIBSection(hDC, &bmpInfo, 
		DIB_RGB_COLORS, (void**)&bitmap->data, nullptr, 0);
	massert(bitmap->hBitmap != nullptr);
	bitmap->width = width;
	bitmap->height = height;

	memset(bitmap->data, 0xFFFFFFFF, width * height * 4);

	return bitmap;
}

byte* Bitmap::GetDataPointer() const noexcept
{
	return data;
}

Bitmap::~Bitmap()
{
	if (hBitmap)
	{
		DeleteObject(hBitmap);
		hBitmap = nullptr;
	}
	data = nullptr;
}

HBITMAP Bitmap::GetNativeHandle() const noexcept
{
	return hBitmap;
}

void Bitmap::AlphaBlend(argb_color color)
{
	auto ptr = (argb_color*)data;
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			auto orgColor = ptr[x];
			ptr[x] = GraphicAlgorithms::MixColor(orgColor, color, orgColor.alpha / 255.0);
		}
		ptr += width;
	}
}