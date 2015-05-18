#include "stdafx.h"
#include "GDI/GDIRenderCoreProvider.h"
#include "../include/visual/GraphicAlgorithms.h"
#include "NativeWindow.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::GDI;

DEFINE_TYPE(GDIRenderCoreProvider, MPF::GDI::GDIRenderCoreProvider)

GDIRenderCoreProvider::GDIRenderCoreProvider(NativeWindow& window)
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
	frontBuffer = DeviceContext::FromWindowClient((HWND)window.GetNativeHandle());
	massert(frontBuffer != nullptr);
	//创建后背缓冲
	backBufferSurface = Bitmap::CreateDIBSection(frontBuffer->GetNativeHandle(),
		window.GetClientWidth(), window.GetClientHeight());
	backBuffer = DeviceContext::CreateCompatible(frontBuffer->GetNativeHandle());
}

void GDIRenderCoreProvider::Clear(color_t color)
{
	backBufferSurface->Clear(color);
}

void GDIRenderCoreProvider::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, color_t color)
{
	auto data = backBufferSurface->GetDataPointer();
	
	//绘制直线
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, backBufferSurface->GetWidth(), x1, y1, x2, y2, color);
}

void GDIRenderCoreProvider::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2,
	float u1, float v1, float u2, float v2, const Brush& brush)
{
	auto data = backBufferSurface->GetDataPointer();

	//绘制直线
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, backBufferSurface->GetWidth(),
		x1, y1, x2, y2, u1, v1, u2, v2, brush);
}

void GDIRenderCoreProvider::DrawTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, color_t color)
{
	auto data = backBufferSurface->GetDataPointer();
	auto stride = backBufferSurface->GetWidth();

	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x1, y1, x2, y2, color);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x2, y2, x3, y3, color);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x1, y1, x3, y3, color);
}

void GDIRenderCoreProvider::DrawTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3,
	float u1, float v1, float u2, float v2, float u3, float v3, const Brush& brush)
{
	auto data = backBufferSurface->GetDataPointer();
	auto stride = backBufferSurface->GetWidth();

	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x1, y1, x2, y2, u1, v1, u2, v2, brush);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x2, y2, x3, y3, u2, v2, u3, v3, brush);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x1, y1, x3, y3, u1, v1, u3, v3, brush);
}

void GDIRenderCoreProvider::FillTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, color_t color)
{
	auto data = backBufferSurface->GetDataPointer();
	auto stride = backBufferSurface->GetWidth();

	GraphicAlgorithms::FillTriangle_Solid((color_t*)data, stride, x1, y1, x2, y2, x3, y3, color);
}

void GDIRenderCoreProvider::FillTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3,
	float u1, float v1, float u2, float v2, float u3, float v3, const Brush& brush)
{
	auto data = backBufferSurface->GetDataPointer();
	auto stride = backBufferSurface->GetWidth();

	GraphicAlgorithms::FillTriangle((color_t*)data, stride, x1, y1, x2, y2, x3, y3, u1, v1, u2, v2, u3, v3, brush);
}

void GDIRenderCoreProvider::Present()
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = 255;

	backBufferSurface->AlphaBlend(0xFFFFFFFF);
	//绘制
	BitBlt(frontBuffer->GetNativeHandle(), 0, 0, window.GetClientWidth(),
		window.GetClientHeight(), backBuffer->GetNativeHandle(), 0, 0, SRCCOPY);
}

void GDIRenderCoreProvider::BeginDraw()
{
	SelectObject(backBuffer->GetNativeHandle(), backBufferSurface->GetNativeHandle());
}

void GDIRenderCoreProvider::EndDraw()
{
	auto data = backBufferSurface->GetDataPointer();

	SelectObject(backBuffer->GetNativeHandle(), nullptr);
}

void GDIRenderCoreProvider::FillQuad(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, uint32_t x4, uint32_t y4,
	float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4, const Brush& brush)
{
	auto data = backBufferSurface->GetDataPointer();
	auto stride = backBufferSurface->GetWidth();

	GraphicAlgorithms::FillQuad((color_t*)data, stride, x1, y1, x2, y2, x3, y3, x4, y4,
		u1, v1, u2, v2, u3, v3, u4, v4, brush);
}

void GDIRenderCoreProvider::DrawQuad(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, uint32_t x4, uint32_t y4,
	float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4, const Brush& brush)
{
	auto data = backBufferSurface->GetDataPointer();
	auto stride = backBufferSurface->GetWidth();

	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x1, y1, x2, y2, u1, v1, u2, v2, brush);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x2, y2, x3, y3, u2, v2, u3, v3, brush);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x3, y3, x4, y4, u3, v3, u4, v4, brush);
	GraphicAlgorithms::DrawLine_WuXiaolin((color_t*)data, stride, x1, y1, x4, y4, u1, v1, u4, v4, brush);
}