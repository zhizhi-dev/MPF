#include "stdafx.h"
#include "../include/Application.h"
#include <iostream>

using namespace MPF;

DEFINE_TYPE(Application, MPF::Application)
//当前 Application
Application Application::currentApp;

Application::Application() noexcept
{
}

Application& Application::GetCurrent() noexcept
{
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

String Application::GetCommandLines() const
{
	return GetCommandLine();
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

void Application::CreateApplication(MPFMainHandler handler)
{
	currentApp.Run(handler);
}

int _stdcall MPFStartup(MPFMainHandler handler)
{
	Application::CreateApplication(handler);
	return 0;
}

int _stdcall MPFConsoleStartup(MPFMainHandler handler)
{
	std::locale::global(std::locale(""));
	Application::CreateApplication(handler);
	return 0;
}