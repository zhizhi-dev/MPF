#include "stdafx.h"
#include "GDI/DeviceContext.h"

using namespace MPF;
using namespace MPF::GDI;

DEFINE_TYPE(DeviceContext, MPF::GDI::DeviceContext)

DeviceContext::DeviceContext()
{

}

DeviceContext::~DeviceContext()
{
	if (isOwner && hDC != nullptr)
	{
		ReleaseDC(hWnd, hDC);
	}
	hDC = nullptr;
	isOwner = false;
}

std::unique_ptr<DeviceContext> DeviceContext::FromWindowClient(HWND hWnd)
{
	massert(hWnd);
	auto dc = std::make_unique<DeviceContext>();

	dc->hWnd = hWnd;
	//获取客户端 HDC
	dc->hDC = GetDC(dc->hWnd);

	return dc;
}

HDC DeviceContext::GetNativeHandle() const mnoexcept
{
	return hDC;
}

std::unique_ptr<DeviceContext> DeviceContext::CreateCompatible(HDC hDC)
{
	massert(hDC);
	auto dc = std::make_unique<DeviceContext>();

	dc->hDC = CreateCompatibleDC(hDC);
	dc->isOwner = true;
	return dc;
}