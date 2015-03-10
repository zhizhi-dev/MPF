#pragma once
#include "../../include/visual/RenderCoreProvider.h"
#include "DeviceContext.h"
#include "Bitmap.h"

NS_MPF
NS_GDI

//GDI 渲染提供程序
class GDIRenderCoreProvider : public MPF::Visual::RenderCoreProvider
{
public:
	//创建 GDIRenderCoreProvider 的新实例
	GDIRenderCoreProvider(MPF::Visual::NativeWindow& window);
	virtual ~GDIRenderCoreProvider();

	//开始绘制
	virtual void BeginDraw();
	//结束绘制
	virtual void EndDraw();

	//呈现
	virtual void Present();

	virtual size_t GetBackBufferWidth() const noexcept { return backBufferSurface->GetWidth(); }
	virtual size_t GetBackBufferHeight() const noexcept { return backBufferSurface->GetHeight(); }

	//获取类型
	DECLARE_GETTYPE(GDIRenderCoreProvider)
protected:
	//绘制线段
	virtual void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, color_t color);
	//绘制线段
	virtual void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2,
		float u1, float v1, float u2, float v2, const MPF::Visual::Brush& brush);
	//绘制三角形
	virtual void DrawTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, color_t color);
	//绘制三角形
	virtual void DrawTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3,
		float u1, float v1, float u2, float v2, float u3, float v3, const MPF::Visual::Brush& brush);
	//填充三角形
	virtual void FillTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, color_t color);
	//填充三角形
	virtual void FillTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3,
		float u1, float v1, float u2, float v2, float u3, float v3, const MPF::Visual::Brush& brush);
	//绘制四边形
	virtual void DrawQuad(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, uint32_t x4, uint32_t y4,
		float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4,
		const MPF::Visual::Brush& brush);
	//填充四边形
	virtual void FillQuad(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, uint32_t x4, uint32_t y4,
		float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4, 
		const MPF::Visual::Brush& brush);
private:
	//初始化 GDI
	void InitializeGDI();
private:
	//主缓冲
	std::unique_ptr<DeviceContext> frontBuffer;
	//后背缓冲表面
	std::unique_ptr<Bitmap> backBufferSurface;
	//后背缓冲
	std::unique_ptr<DeviceContext> backBuffer;

	DECLARE_TYPE(GDIRenderCoreProvider)
};

NS_ED
NS_ED