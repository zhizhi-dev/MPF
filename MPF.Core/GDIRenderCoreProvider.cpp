#include "stdafx.h"
#include "GDI/GDIRenderCoreProvider.h"
#include "../include/visual/GraphicAlgorithms.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::GDI;

DEFINE_TYPE(GDIRenderCoreProvider, MPF::GDI::GDIRenderCoreProvider)

GDIRenderCoreProvider::GDIRenderCoreProvider(std::shared_ptr<NativeWindow> window)
:RenderCoreProvider(window)
{
	InitializeGDI();
}

GDIRenderCoreProvider::~GDIRenderCoreProvider()
{

}

void GDIRenderCoreProvider::InitializeGDI()
{
	//获取主缓冲
	frontBuffer = DeviceContext::FromWindowClient((HWND)window->GetNativeHandle());
	massert(frontBuffer != nullptr);
	//创建后背缓冲
	backBufferSurface = Bitmap::CreateDIBSection(frontBuffer->GetNativeHandle(),
		window->GetClientWidth(), window->GetClientHeight());
	backBuffer = DeviceContext::CreateCompatible(frontBuffer->GetNativeHandle());
}

void GDIRenderCoreProvider::DrawLine(uint x1, uint y1, uint x2, uint y2, color_t color)
{
	auto data = backBufferSurface->GetDataPointer();
	
	//绘制直线
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, backBufferSurface->GetWidth(), x1, y1, x2, y2, color);
}

void GDIRenderCoreProvider::DrawLine(uint x1, uint y1, uint x2, uint y2,
	float u1, float v1, float u2, float v2, const Brush& brush)
{
	auto data = backBufferSurface->GetDataPointer();

	//绘制直线
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, backBufferSurface->GetWidth(),
		x1, y1, x2, y2, u1, v1, u2, v2, brush);
}

void GDIRenderCoreProvider::DrawTriangle(uint x1, uint y1, uint x2, uint y2, uint x3, uint y3, color_t color)
{
	auto data = backBufferSurface->GetDataPointer();
	auto stride = backBufferSurface->GetWidth();

	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x1, y1, x2, y2, color);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x2, y2, x3, y3, color);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x1, y1, x3, y3, color);
}

void GDIRenderCoreProvider::DrawTriangle(uint x1, uint y1, uint x2, uint y2, uint x3, uint y3,
	float u1, float v1, float u2, float v2, float u3, float v3, const Brush& brush)
{
	auto data = backBufferSurface->GetDataPointer();
	auto stride = backBufferSurface->GetWidth();

	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x1, y1, x2, y2, u1, v1, u2, v2, brush);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x2, y2, x3, y3, u2, v2, u3, v3, brush);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x1, y1, x3, y3, u1, v1, u3, v3, brush);
}

void GDIRenderCoreProvider::FillTriangle(uint x1, uint y1, uint x2, uint y2, uint x3, uint y3, color_t color)
{
	auto data = backBufferSurface->GetDataPointer();
	auto stride = backBufferSurface->GetWidth();

	GraphicAlgorithms::FillTriangle_Solid((color_t*)data, stride, x1, y1, x2, y2, x3, y3, color);
}

void GDIRenderCoreProvider::FillTriangle(uint x1, uint y1, uint x2, uint y2, uint x3, uint y3,
	float u1, float v1, float u2, float v2, float u3, float v3, const Brush& brush)
{
	auto data = backBufferSurface->GetDataPointer();
	auto stride = backBufferSurface->GetWidth();

	GraphicAlgorithms::FillTriangle((color_t*)data, stride, x1, y1, x2, y2, x3, y3, u1, v1, u2, v2, u3, v3, brush);
}

void GDIRenderCoreProvider::Present()
{
	//绘制
	BitBlt(frontBuffer->GetNativeHandle(), 0, 0, window->GetClientWidth(),
		window->GetClientHeight(), backBuffer->GetNativeHandle(), 0, 0, SRCCOPY);
}

void GDIRenderCoreProvider::BeginDraw()
{
	SelectObject(backBuffer->GetNativeHandle(), backBufferSurface->GetNativeHandle());
}

void GDIRenderCoreProvider::EndDraw()
{
	auto data = backBufferSurface->GetDataPointer();

	//GraphicAlgorithms::MLAA((color_t*)data, backBufferSurface->GetWidth(), backBufferSurface->GetHeight());
	SelectObject(backBuffer->GetNativeHandle(), nullptr);
}