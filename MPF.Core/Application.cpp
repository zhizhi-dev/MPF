#include "stdafx.h"
#include "../include/Application.h"
#include <iostream>

using namespace MPF;

DEFINE_TYPE(Application, MPF::Application)
//当前 Application
std::shared_ptr<Application> currentApp = nullptr;

Application::Application()
{
}

std::shared_ptr<Application> Application::GetCurrent() mnoexcept
{
	massert(currentApp != nullptr);

	return currentApp;
}

handle_t Application::GetNativeHandle() const
{
	return (handle_t)GetModuleHandle(nullptr);
}

void Application::OnUncaughtException(bool& isHandled) const
{
	UncaughtException([&](UncaughtExceptionEventHandler handler)
	{
		handler(isHandled);
	});
}

void Application::Run(MPFMainHandler handler) const
{
	massert(handler != nullptr);

	try
	{
		handler();
	}
	catch (...)
	{
		bool handled = false;
		OnUncaughtException(handled);
		//异常未处理
		if (!handled)
		{
			throw;
		}
	}
}

std::shared_ptr<String> Application::GetCommandLines() const
{
	return std::make_shared<String>(GetCommandLine());
}

void Application::Run() const
{
	MSG msg;

	while (GetMessage(&msg, nullptr, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void CreateApplication()
{
	currentApp = std::make_shared<Application>();
}

int _stdcall MPFStartup(MPFMainHandler handler)
{
	CreateApplication();
	currentApp->Run(handler);
	return 0;
}

int _stdcall MPFConsoleStartup(MPFMainHandler handler)
{
	std::locale::global(std::locale(""));
	CreateApplication();
	currentApp->Run(handler);
	return 0;
}