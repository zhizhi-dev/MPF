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
	GDIRenderCoreProvider(std::shared_ptr<MPF::Visual::NativeWindow> window);
	virtual ~GDIRenderCoreProvider();

	//开始绘制
	virtual void BeginDraw();
	//结束绘制
	virtual void EndDraw();

	//呈现
	virtual void Present();

	//获取类型
	DECLARE_GETTYPE(GDIRenderCoreProvider)
protected:
	//绘制线段
	virtual void DrawLine(uint x1, uint y1, uint x2, uint y2, color_t color);
	//绘制线段
	virtual void DrawLine(uint x1, uint y1, uint x2, uint y2,
		float u1, float v1, float u2, float v2, const MPF::Visual::Brush& brush);
	//绘制三角形
	virtual void DrawTriangle(uint x1, uint y1, uint x2, uint y2, uint x3, uint y3, color_t color);
	//绘制三角形
	virtual void DrawTriangle(uint x1, uint y1, uint x2, uint y2, uint x3, uint y3,
		float u1, float v1, float u2, float v2, float u3, float v3, const MPF::Visual::Brush& brush);
	//填充三角形
	virtual void FillTriangle(uint x1, uint y1, uint x2, uint y2, uint x3, uint y3, color_t color);
	//填充三角形
	virtual void FillTriangle(uint x1, uint y1, uint x2, uint y2, uint x3, uint y3,
		float u1, float v1, float u2, float v2, float u3, float v3, const MPF::Visual::Brush& brush);
private:
	//初始化 GDI
	void InitializeGDI();
private:
	//主缓冲
	std::shared_ptr<DeviceContext> frontBuffer;
	//后背缓冲表面
	std::shared_ptr<Bitmap> backBufferSurface;
	//后背缓冲
	std::shared_ptr<DeviceContext> backBuffer;

	DECLARE_TYPE(GDIRenderCoreProvider)
};

NS_ED
NS_ED