//
// MPF
// 旋转正方形
//
// (c) SunnyCase 
// 创建日期 2015-05-19

#include "stdafx.h"
#include "../include/visual/Matrix2D.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;
using namespace MPF::Input;

const float PI = 3.1415926f;

class RotateSquareApp : public Application
{
	const float SquareCenterX = 310.f, SquareCenterY = 390.f;
	const float A = 30.f; // 边长的一半
public:
	RotateSquareApp()
		:square({ -A, -A }, { A, A, 1.f, 1.f }), solidBrush(0xFF2277FF)
	{
		win.Width = 640;
		win.Height = 480; 
		win.Title = L"MPF - 旋转正方形";

		button.Text = L"开始动画";
		button.MouseLeftButtonUp += [=](MouseEventArgs&)
		{
			// 开始动画
			animate = true;
		};
		canvas.SetPosition(button, { 20.f, 20.f });
		canvas.AddChildren(button);
		win.Content = &canvas;

		win.Show();
	}

	virtual void OnFrame() override
	{
		// 先旋转再平移
		auto mat = Matrix2D<>::MakeRotate(rotate) * Matrix2D<>::MakeTranslate(SquareCenterX, SquareCenterY);
		auto& render = win.GetRenderCoreProvider();
		render.BeginDraw();
		render.Clear(0xFFFFFFFF);
		render.DrawQuad(square, solidBrush, mat);
		render.EndDraw();

		// 如果开始动画则增加旋转角度
		if (animate)
			rotate += PI / 64;

		win.DoFrame();
	}
private:
	Window win;
	Button button;
	Canvas canvas;
	bool animate = false;	// 是否开始动画
	SolidColorBrush solidBrush;
	Quad square;
	float rotate = 0.f;	// 旋转角度
};

//void _stdcall MPFMain()
//{
//	RotateSquareApp app;
//	app.Run();
//}