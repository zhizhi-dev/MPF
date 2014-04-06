// MPF.Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;
using namespace MPF::Input;

void _stdcall MPFMain()
{
	auto& app = Application::GetCurrent();
	app.UncaughtException += [&](bool& isHandled)
	{
		std::wcout << L"发生异常！" << std::endl;

		system("Pause");
	};

	Window win;
	win.Title = L"Hello MPF Window.";
	win.Width = 800;
	win.Height = 600;
	win.Initialize();

	//TextBlock::FontProperty.SetValue(Font(L"Microsoft YaHei", 40.f));
	LinearGradientBrush linearBrush(0xFF00FF00, 0xFFFF0000);
	//TextBlock::ForegroundProperty.SetValue(&linearBrush);

	TextBlock textBlock1(L"帝球とchuは本当にばかです。");
	Canvas::SetPosition(textBlock1, { 50.f, 50.f });

	TextBlock textBlock2(L"The quick fox jumps");
	SolidColorBrush soldBrush(0xFF2277FF);
	textBlock2.Foreground = &linearBrush;

	Border border1;
	border1.BorderBrush = &linearBrush;
	border1.Content = &textBlock2;
	border1.Padding = 10.f;
	//border1.Background = &linearBrush;
	border1.BorderThickness = 1.f;
	Canvas::SetPosition(border1, { 50.f, 80.f });

	Button button1;
	button1.BorderBrush = &linearBrush;
	button1.Text = L"The quick fox jumps";
	button1.Padding = 10.f;
	button1.BorderThickness = 1.f;
	Canvas::SetPosition(button1, { 50.f, 150.f });

	Canvas canvas;
	canvas.AddChildren({ textBlock1, border1, button1 });
	win.Content = &canvas;
	win.Show();
	win.DoFrame();

	button1.MouseLeftButtonUp += [&](MouseEventArgs& e)
	{
		std::wcout << L"Button1 MouseLeftButton Up" << std::endl;
		auto hit = win.HitTest(e.GetPosition());
	};

	app.Run();
}