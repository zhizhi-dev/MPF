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
	byte* GetDataPointer() const mnoexcept;

	//获取本机标识符
	HBITMAP GetNativeHandle() const mnoexcept;

	//获取宽度
	uint GetWidth() const mnoexcept { return width; }

	//获取高度
	uint GetHeight() const mnoexcept { return height; }

	//创建设备无关位图
	static std::shared_ptr<Bitmap> CreateDIBSection(HDC hDC, uint width, uint height);

	//获取类型
	DECLARE_GETTYPE(Bitmap)
private:
	HBITMAP hBitmap = nullptr;
	uint width, height;
	byte* data = nullptr;
	DECLARE_TYPE(Bitmap)
};

NS_ED
NS_ED