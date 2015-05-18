#pragma once
#include "../../include/Type.h"

NS_MPF
NS_GDI

//位图
class Bitmap : public Object
{
public:
	//创建 Bitmap 的新实例
	Bitmap();
	//释放
	virtual ~Bitmap();

	//获取数据
	byte* GetDataPointer() const noexcept;

	//获取本机标识符
	HBITMAP GetNativeHandle() const noexcept;

	//获取宽度
	uint32_t GetWidth() const noexcept { return width; }

	//获取高度
	uint32_t GetHeight() const noexcept { return height; }

	//创建设备无关位图
	static std::unique_ptr<Bitmap> CreateDIBSection(HDC hDC, uint32_t width, uint32_t height);

	void AlphaBlend(argb_color color);
	void Clear(argb_color color);

	//获取类型
	DECLARE_GETTYPE(Bitmap)
private:
	HBITMAP hBitmap = nullptr;
	uint32_t width, height;
	byte* data = nullptr;
	DECLARE_TYPE(Bitmap)
};

NS_ED
NS_ED