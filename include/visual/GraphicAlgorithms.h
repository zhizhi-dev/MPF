#pragma once
#include "Geometry.h"
#include "Brush.h"

NS_MPF
NS_VSL

//图形算法
class GraphicAlgorithms
{
public:
	//Bresenham 直线生成算法
	MPF_API static void DrawLine_Bresenham(color_t* data, uint32_t stride, int x1, int y1, int x2, int y2, color_t color);

	//吴小林直线生成算法
	MPF_API static void DrawLine_WuXiaolin(color_t* data, uint32_t stride, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, color_t color);

	//吴小林直线生成算法
	MPF_API static void DrawLine_WuXiaolin(color_t* data, uint32_t stride, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2,
		float u1, float v1, float u2, float v2, const Brush& brush);

	//MLAA
	MPF_API static void MLAA(color_t* data, uint32_t width, uint32_t height);

	//纯色填充三角形
	MPF_API static void FillTriangle_Solid(color_t* data, uint32_t stride, uint32_t x1, uint32_t y1,
		uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, color_t color);
	//填充三角形
	MPF_API static void FillTriangle(color_t* data, uint32_t stride, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2,
		uint32_t x3, uint32_t y3, float u1, float v1, float u2, float v2, float u3, float v3, const Brush& brush);
	//填充四边形
	MPF_API static void FillQuad(color_t* data, uint32_t stride, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2,
		uint32_t x3, uint32_t y3, uint32_t x4, uint32_t y4, float u1, float v1, float u2, float v2, 
		float u3, float v3, float u4, float v4, const Brush& brush);

	static inline argb_color MixColor(argb_color col1, argb_color col2, float p)
	{
		argb_color color;

		color.red = col1.red * p + col2.red * (1 - p);
		color.green = col1.green * p + col2.green * (1 - p);
		color.blue = col1.blue * p + col2.blue * (1 - p);

		return color;
	}
private:
	//绘制横向、纵向、45度、135度直线
	static bool DrawSpecialLine(color_t* data, uint32_t stride, int x1, int y1, int x2, int y2, color_t color);

	//绘制横向、纵向、45度、135度直线
	static bool DrawSpecialLine(color_t* data, uint32_t stride, int x1, int y1, 
		int x2, int y2, float u1, float v1, float u2, float v2, const Brush& brush);
};

NS_ED
NS_ED