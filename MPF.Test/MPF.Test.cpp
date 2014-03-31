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

	TextBlock::FontProperty.SetValue(Font(L"Microsoft YaHei", 40.f));

	TextBlock textBlock1(L"帝球とchuは本当にばかです。");
	Canvas::SetPosition(textBlock1, { 50.f, 50.f });

	TextBlock textBlock2(L"The quick fox jumps");
	Canvas::SetPosition(textBlock2, { 50.f, 150.f });

	Canvas canvas;
	canvas.AddChild(textBlock1);
	canvas.AddChild(textBlock2);
	win.Content = &canvas;
	win.Show();
	win.DoFrame();

	app.Run();
}