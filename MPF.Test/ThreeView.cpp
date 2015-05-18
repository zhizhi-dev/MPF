//
// MPF
// 三视图
//
// (c) SunnyCase 
// 创建日期 2015-05-19

#include "stdafx.h"
#include "../include/visual/Matrix3D.h"
#include "../include/visual/Projector3D.h"
#include "../include/visual/Line3D.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;
using namespace MPF::Input;

const float PI = 3.1415926f;

class ThreViewApp : public Application
{
	// 10 个顶点组成的模型
	const std::array<Point3D, 10> points = {
		Point3D(), Point3D(120.f, 0.f, 0.f, 1.f), Point3D(120.f, 0.f, 60.f, 1.f, 1.f),
		Point3D(0.f, 0.f, 60.f, 0.f, 1.f), Point3D(0.f, 60.f, 60.f, 0.f, 1.f),
		Point3D(120.f, 60.f, 60.f, 1.f, 1.f), Point3D(120.f, 90.f, 30.f, 1.f, 0.f),
		Point3D(0.f, 90.f, 30.f, 0.f, 0.f), Point3D(0.f, 60.f, 0.f, 0.f, 1.f),
		Point3D(120.f, 60.f, 0.f, 1.f, 1.f)
	};
public:
	ThreViewApp()
		:model{
		// 面 1
		Line3D(points[0], points[1]),
		Line3D(points[1], points[2]),
		Line3D(points[2], points[3]),
		Line3D(points[3], points[0]),
		// 面 2
		Line3D(points[3], points[4]),
		Line3D(points[4], points[5]),
		Line3D(points[5], points[2]),
		// 面 3
		Line3D(points[5], points[6]),
		Line3D(points[6], points[7]),
		Line3D(points[7], points[4]),
		// 面 4
		Line3D(points[7], points[8]),
		Line3D(points[8], points[9]),
		Line3D(points[9], points[6]),
		// 面 5
		Line3D(points[9], points[1]),
		Line3D(points[8], points[0])
	}, solidBrush(0xFF2277FF), 
		obliqueProj(Matrix3D<>::MakeObliqueProject(PI / 4, PI / 4)),
		obliqueWorld(Matrix2D<>::MakeFlipX() * Matrix2D<>::MakeTranslate(100.f, 240.f)),
		frontProj(Matrix3D<>::MakeRotateYaw(-PI / 2)),
		frontWorld(Matrix2D<>::MakeFlipX() * Matrix2D<>::MakeTranslate(420.f, 200.f)),
		downProj(Matrix3D<>::MakeRotatePitch(PI / 2)),
		downWorld(Matrix2D<>::MakeFlipX() * Matrix2D<>::MakeRotate(-PI / 2)
			* Matrix2D<>::MakeTranslate(360.f, 400.f)),
		leftProj(Matrix3D<>::MakeIdentity()),
		leftWorld(Matrix2D<>::MakeFlipX() * Matrix2D<>::MakeTranslate(480.f, 200.f))
	{
		win.Width = 640;
		win.Height = 480;
		win.Title = L"MPF - 三视图";
		win.Content = &canvas;

		win.Show();
	}

	virtual void OnFrame() override
	{
		// 先旋转再平移
		auto& render = win.GetRenderCoreProvider();
		render.BeginDraw();
		render.Clear(0xFFFFFFFF);

		DrawOblique(render);
		DrawFront(render);
		DrawDown(render);
		DrawLeft(render);

		render.DrawLine(Line({ 260, 240 }, { 623, 240 }), solidBrush);
		render.DrawLine(Line({ 260, 0 }, { 260, 440 }), solidBrush);
		render.DrawLine(Line({ 460, 0 }, { 460, 440 }), solidBrush);

		render.EndDraw();

		win.DoFrame();
	}

	// 绘制斜等测图
	void DrawOblique(RenderCoreProvider& render)
	{
		for (auto& line : model)
		{
			auto newLine = line * obliqueProj * obliqueWorld;
			render.DrawLine(newLine, solidBrush);
		}
	}

	// 绘制正视图
	void DrawFront(RenderCoreProvider& render)
	{
		for (auto& line : model)
		{
			auto newLine = line * frontProj * frontWorld;
			render.DrawLine(newLine, solidBrush);
		}
	}

	// 绘制俯视图
	void DrawDown(RenderCoreProvider& render)
	{
		for (auto& line : model)
		{
			auto newLine = line * downProj * downWorld;
			render.DrawLine(newLine, solidBrush);
		}
	}

	// 绘制侧视图
	void DrawLeft(RenderCoreProvider& render)
	{
		for (auto& line : model)
		{
			auto newLine = line * leftProj * leftWorld;
			render.DrawLine(newLine, solidBrush);
		}
	}
private:
	Window win;
	Canvas canvas;
	SolidColorBrush solidBrush;
	std::vector<Line3D> model;	// 线段组成的3d模型
	Projector3D<> obliqueProj;	// 斜等测图投影器
	Matrix2D<> obliqueWorld;	// 斜等测图世界矩阵
	Projector3D<> frontProj;	// 正视图投影器
	Matrix2D<> frontWorld;		// 正视图世界矩阵
	Projector3D<> downProj;		// 俯视图投影器
	Matrix2D<> downWorld;		// 俯视图世界矩阵
	Projector3D<> leftProj;		// 侧视图投影器
	Matrix2D<> leftWorld;		// 侧视图世界矩阵
};

void _stdcall MPFMain()
{
	ThreViewApp app;
	app.Run();
}