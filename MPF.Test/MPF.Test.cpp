// MPF.Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;

void _stdcall MPFMain()
{
	auto& app = Application::GetCurrent();
	app.UncaughtException += UncaughtExceptionEventHandler([&](bool& isHandled)
	{
		std::wcout << L"发生异常！" << std::endl;

		system("Pause");
	});

	Window win;
	win.Title = L"Hello MPF Window.";
	win.Width = 800;
	win.Height = 600;
	win.Initialize();

	Font font(L"Microsoft YaHei", 40.f);
	TextBlock textBlock1;
	textBlock1.Font = font;
	textBlock1.Text = L"帝球とchuは本当にばかです。";
	Canvas::SetLeft(textBlock1, 50.f);
	Canvas::SetTop(textBlock1, 50.f);

	TextBlock textBlock2;
	textBlock2.Font = font;
	textBlock2.Text = L"The quick fox jumps";
	Canvas::SetLeft(textBlock2, 50.f);
	Canvas::SetTop(textBlock2, 150.f);

	Canvas canvas;
	canvas.AddChild(textBlock1);
	canvas.AddChild(textBlock2);
	win.Content = &canvas;
	win.Show();
	win.DoFrame();

	app.Run();
}