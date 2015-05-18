// MPF.Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "../include/visual/Matrix2D.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;
using namespace MPF::Input;
using namespace MPF::IO;
using namespace MPF::Media;

const float PI = 3.1415926f;

class App : public Application
{
public:
	App()
		:linearBrush(0xFF00FF00, 0xFFFF0000), imageSource(L"untitled.bmp"),
		imageBrush(imageSource), textBlock1(L"帝球とchuは本当にばかです。"),
		textBlock2(L"The quick fox jumps"), solidBrush(0xFF2277FF)
	{
		UncaughtException += [&](bool& isHandled)
		{
			MessageBox(L"Hello MPF", L"发生异常！", MessageBoxIcons::Error);
		};

		InitializeComponent();
	}

	void InitializeComponent()
	{
		win.Title = L"Hello MPF Window.";
		win.Width = 800;
		win.Height = 600;

		Canvas::SetPosition(textBlock1, { 50.f, 50.f });

		textBlock2.Foreground = &linearBrush;

		border1.BorderBrush = &linearBrush;
		border1.Content = &textBlock2;
		border1.Padding = 10.f;
		border1.BorderThickness = 1.f;
		Canvas::SetPosition(border1, { 50.f, 80.f });

		button1.Text = L"我是按钮";
		button1.Padding = 10.f;
		button1.BorderThickness = 1.f;
		Canvas::SetPosition(button1, { 50.f, 150.f });
		/*button1.MouseLeftButtonUp += [&](MouseEventArgs& e)
		{
			std::wcout << L"Button1 MouseLeftButton Up" << std::endl;
			MessageBox(L"Hello MPF", L"Button1 MouseLeftButton Up", MessageBoxIcons::Information);
		};*/

		canvas.AddChildren(textBlock1, border1, button1);
		
		win.Background = &imageBrush;
		win.Content = &canvas;
		win.Show();
	}

	virtual void OnFrame() override
	{
		auto mat = Matrix2D<>::MakeTranslate(-5, -4) * Matrix2D<>::MakeRotate(PI / 4) *
			Matrix2D<>::MakeTranslate(5, 4);
		auto v = { mat * Vector2D<>(4, 1),
			mat * Vector2D<>(7, 3), mat * Vector2D<>(7, 7), mat * Vector2D<>(1, 4)
		};
		//win.DoFrame();

		Triangle tri({ 100.f, 10.f, 0.5f }, { 10.f, 200.f, 0.f, 1.f }, { 200.f, 150.f, 1.f, 1.f });
		auto& renderer = win.GetRenderCoreProvider();

		renderer.BeginDraw();
		renderer.Clear(0xFFFFFFFF);
		renderer.FillTriangle(tri, linearBrush);
		renderer.DrawTriangle(tri, solidBrush);
		renderer.EndDraw();
		renderer.Present();
	}
private:
	Window win;
	Canvas canvas;
	LinearGradientBrush linearBrush;
	SolidColorBrush solidBrush;
	ImageSource imageSource;
	ImageBrush imageBrush;
	TextBlock textBlock1, textBlock2;
	Border border1;
	Button button1;
};

//void _stdcall MPFMain()
//{
//	{
//		App app;
//		app.Run();
//	}
//}