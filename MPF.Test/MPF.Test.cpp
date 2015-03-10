// MPF.Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;
using namespace MPF::Input;
using namespace MPF::IO;
using namespace MPF::Media;

void _stdcall MPFMain()
{
	auto& app = Application::GetCurrent();
	app.UncaughtException += [&](bool& isHandled)
	{
		MessageBox(L"Hello MPF", L"发生异常！", MessageBoxIcons::Error);
	};

	Window win;
	win.Title = L"Hello MPF Window.";
	win.Width = 800;
	win.Height = 600;

	LinearGradientBrush linearBrush(0xFF00FF00, 0xFFFF0000);
	ImageSource imageSource(L"untitled.bmp");
	ImageBrush imageBrush(imageSource);
	win.Background = &imageBrush;

	TextBlock textBlock1(L"帝球とchuは本当にばかです。");
	Canvas::SetPosition(textBlock1, { 50.f, 50.f });

	TextBlock textBlock2(L"The quick fox jumps");
	SolidColorBrush soldBrush(0xFF2277FF);
	textBlock2.Foreground = &linearBrush;

	Border border1;
	border1.BorderBrush = &linearBrush;
	border1.Content = &textBlock2;
	border1.Padding = 10.f;
	border1.BorderThickness = 1.f;
	Canvas::SetPosition(border1, { 50.f, 80.f });

	Button button1;
	button1.BorderBrush = &linearBrush;
	button1.Text = L"我是按钮";
	button1.Padding = 10.f;
	button1.BorderThickness = 1.f;
	button1.Background = &imageBrush;
	Canvas::SetPosition(button1, { 50.f, 150.f });

	Canvas canvas;
	canvas.AddChildren(textBlock1, border1, button1);
	win.Content = &canvas;
	win.Show();
	win.DoFrame();

	button1.MouseLeftButtonUp += [&](MouseEventArgs& e)
	{
		std::wcout << L"Button1 MouseLeftButton Up" << std::endl;
		MessageBox(L"Hello MPF", L"Button1 MouseLeftButton Up", MessageBoxIcons::Information);
	};

	app.Run();
}