#pragma once
#include <windef.h>

NS_MPF
NS_GDI

//设备上下文
class DeviceContext
{
public:
	//创建 DeviceContext 的新实例
	DeviceContext();
	//析构
	virtual ~DeviceContext();

	//获取 HDC
	HDC GetNativeHandle() const mnoexcept;

	//设置颜色

	//从窗口客户端获取
	static std::unique_ptr<DeviceContext> FromWindowClient(HWND hWnd);
	//创建兼容设备上下文
	static std::unique_ptr<DeviceContext> CreateCompatible(HDC hDC);
protected:
private:
	HDC hDC = nullptr;
	HWND hWnd = nullptr;
	bool isOwner = false;
};

NS_ED
NS_ED