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
	auto size = font->MeasureText(L"Hello Everyone!");
	auto textBlock = std::make_shared<TextBlock>();
	textBlock->Font = font;
	textBlock->Text = std::make_shared<String>(L"帝球とchuは本当にばかです。");
	win->Content = textBlock;
	win->Show();
	win->DoFrame();
	//textBlock->Update()

	app->Run();
	
	/*auto window = std::make_shared<NativeWindow>();
	window->Create();
	window->SetTitle(std::make_shared<String>(L"Hello MPF Window."));
	window->SetWidth(800);
	window->SetHeight(600);
	window->Show();

	auto render = window->CreateRenderCoreProvider(RenderCoreProviders::GDI);
	SolidColorBrush solidBrush(0xFF00FF00);
	LinearGradientBrush linearBrush(0xFF00FF00, 0xFFFF00FF);

	render->BeginDraw();
	render->FillTriangle(Triangle(Point(100, 100), Point(50, 300, .5f, .5f),
		Point(300, 50, 1.f, 1.f)), linearBrush);
	render->DrawTriangle(Triangle(Point(100, 100), Point(50, 300, .5f, .5f), 
		Point(300, 50, 1.f, 1.f)), linearBrush);
	render->EndDraw();
	render->Present();*/

}