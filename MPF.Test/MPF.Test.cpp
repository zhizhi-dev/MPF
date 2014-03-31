// MPF.Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;

void _stdcall MPFMain()
{
	auto app = Application::GetCurrent();
	app->UncaughtException += UncaughtExceptionEventHandler([&](bool& isHandled)
	{
		std::wcout << L"发生异常！" << std::endl;

		system("Pause");
	});

	auto win = std::make_shared<MPF::UI::Window>();
	win->Title = std::make_shared<String>(L"Hello MPF Window.");
	win->Width = 800;
	win->Height = 600;
	win->Initialize();

	auto font = std::make_shared<Font>(std::make_shared<String>(L"Microsoft YaHei"), 40.f);
	auto textBlock1 = std::make_shared<TextBlock>();
	textBlock1->Font = font;
	textBlock1->Text = std::make_shared<String>(L"帝球とchuは本当にばかです");
	textBlock1->SetValue(Canvas::LeftProperty, 50.f);
	textBlock1->SetValue(Canvas::TopProperty, 50.f);

	auto textBlock2 = std::make_shared<TextBlock>();
	textBlock2->Font = font;
	textBlock2->Text = std::make_shared<String>(L"The quick fox jumps");
	textBlock2->SetValue(Canvas::LeftProperty, 50.f);
	textBlock2->SetValue(Canvas::TopProperty, 150.f);

	auto canvas = std::make_shared<Canvas>();
	canvas->GetChildren().push_back(textBlock1);
	canvas->GetChildren().push_back(textBlock2);
	win->Content = canvas;
	win->Show();
	win->DoFrame();

	app->Run();
}